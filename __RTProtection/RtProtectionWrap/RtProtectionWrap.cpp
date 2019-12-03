#include "pch.h"

#include "RtProtectionWrap.h"

RtProtectionWrap::RtProtectionWrap() 
    : 
    ptr_RtProtectionCtrl(new RtProtectionCtrl()),
    ptr_RtProtectionInjectCtrl(new RtProtectionInjectCtrl())
{}

RtProtectionWrap::~RtProtectionWrap() { delete ptr_RtProtectionCtrl; }

VOID RtProtectionWrap::WRAP_RtProtectionDrv_LoadDriver() { loaded = ptr_RtProtectionCtrl->RtProtectionDrv_LoadDriver(); }

VOID RtProtectionWrap::WRAP_RtProtectionDrv_UnloadDriver() { 
    bool res = ptr_RtProtectionCtrl->RtProtectionDrv_UnloadDriver();
    if (res) {
        loaded = false;
    }
}

bool RtProtectionWrap::WRAP_RtProtectionDrv_NewProcMon() {
    NEWPROC_INFO proc_info = { 0 };
    bool res = ptr_RtProtectionCtrl->RtProtectionDrv_NewProcMon(&proc_info);
    if (res) {
        _ParentId = (int)proc_info.ParentId;
        _ProcessId= (int)proc_info.ProcessId;
        _Create= proc_info.Create;
    }
    return res;
}

bool RtProtectionWrap::Get_loaded() { return loaded; }

int RtProtectionWrap::Get_ParentId() { return _ParentId; }

int RtProtectionWrap::Get_ProcessId() { return _ProcessId; }

int RtProtectionWrap::Get_Create() { return _Create; }

VOID RtProtectionWrap::WRAP_InjectBasicLib(int pid) {
    PWCHAR dll_to_inject = L"RtProtectionPayloadDll.dll";
    DWORD dll_data = pid;
    ULONG data_sz = sizeof(DWORD);
    ptr_RtProtectionInjectCtrl->InjectLib((DWORD)pid, dll_to_inject, &dll_data, data_sz);
}

VOID RtProtectionWrap::WRAP_InjectWinhttpLib(int pid) {
    PWCHAR dll_to_inject = L"RtProtectionWinhttpDll.dll";
    DWORD dll_data = pid;
    ULONG data_sz = sizeof(DWORD);
    ptr_RtProtectionInjectCtrl->InjectLib((DWORD)pid, dll_to_inject, &dll_data, data_sz);
}

VOID RtProtectionWrap::WRAP_InjectWininetLib(int pid) {
    PWCHAR dll_to_inject = L"RtProtectionWininetDll.dll";
    DWORD dll_data = pid;
    ULONG data_sz = sizeof(DWORD);
    ptr_RtProtectionInjectCtrl->InjectLib((DWORD)pid, dll_to_inject, &dll_data, data_sz);
}

VOID RtProtectionWrap::WRAP_InjectWs2_32Lib(int pid) {
    PWCHAR dll_to_inject = L"RtProtectionWs2_32Dll.dll";
    DWORD dll_data = pid;
    ULONG data_sz = sizeof(DWORD);
    ptr_RtProtectionInjectCtrl->InjectLib((DWORD)pid, dll_to_inject, &dll_data, data_sz);
}

VOID RtProtectionWrap::WRAP_InjectConsoleLib(int pid) {
    PWCHAR dll_to_inject = L"RtProtectionConsoleDll.dll";
    DWORD dll_data = pid;
    ULONG data_sz = sizeof(DWORD);
    ptr_RtProtectionInjectCtrl->InjectLib((DWORD)pid, dll_to_inject, &dll_data, data_sz);
}

