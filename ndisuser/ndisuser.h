#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <devioctl.h>
#include <tchar.h>
#include <strsafe.h>

#define DRIVER_NAME             L"NdisLwf"
#define DRIVER_NAME_WITH_EXT    L"NdisLwf.sys"

#define NT_DEVICE_NAME          L"\\Device\\NdisLwf"
#define DOS_DEVICES_LINK_NAME   L"\\DosDevices\\NdisLwf"
#define WIN32_DEVICE_NAME       L"\\\\.\\NdisLwf"


 #define IOCTL_FILTER_RESTART_ALL               ( ((0x00000017)<<16)|((0)<<14)|((0)<<2)|(0) )
 #define IOCTL_FILTER_RESTART_ONE_INSTANCE      ( ((0x00000017)<<16)|((0)<<14)|((1)<<2)|(0) )
 #define IOCTL_FILTER_ENUMERATE_ALL_INSTANCES   ( ((0x00000017)<<16)|((0)<<14)|((2)<<2)|(0) )

#define BUF_LEN 512
#define ARRAY_LENGTH(array)    (sizeof (array) / sizeof (array[0]))

#pragma pack(push, 1)
typedef struct _FLTUNICODE_STRING {
    USHORT Length;
    LPWSTR Buffer;
} FLTUNICODE_STRING, *PFLTUNICODE_STRING;
#pragma pack(pop)

#define InfoPrint(str, ...)                 \
    printf(##str"\n",                       \
            __VA_ARGS__)

#define ErrorPrint(str, ...)                \
    printf("ERROR: %u: "##str"\n",          \
            __LINE__,                       \
            __VA_ARGS__)

// IOCTL
VOID RestartAllInstances();
VOID RestartOneInstance();
VOID EnumerateAllInstances();

// DRIVER
BOOL
UtilLoadDriver(
    _In_ LPTSTR szDriverNameNoExt,
    _In_ LPTSTR szDriverNameWithExt,
    _In_ LPTSTR szWin32DeviceName,
    _Out_ HANDLE* pDriver
);

BOOL
UtilUnloadDriver(
    _In_ HANDLE hDriver,
    _In_opt_ SC_HANDLE hSCM,
    _In_ LPTSTR szDriverNameNoExt
);

// UTIL
BOOL
UtilCreateService(
    _In_ SC_HANDLE hSCM,
    _In_ LPTSTR szDriverName,
    _In_ LPTSTR szDriverPath
);

BOOL
UtilStartService(
    _In_ SC_HANDLE hSCM,
    _In_ LPTSTR szDriverName
);

BOOL
UtilStopService(
    _In_ SC_HANDLE hSCM,
    _In_ LPTSTR szDriverName
);

BOOL
UtilDeleteService(
    _In_ SC_HANDLE hSCM,
    _In_ LPTSTR szDriverName
);

BOOL
UtilOpenDevice(
    _In_ LPTSTR szWin32DeviceName,
    _Out_ HANDLE* phDevice);

BOOL
UtilGetServiceState(
    _In_ SC_HANDLE hService,
    _Out_ DWORD* State);

BOOL
UtilWaitForServiceState(
    _In_ SC_HANDLE hService,
    _In_ DWORD State);