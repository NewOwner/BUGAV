#include "pch.h"
#include "FilterNetworkCtrl.h"

FilterNetworkCtrl::FilterNetworkCtrl() : hDriver(NULL) {

}

FilterNetworkCtrl::~FilterNetworkCtrl() {

}

VOID FilterNetworkCtrl::Ndis_LoadDriver() {
    // Not works
}

VOID FilterNetworkCtrl::Ndis_UnloadDriver() {
    // Not works
}

VOID FilterNetworkCtrl::Ndis_OpenDevice() {
    BOOL ReturnValue = FilterCommonCtrl::UtilOpenDevice((LPTSTR)NDIS_WIN32_DEVICE_NAME, &hDriver);

    if (ReturnValue == FALSE) {
        ErrorPrint("UtilOpenDevice failed");
    }
}

VOID FilterNetworkCtrl::Ndis_UpdateConfig() {
    BOOL Result;
    DWORD BytesReturned;

    Result = DeviceIoControl(hDriver,
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
}

VOID FilterNetworkCtrl::Ndis_RestartAllInstances() {
    BOOL Result;
    DWORD BytesReturned;

    Result = DeviceIoControl(hDriver,
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

VOID FilterNetworkCtrl::Ndis_RestartOneInstance() {
    BOOL Result;
    DWORD BytesReturned = 0;
    UCHAR                      InputBuffer[NDIS_BUF_LEN] = { 0 };
    UCHAR                      OutputBuffer[NDIS_BUF_LEN] = { 0 };
    LPCWSTR instname = L"{D1C4F789-7C48-4C14-B848-6A7362BE9D9A}-{5CBF81BD-5055-47CD-9055-A76B2B4E3697}-0000";

    RtlCopyMemory(InputBuffer, instname, 164);
    Result = DeviceIoControl(hDriver,
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

VOID FilterNetworkCtrl::Ndis_EnumerateAllInstances() {
    BOOL Result;
    DWORD BytesReturned = 0;
    UCHAR                      InputBuffer[NDIS_BUF_LEN] = { 0 };
    UCHAR                      OutputBuffer[NDIS_BUF_LEN] = { 0 };

    Result = DeviceIoControl(hDriver,
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
        (__wchar_t*)(OutputBuffer + sizeof(USHORT)));
}
