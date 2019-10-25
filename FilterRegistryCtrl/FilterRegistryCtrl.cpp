#include "pch.h"
#include "FilterRegistryCtrl.h"

FilterRegistryCtrl::FilterRegistryCtrl() 
    : 
    hDriver(NULL), 
    g_MajorVersion(0),
    g_MinorVersion(0)
{
    RtlZeroMemory(&RegisterCallbackInput, sizeof(REGISTER_CALLBACK_INPUT));
    RtlZeroMemory(&RegisterCallbackOutput, sizeof(REGISTER_CALLBACK_OUTPUT));
    RtlZeroMemory(&UnRegisterCallbackInput, sizeof(UNREGISTER_CALLBACK_INPUT));
}

FilterRegistryCtrl::~FilterRegistryCtrl() {

}

VOID FilterRegistryCtrl::Reg_LoadDriver() {
    BOOL Result;
    Result = FilterCommonCtrl::UtilLoadDriver((LPTSTR)REG_DRIVER_NAME,
        (LPTSTR)REG_DRIVER_NAME_WITH_EXT,
        (LPTSTR)REG_WIN32_DEVICE_NAME,
        &hDriver);

    if (Result != TRUE) {
        ErrorPrint("UtilLoadDriver failed, exiting...");
    }
}

VOID FilterRegistryCtrl::Reg_UnloadDriver() {
    BOOL Result;
    Result = FilterCommonCtrl::UtilUnloadDriver(hDriver, NULL, (LPTSTR)REG_DRIVER_NAME);
}

VOID FilterRegistryCtrl::Reg_OpenDevice() {
    BOOL ReturnValue;
    ReturnValue = FilterCommonCtrl::UtilOpenDevice((LPTSTR)REG_WIN32_DEVICE_NAME, &hDriver);

    if (ReturnValue == FALSE) {
        ErrorPrint("UtilOpenDevice failed");
    }
}

BOOL FilterRegistryCtrl::Reg_UpdateConfig() {
    BOOL Result;
    DWORD BytesReturned;

    Result = DeviceIoControl(hDriver,
        IOCTL_UPDATE_CONFIG,
        NULL,
        0,
        NULL,
        0,
        &BytesReturned,
        NULL);

    if (Result != TRUE) {
        ErrorPrint("UpdateConfig failed. Error %d", GetLastError());
    }

    return Result;
}

VOID FilterRegistryCtrl::Reg_RegisterCallback() {
    HRESULT hr;
    DWORD BytesReturned;
    BOOL Result;

    RtlZeroMemory(RegisterCallbackInput.Altitude, MAX_ALTITUDE_BUFFER_LENGTH * sizeof(WCHAR));
    hr = StringCbPrintf(RegisterCallbackInput.Altitude,
        MAX_ALTITUDE_BUFFER_LENGTH * sizeof(WCHAR),
        CALLBACK_ALTITUDE);

    if (!SUCCEEDED(hr)) {
        ErrorPrint("Copying altitude string failed. Error %d", hr);
    }

    RegisterCallbackInput.CallbackMode = CALLBACK_MODE_PRE_NOTIFICATION_BLOCK;

    Result = DeviceIoControl(hDriver,
        IOCTL_REGISTER_CALLBACK,
        &RegisterCallbackInput,
        sizeof(REGISTER_CALLBACK_INPUT),
        &RegisterCallbackOutput,
        sizeof(REGISTER_CALLBACK_OUTPUT),
        &BytesReturned,
        NULL);

    if (Result != TRUE) {
        ErrorPrint("RegisterCallback failed. Error %d", GetLastError());
    }
}

VOID FilterRegistryCtrl::Reg_UnregisterCallback() {
    DWORD BytesReturned;
    BOOL Result;

    UnRegisterCallbackInput.Cookie = RegisterCallbackOutput.Cookie;

    Result = DeviceIoControl(hDriver,
        IOCTL_UNREGISTER_CALLBACK,
        &UnRegisterCallbackInput,
        sizeof(UNREGISTER_CALLBACK_INPUT),
        NULL,
        0,
        &BytesReturned,
        NULL);

    if (Result != TRUE) {
        ErrorPrint("UnRegisterCallback failed. Error %d", GetLastError());
    }
}

BOOL FilterRegistryCtrl::Reg_GetCallbackVersion() {
    DWORD BytesReturned = 0;
    BOOL Result;
    GET_CALLBACK_VERSION_OUTPUT Output = { 0 };

    Result = DeviceIoControl(hDriver,
        IOCTL_GET_CALLBACK_VERSION,
        NULL,
        0,
        &Output,
        sizeof(GET_CALLBACK_VERSION_OUTPUT),
        &BytesReturned,
        NULL);

    if (Result != TRUE) {
        ErrorPrint("DeviceIoControl for GET_CALLBACK_VERSION failed, error %d\n", GetLastError());
        return FALSE;
    }

    g_MajorVersion = Output.MajorVersion;
    g_MinorVersion = Output.MinorVersion;

    return TRUE;
}

VOID FilterRegistryCtrl::Reg_TestCallbacks() {
    // Handle to the root test key
    HKEY g_RootKey;
    LONG Res;
    HKEY Key = NULL;
    HKEY NotModifiedKey = NULL;
    DWORD ValueData = 0xDEADBEEF;
    BOOL Success = TRUE;

    // root key

    Res = RegCreateKeyEx(HKEY_LOCAL_MACHINE,
        ROOT_KEY_REL_PATH,
        0,
        NULL,
        0,
        KEY_ALL_ACCESS,
        NULL,
        &g_RootKey,
        NULL);

    if (Res != ERROR_SUCCESS) {
        ErrorPrint("Creating root key failed. Error %d", Res);
    }
    // Create two keys.



    Res = RegCreateKeyEx(g_RootKey,
        NOT_MODIFIED_KEY_NAME,
        0,
        (LPWSTR)L"Regfltr_test_class",
        0,
        KEY_ALL_ACCESS,
        NULL,
        &NotModifiedKey,
        NULL);

    if (Res != ERROR_SUCCESS) {
        ErrorPrint("RegCreateKeyEx returned unexpected error %d", Res);
        Success = FALSE;
    }

    Res = RegCreateKeyEx(g_RootKey,
        KEY_NAME,
        0,
        (LPWSTR)L"Regfltr_test_class",
        0,
        KEY_ALL_ACCESS,
        NULL,
        &Key,
        NULL);

    if (Res != ERROR_ACCESS_DENIED) {
        ErrorPrint("RegCreateKeyEx returned unexpected error %d", Res);
        Success = FALSE;
    }

    // Set two values. 
    Res = RegSetValueEx(g_RootKey,
        NOT_MODIFIED_VALUE_NAME,
        0,
        REG_DWORD,
        (BYTE*)&ValueData,
        sizeof(ValueData));

    if (Res != ERROR_SUCCESS) {
        ErrorPrint("RegSetValueEx return unexpected status %d", Res);
        Success = FALSE;
    }

    Res = RegSetValueEx(g_RootKey,
        VALUE_NAME,
        0,
        REG_DWORD,
        (BYTE*)&ValueData,
        sizeof(ValueData));

    if (Res != ERROR_ACCESS_DENIED) {
        ErrorPrint("RegSetValueEx return unexpected status %d", Res);
        Success = FALSE;
    }

    // Clean up
    if (Key != NULL) {
        RegCloseKey(Key);
    }
    RegDeleteKey(g_RootKey, KEY_NAME);

    if (NotModifiedKey != NULL) {
        RegCloseKey(NotModifiedKey);
    }
    RegDeleteKey(g_RootKey, NOT_MODIFIED_KEY_NAME);

    RegDeleteValue(g_RootKey, NOT_MODIFIED_VALUE_NAME);
    RegDeleteValue(g_RootKey, VALUE_NAME);

    if (Success) {
        InfoPrint("Pre-Notification Block Sample succeeded.");
    } else {
        ErrorPrint("Pre-Notification Block Sample FAILED.");
    }
}
