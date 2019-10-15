/*++
    Samples that show what callbacks can do during the pre-notification
    phase.
--*/



#include "regctrl.h"


VOID 
PreNotificationBlockSample()
/*++

Routine Description:

    This sample shows how to block a registry operation in the
    pre-notification phase. 

    Two keys are created. The create operations should succeed, but one
    is intercepted by the callback and failed with ERROR_ACCESS_DENIED.
    The same is done for two values.

    See ..\sys\Pre.c for the callback routine used in this sample. 

--*/
{

    LONG Res;
    HRESULT hr;
    HKEY Key = NULL;
    HKEY NotModifiedKey = NULL;
    DWORD ValueData = 0xDEADBEEF; 
    DWORD BytesReturned;
    BOOL Result;
    BOOL Success = FALSE;
    REGISTER_CALLBACK_INPUT RegisterCallbackInput = {0};
    REGISTER_CALLBACK_OUTPUT RegisterCallbackOutput = {0};
    UNREGISTER_CALLBACK_INPUT UnRegisterCallbackInput = {0};

    InfoPrint("");
    InfoPrint("=== Pre-Notification Block Sample ====");

    //
    // Register callback
    //
    
    RtlZeroMemory(RegisterCallbackInput.Altitude, MAX_ALTITUDE_BUFFER_LENGTH * sizeof(WCHAR));
    hr = StringCbPrintf(RegisterCallbackInput.Altitude, 
                          MAX_ALTITUDE_BUFFER_LENGTH * sizeof(WCHAR),
                          CALLBACK_ALTITUDE);

    if (!SUCCEEDED(hr)) {
        ErrorPrint("Copying altitude string failed. Error %d", hr);
        goto Exit;
    }

    RegisterCallbackInput.CallbackMode = CALLBACK_MODE_PRE_NOTIFICATION_BLOCK;

    Result = DeviceIoControl(g_Driver,
                             IOCTL_REGISTER_CALLBACK,
                             &RegisterCallbackInput,
                             sizeof(REGISTER_CALLBACK_INPUT),
                             &RegisterCallbackOutput,
                             sizeof(REGISTER_CALLBACK_OUTPUT),
                             &BytesReturned,
                             NULL);

    if (Result != TRUE) {    
        ErrorPrint("RegisterCallback failed. Error %d", GetLastError());
        goto Exit;
    }

    Success = TRUE;

    //
    // Create two keys.
    // Creating the "not modified" key will succeed.
    // Creating the other key will fail with ERROR_ACCESS_DENIED
    //

    //
    // NOTE: In the kernel debugger output, you will see 3 pre-notifications 
    // for create key even though we only call create key twice.
    // You will also see the message that create key is blocked twice.
    //
    // Kd output:
    //
    // RegFltr:        Callback: Altitude-380010, NotifyClass-RegNtPreCreateKeyEx.
    // RegFltr:        Callback: Altitude-380010, NotifyClass-RegNtPostCreateKeyEx.
    // RegFltr:        Callback: Altitude-380010, NotifyClass-RegNtPreCreateKeyEx.
    // RegFltr:        Callback: Create key _RegFltrKey blocked.
    // RegFltr:        Callback: Altitude-380010, NotifyClass-RegNtPreCreateKeyEx.
    // RegFltr:        Callback: Create key _RegFltrKey blocked.
    //
    // The reason this happens is that RegCreateKeyEx is more than just a 
    // wrapper around NtCreateKey. If the call to NtCreateKey fails, 
    // RegCreateKeyEx will retry the call in slightly different ways 
    // depending on the error returned. 
    //

    Res = RegCreateKeyEx(g_RootKey,
                         NOT_MODIFIED_KEY_NAME,
                         0,
                         L"Regfltr_test_class",
                         0,
                         KEY_ALL_ACCESS,
                         NULL,
                         &NotModifiedKey,
                         NULL);

    if (Res != ERROR_SUCCESS) {
        ErrorPrint("RegCreateKeyEx returned unexpected error %d", Res);
        Success = FALSE;
    }

    Res = RegCreateKeyEx(g_RootKey,
                         KEY_NAME,
                         0,
                         L"Regfltr_test_class",
                         0,
                         KEY_ALL_ACCESS,
                         NULL,
                         &Key,
                         NULL);

    if (Res != ERROR_ACCESS_DENIED) {
        ErrorPrint("RegCreateKeyEx returned unexpected error %d", Res);
        Success = FALSE;
    }

    //
    // Set two values. 
    // Setting the "not modified" value will succeed.
    // Setting the other value will fail with ERROR_ACCESS_DENIED.
    //

    Res = RegSetValueEx(g_RootKey,
                        NOT_MODIFIED_VALUE_NAME,
                        0,
                        REG_DWORD,
                        (BYTE *) &ValueData,
                        sizeof(ValueData));
        
    if(Res != ERROR_SUCCESS) {
        ErrorPrint("RegSetValueEx return unexpected status %d", Res);
        Success = FALSE;
    }

    Res = RegSetValueEx(g_RootKey,
                        VALUE_NAME,
                        0,
                        REG_DWORD,
                        (BYTE *) &ValueData,
                        sizeof(ValueData));
        
    if(Res != ERROR_ACCESS_DENIED) {
        ErrorPrint("RegSetValueEx return unexpected status %d", Res);
        Success = FALSE;
    }

    //
    // Unregister the callback
    //

    UnRegisterCallbackInput.Cookie = RegisterCallbackOutput.Cookie;

    Result = DeviceIoControl(g_Driver,
                             IOCTL_UNREGISTER_CALLBACK,
                             &UnRegisterCallbackInput,
                             sizeof(UNREGISTER_CALLBACK_INPUT),
                             NULL,
                             0,
                             &BytesReturned,
                             NULL);

    if (Result != TRUE) {    
        ErrorPrint("UnRegisterCallback failed. Error %d", GetLastError());
        Success = FALSE;
    }

  Exit: 

    // Clean up
    if (Key != NULL) {
        RegCloseKey(Key);
    }
    RegDeleteKey(g_RootKey, KEY_NAME);
    
    if (NotModifiedKey != NULL) {
        RegCloseKey(NotModifiedKey);
    }
    RegDeleteKey(g_RootKey, NOT_MODIFIED_KEY_NAME);
    
    RegDeleteValue(g_RootKey, NOT_MODIFIED_VALUE_NAME);
    RegDeleteValue(g_RootKey, VALUE_NAME);

    if (Success) {
        InfoPrint("Pre-Notification Block Sample succeeded.");
    } else {
        ErrorPrint("Pre-Notification Block Sample FAILED.");
    }
  
}

