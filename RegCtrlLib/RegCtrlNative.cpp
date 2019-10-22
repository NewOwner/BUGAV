#include "pch.h"
#include "RegCtrlNative.h"

RegCtrlNative::RegCtrlNative() {}
RegCtrlNative::~RegCtrlNative() {}
int RegCtrlNative::NativeMethod() {
    int a = 7;
    int b = a;
    return b;
}