#pragma once

#include "../FilterRegistryCtrl/FilterRegistryCtrl.h"

using namespace System;

public ref class FilterRegistryWrap {
    FilterRegistryCtrl* ptr_FilterRegistryCtrl;
    bool loaded;

public:
    FilterRegistryWrap();
    ~FilterRegistryWrap();

    VOID WRAP_FilterRegistryDrv_LoadDriver();
    VOID WRAP_FilterRegistryDrv_UnloadDriver();
    VOID WRAP_FilterRegistryDrv_OpenDevice();

    VOID WRAP_FilterRegistryDrv_UpdateConfig();
    VOID WRAP_FilterRegistryDrv_RegisterCallback();
    VOID WRAP_FilterRegistryDrv_UnregisterCallback();
    VOID WRAP_FilterRegistryDrv_GetCallbackVersion();
    VOID WRAP_FilterRegistryDrv_TestCallbacks();

    bool Get_loaded();
};
