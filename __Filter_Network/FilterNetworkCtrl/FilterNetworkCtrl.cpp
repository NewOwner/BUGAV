#include "pch.h"
#include "FilterNetworkCtrl.h"

FilterNetworkCtrl::FilterNetworkCtrl() : hDriver(NULL) {}

FilterNetworkCtrl::~FilterNetworkCtrl() {}

BOOL FilterNetworkCtrl::FilterNetworkDrv_LoadDriver() {
    BOOL Result = FALSE;
    return Result;
    // Not implemented
}

BOOL FilterNetworkCtrl::FilterNetworkDrv_UnloadDriver() {
    BOOL Result = FALSE;
    return Result;
    // Not implemented
}

BOOL FilterNetworkCtrl::FilterNetworkDrv_OpenDevice() {
    BOOL Result = DriverCtrl::UtilOpenDevice((LPTSTR)NDIS_WIN32_DEVICE_NAME, &hDriver);

    if (Result == FALSE) {
        ErrorPrint("UtilOpenDevice failed");
    }
    return Result;
}

BOOL FilterNetworkCtrl::FilterNetworkDrv_UpdateConfig() {
    DWORD BytesReturned;
    
    BOOL Result = DeviceIoControl(hDriver,
        IOCTL_FILTER_UPDATE_CONFIG,
        NULL,
        0,
        NULL,
        0,
        &BytesReturned,
        NULL);

    if (Result != TRUE) {
        ErrorPrint("RestartAllInstances failed. Error %d", GetLastError());
    }
    return Result;
}

BOOL FilterNetworkCtrl::FilterNetworkDrv_RestartAllInstances() {
    DWORD BytesReturned;

    BOOL Result = DeviceIoControl(hDriver,
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
    return Result;
}

BOOL FilterNetworkCtrl::FilterNetworkDrv_RestartOneInstance() {
    DWORD BytesReturned = 0;
    UCHAR                      InputBuffer[NDIS_BUF_LEN] = { 0 };
    UCHAR                      OutputBuffer[NDIS_BUF_LEN] = { 0 };
    LPCWSTR instname = L"{D1C4F789-7C48-4C14-B848-6A7362BE9D9A}-{5CBF81BD-5055-47CD-9055-A76B2B4E3697}-0000";

    RtlCopyMemory(InputBuffer, instname, 164);
    BOOL Result =  DeviceIoControl(hDriver,
        IOCTL_FILTER_RESTART_ONE_INSTANCE,
        InputBuffer,
        sizeof(InputBuffer),
        OutputBuffer,
        sizeof(OutputBuffer),
        &BytesReturned,
        NULL);

    if (Result != TRUE) {
        ErrorPrint("EnumerateAllInstances failed. Error %d", GetLastError());
        return Result;
    }

    //{D1C4F789-7C48-4C14-B848-6A7362BE9D9A}-{5CBF81BD-5055-47CD-9055-A76B2B4E3697}-0000

    wprintf(L"%d, %d, %s\n", BytesReturned,
        ((PFLTUNICODE_STRING)OutputBuffer)->Length,
        (__wchar_t*)(OutputBuffer + sizeof(USHORT)));
    return Result;
}

BOOL FilterNetworkCtrl::FilterNetworkDrv_EnumerateAllInstances() {
    DWORD BytesReturned = 0;
    UCHAR                      InputBuffer[NDIS_BUF_LEN] = { 0 };
    UCHAR                      OutputBuffer[NDIS_BUF_LEN] = { 0 };

    BOOL Result = DeviceIoControl(hDriver,
        IOCTL_FILTER_ENUMERATE_ALL_INSTANCES,
        InputBuffer,
        sizeof(InputBuffer),
        OutputBuffer,
        sizeof(OutputBuffer),
        &BytesReturned,
        NULL);

    if (Result != TRUE) {
        ErrorPrint("EnumerateAllInstances failed. Error %d", GetLastError());
        return Result;
    }

    //{D1C4F789-7C48-4C14-B848-6A7362BE9D9A}-{5CBF81BD-5055-47CD-9055-A76B2B4E3697}-0000

    wprintf(L"%d, %d, %s\n", BytesReturned,
        ((PFLTUNICODE_STRING)OutputBuffer)->Length,
        (__wchar_t*)(OutputBuffer + sizeof(USHORT)));

    return Result;
}
