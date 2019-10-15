#include "regctrl.h"

// Handle to the driver
HANDLE g_Driver;

// Handle to the root test key
HKEY g_RootKey;

// Version number for the registry callback
ULONG g_MajorVersion;
ULONG g_MinorVersion;

BOOL GetCallbackVersion();
VOID DoUserModeSamples();

VOID __cdecl
wmain(
    _In_ ULONG argc,
    _In_reads_(argc) LPCWSTR argv[]
    )
{
    BOOL Result;
    UNREFERENCED_PARAMETER(argc);
    UNREFERENCED_PARAMETER(argv);

    Result = UtilLoadDriver(DRIVER_NAME,
                             DRIVER_NAME_WITH_EXT,
                             WIN32_DEVICE_NAME,
                             &g_Driver);

    if (Result != TRUE) {
        ErrorPrint("UtilLoadDriver failed, exiting...");
        exit(1);
    }

    printf("Starting Callback samples...\n");
    
    if (GetCallbackVersion()) {
        InfoPrint("Callback version is %u.%u", g_MajorVersion, g_MinorVersion);
    }
    
    DoUserModeSamples();
    UtilUnloadDriver(g_Driver, NULL, DRIVER_NAME);
}

VOID DoUserModeSamples() 
/*++
    Creates the callback root test key and calls the usermode samples.
--*/
{
    LONG Res;

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
        goto Exit;
    }

    PreNotificationBlockSample();

  Exit:
    
    if (g_RootKey != NULL) {
        RegCloseKey(g_RootKey);
    }
    RegDeleteKey(HKEY_LOCAL_MACHINE, ROOT_KEY_REL_PATH);
    
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