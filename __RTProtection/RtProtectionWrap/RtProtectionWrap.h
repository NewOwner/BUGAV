#pragma once

#include "../RtProtectionCtrl/RtProtectionCtrl.h"

using namespace System;

public ref class RtProtectionWrap {
    RtProtectionCtrl* ptr_RtProtectionCtrl;
    bool loaded;

public:
    RtProtectionWrap();
    ~RtProtectionWrap();

    VOID WRAP_RtProtectionDrv_LoadDriver();
    VOID WRAP_RtProtectionDrv_UnloadDriver();
    VOID WRAP_RtProtectionDrv_NewProcMon();
    bool Get_loaded();
};
