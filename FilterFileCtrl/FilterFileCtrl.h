#pragma once

#include "../FilterCommonCtrl/FilterCommonCtrl.h"
#include <Fltuser.h>

#define SUCCESS             0
#define USAGE_ERROR         1
#define BUFFER_SIZE         4096

// XXX driver name

#define PASSFLT_DRIVER_NAME             L"NdisLwf"
#define PASSFLT_DRIVER_NAME_WITH_EXT    L"NdisLwf.sys"

#define PASSFLT_NT_DEVICE_NAME          L"\\Device\\NdisLwf"
#define PASSFLT_DOS_DEVICES_LINK_NAME   L"\\DosDevices\\NdisLwf"
#define PASSFLT_WIN32_DEVICE_NAME       L"\\\\.\\NdisLwf"

#define PASSFLT_PORT_NAME                   L"\\PassFltPort"

#define PASSFLT_UPD_CFG_MSG         "updfcfg"

class FilterFileCtrl {
    HANDLE hDriver;
    HANDLE hPort;

public:
    FilterFileCtrl();
    ~FilterFileCtrl();

    VOID Passflt_LoadDriver();
    VOID Passflt_UnloadDriver();
    VOID Passflt_OpenDevice();
    VOID Passflt_UpdateConfig();
    VOID Passflt_ConnectCommunicationPort();
    VOID Passflt_SendMessage(PCHAR msg);
};

