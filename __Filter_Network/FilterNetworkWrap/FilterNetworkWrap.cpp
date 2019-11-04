#include "pch.h"

#include "FilterNetworkWrap.h"

FilterNetworkWrap::FilterNetworkWrap() : ptr_FilterNetworkCtrl(new FilterNetworkCtrl()) {}

FilterNetworkWrap::~FilterNetworkWrap() {
    delete ptr_FilterNetworkCtrl;
}

VOID FilterNetworkWrap::WRAP_FilterNetworkDrv_LoadDriver() { /* not implemented */ }

VOID FilterNetworkWrap::WRAP_FilterNetworkDrv_UnloadDriver() { /* not implemented */ }

VOID FilterNetworkWrap::WRAP_FilterNetworkDrv_OpenDevice() { ptr_FilterNetworkCtrl->FilterNetworkDrv_OpenDevice(); }

VOID FilterNetworkWrap::WRAP_FilterNetworkDrv_UpdateConfig() { ptr_FilterNetworkCtrl->FilterNetworkDrv_UpdateConfig(); }

VOID FilterNetworkWrap::WRAP_FilterNetworkDrv_RestartAllInstances() { ptr_FilterNetworkCtrl->FilterNetworkDrv_RestartAllInstances(); }

VOID FilterNetworkWrap::WRAP_FilterNetworkDrv_RestartOneInstance() { ptr_FilterNetworkCtrl->FilterNetworkDrv_RestartOneInstance(); }

VOID FilterNetworkWrap::WRAP_FilterNetworkDrv_EnumerateAllInstances() { ptr_FilterNetworkCtrl->FilterNetworkDrv_EnumerateAllInstances(); }
