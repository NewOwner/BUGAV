#pragma once

#include "../../__LIBS/DriverCtrl/DriverCtrl.h"

#define NDIS_DRIVER_NAME             L"FilterNetworkDrv"
#define NDIS_DRIVER_NAME_WITH_EXT    L"FilterNetworkDrv.sys"

#define NDIS_NT_DEVICE_NAME          L"\\Device\\FilterNetworkDrv"
#define NDIS_DOS_DEVICES_LINK_NAME   L"\\DosDevices\\FilterNetworkDrv"
#define NDIS_WIN32_DEVICE_NAME       L"\\\\.\\FilterNetworkDrv"

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

    BOOL FilterNetworkDrv_LoadDriver();
    BOOL FilterNetworkDrv_UnloadDriver();

    BOOL FilterNetworkDrv_OpenDevice();

    BOOL FilterNetworkDrv_UpdateConfig();
    BOOL FilterNetworkDrv_RestartAllInstances();
    BOOL FilterNetworkDrv_RestartOneInstance();
    BOOL FilterNetworkDrv_EnumerateAllInstances();
};

