#pragma once

#include "../FilterFileCtrl/FilterFileCtrl.h"

using namespace System;

public ref class FilterFileWrap {
    FilterFileCtrl* ptr_FilterFileCtrl;

public:
    FilterFileWrap();
    ~FilterFileWrap();

    VOID CLI_Passflt_LoadDriver();
    VOID CLI_Passflt_UnloadDriver();
    VOID CLI_Passflt_OpenDevice();
    
    VOID CLI_Passflt_UpdateConfig();
    VOID CLI_Passflt_ConnectCommunicationPort();
    VOID CLI_Passflt_SendMessage(PCHAR msg);

};
