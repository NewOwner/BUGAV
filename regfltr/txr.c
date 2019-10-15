/*++
    Samples that show how to deal with transactional registry operations.
--*/

#include "regfltr.h"


BOOLEAN
TransactionEnlistSample(
    )
/*++

Routine Description:

    This sample shows how to enlist to a transaction that a registry operation
    is part of inorder to get notifications when it commits or aborts. 

Return Value:

    TRUE if the sample completed successfully.

--*/

{
    PCALLBACK_CONTEXT CallbackCtx = NULL;
    PRMCALLBACK_CONTEXT RMCallbackCtx = NULL;
    NTSTATUS Status;
    UNICODE_STRING Name;
    OBJECT_ATTRIBUTES KeyAttributes;
    OBJECT_ATTRIBUTES TxAttributes;
    HANDLE Key = NULL;
    HANDLE Transaction = NULL;
    BOOLEAN Success = FALSE;
    
    InfoPrint("");
    InfoPrint("=== Transaction Enlist Sample ====");

    if (!g_RMCreated) {
        ErrorPrint("Sample can't run because KTM data structures were not successfully created.");
        goto Exit;
    }

    //
    // Create the registry callback context and the transaction callback context.
    //
    
    CallbackCtx = CreateCallbackContext(CALLBACK_MODE_TRANSACTION_ENLIST,
                                         CALLBACK_ALTITUDE);
    if (CallbackCtx == NULL) {
        goto Exit;
    }

    RMCallbackCtx = (PRMCALLBACK_CONTEXT) ExAllocatePoolWithTag (
                        PagedPool, 
                        sizeof(RMCALLBACK_CONTEXT), 
                        REGFLTR_CONTEXT_POOL_TAG);
    if (RMCallbackCtx == NULL) {
        goto Exit;
    }
    RtlZeroMemory(RMCallbackCtx, sizeof(RMCALLBACK_CONTEXT));
    CallbackCtx->RMCallbackCtx = RMCallbackCtx;

    //
    // Create a transaction
    //

    InitializeObjectAttributes(&TxAttributes,
                               NULL,
                               OBJ_KERNEL_HANDLE,
                               NULL,
                               NULL);
    
    Status = ZwCreateTransaction(&Transaction,
                                 TRANSACTION_ALL_ACCESS,
                                 &TxAttributes,
                                 NULL,
                                 NULL,
                                 0,
                                 0,
                                 0,
                                 NULL,
                                 NULL);

    if (!NT_SUCCESS(Status)) {
        ErrorPrint("CreateTransaction failed. Status 0x%x", Status);
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
        Success = FALSE;
    }

    Success = TRUE;

    //
    // Create a key
    //

    RtlInitUnicodeString(&Name, KEY_NAME);
    InitializeObjectAttributes(&KeyAttributes,
                               &Name,
                               OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE,
                               g_RootKey,
                               NULL);

    Status = ZwCreateKeyTransacted(&Key,
                                   KEY_ALL_ACCESS,
                                   &KeyAttributes,
                                   0,
                                   NULL,
                                   0,
                                   Transaction,
                                   NULL);

    if (!NT_SUCCESS(Status)) {
        ErrorPrint("ZwCreateKeyTransacted failed. Status 0x%x", Status);
        Success = FALSE;
    }

    //
    // Commit the transaction
    //

    Status = ZwCommitTransaction(Transaction, TRUE);
    
    if (!NT_SUCCESS(Status)) {
        ErrorPrint("ZwCommitTransaction failed. Status 0x%x", Status);
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
    // Check that the transaction callback context records a commit notification
    //

    if (RMCallbackCtx->Notification != TRANSACTION_NOTIFY_COMMIT) {
        ErrorPrint("RMContext notification mask is 0x%x instead of 0x%x.",
                   RMCallbackCtx->Notification,
                   TRANSACTION_NOTIFY_COMMIT);
        Success = FALSE;
    }

  Exit:
    
    //
    // Clean up
    //

    if (Transaction != NULL) {
        ZwClose(Transaction);
    }

    //
    // Need to reopen the key to delete it because the previous 
    // handle was part of a transaction that is now gone.
    //

    if (Key != NULL) {
        ZwClose(Key);
        Key = NULL;
    }

    RtlInitUnicodeString(&Name, KEY_NAME);
    InitializeObjectAttributes(&KeyAttributes,
                               &Name,
                               OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE,
                               g_RootKey,
                               NULL);
    
    ZwOpenKey(&Key, KEY_ALL_ACCESS, &KeyAttributes); 
    if (Key != NULL) {
        ZwDeleteKey(Key);
        ZwClose(Key);
    }

    if (CallbackCtx != NULL) {
        ExFreePoolWithTag(CallbackCtx, REGFLTR_CONTEXT_POOL_TAG);
    }

    if (RMCallbackCtx != NULL) {
        ExFreePoolWithTag(RMCallbackCtx, REGFLTR_CONTEXT_POOL_TAG);
    }

    if (Success) {
        InfoPrint("Transaction Enlist Demo succeeded.");
    } else {
        ErrorPrint("Transaction Enlist Demo FAILED.");
    }

    return Success;
}

BOOLEAN 
TransactionReplaySample(
    )
/*++

Routine Description:

    This sample shows how to copy a transactional create key operation.

Return Value:

    TRUE if the sample completed successfully.

--*/

{
    PCALLBACK_CONTEXT CallbackCtx = NULL;
    NTSTATUS Status;
    UNICODE_STRING Name;
    OBJECT_ATTRIBUTES KeyAttributes;
    OBJECT_ATTRIBUTES TxAttributes;
    HANDLE Key = NULL;
    HANDLE Transaction = NULL;
    HANDLE TransactedRoot = NULL;
    BOOLEAN bSuccess = FALSE;
    
    InfoPrint("");
    InfoPrint("=== Transaction Replay Sample ====");

    if (!g_RMCreated) {
        ErrorPrint("Sample can't run because KTM data structures were not successfully created.");
        goto Exit;
    }

    //
    // Create the callback context
    //

    CallbackCtx = CreateCallbackContext(CALLBACK_MODE_TRANSACTION_REPLAY,
                                         CALLBACK_ALTITUDE);
    if (CallbackCtx == NULL) {
        goto Exit;
    }
 
    //
    // Create a transaction
    //

    InitializeObjectAttributes(&TxAttributes,
                               NULL,
                               OBJ_KERNEL_HANDLE,
                               NULL,
                               NULL);

    Status = ZwCreateTransaction(&Transaction,
                                 TRANSACTION_ALL_ACCESS,
                                 &TxAttributes,
                                 NULL,
                                 NULL,
                                 0,
                                 0,
                                 0,
                                 NULL,
                                 NULL);

    if (!NT_SUCCESS(Status)) {
        ErrorPrint("CreateTransaction failed. Status 0x%x", Status);
        goto Exit;
    }

    //
    // Open a transacted handle to the root key
    //
    
    RtlInitUnicodeString(&Name, ROOT_KEY_ABS_PATH);
    InitializeObjectAttributes(&KeyAttributes,
                               &Name,
                               OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE,
                               NULL,
                               NULL);
    
    Status = ZwOpenKeyTransacted(&TransactedRoot,
                                 KEY_ALL_ACCESS,
                                 &KeyAttributes,
                                 Transaction);
    if (!NT_SUCCESS(Status)) {
        ErrorPrint("ZwOpenKeyTransacted failed. Status 0x%x",Status);
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

    bSuccess = TRUE;
    
    //
    // Create a key using the transacted root key handle.
    //

    RtlInitUnicodeString(&Name, KEY_NAME);
    InitializeObjectAttributes(&KeyAttributes,
                               &Name,
                               OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE,
                               TransactedRoot,
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
        bSuccess = FALSE;
    } 

    //
    // Unregister the callback
    //

    Status = CmUnRegisterCallback(CallbackCtx->Cookie);

    if (!NT_SUCCESS(Status)) {
        ErrorPrint("CmUnRegisterCallback failed. Status 0x%x", Status);
        bSuccess = FALSE;
    }


    //
    // Verify that the key created exists and that a key with the
    // "modified" name is also exists.
    //
    
    if (Key != NULL) {
        ZwClose(Key);
        Key = NULL;
    }

    Status = ZwOpenKey(&Key,
                       KEY_ALL_ACCESS,
                       &KeyAttributes);
    if (!NT_SUCCESS(Status)) {
        ErrorPrint("ZwCreateKey failed. Status 0x%x", Status);
        bSuccess = FALSE;
    } else {
        ZwClose(Key);
        Key = NULL;
    }
    
    RtlInitUnicodeString(&Name, MODIFIED_KEY_NAME);
    InitializeObjectAttributes(&KeyAttributes,
                               &Name,
                               OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE,
                               TransactedRoot,
                               NULL);

    Status = ZwOpenKey(&Key,
                       KEY_ALL_ACCESS,
                       &KeyAttributes);

    if (!NT_SUCCESS(Status)) {
        ErrorPrint("ZwCreateKey failed. Status 0x%x", Status);
        bSuccess = FALSE;
    } else {
        ZwClose(Key);
        Key = NULL;
    }

    //
    // Roll back transaction
    //

    Status = ZwRollbackTransaction(Transaction, TRUE);
    
    if (!NT_SUCCESS(Status)) {
        ErrorPrint("ZwRollbackTransaction failed. Status 0x%x", Status);
        bSuccess = FALSE;
        goto Exit;
    }
    
    //
    // Check that both keys no longer exist. 
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
        ErrorPrint("ZwOpenKey returned unexpected status 0x%x. Expected 0x%x", 
                   Status,
                   STATUS_OBJECT_NAME_NOT_FOUND);
        bSuccess = FALSE;
    }

    if (Key != NULL) {
        ZwDeleteKey(Key);
        ZwClose(Key);
        Key = NULL;
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
    if (Status != STATUS_OBJECT_NAME_NOT_FOUND) {
        ErrorPrint("ZwOpenKey returned unexpected status 0x%x. Expected 0x%x", 
                   Status,
                   STATUS_OBJECT_NAME_NOT_FOUND);
        bSuccess = FALSE;
    }

  Exit:
    
    //
    // Clean up 
    //

    if (Key != NULL) {
        ZwDeleteKey(Key);
        ZwClose(Key);
    }

    if (TransactedRoot!= NULL) {
        ZwDeleteKey(TransactedRoot);
        ZwClose(TransactedRoot);
    }

    if (Transaction != NULL) {
        ZwClose(Transaction);
    }

    if (CallbackCtx != NULL) {
        ExFreePoolWithTag(CallbackCtx, REGFLTR_CONTEXT_POOL_TAG);
    }

    if (bSuccess) {
        InfoPrint("Transaction Replay Sample succeeded.");
    } else {
        ErrorPrint("Transaction Replay Sample FAILED.");
    }

    return bSuccess;
    
}