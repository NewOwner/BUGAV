#include "pch.h"

#include "WebApcInjldrWrap.h"

WebApcInjldrWrap::WebApcInjldrWrap() : ptr_WebApcInjldrCtrl(new WebApcInjldrCtrl()) {}
WebApcInjldrWrap::~WebApcInjldrWrap() { delete ptr_WebApcInjldrCtrl; }

bool WebApcInjldrWrap::WRAP_Load() {
    return ptr_WebApcInjldrCtrl->Load();
}

bool WebApcInjldrWrap::WRAP_StartSession() {
    return ptr_WebApcInjldrCtrl->StartSession();
}

bool WebApcInjldrWrap::WRAP_StopSession() {
    return ptr_WebApcInjldrCtrl->StopSession();
}

bool WebApcInjldrWrap::Get_loaded() {
    return ptr_WebApcInjldrCtrl->installed;
}
