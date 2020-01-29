#pragma once

#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <devioctl.h>
#include <tchar.h>
#include <strsafe.h>

#define ARRAY_LENGTH(array)    (sizeof (array) / sizeof (array[0]))
#define InfoPrint(str, ...)                 \
    printf(##str"\n",                       \
            __VA_ARGS__)

#define ErrorPrint(str, ...)                \
    printf("ERROR: %u: "##str"\n",          \
            __LINE__,                       \
            __VA_ARGS__)

class DriverCtrl {
public:
    DriverCtrl();
    ~DriverCtrl();

    // DRIVER
    static BOOL UtilLoadDriver(_In_ LPTSTR szDriverNameNoExt, _In_ LPTSTR szDriverNameWithExt, _In_ LPTSTR szWin32DeviceName, _Out_ HANDLE* pDriver);

    static BOOL UtilUnloadDriver(_In_ HANDLE hDriver, _In_opt_ SC_HANDLE hSCM, _In_ LPTSTR szDriverNameNoExt);

    // UTIL
    static BOOL UtilCreateService(_In_ SC_HANDLE hSCM, _In_ LPTSTR szDriverName, _In_ LPTSTR szDriverPath);

    static BOOL UtilStartService(_In_ SC_HANDLE hSCM, _In_ LPTSTR szDriverName);

    static BOOL UtilStopService(_In_ SC_HANDLE hSCM, _In_ LPTSTR szDriverName);

    static BOOL UtilDeleteService(_In_ SC_HANDLE hSCM, _In_ LPTSTR szDriverName);

    static BOOL UtilOpenDevice(_In_ LPTSTR szWin32DeviceName, _Out_ HANDLE* phDevice);

    static BOOL UtilGetServiceState(_In_ SC_HANDLE hService, _Out_ DWORD* State);

    static BOOL UtilWaitForServiceState(_In_ SC_HANDLE hService, _In_ DWORD State);

};

