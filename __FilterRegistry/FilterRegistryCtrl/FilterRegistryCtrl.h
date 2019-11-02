#pragma once

#include "../../__LIBS/DriverCtrl/DriverCtrl.h"

#define REG_DRIVER_NAME             L"FilterRegistryDrv"
#define REG_DRIVER_NAME_WITH_EXT    L"FilterRegistryDrv.sys"

#define REG_NT_DEVICE_NAME          L"\\Device\\FilterRegistryDrv"
#define REG_DOS_DEVICES_LINK_NAME   L"\\DosDevices\\FilterRegistryDrv"
#define REG_WIN32_DEVICE_NAME       L"\\\\.\\FilterRegistryDrv"

// SDDL string used when creating the device. This string
// limits access to this driver to system and admins only.

#define REG_DEVICE_SDDL             L"D:P(A;;GA;;;SY)(A;;GA;;;BA)"

// IOCTLs exposed by the driver.

#define IOCTL_UPDATE_CONFIG            CTL_CODE (FILE_DEVICE_UNKNOWN, (0x800 + 0), METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define IOCTL_REGISTER_CALLBACK        CTL_CODE (FILE_DEVICE_UNKNOWN, (0x800 + 1), METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define IOCTL_UNREGISTER_CALLBACK      CTL_CODE (FILE_DEVICE_UNKNOWN, (0x800 + 2), METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define IOCTL_GET_CALLBACK_VERSION     CTL_CODE (FILE_DEVICE_UNKNOWN, (0x800 + 3), METHOD_BUFFERED, FILE_SPECIAL_ACCESS)


#define MAX_ALTITUDE_BUFFER_LENGTH 10
// List of callback modes
//
typedef enum _CALLBACK_MODE {
    CALLBACK_MODE_PRE_NOTIFICATION_BLOCK,
    CALLBACK_MODE_PRE_NOTIFICATION_BYPASS,
    CALLBACK_MODE_POST_NOTIFICATION_OVERRIDE_ERROR,
    CALLBACK_MODE_POST_NOTIFICATION_OVERRIDE_SUCCESS,
    CALLBACK_MODE_TRANSACTION_REPLAY,
    CALLBACK_MODE_TRANSACTION_ENLIST,
    CALLBACK_MODE_MULTIPLE_ALTITUDE_BLOCK_DURING_PRE,
    CALLBACK_MODE_MULTIPLE_ALTITUDE_INTERNAL_INVOCATION,
    CALLBACK_MODE_MULTIPLE_ALTITUDE_MONITOR,
    CALLBACK_MODE_SET_CALL_CONTEXT,
    CALLBACK_MODE_SET_OBJECT_CONTEXT,
    CALLBACK_MODE_CAPTURE,
    CALLBACK_MODE_VERSION_BUGCHECK,
    CALLBACK_MODE_VERSION_CREATE_OPEN_V1,
} CALLBACK_MODE;

// Input and output data structures for the various driver IOCTLs
typedef struct _REGISTER_CALLBACK_INPUT {
    CALLBACK_MODE CallbackMode;                 // specifies the callback mode for the callback context
    WCHAR Altitude[MAX_ALTITUDE_BUFFER_LENGTH]; // specifies the altitude to register the callback at
} REGISTER_CALLBACK_INPUT, * PREGISTER_CALLBACK_INPUT;

typedef struct _REGISTER_CALLBACK_OUTPUT {
    LARGE_INTEGER Cookie;                       // receives the cookie value from registering the callback
} REGISTER_CALLBACK_OUTPUT, * PREGISTER_CALLBACK_OUTPUT;

typedef struct _UNREGISTER_CALLBACK_INPUT {
    LARGE_INTEGER Cookie;                       // specifies the cookie value for the callback
} UNREGISTER_CALLBACK_INPUT, * PUNREGISTER_CALLBACK_INPUT;

typedef struct _GET_CALLBACK_VERSION_OUTPUT {
    ULONG MajorVersion;                         // Receives the version number of the registry callback
    ULONG MinorVersion;
} GET_CALLBACK_VERSION_OUTPUT, * PGET_CALLBACK_VERSION_OUTPUT;

class FilterRegistryCtrl {
    HANDLE hDriver;
    ULONG g_MajorVersion;   // Version number for the registry callback
    ULONG g_MinorVersion;
    REGISTER_CALLBACK_INPUT RegisterCallbackInput;
    REGISTER_CALLBACK_OUTPUT RegisterCallbackOutput;
    UNREGISTER_CALLBACK_INPUT UnRegisterCallbackInput;

public:
    FilterRegistryCtrl();
    ~FilterRegistryCtrl();

    BOOL FilterRegistryDrv_LoadDriver();
    BOOL FilterRegistryDrv_UnloadDriver();
    BOOL FilterRegistryDrv_OpenDevice();

    BOOL FilterRegistryDrv_UpdateConfig();
    BOOL FilterRegistryDrv_RegisterCallback();
    BOOL FilterRegistryDrv_UnregisterCallback();
    BOOL FilterRegistryDrv_GetCallbackVersion();
    VOID FilterRegistryDrv_TestCallbacks();
};



// Test definitions

#define ROOT_KEY_ABS_PATH          L"\\REGISTRY\\MACHINE\\Software\\_RegFltrRoot"
#define ROOT_KEY_REL_PATH          L"Software\\_RegFltrRoot"
#define KEY_NAME                   L"_RegFltrKey"
#define MODIFIED_KEY_NAME          L"_RegFltrModifiedKey"
#define NOT_MODIFIED_KEY_NAME      L"_RegFltrNotModifiedKey"
#define VALUE_NAME                 L"_RegFltrValue"
#define MODIFIED_VALUE_NAME        L"_RegFltrModifiedValue"
#define NOT_MODIFIED_VALUE_NAME    L"_RegFltrNotModifiedValue"

#define CALLBACK_LOW_ALTITUDE      L"380000"
#define CALLBACK_ALTITUDE          L"380010"
#define CALLBACK_HIGH_ALTITUDE     L"380020"

#define MAX_ALTITUDE_BUFFER_LENGTH 10