#pragma once

#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <devioctl.h>
#include <tchar.h>
#include <strsafe.h>

class FilterNetworkCtrl {
public:
    FilterNetworkCtrl();
    ~FilterNetworkCtrl();

// IOCTL
    VOID RestartAllInstances();
    VOID RestartOneInstance();
    VOID EnumerateAllInstances();
};

