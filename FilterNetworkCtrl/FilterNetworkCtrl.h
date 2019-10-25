#pragma once

#include "../FilterCommonCtrl/FilterCommonCtrl.h"

#define NDIS_DRIVER_NAME             L"NdisLwf"
#define NDIS_DRIVER_NAME_WITH_EXT    L"NdisLwf.sys"

#define NDIS_NT_DEVICE_NAME          L"\\Device\\NdisLwf"
#define NDIS_DOS_DEVICES_LINK_NAME   L"\\DosDevices\\NdisLwf"
#define NDIS_WIN32_DEVICE_NAME       L"\\\\.\\NdisLwf"

#define IOCTL_FILTER_RESTART_ALL               ( ((0x00000017)<<16)|((0)<<14)|((0)<<2)|(0) )
#define IOCTL_FILTER_RESTART_ONE_INSTANCE      ( ((0x00000017)<<16)|((0)<<14)|((1)<<2)|(0) )
#define IOCTL_FILTER_ENUMERATE_ALL_INSTANCES   ( ((0x00000017)<<16)|((0)<<14)|((2)<<2)|(0) )
#define IOCTL_FILTER_UPDATE_CONFIG             ( ((0x00000017)<<16)|((0)<<14)|((14)<<2)|(0) )

#define NDIS_BUF_LEN 512

#pragma pack(push, 1)
typedef struct _FLTUNICODE_STRING {
    USHORT Length;
    LPWSTR Buffer;
} FLTUNICODE_STRING, * PFLTUNICODE_STRING;
#pragma pack(pop)

class FilterNetworkCtrl {
    HANDLE hDriver;

public:
    FilterNetworkCtrl();
    ~FilterNetworkCtrl();

    VOID Ndis_LoadDriver();
    VOID Ndis_UnloadDriver();

    VOID Ndis_OpenDevice();
// IOCTL
    VOID Ndis_UpdateConfig();
    VOID Ndis_RestartAllInstances();
    VOID Ndis_RestartOneInstance();
    VOID Ndis_EnumerateAllInstances();
};

