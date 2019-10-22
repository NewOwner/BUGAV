#include "pch.h"

#include "FilterCtrlWrapper.h"

FilterCtrlWrapper::FilterCtrlWrapper() 
    : 
    ptr_FilterCommonCtrl(new FilterCommonCtrl()),
    ptr_FilterFileCtrl(new FilterFileCtrl()),
    ptr_FilterNetworkCtrl(new FilterNetworkCtrl()),
    ptr_FilterRegistryCtrl(new FilterRegistryCtrl())
{}

FilterCtrlWrapper::~FilterCtrlWrapper() {
    delete ptr_FilterFileCtrl;
    delete ptr_FilterNetworkCtrl;
    delete ptr_FilterRegistryCtrl;
}
