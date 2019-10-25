#pragma once

#include "../FilterFileCtrl/FilterFileCtrl.h"
#include "../FilterRegistryCtrl/FilterRegistryCtrl.h"
#include "../FilterNetworkCtrl/FilterNetworkCtrl.h"

using namespace System;

public ref class FilterCtrlWrapper {
    FilterFileCtrl* ptr_FilterFileCtrl;
    FilterRegistryCtrl* ptr_FilterRegistryCtrl;
    FilterNetworkCtrl* ptr_FilterNetworkCtrl;

public:
    FilterCtrlWrapper();
    ~FilterCtrlWrapper();

    // FILE
    
    VOID CLI_Passflt_LoadDriver();
    VOID CLI_Passflt_UnloadDriver();
    VOID CLI_Passflt_OpenDevice();
    
    VOID CLI_Passflt_UpdateConfig();
    VOID CLI_Passflt_ConnectCommunicationPort();
    VOID CLI_Passflt_SendMessage(PCHAR msg);

    // REGISTRY

    VOID CLI_Reg_LoadDriver();
    VOID CLI_Reg_UnloadDriver();
    VOID CLI_Reg_OpenDevice();

    VOID CLI_Reg_UpdateConfig();
    VOID CLI_Reg_RegisterCallback();
    VOID CLI_Reg_UnregisterCallback();
    VOID CLI_Reg_GetCallbackVersion();
    VOID CLI_Reg_TestCallbacks();

    // NETWORK

    VOID CLI_Ndis_LoadDriver();
    VOID CLI_Ndis_UnloadDriver();
    VOID CLI_Ndis_OpenDevice();

    VOID CLI_Ndis_UpdateConfig();
    VOID CLI_Ndis_RestartAllInstances();
    VOID CLI_Ndis_RestartOneInstance();
    VOID CLI_Ndis_EnumerateAllInstances();

};
