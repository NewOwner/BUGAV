#pragma once
#include <windows.h>

#define DRIVER_FUNC_INSTALL     0x01
#define DRIVER_FUNC_REMOVE      0x02

#define DRIVER_NAME_BASIC       L"injdrvbasic"
#define DRIVER_NAME_WEB         L"injdrvweb"

BOOLEAN
ManageDriver(
    _In_ LPCTSTR  DriverName,
    _In_ LPCTSTR  ServiceName,
    _In_ USHORT   Function
);

BOOLEAN
SetupDriverNameBasic(
    _Inout_updates_bytes_all_(BufferLength) PTCHAR DriverLocation,
    _In_ ULONG BufferLength
);

BOOLEAN
SetupDriverNameWeb(
    _Inout_updates_bytes_all_(BufferLength) PTCHAR DriverLocation,
    _In_ ULONG BufferLength
);
