#pragma once

#include "../FilterCommonCtrl/FilterCommonCtrl.h"
#include "../FilterFileCtrl/FilterFileCtrl.h"
#include "../FilterNetworkCtrl/FilterNetworkCtrl.h"
#include "../FilterRegistryCtrl/FilterRegistryCtrl.h"

using namespace System;

public ref class FilterCtrlWrapper {
    FilterCommonCtrl* ptr_FilterCommonCtrl;
    FilterFileCtrl* ptr_FilterFileCtrl;
    FilterNetworkCtrl* ptr_FilterNetworkCtrl;
    FilterRegistryCtrl* ptr_FilterRegistryCtrl;

public:
    FilterCtrlWrapper();
    ~FilterCtrlWrapper();
};
