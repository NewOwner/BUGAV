#pragma once

#include "../../__LIBS/DriverCtrl/DriverCtrl.h"
#include <Fltuser.h>

#define SUCCESS             0
#define USAGE_ERROR         1
#define BUFFER_SIZE         4096

// XXX driver name

#define FILTERFILEDRV_DRIVER_NAME             L"FilterFileDrv"
#define FILTERFILEDRV_DRIVER_NAME_WITH_EXT    L"FilterFileDrv.sys"

#define FILTERFILEDRV_NT_DEVICE_NAME          L"\\Device\\FilterFileDrv"
#define FILTERFILEDRV_DOS_DEVICES_LINK_NAME   L"\\DosDevices\\FilterFileDrv"
#define FILTERFILEDRV_WIN32_DEVICE_NAME       L"\\\\.\\FilterFileDrv"

#define PASSFLT_PORT_NAME                   L"\\FilterFileDrvPort"

#define PASSFLT_UPD_CFG_MSG         "updfcfg"

class FilterFileCtrl {
    HANDLE hDriver;
    HANDLE hPort;

public:
    FilterFileCtrl();
    ~FilterFileCtrl();

    VOID FilterFileDrv_LoadDriver();
    VOID FilterFileDrv_UnloadDriver();
    VOID FilterFileDrv_OpenDevice();
    VOID FilterFileDrv_UpdateConfig();
    VOID FilterFileDrv_ConnectCommunicationPort();
    VOID FilterFileDrv_SendMessage(PCHAR msg);
};

