#include "pch.h"

#include "RT_HookWrapper.h"

RT_HookWrapper::RT_HookWrapper() 
    : 
    ptr_InjectCtrl(new InjectCtrl()) 
{}

RT_HookWrapper::~RT_HookWrapper() {
    delete ptr_InjectCtrl;
}

VOID RT_HookWrapper::CLI_InjectLib(DWORD pid, PWCHAR dll_to_inject, PVOID dll_data, ULONG data_sz) {
    ptr_InjectCtrl->InjectLib(pid, dll_to_inject, dll_data, data_sz);
}
