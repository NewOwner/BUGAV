#pragma once

#include "../RtProtectionCtrl/RtProtectionCtrl.h"
#include "../RtProtectionInjectCtrl/RtProtectionInjectCtrl.h"

using namespace System;

public struct PROCINFO {
    int _ParentId;
    int _ProcessId;
    int _Create;
};

public ref class RtProtectionWrap {
    RtProtectionCtrl* ptr_RtProtectionCtrl;
    RtProtectionInjectCtrl* ptr_RtProtectionInjectCtrl;
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

    /////

    VOID WRAP_InjectLib(int pid) {
        PWCHAR dll_to_inject = L"RtProtectionPayloadDll.dll";
        DWORD dll_data = 1000;
        ULONG data_sz = sizeof(DWORD);
        ptr_RtProtectionInjectCtrl->InjectLib((DWORD)pid, dll_to_inject, &dll_data, data_sz);
    }
};
