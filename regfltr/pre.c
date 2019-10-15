/*++
    Samples that show what callbacks can do during the pre-notification
    phase.
--*/

#include "regfltr.h"


BOOLEAN
PreNotificationBlockSample(
    )
/*++

Routine Description:

    This sample shows how to block a registry operation in the
    pre-notification phase. 

    Two keys are created. The create operations should succeed, but one
    is intercepted by the callback and failed with STATUS_ACCESS_DENIED.
    The same is done for two values.

Return Value:

    TRUE if the sample completed successfully.

--*/
{
    PCALLBACK_CONTEXT CallbackCtx = NULL;
    NTSTATUS Status;
    OBJECT_ATTRIBUTES KeyAttributes;
    UNICODE_STRING Name;
    HANDLE Key = NULL;
    HANDLE NotModifiedKey = NULL;
    DWORD ValueData = 0; 
    BOOLEAN Success = FALSE;

    InfoPrint("");
    InfoPrint("=== Pre-Notification Block Sample ====");
    
    // Create the callback context
    CallbackCtx = CreateCallbackContext(CALLBACK_MODE_PRE_NOTIFICATION_BLOCK,
                                        CALLBACK_ALTITUDE);
    if (CallbackCtx == NULL) {
        goto Exit;
    }
    
    //
    // Register callback

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
    // Create two keys.
    // Creating the "not modified" key will succeed.
    // Creating the other key will fail with STATUS_ACCESS_DENIED
    //

    RtlInitUnicodeString(&Name, NOT_MODIFIED_KEY_NAME);
    InitializeObjectAttributes(&KeyAttributes,
                               &Name,
                               OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE,
                               g_RootKey,
                               NULL);

    Status = ZwCreateKey(&NotModifiedKey,
                         KEY_ALL_ACCESS,
                         &KeyAttributes,
                         0,
                         NULL,
                         0,
                         NULL);

    if (Status != STATUS_SUCCESS) {
        ErrorPrint("ZwCreateKey returned unexpected status 0x%x", Status);
        Success = FALSE;
    }

    RtlInitUnicodeString(&Name, KEY_NAME);
    InitializeObjectAttributes(&KeyAttributes,
                               &Name,
                               OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE,
                               g_RootKey,
                               NULL);

    Status = ZwCreateKey(&Key,
                         KEY_ALL_ACCESS,
                         &KeyAttributes,
                         0,
                         NULL,
                         0,
                         NULL);

    if (Status != STATUS_ACCESS_DENIED) {
        ErrorPrint("ZwCreateKey returned unexpected status 0x%x", Status);
        Success = FALSE;
    }


    //
    // Set two values. 
    // Setting the "not modified" value will succeed.
    // Setting the other value will fail with STATUS_ACCESS_DENIED.
    //

    RtlInitUnicodeString(&Name, NOT_MODIFIED_VALUE_NAME);
    Status = ZwSetValueKey(g_RootKey,
                           &Name,
                           0,
                           REG_DWORD,
                           &ValueData,
                           sizeof(ValueData));
    
    if(Status != STATUS_SUCCESS) {
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

  Exit:

    //
    // Clean up
    //

    if (Key != NULL) {
        ZwDeleteKey(Key);
        ZwClose(Key);
    }

    if (NotModifiedKey != NULL) {
        ZwDeleteKey(NotModifiedKey);
        ZwClose(NotModifiedKey);
    }

    RtlInitUnicodeString(&Name, VALUE_NAME);
    ZwDeleteValueKey(g_RootKey, &Name);
    RtlInitUnicodeString(&Name, NOT_MODIFIED_VALUE_NAME);
    ZwDeleteValueKey(g_RootKey, &Name);

    if (CallbackCtx != NULL) {
        ExFreePoolWithTag(CallbackCtx, REGFLTR_CONTEXT_POOL_TAG);
    }

    if (Success) {
        InfoPrint("Pre-Notification Block Sample succeeded.");
    } else {
        ErrorPrint("Pre-Notification Block Sample FAILED.");
    }

    return Success;
    
}

// USER XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
// XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
// XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
NTSTATUS 
CallbackPreNotificationBlock(
    _In_ PCALLBACK_CONTEXT CallbackCtx,
    _In_ REG_NOTIFY_CLASS NotifyClass,
    _Inout_ PVOID Argument2
    )
/*++

Routine Description:

    This helper callback routine shows hot to fail a registry operation
    in the pre-notification phase.
    
Arguments:

    CallbackContext - The value that the driver passed to the Context parameter
        of CmRegisterCallbackEx when it registers this callback routine.

    NotifyClass - A REG_NOTIFY_CLASS typed value that identifies the type of 
        registry operation that is being performed and whether the callback
        is being called in the pre or post phase of processing.

    Argument2 - A pointer to a structure that contains information specific
        to the type of the registry operation. The structure type depends
        on the REG_NOTIFY_CLASS value of Argument1. 

Return Value:

    NTSTATUS

--*/
{
    NTSTATUS Status = STATUS_SUCCESS;
    PREG_CREATE_KEY_INFORMATION PreCreateInfo;
    PREG_SET_VALUE_KEY_INFORMATION PreSetValueInfo;
    UNICODE_STRING Name;

    UNREFERENCED_PARAMETER(CallbackCtx);
    
    switch(NotifyClass) {
        case RegNtPreCreateKeyEx:
            
            PreCreateInfo = (PREG_CREATE_KEY_INFORMATION) Argument2;

            //
            // Only intercept the operation if the key being created has the 
            // name KEY_NAME.
            //
            
            RtlInitUnicodeString(&Name, KEY_NAME);
            if (RtlEqualUnicodeString((PCUNICODE_STRING) &Name, 
                                      (PCUNICODE_STRING) PreCreateInfo->CompleteName, 
                                      TRUE)) {
                //
                // By returning an error status, we block the operation.
                //
                
                InfoPrint("\tCallback: Create key %wZ blocked.", 
                          PreCreateInfo->CompleteName);
                Status = STATUS_ACCESS_DENIED;
            }
            break;
            
        case RegNtPreSetValueKey:
            
            PreSetValueInfo = (PREG_SET_VALUE_KEY_INFORMATION) Argument2;

            //
            // Only intercept the operation if the value being set has the 
            // name VALUE_NAME.
            //
            
            RtlInitUnicodeString(&Name, VALUE_NAME);
            if (RtlEqualUnicodeString((PCUNICODE_STRING) &Name, 
                                      (PCUNICODE_STRING) PreSetValueInfo->ValueName, 
                                      TRUE)) {
                //
                // By returning an error status, we block the operation.
                //
               
                InfoPrint("\tCallback: Set value %wZ blocked.", 
                          PreSetValueInfo->ValueName);
                Status = STATUS_ACCESS_DENIED;
            }
            break;
            
        default:
            //
            // Do nothing for other notifications
            //
            break;
    }

    return Status;
}



BOOLEAN
PreNotificationBypassSample(
    )
/*++

Routine Description:

    This sample shows how to bypass a registry operation so that the CM does
    not process the operation. Unlike block, an operation that is bypassed
    is still considered successful so the callback must provide the caller
    with what the CM would have provided.

    A key and a value are created. However both operations are bypassed by the
    callback so that the key and value actually created have different names
    than would is expected.
    
Return Value:

    TRUE if the sample completed successfully.

--*/
{
    PCALLBACK_CONTEXT CallbackCtx = NULL;
    NTSTATUS Status;
    OBJECT_ATTRIBUTES KeyAttributes;
    UNICODE_STRING Name;
    HANDLE Key = NULL;
    DWORD ValueData = 0; 
    BOOLEAN Success = FALSE;

    InfoPrint("");
    InfoPrint("=== Pre-Notification Bypass Sample ====");

    //
    // Create the callback context
    //

    CallbackCtx = CreateCallbackContext(CALLBACK_MODE_PRE_NOTIFICATION_BYPASS,
                                        CALLBACK_ALTITUDE);
    if (CallbackCtx == NULL) {
        goto Exit;
    }

    //
    // Register the callback
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
    // Create a key and set a value. Both should succeed
    //

    RtlInitUnicodeString(&Name, KEY_NAME);
    InitializeObjectAttributes(&KeyAttributes,
                               &Name,
                               OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE,
                               g_RootKey,
                               NULL);

    Status = ZwCreateKey(&Key,
                         KEY_ALL_ACCESS,
                         &KeyAttributes,
                         0,
                         NULL,
                         0,
                         NULL);

    if (!NT_SUCCESS(Status)) {
        ErrorPrint("ZwCreateKey failed. Status 0x%x", Status);
        Success = FALSE;
    }

    RtlInitUnicodeString(&Name, VALUE_NAME);
    Status = ZwSetValueKey(g_RootKey,
                           &Name,
                           0,
                           REG_DWORD,
                           &ValueData,
                           sizeof(ValueData));
    
    if(!NT_SUCCESS(Status)) {
        ErrorPrint("ZwSetValue failed. Status 0x%x", Status);
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
    // Check that a key with the expected name KEY_NAME cannot be found 
    // but a key with the "modified" name can be found. 
    //

    if (Key != NULL) {
        ZwClose(Key);
    }

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
        ErrorPrint("ZwOpenKey on key returned unexpected status: 0x%x", Status);
        if (Key != NULL) {
            ZwDeleteKey(Key);
            ZwClose(Key);
            Key = NULL;
        }
        Success = FALSE;
    }

    RtlInitUnicodeString(&Name, MODIFIED_KEY_NAME);
    InitializeObjectAttributes(&KeyAttributes,
                               &Name,
                               OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE,
                               g_RootKey,
                               NULL);

    Status = ZwOpenKey(&Key,
                       KEY_ALL_ACCESS,
                       &KeyAttributes);

    if (!NT_SUCCESS(Status)) {
        ErrorPrint("ZwOpenKey on modified key path failed. Status: 0x%x", Status);
        Success = FALSE;
    }
        

    //
    // Do the same check by trying to delete a value with VALUE_NAME and
    // with the "modified" name. 
    //

    RtlInitUnicodeString(&Name, VALUE_NAME);
    Status = ZwDeleteValueKey(g_RootKey, &Name);

    if (Status != STATUS_OBJECT_NAME_NOT_FOUND) {
        ErrorPrint("ZwDeleteValueKey on original value returned unexpected status: 0x%x", 
                   Status);
        Success = FALSE;
    }

    RtlInitUnicodeString(&Name, MODIFIED_VALUE_NAME);
    Status = ZwDeleteValueKey(g_RootKey, &Name);

    if (!NT_SUCCESS(Status)) {
        ErrorPrint("ZwDeleteValueKey on modified value failed. Status: 0x%x", 
                   Status);
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

    if (CallbackCtx != NULL) {
        ExFreePoolWithTag(CallbackCtx, REGFLTR_CONTEXT_POOL_TAG);
    }

    if (Success) {
        InfoPrint("Pre-Notification Bypass Sample succeeded.");
    } else {
        ErrorPrint("Pre-Notification Bypass Sample FAILED.");
    }

    return Success;
}
