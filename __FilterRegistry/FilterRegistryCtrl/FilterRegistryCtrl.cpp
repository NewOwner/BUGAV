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

FilterRegistryCtrl::~FilterRegistryCtrl() {}

BOOL FilterRegistryCtrl::FilterRegistryDrv_LoadDriver() {
    BOOL Result = DriverCtrl::UtilLoadDriver((LPTSTR)REG_DRIVER_NAME,
        (LPTSTR)REG_DRIVER_NAME_WITH_EXT,
        (LPTSTR)REG_WIN32_DEVICE_NAME,
        &hDriver);

    if (Result != TRUE) {
        ErrorPrint("UtilLoadDriver failed, exiting...");
    }
    return Result;
}

BOOL FilterRegistryCtrl::FilterRegistryDrv_UnloadDriver() {
    BOOL Result = DriverCtrl::UtilUnloadDriver(hDriver, NULL, (LPTSTR)REG_DRIVER_NAME);
    return Result;
}

BOOL FilterRegistryCtrl::FilterRegistryDrv_OpenDevice() {
    BOOL Result = DriverCtrl::UtilOpenDevice((LPTSTR)REG_WIN32_DEVICE_NAME, &hDriver);

    if (Result == FALSE) {
        ErrorPrint("UtilOpenDevice failed");
    }
    return Result;
}

BOOL FilterRegistryCtrl::FilterRegistryDrv_UpdateConfig() {
    DWORD BytesReturned;

    BOOL Result = DeviceIoControl(hDriver,
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

BOOL FilterRegistryCtrl::FilterRegistryDrv_RegisterCallback() {
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

    return Result;
}

BOOL FilterRegistryCtrl::FilterRegistryDrv_UnregisterCallback() {
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

    return Result;
}

BOOL FilterRegistryCtrl::FilterRegistryDrv_GetCallbackVersion() {
    DWORD BytesReturned = 0;
    GET_CALLBACK_VERSION_OUTPUT Output = { 0 };

    BOOL Result = DeviceIoControl(hDriver,
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

VOID FilterRegistryCtrl::FilterRegistryDrv_TestCallbacks() {
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

    Res = RegCreateKeyEx(g_RootKey,
        NOT_MODIFIED_KEY_NAME,
        0,
        (LPWSTR)L"Regfltr_test_class",
        0,
        KEY_ALL_ACCESS,
        NULL,
        &NotModifiedKey,
        NULL);

    Res = RegCreateKeyEx(g_RootKey,
        KEY_NAME,
        0,
        (LPWSTR)L"Regfltr_test_class",
        0,
        KEY_ALL_ACCESS,
        NULL,
        &Key,
        NULL);

    Res = RegSetValueEx(g_RootKey,
        NOT_MODIFIED_VALUE_NAME,
        0,
        REG_DWORD,
        (BYTE*)&ValueData,
        sizeof(ValueData));

    Res = RegSetValueEx(g_RootKey,
        VALUE_NAME,
        0,
        REG_DWORD,
        (BYTE*)&ValueData,
        sizeof(ValueData));

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
}
