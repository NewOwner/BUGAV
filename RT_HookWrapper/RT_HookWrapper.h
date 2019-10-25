#pragma once

#include "../InjectorLib/InjectCtrl.h"

#include <easyhook.h>

using namespace System;

public ref class RT_HookWrapper {
    InjectCtrl* ptr_InjectCtrl;
    
public:
    RT_HookWrapper();
    ~RT_HookWrapper();

    VOID CLI_InjectLib(DWORD pid, PWCHAR dll_to_inject, PVOID dll_data, ULONG data_sz);
};
