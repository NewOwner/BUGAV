#pragma once

#include "../WebApcInjldrCtrl/WebApcInjldrCtrl.h"

using namespace System;

public ref class WebApcInjldrWrap {
    WebApcInjldrCtrl* ptr_WebApcInjldrCtrl;

public:
    WebApcInjldrWrap();
    ~WebApcInjldrWrap();

    bool WRAP_Load();
    bool WRAP_StartSession();
    bool WRAP_StopSession();
    bool Get_loaded();
};
