#include "pch.h"

#include "FilterCtrlWrapper.h"

FilterCtrlWrapper::FilterCtrlWrapper() 
    : 
    ptr_FilterFileCtrl(new FilterFileCtrl()),
    ptr_FilterRegistryCtrl(new FilterRegistryCtrl()),
    ptr_FilterNetworkCtrl(new FilterNetworkCtrl())
{}

FilterCtrlWrapper::~FilterCtrlWrapper() {
    delete ptr_FilterFileCtrl;
    delete ptr_FilterRegistryCtrl;
    delete ptr_FilterNetworkCtrl;
}

// FILE

VOID FilterCtrlWrapper::CLI_Passflt_LoadDriver() { ptr_FilterFileCtrl->Passflt_LoadDriver(); }
VOID FilterCtrlWrapper::CLI_Passflt_UnloadDriver() { ptr_FilterFileCtrl->Passflt_UnloadDriver(); }
VOID FilterCtrlWrapper::CLI_Passflt_OpenDevice() { ptr_FilterFileCtrl->Passflt_OpenDevice(); }

VOID FilterCtrlWrapper::CLI_Passflt_UpdateConfig() { ptr_FilterFileCtrl->Passflt_UpdateConfig(); }
VOID FilterCtrlWrapper::CLI_Passflt_ConnectCommunicationPort() { ptr_FilterFileCtrl->Passflt_ConnectCommunicationPort(); }
VOID FilterCtrlWrapper::CLI_Passflt_SendMessage(PCHAR msg) { ptr_FilterFileCtrl->Passflt_SendMessage(msg); }

// REGISTRY

VOID FilterCtrlWrapper::CLI_Reg_LoadDriver() { ptr_FilterRegistryCtrl->Reg_LoadDriver(); }
VOID FilterCtrlWrapper::CLI_Reg_UnloadDriver() { ptr_FilterRegistryCtrl->Reg_UnloadDriver(); }
VOID FilterCtrlWrapper::CLI_Reg_OpenDevice() { ptr_FilterRegistryCtrl->Reg_OpenDevice(); }

VOID FilterCtrlWrapper::CLI_Reg_UpdateConfig() { ptr_FilterRegistryCtrl->Reg_UpdateConfig(); }
VOID FilterCtrlWrapper::CLI_Reg_RegisterCallback() { ptr_FilterRegistryCtrl->Reg_RegisterCallback(); }
VOID FilterCtrlWrapper::CLI_Reg_UnregisterCallback() { ptr_FilterRegistryCtrl->Reg_UnregisterCallback(); }
VOID FilterCtrlWrapper::CLI_Reg_GetCallbackVersion() { ptr_FilterRegistryCtrl->Reg_GetCallbackVersion(); }
VOID FilterCtrlWrapper::CLI_Reg_TestCallbacks() { ptr_FilterRegistryCtrl->Reg_TestCallbacks(); }

// NETWORK

VOID FilterCtrlWrapper::CLI_Ndis_LoadDriver() { ptr_FilterNetworkCtrl->Ndis_LoadDriver(); }
VOID FilterCtrlWrapper::CLI_Ndis_UnloadDriver() { ptr_FilterNetworkCtrl->Ndis_UnloadDriver(); }
VOID FilterCtrlWrapper::CLI_Ndis_OpenDevice() { ptr_FilterNetworkCtrl->Ndis_OpenDevice(); }

VOID FilterCtrlWrapper::CLI_Ndis_UpdateConfig() { ptr_FilterNetworkCtrl->Ndis_UpdateConfig(); }
VOID FilterCtrlWrapper::CLI_Ndis_RestartAllInstances() { ptr_FilterNetworkCtrl->Ndis_RestartAllInstances(); }
VOID FilterCtrlWrapper::CLI_Ndis_RestartOneInstance() { ptr_FilterNetworkCtrl->Ndis_RestartOneInstance(); }
VOID FilterCtrlWrapper::CLI_Ndis_EnumerateAllInstances() { ptr_FilterNetworkCtrl->Ndis_EnumerateAllInstances(); }
