#pragma once

#include <tchar.h>

#include <iostream>
#include <string>
#include <cstring>

#include <easyhook.h>

class InjectCtrl {
public:
    InjectCtrl();
    ~InjectCtrl();

    VOID InjectLib(DWORD pid, PWCHAR dll_to_inject, PVOID dll_data, ULONG data_sz);
};

