#include "pch.h"
#include "FilterFileCtrl.h"

VOID DisplayError(_In_ DWORD Code);

FilterFileCtrl::FilterFileCtrl() 
    : 
    hDriver(NULL), 
    hPort(NULL) 
{}

FilterFileCtrl::~FilterFileCtrl() {}

BOOL FilterFileCtrl::FilterFileDrv_LoadDriver() {
    BOOL Result = DriverCtrl::UtilLoadDriver((LPTSTR)FILTERFILEDRV_DRIVER_NAME,
        (LPTSTR)FILTERFILEDRV_DRIVER_NAME_WITH_EXT,
        (LPTSTR)FILTERFILEDRV_WIN32_DEVICE_NAME,
        &hDriver);

    if (Result != TRUE) {
        ErrorPrint("UtilLoadDriver failed, exiting...");
    }
    return Result;
}

BOOL FilterFileCtrl::FilterFileDrv_UnloadDriver() {
    BOOL Result = DriverCtrl::UtilUnloadDriver(hDriver, NULL, (LPTSTR)FILTERFILEDRV_DRIVER_NAME);
    return Result;
}

BOOL FilterFileCtrl::FilterFileDrv_OpenDevice() {
    BOOL Result = DriverCtrl::UtilOpenDevice((LPTSTR)FILTERFILEDRV_WIN32_DEVICE_NAME, &hDriver);

    if (Result == FALSE) {
        ErrorPrint("UtilOpenDevice failed");
    }
    return Result;
}

BOOL FilterFileCtrl::FilterFileDrv_UpdateConfig() {
    BOOL Result = FilterFileDrv_SendMessage((PCHAR)PASSFLT_UPD_CFG_MSG);
    return Result;
}

BOOL FilterFileCtrl::FilterFileDrv_ConnectCommunicationPort() {
    BOOL Result = TRUE;
    HRESULT hResult = S_OK;
    hResult = FilterConnectCommunicationPort(PASSFLT_PORT_NAME,
        0,
        NULL,
        0,
        NULL,
        &hPort);

    if (hResult != S_OK) {
        printf("Could not connect to filter: 0x%08x\n", hResult);
        DisplayError(hResult);
        Result = FALSE;
    }
    return Result;
}

BOOL FilterFileCtrl::FilterFileDrv_SendMessage(PCHAR msg) {
    BOOL Result = TRUE;
    DWORD msg_sz = strlen(msg);
    CHAR out_buffer[10];
    DWORD breturned = 0;
    HRESULT hResult = S_OK;
    hResult = FilterSendMessage(hPort, msg, msg_sz, out_buffer, 10, &breturned);
    
    if (hResult != S_OK) {
        printf("Could not connect to filter: 0x%08x\n", hResult);
        DisplayError(hResult);
        Result = FALSE;
    }
    return Result;
}

VOID DisplayError(_In_ DWORD Code)
/*++
   This routine will display an error message based off of the Win32 error
   code that is passed in. This allows the user to see an understandable
   error message instead of just the code.
--*/

{
    WCHAR buffer[MAX_PATH] = { 0 };
    DWORD count;
    HMODULE module = NULL;
    HRESULT status;

    count = FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,
        NULL,
        Code,
        0,
        buffer,
        sizeof(buffer) / sizeof(WCHAR),
        NULL);

    if (count == 0) {
        count = GetSystemDirectory(buffer, sizeof(buffer) / sizeof(WCHAR));

        if (count == 0 || count > sizeof(buffer) / sizeof(WCHAR)) {
            //  In practice we expect buffer to be large enough to hold the 
            //  system directory path. 
            printf("    Could not translate error: %d\n", Code);
            return;
        }

        status = StringCchCat(buffer, sizeof(buffer) / sizeof(WCHAR), L"\\fltlib.dll");

        if (status != S_OK) {
            printf("    Could not translate error: %d\n", Code);
            return;
        }

        module = LoadLibraryExW(buffer, NULL, LOAD_LIBRARY_AS_DATAFILE);

        //  Translate the Win32 error code into a useful message.
        count = FormatMessage(FORMAT_MESSAGE_FROM_HMODULE,
            module,
            Code,
            0,
            buffer,
            sizeof(buffer) / sizeof(WCHAR),
            NULL);

        if (module != NULL) { FreeLibrary(module); }

        //  If we still couldn't resolve the message, generate a string
        if (count == 0) {
            printf("    Could not translate error: %d\n", Code);
            return;
        }
    }
    //  Display the translated error.
    printf("    %ws\n", buffer);
}