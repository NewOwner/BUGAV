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

    //RestartAllInstances();
    RestartOneInstance();
    //EnumerateAllInstances();
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
        ErrorPrint("RestartAllInstances failed. Error %d", GetLastError());
    }
}

VOID RestartOneInstance() {
    BOOL Result;
    DWORD BytesReturned = 0;
    UCHAR                      InputBuffer[BUF_LEN] = { 0 };
    UCHAR                      OutputBuffer[BUF_LEN] = { 0 };
    LPCWSTR instname = L"{D1C4F789-7C48-4C14-B848-6A7362BE9D9A}-{5CBF81BD-5055-47CD-9055-A76B2B4E3697}-0000";

    RtlCopyMemory(InputBuffer, instname, 164);
    Result = DeviceIoControl(g_Driver,
        IOCTL_FILTER_RESTART_ONE_INSTANCE,
        InputBuffer,
        sizeof(InputBuffer),
        OutputBuffer,
        sizeof(OutputBuffer),
        &BytesReturned,
        NULL);

    if (Result != TRUE) {
        ErrorPrint("EnumerateAllInstances failed. Error %d", GetLastError());
        return;
    }

    //{D1C4F789-7C48-4C14-B848-6A7362BE9D9A}-{5CBF81BD-5055-47CD-9055-A76B2B4E3697}-0000

    wprintf(L"%d, %d, %s\n", BytesReturned,
        ((PFLTUNICODE_STRING)OutputBuffer)->Length,
        (__wchar_t*)(OutputBuffer + sizeof(USHORT)));
}

VOID EnumerateAllInstances() {
    BOOL Result;
    DWORD BytesReturned=0;
    UCHAR                      InputBuffer[BUF_LEN] = { 0 };
    UCHAR                      OutputBuffer[BUF_LEN] = { 0 };

    Result = DeviceIoControl(g_Driver,
        IOCTL_FILTER_ENUMERATE_ALL_INSTANCES,
        InputBuffer,
        sizeof(InputBuffer),
        OutputBuffer,
        sizeof(OutputBuffer),
        &BytesReturned,
        NULL);

    if (Result != TRUE) {
        ErrorPrint("EnumerateAllInstances failed. Error %d", GetLastError());
        return;
    }

    //{D1C4F789-7C48-4C14-B848-6A7362BE9D9A}-{5CBF81BD-5055-47CD-9055-A76B2B4E3697}-0000

    wprintf(L"%d, %d, %s\n", BytesReturned,
        ((PFLTUNICODE_STRING)OutputBuffer)->Length,
        (__wchar_t*)(OutputBuffer+sizeof(USHORT)));
}

