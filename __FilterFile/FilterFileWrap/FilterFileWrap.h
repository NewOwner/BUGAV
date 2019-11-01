#pragma once

#include "../FilterFileCtrl/FilterFileCtrl.h"

using namespace System;

public ref class FilterFileWrap {
    FilterFileCtrl* ptr_FilterFileCtrl;
    bool loaded;

public:
    FilterFileWrap();
    ~FilterFileWrap();

    VOID WRAP_FilterFileDrv_LoadDriver();
    VOID WRAP_FilterFileDrv_UnloadDriver();
    VOID WRAP_FilterFileDrv_OpenDevice();
    
    VOID WRAP_FilterFileDrv_UpdateConfig();
    VOID WRAP_FilterFileDrv_ConnectCommunicationPort();
    VOID WRAP_FilterFileDrv_SendMessage(PCHAR msg);
    bool Get_loaded();
};
