/*++
    Samples that show what callbacks can do during the post-notification
    phase.
--*/

#include "regfltr.h"


/*++

    In registry callback version 1.0, there is a bug with post-notification
    processing and multiple registry filter drivers that can break the samples 
    here. It is fixed with version 1.1.

    The bug occurs when a driver blocks or bypasses a registry operation in the
    pre-notification phase. Even though the processing of the operation stops 
    there, registry filter drivers registered at higher altitudes will still 
    get a post-notification for the operation. If the higher altitude driver 
    tries to change the status of the operation from failure to success or 
    vice versa, this change will be ignored and the status returned 
    will be the status returned by the driver who bypassed or blocked the 
    operation during the pre-notification phase.

    For more information on how notification processing works with multiple 
    registry filter drivers registered see MultiAlt.c
    
    For more information on issues in version 1.0 and changes in version 1.1
    see Version.c 

    
    Beginning with Windows 8.1, it is no longer possible to pass the object
    provided to a RegNtPostCreateKeyEx or RegNtPostOpenKeyEx callout to
    ObOpenObjectByPointer. To work around this, filters should perform all
    create key or open key processing in a RegNtPreCreateKeyEx or
    RegNtPreOpenKeyEx callout. If for any reason the desired processing cannot
    be performed in a RegNtPreCreateKeyEx or RegNtPreOpenKeyEx callout, then
    use CmSetCallbackObjectContext to tag a newly-created or newly-opened key
    as unprocessed and process it in the pre-operation callback for a
    subsequent operation.

--*/



BOOLEAN
PostNotificationOverrideSuccessSample(
    )
/*++

Routine Description:

    This sample shows how registry callbacks can fail a registry operation 
    in the post-notification phase. 

    Two values are created. The creates normally should succeeded, but one 
    is intercepted by the callback and failed with STATUS_ACCESS_DENIED.
    
    NOTE: This sample does not take into account transactions. See txr.c for
    examples on how to handle transactional registry operations.

Return Value:

    TRUE if the sample completed successfully.

--*/
{
    PCALLBACK_CONTEXT CallbackCtx = NULL;
    NTSTATUS Status;
    UNICODE_STRING Name;
    DWORD ValueData = 0; 
    BOOLEAN Success = FALSE;

    InfoPrint("");
    InfoPrint("=== Post-Notification Override Success Sample ====");

    //
    // Create the callback context
    //

    CallbackCtx = CreateCallbackContext(CALLBACK_MODE_POST_NOTIFICATION_OVERRIDE_SUCCESS, 
                                         CALLBACK_ALTITUDE);

    if (CallbackCtx == NULL) {
        goto Exit;
    }
    
    //
    // Register callback 
    //

    Status = CmRegisterCallbackEx(Callback,
                                  &CallbackCtx->Altitude,
                                  g_DeviceObj->DriverObject,
                                  (PVOID) CallbackCtx,
                                  &CallbackCtx->Cookie, 
                                  NULL);
    if (!NT_SUCCESS(Status)) {
        ErrorPrint("CmRegisterCallback failed. Status 0x%x", Status);
        goto Exit;
    }

    Success = TRUE;

    //
    // Set two values. 
    // Setting the "not modified" value will succeed.
    // Setting the other value will fail with file not found.
    //
    
    RtlInitUnicodeString(&Name, NOT_MODIFIED_VALUE_NAME);
    Status = ZwSetValueKey(g_RootKey,
                           &Name,
                           0,
                           REG_DWORD,
                           &ValueData,
                           sizeof(ValueData));
    
    if(!NT_SUCCESS(Status)) {
        ErrorPrint("ZwSetValue return unexpected status 0x%x", Status);
        Success = FALSE;
    }

    RtlInitUnicodeString(&Name, VALUE_NAME);
    Status = ZwSetValueKey(g_RootKey,
                           &Name,
                           0,
                           REG_DWORD,
                           &ValueData,
                           sizeof(ValueData));
    
    if(Status != STATUS_ACCESS_DENIED) {
        ErrorPrint("ZwSetValue return unexpected status 0x%x", Status);
        Success = FALSE;
    }

    //
    // Unregister the callback
    //

    Status = CmUnRegisterCallback(CallbackCtx->Cookie);

    if (!NT_SUCCESS(Status)) {
        ErrorPrint("CmUnRegisterCallback failed. Status 0x%x", Status);
        Success = FALSE;
    }


    //
    // Verify that the set value calls were failed by 
    // checking that the value with VALUE_NAME does not
    // exist.
    //  
    // Deleting the other value should return STATUS_OBJECT_NAME_NOT_FOUND
    // Deleting value with the modified name should succeed.
    //

    RtlInitUnicodeString(&Name, VALUE_NAME);
    Status = ZwDeleteValueKey(g_RootKey, &Name);

    if (Status != STATUS_OBJECT_NAME_NOT_FOUND) {
        ErrorPrint("ZwDeleteValueKey on value failed. Status: 0x%x", Status);
        Success = FALSE;
    }

  Exit:
    
    //
    // Clean up
    //

    RtlInitUnicodeString(&Name, VALUE_NAME);
    ZwDeleteValueKey(g_RootKey, &Name);
    RtlInitUnicodeString(&Name, NOT_MODIFIED_VALUE_NAME);
    ZwDeleteValueKey(g_RootKey, &Name);

    if (CallbackCtx != NULL) {
        ExFreePoolWithTag(CallbackCtx, REGFLTR_CONTEXT_POOL_TAG);
    }

    if (Success) {
        InfoPrint("Post-Notification Override Success Sample succeeded.");
    } else {
        ErrorPrint("Post-Notification Override Success Sample FAILED.");
    }
    return Success;
    
}




BOOLEAN 
PostNotificationOverrideErrorSample(
    )
/*++

Routine Description:

    This sample shows how a registry callback can change a failed registry
    operation into a successful operation in the post-notification phase. 

    A key that does not exist is opened. The opens should fail, but it is 
    intercepted by the callback and the open is redirected to a key that 
    does exist.

    NOTE: This sample does not take into account transactions. See txr.c for
    examples on how to handle transactional registry operations.
    
Return Value:

    TRUE if the sample completed successfully.

--*/
{
    PCALLBACK_CONTEXT CallbackCtx = NULL;
    NTSTATUS Status;
    OBJECT_ATTRIBUTES KeyAttributes;
    UNICODE_STRING Name;
    BOOLEAN Success = FALSE;
    HANDLE Key = NULL;
    HANDLE ModifiedKey = NULL;

    InfoPrint("");
    InfoPrint("=== Post-Notification Override Error Sample ====");

    //
    // Create the callback context 
    //

    CallbackCtx = CreateCallbackContext(CALLBACK_MODE_POST_NOTIFICATION_OVERRIDE_ERROR,
                                         CALLBACK_ALTITUDE);
    if (CallbackCtx == NULL) {
        goto Exit;
    }

    //
    // Create a key with name MODIFIED_KEY_NAME
    //

    RtlInitUnicodeString(&Name, MODIFIED_KEY_NAME);
    InitializeObjectAttributes(&KeyAttributes,
                               &Name,
                               OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE,
                               g_RootKey,
                               NULL);

    Status = ZwCreateKey(&ModifiedKey,
                         KEY_ALL_ACCESS,
                         &KeyAttributes,
                         0,
                         NULL,
                         0,
                         NULL);

    if (!NT_SUCCESS(Status)) {
        ErrorPrint("Creating modified key failed. Status 0x%x", Status);
        goto Exit;
    }

    //
    // Now try to open a key by KEY_NAME which does not exist. Verify that 
    // this fails.
    //

    RtlInitUnicodeString(&Name, KEY_NAME);
    InitializeObjectAttributes(&KeyAttributes,
                               &Name,
                               OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE,
                               g_RootKey,
                               NULL);

    Status = ZwOpenKey(&Key,
                       KEY_ALL_ACCESS,
                       &KeyAttributes);

    if (Status != STATUS_OBJECT_NAME_NOT_FOUND) {
        ErrorPrint("ZwCreateKey returned unexpected status 0x%x", Status);
        goto Exit;
    } 
        
    //
    // Register our callback with the context
    //

    Status = CmRegisterCallbackEx(Callback,
                                  &CallbackCtx->Altitude,
                                  g_DeviceObj->DriverObject,
                                  (PVOID) CallbackCtx,
                                  &CallbackCtx->Cookie, 
                                  NULL);
    if (!NT_SUCCESS(Status)) {
        ErrorPrint("CmRegisterCallback failed. Status 0x%x", Status);
        goto Exit;
    }

    Success = TRUE;
    
    //
    // Open key again. The callback will intercept this and make it succeed.
    //

    Status = ZwOpenKey(&Key,
                       KEY_ALL_ACCESS,
                       &KeyAttributes);

    if (!NT_SUCCESS(Status)) {
        ErrorPrint("ZwOpenKey failed unexpectedly. Status 0x%x", Status);
        Success = FALSE;
    }

    //
    // Unregister the callback
    //

    Status = CmUnRegisterCallback(CallbackCtx->Cookie);

    if (!NT_SUCCESS(Status)) {
        ErrorPrint("CmUnRegisterCallback failed. Status 0x%x", Status);
        Success = FALSE;
    }

  Exit:

    //
    // Clean up
    //

    if (Key != NULL) {
        ZwDeleteKey(Key);
        ZwClose(Key);
    }

    if (ModifiedKey != NULL) {
        ZwDeleteKey(ModifiedKey);
        ZwClose(ModifiedKey);
    }

    if (CallbackCtx != NULL) {
        ExFreePoolWithTag(CallbackCtx, REGFLTR_CONTEXT_POOL_TAG);
    }
    
    if (Success) {
        InfoPrint("Post-Notification Override Error Sample succeeded.");
    } else {
        ErrorPrint("Post-Notification Override Error Sample FAILED.");
    }

    return Success;
}