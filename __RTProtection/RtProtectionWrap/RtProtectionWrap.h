#pragma once

#include "../RtProtectionCtrl/RtProtectionCtrl.h"

using namespace System;

public struct PROCINFO {
    int _ParentId;
    int _ProcessId;
    int _Create;
};

public ref class RtProtectionWrap {
    RtProtectionCtrl* ptr_RtProtectionCtrl;
    bool loaded;
    int _ParentId;
    int _ProcessId;
    int _Create;

public:
    RtProtectionWrap();
    ~RtProtectionWrap();

    VOID WRAP_RtProtectionDrv_LoadDriver();
    VOID WRAP_RtProtectionDrv_UnloadDriver();
    bool WRAP_RtProtectionDrv_NewProcMon();
    
    bool Get_loaded();
    int Get_ParentId();
    int Get_ProcessId();
    int Get_Create();
};
