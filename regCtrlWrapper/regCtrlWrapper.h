#pragma once

#include "../RegCtrlLib/RegCtrlNative.h"

using namespace System;

public ref class WrapRegCtrl {
  RegCtrlNative* RegCtrlNativePtr;
public:
    WrapRegCtrl()  : RegCtrlNativePtr(new RegCtrlNative()) {}
    ~WrapRegCtrl()  { delete RegCtrlNativePtr; }

    void ManagedMethod() {
        int ret = RegCtrlNativePtr->NativeMethod();
    }
};
