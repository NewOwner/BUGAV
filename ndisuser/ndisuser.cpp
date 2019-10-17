#pragma warning(disable:4201)  //nonstandard extension used : nameless struct/union
#include "ndisuser.h"

HANDLE g_Driver;

VOID __cdecl
wmain(
    _In_ ULONG argc,
    _In_reads_(argc) LPCWSTR argv[]
    )
{
    UNREFERENCED_PARAMETER(argc);
    UNREFERENCED_PARAMETER(argv);

    BOOL ReturnValue = FALSE;
    HANDLE hDriver = NULL;

    ReturnValue = UtilOpenDevice(WIN32_DEVICE_NAME, &hDriver);

    if (ReturnValue == FALSE) {
        ErrorPrint("UtilOpenDevice failed");
    }

    g_Driver = hDriver;

    RestartAllInstances();
}

VOID RestartAllInstances() {
    BOOL Result;
    DWORD BytesReturned;

    Result = DeviceIoControl(g_Driver,
        IOCTL_FILTER_RESTART_ALL,
        NULL,
        0,
        NULL,
        0,
        &BytesReturned,
        NULL);
    
    if (Result != TRUE) {
        ErrorPrint("RegisterCallback failed. Error %d", GetLastError());
    }
}