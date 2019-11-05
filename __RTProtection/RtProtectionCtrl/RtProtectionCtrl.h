#pragma once
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#include "../../__LIBS/DriverCtrl/DriverCtrl.h"
#include "../RtProtectionDrv/RtProtectionDrv.h"

BOOLEAN ManageDriver(
    _In_ LPCTSTR  DriverName,
    _In_ LPCTSTR  ServiceName,
    _In_ USHORT   Function
);

BOOLEAN SetupDriverName(
    _Inout_updates_bytes_all_(BufferLength) LPWSTR DriverLocation,
    _In_ ULONG BufferLength
);

class RtProtectionCtrl {
    HANDLE hDevice;
    TCHAR driverLocation[MAX_PATH];

public:
    RtProtectionCtrl();
    ~RtProtectionCtrl();

    BOOL RtProtectionDrv_LoadDriver();
    BOOL RtProtectionDrv_UnloadDriver();
    BOOL RtProtectionDrv_NewProcMon(PNEWPROC_INFO _newproc_info);
};