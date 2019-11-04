#pragma once

#include "../FilterNetworkCtrl/FilterNetworkCtrl.h"

using namespace System;

public ref class FilterNetworkWrap {
    FilterNetworkCtrl* ptr_FilterNetworkCtrl;
    bool loaded;

public:
    FilterNetworkWrap();
    ~FilterNetworkWrap();

    VOID WRAP_FilterNetworkDrv_LoadDriver();
    VOID WRAP_FilterNetworkDrv_UnloadDriver();

    VOID WRAP_FilterNetworkDrv_OpenDevice();

    VOID WRAP_FilterNetworkDrv_UpdateConfig();
    VOID WRAP_FilterNetworkDrv_RestartAllInstances();
    VOID WRAP_FilterNetworkDrv_RestartOneInstance();
    VOID WRAP_FilterNetworkDrv_EnumerateAllInstances();
};
