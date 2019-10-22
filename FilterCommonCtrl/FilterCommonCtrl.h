#pragma once

#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <devioctl.h>
#include <tchar.h>
#include <strsafe.h>

class FilterCommonCtrl {
public:
    FilterCommonCtrl();
    ~FilterCommonCtrl();

    // DRIVER
    BOOL UtilLoadDriver(
            _In_ LPTSTR szDriverNameNoExt,
            _In_ LPTSTR szDriverNameWithExt,
            _In_ LPTSTR szWin32DeviceName,
            _Out_ HANDLE* pDriver
        );

    BOOL UtilUnloadDriver(
            _In_ HANDLE hDriver,
            _In_opt_ SC_HANDLE hSCM,
            _In_ LPTSTR szDriverNameNoExt
        );

    // UTIL
    BOOL UtilCreateService(
            _In_ SC_HANDLE hSCM,
            _In_ LPTSTR szDriverName,
            _In_ LPTSTR szDriverPath
        );

    BOOL UtilStartService(
            _In_ SC_HANDLE hSCM,
            _In_ LPTSTR szDriverName
        );

    BOOL UtilStopService(
            _In_ SC_HANDLE hSCM,
            _In_ LPTSTR szDriverName
        );

    BOOL UtilDeleteService(
            _In_ SC_HANDLE hSCM,
            _In_ LPTSTR szDriverName
        );

    BOOL UtilOpenDevice(
            _In_ LPTSTR szWin32DeviceName,
            _Out_ HANDLE* phDevice);

    BOOL UtilGetServiceState(
            _In_ SC_HANDLE hService,
            _Out_ DWORD* State);

    BOOL UtilWaitForServiceState(
            _In_ SC_HANDLE hService,
            _In_ DWORD State);

};

