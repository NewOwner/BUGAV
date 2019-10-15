/*++
    Samples that show how to set call contexts and object contexts.
--*/

#include "regfltr.h"


BOOLEAN 
SetObjectContextSample(
    )
/*++

Routine Description:

    This sample shows how a registry callback can associate a context on
    a registry object using CmSetCallbackObjectContext. 

    This context is available in the ObjectContext field of the 
    REG_Xxx_KEY_INFORMATION data structures. The registry object is a handle
    to a key and not the registry key itself. When the handle is closed
    or the callback is unregistered, the callback will receive a 
    RegNtCallbackObjectContextCleanup notification to give a chance to 
    clean up the context.

Return Value:

    TRUE if the sample completed successfully.

--*/
{

    PCALLBACK_CONTEXT CallbackCtx = NULL;
    NTSTATUS Status;
    UNICODE_STRING Name;
    OBJECT_ATTRIBUTES KeyAttributes;
    HANDLE RootKeyWithContext = NULL;
    DWORD ValueData = 0;
    BOOLEAN Success = FALSE;


   DbgPrint("REGFLTR ###\n");
   DbgPrint("REGFLTR ### === Set Object Context Sample ====\n");

    //
    // Create the callback context
    //

    CallbackCtx = CreateCallbackContext(CALLBACK_MODE_SET_OBJECT_CONTEXT,
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
        DbgPrint("REGFLTR ### CmRegisterCallback failed. Status 0x%x\n", Status);
        goto Exit;
    }

    Success = TRUE;
    
    //
    // Open the root key again. The callback will associate an object
    // context with the RootKeyWithContext handle.
    //

    RtlInitUnicodeString(&Name, ROOT_KEY_ABS_PATH);
    InitializeObjectAttributes(&KeyAttributes,
                               &Name,
                               OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE,
                               NULL,
                               NULL);
    
    Status = ZwOpenKey(&RootKeyWithContext,
                       KEY_ALL_ACCESS,
                       &KeyAttributes);

    if (!NT_SUCCESS(Status)) {
        DbgPrint("REGFLTR ### ZwOpenKey on root key failed. Status 0x%x\n", Status);
        Success = FALSE;
    }

    //
    // Set value using both the g_RootKey handle and the RootKeyWithContext
    // handle.
    //

    RtlInitUnicodeString(&Name, VALUE_NAME);
    Status = ZwSetValueKey(g_RootKey,
                           &Name,
                           0,
                           REG_DWORD,
                           &ValueData,
                           sizeof(ValueData));
    
    if(!NT_SUCCESS(Status)) {
        DbgPrint("REGFLTR ### ZwSetValue failed. Status 0x%x\n", Status);
        Success = FALSE;
    }

    if (RootKeyWithContext != NULL) {
        Status = ZwSetValueKey(RootKeyWithContext,
                               &Name,
                               0,
                               REG_DWORD,
                               &ValueData,
                               sizeof(ValueData));
        
        if(!NT_SUCCESS(Status)) {
            DbgPrint("REGFLTR ### ZwSetValue failed. Status 0x%x\n", Status);
            Success = FALSE;
        }
    }

    //
    // Unregister the callback
    //

    Status = CmUnRegisterCallback(CallbackCtx->Cookie);

    if (!NT_SUCCESS(Status)) {
        DbgPrint("REGFLTR ### CmUnRegisterCallback failed. Status 0x%x\n", Status);
    }

    //
    // Check that the RegNtCallbackObjectContextCleanup notification was
    // received when we unregistered the callback.
    //

    if (CallbackCtx->ContextCleanupCount != 1) {
        DbgPrint("REGFLTR ### Callback was not invoked for a context cleanup notification.\n");
        Success = FALSE;
    } 

    //
    // Check that there were two notifications that had the object context set.
    // These are the pre and post set value using the RootKeyWithContext handle.
    //
    
    if (CallbackCtx->NotificationWithContextCount != 2) {
        DbgPrint("REGFLTR ### Callback OperationWithContext count expected 2, instead it was %d\n",
                   CallbackCtx->NotificationWithContextCount);
        Success = FALSE;
    } 

    //
    // Check that there were two notifications that did not have the object 
    // context set. These are the pre and post set value using the 
    // g_RootKey handle.
    //
    
    if (CallbackCtx->NotificationWithNoContextCount != 2) {
        DbgPrint("REGFLTR ### Callback OperationWithNoContext count expected 2, instead it was %d\n",
                   CallbackCtx->NotificationWithNoContextCount);
        Success = FALSE;
    } 

  Exit:
    
    if (Success == TRUE) {
       DbgPrint("REGFLTR ### Set Object Context Sample Succeeded.\n");
    } else {
        DbgPrint("REGFLTR ### Set Object Context Sample FAILED.\n");
    }

    //
    // Clean up
    //
    
    RtlInitUnicodeString(&Name, VALUE_NAME);
    ZwDeleteValueKey(g_RootKey, &Name);
    
    if (RootKeyWithContext != NULL) {
        ZwClose(RootKeyWithContext);
    }

    if (CallbackCtx != NULL) {
        ExFreePoolWithTag(CallbackCtx, REGFLTR_CONTEXT_POOL_TAG);
    }

    return Success;
}


BOOLEAN
SetCallContextSample(
    )
/*++

Routine Description:

    This sample shows how a registry callback can associate a context
    with a registry operation during the pre-notification phase so that it
    is available in the post-notification phase. 

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
    

   DbgPrint("REGFLTR ###\n");
   DbgPrint("REGFLTR ### === Set Operation Context Sample ====\n");

    //
    // Create the callback context
    //

    CallbackCtx = CreateCallbackContext(CALLBACK_MODE_SET_CALL_CONTEXT,
                                         CALLBACK_ALTITUDE);

    if (CallbackCtx == NULL) {
        goto Exit;
    }
    
    //
    // Register callback with the context
    //

    Status = CmRegisterCallbackEx(Callback,
                                  &CallbackCtx->Altitude,
                                  g_DeviceObj->DriverObject,
                                  (PVOID) CallbackCtx,
                                  &CallbackCtx->Cookie, 
                                  NULL);
    if (!NT_SUCCESS(Status)) {
        DbgPrint("REGFLTR ### CmRegisterCallback failed. Status 0x%x\n", Status);
        goto Exit;
    }

    Success = TRUE;

    //
    // Create a key and set a value.
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
        DbgPrint("REGFLTR ### ZwCreateKey failed. Status 0x%x\n", Status);
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
        DbgPrint("REGFLTR ### ZwSetValue failed. Status 0x%x\n", Status);
        Success = FALSE;
    }

    //
    // Unregister the callback
    //

    Status = CmUnRegisterCallback(CallbackCtx->Cookie);

    if (!NT_SUCCESS(Status)) {
        DbgPrint("REGFLTR ### CmUnRegisterCallback failed. Status 0x%x\n", Status);
        Success = FALSE;
    }


    //
    // Check that the callback records 2 in OperationContextCount.
    // The count should be incremented once in the post-notification for the
    // create key and once for the set value.
    //

    if (CallbackCtx->NotificationWithContextCount != 2) {
        DbgPrint("REGFLTR ### Callback OperationWithContextCount expected 2, got %d\n",
                   CallbackCtx->NotificationWithContextCount);
        Success = FALSE;
    }

  Exit:
    
    if (Success == TRUE) {
       DbgPrint("REGFLTR ### Set Call Context sample succeeded.\n");
    } else {
        DbgPrint("REGFLTR ### Set Call Context sample FAILED.\n");
    }

    //
    // Clean up
    //
    
    if (Key != NULL) {
        ZwDeleteKey(Key);
        ZwClose(Key);
    }

    RtlInitUnicodeString(&Name, VALUE_NAME);
    ZwDeleteValueKey(g_RootKey, &Name);

    if (CallbackCtx != NULL) {
        ExFreePoolWithTag(CallbackCtx, REGFLTR_CONTEXT_POOL_TAG);
    }

    return Success;

}