#include "regctrl.h"

// Handle to the driver
HANDLE g_Driver;

REGISTER_CALLBACK_INPUT RegisterCallbackInput = { 0 };
REGISTER_CALLBACK_OUTPUT RegisterCallbackOutput = { 0 };
UNREGISTER_CALLBACK_INPUT UnRegisterCallbackInput = { 0 };

// Handle to the root test key
HKEY g_RootKey;

// Version number for the registry callback
ULONG g_MajorVersion;
ULONG g_MinorVersion;

BOOL GetCallbackVersion();

VOID __cdecl
wmain(
    _In_ ULONG argc,
    _In_reads_(argc) LPCWSTR argv[]
    )
{
    UNREFERENCED_PARAMETER(argc);
    UNREFERENCED_PARAMETER(argv);
    BOOL Result;
    //if (argc < 2) { return; }
    printf("load driver...\n");
    Result = UtilLoadDriver(DRIVER_NAME,
        DRIVER_NAME_WITH_EXT,
        WIN32_DEVICE_NAME,
        &g_Driver);

    if (Result != TRUE) {
        ErrorPrint("UtilLoadDriver failed, exiting...");
        exit(1);
    }

    if (GetCallbackVersion()) {
            InfoPrint("Callback version is %u.%u", g_MajorVersion, g_MinorVersion);
        }

    RegisterCallback();
    TestCallbacks();
    UnregisterCallback();
    
    getchar();
    UpdateConfig();
    
    RegisterCallback();
    TestCallbacks();
    UnregisterCallback();

    printf("unload driver...\n");
    UtilUnloadDriver(g_Driver, NULL, DRIVER_NAME);

    //if (wcscmp(L"unload", argv[1]) == 0) {
    //    printf("unload driver...\n");
    //    UtilUnloadDriver(g_Driver, NULL, DRIVER_NAME);
    //
    //} else if (wcscmp(L"regcall", argv[1]) == 0) {
    //    if (GetCallbackVersion()) {
    //        InfoPrint("Callback version is %u.%u", g_MajorVersion, g_MinorVersion);
    //    }
    //    RegisterCallback();
    //
    //} else if (wcscmp(L"unregcall", argv[1]) == 0) {
    //    if (GetCallbackVersion()) {
    //        InfoPrint("Callback version is %u.%u", g_MajorVersion, g_MinorVersion);
    //    }
    //    UnregisterCallback();
    //
    //} else if (wcscmp(L"updcfg", argv[1]) == 0) {
    //    if (GetCallbackVersion()) {
    //        InfoPrint("Callback version is %u.%u", g_MajorVersion, g_MinorVersion);
    //    }
    //    UpdateConfig();
    //}
    //else if (wcscmp(L"test", argv[1]) == 0) {
    //    TestCallbacks();
    //}
}

VOID TestCallbacks() {

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
        L"Regfltr_test_class",
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
        L"Regfltr_test_class",
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

BOOL UpdateConfig() {
    BOOL Result;
    DWORD BytesReturned;

    Result = DeviceIoControl(g_Driver,
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

VOID RegisterCallback() {
    HRESULT hr;
    DWORD BytesReturned;
    BOOL Result;
    BOOL Success = FALSE;

    RtlZeroMemory(RegisterCallbackInput.Altitude, MAX_ALTITUDE_BUFFER_LENGTH * sizeof(WCHAR));
    hr = StringCbPrintf(RegisterCallbackInput.Altitude,
        MAX_ALTITUDE_BUFFER_LENGTH * sizeof(WCHAR),
        CALLBACK_ALTITUDE);

    if (!SUCCEEDED(hr)) {
        ErrorPrint("Copying altitude string failed. Error %d", hr);
    }

    RegisterCallbackInput.CallbackMode = CALLBACK_MODE_PRE_NOTIFICATION_BLOCK;

    Result = DeviceIoControl(g_Driver,
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
    Success = TRUE;

}

VOID UnregisterCallback() {
    DWORD BytesReturned;
    BOOL Result; 
    BOOL Success = FALSE;

    UnRegisterCallbackInput.Cookie = RegisterCallbackOutput.Cookie;

    Result = DeviceIoControl(g_Driver,
        IOCTL_UNREGISTER_CALLBACK,
        &UnRegisterCallbackInput,
        sizeof(UNREGISTER_CALLBACK_INPUT),
        NULL,
        0,
        &BytesReturned,
        NULL);

    if (Result != TRUE) {
        ErrorPrint("UnRegisterCallback failed. Error %d", GetLastError());
        Success = FALSE;
    }
}

BOOL GetCallbackVersion()
/*++
    This routine asks the driver for the registry callback version and
    stores it in the global variables g_MajorVersion and g_MinorVersion.
--*/
{
    DWORD BytesReturned = 0;
    BOOL Result;
    GET_CALLBACK_VERSION_OUTPUT Output = { 0 };

    Result = DeviceIoControl(g_Driver,
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