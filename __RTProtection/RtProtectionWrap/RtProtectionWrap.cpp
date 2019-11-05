#include "pch.h"

#include "RtProtectionWrap.h"

RtProtectionWrap::RtProtectionWrap() : ptr_RtProtectionCtrl(new RtProtectionCtrl()) {}

RtProtectionWrap::~RtProtectionWrap() { delete ptr_RtProtectionCtrl; }

VOID RtProtectionWrap::WRAP_RtProtectionDrv_LoadDriver() { loaded = ptr_RtProtectionCtrl->RtProtectionDrv_LoadDriver(); }

VOID RtProtectionWrap::WRAP_RtProtectionDrv_UnloadDriver() { 
    bool res = ptr_RtProtectionCtrl->RtProtectionDrv_UnloadDriver();
    if (res) {
        loaded = false;
    }
}

VOID RtProtectionWrap::WRAP_RtProtectionDrv_NewProcMon() { ptr_RtProtectionCtrl->RtProtectionDrv_NewProcMon(); }

bool RtProtectionWrap::Get_loaded() { return loaded; }
