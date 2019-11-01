#include "pch.h"

#include "FilterRegistryWrap.h"

FilterRegistryWrap::FilterRegistryWrap() :ptr_FilterRegistryCtrl(new FilterRegistryCtrl) {}

FilterRegistryWrap::~FilterRegistryWrap() { delete ptr_FilterRegistryCtrl; }

VOID FilterRegistryWrap::WRAP_FilterRegistryDrv_LoadDriver() { loaded = ptr_FilterRegistryCtrl->FilterRegistryDrv_LoadDriver(); }

VOID FilterRegistryWrap::WRAP_FilterRegistryDrv_UnloadDriver() { 
    bool res = ptr_FilterRegistryCtrl->FilterRegistryDrv_UnloadDriver(); 
    if (res) { loaded = false; } 
    else { loaded = true; }
}

VOID FilterRegistryWrap::WRAP_FilterRegistryDrv_OpenDevice() { ptr_FilterRegistryCtrl->FilterRegistryDrv_OpenDevice(); }

VOID FilterRegistryWrap::WRAP_FilterRegistryDrv_UpdateConfig() { ptr_FilterRegistryCtrl->FilterRegistryDrv_UpdateConfig(); }

VOID FilterRegistryWrap::WRAP_FilterRegistryDrv_RegisterCallback() { ptr_FilterRegistryCtrl->FilterRegistryDrv_RegisterCallback(); }

VOID FilterRegistryWrap::WRAP_FilterRegistryDrv_UnregisterCallback() { ptr_FilterRegistryCtrl->FilterRegistryDrv_UnregisterCallback(); }

VOID FilterRegistryWrap::WRAP_FilterRegistryDrv_GetCallbackVersion() { ptr_FilterRegistryCtrl->FilterRegistryDrv_GetCallbackVersion(); }

VOID FilterRegistryWrap::WRAP_FilterRegistryDrv_TestCallbacks() { ptr_FilterRegistryCtrl->FilterRegistryDrv_TestCallbacks(); }

bool FilterRegistryWrap::Get_loaded() { return loaded; }
