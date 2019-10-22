#pragma once

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <devioctl.h>
#include <tchar.h>
#include <strsafe.h>

class RegCtrlNative {
public:
    RegCtrlNative();
    ~RegCtrlNative();
    int NativeMethod();
};

