/*++
    Samples that feature multiple callbacks registered at different
    altitudes and show what notifications they do and don't recieve.
--*/

#include "regfltr.h"


BOOLEAN 
MultipleAltitudeBlockDuringPreSample(
    )
/*++
    This sample features a stack of three callbacks at different altitudes and
    demonstrates what happens when middle callback blocks an operation
    in the pre-notification phase. 
--*/
{
    PCALLBACK_CONTEXT CallbackCtxHigh = NULL;
    PCALLBACK_CONTEXT CallbackCtxMid = NULL;
    PCALLBACK_CONTEXT CallbackCtxLow = NULL;
    NTSTATUS Status;
    OBJECT_ATTRIBUTES KeyAttributes;
    UNICODE_STRING Name;
    HANDLE Key = NULL;
    BOOLEAN Success = FALSE;

    InfoPrint("");
    InfoPrint("=== Multiple Altitude Block During Pre Sample ====");

    //
    // Create callback contexts for the 3 callbacks.
    // The high and low callbacks will only monitor how many notifications
    // they receive.
    //
    
    CallbackCtxHigh = CreateCallbackContext(CALLBACK_MODE_MULTIPLE_ALTITUDE_MONITOR,
                                            CALLBACK_HIGH_ALTITUDE);
    CallbackCtxMid = CreateCallbackContext(CALLBACK_MODE_MULTIPLE_ALTITUDE_BLOCK_DURING_PRE,
                                           CALLBACK_ALTITUDE);
    CallbackCtxLow = CreateCallbackContext(CALLBACK_MODE_MULTIPLE_ALTITUDE_MONITOR,
                                           CALLBACK_LOW_ALTITUDE);

    if ((CallbackCtxHigh == NULL) ||
        (CallbackCtxMid == NULL) ||
        (CallbackCtxLow == NULL)) {
        goto Exit;
    }

    //
    // Register the callbacks
    //

    Status = CmRegisterCallbackEx(Callback,
                                  &CallbackCtxHigh->Altitude,
                                  g_DeviceObj->DriverObject,
                                  (PVOID) CallbackCtxHigh,
                                  &CallbackCtxHigh->Cookie, 
                                  NULL);
    if (!NT_SUCCESS(Status)) {
        ErrorPrint("CmRegisterCallback failed. Status 0x%x", Status);
        goto Exit;
    }

    Status = CmRegisterCallbackEx(Callback,
                                  &CallbackCtxMid->Altitude,
                                  g_DeviceObj->DriverObject,
                                  (PVOID) CallbackCtxMid,
                                  &CallbackCtxMid->Cookie, 
                                  NULL);
    if (!NT_SUCCESS(Status)) {
        ErrorPrint("CmRegisterCallback failed. Status 0x%x", Status);
        goto Exit;
    }

    Status = CmRegisterCallbackEx(Callback,
                                  &CallbackCtxLow->Altitude,
                                  g_DeviceObj->DriverObject,
                                  (PVOID) CallbackCtxLow,
                                  &CallbackCtxLow->Cookie, 
                                  NULL);
    if (!NT_SUCCESS(Status)) {
        ErrorPrint("CmRegisterCallback failed. Status 0x%x", Status);
        goto Exit;
    }

    Success = TRUE;

    //
    // Do a create key operation which will be blocked by the middle
    // callback and fail with STATUS_ACCESS_DENIED
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

    if (Status != STATUS_ACCESS_DENIED) {
        ErrorPrint("ZwCreateKey returned unexpected status 0x%x", Status);
        Success = FALSE;
    }

    
    //
    // Unregister the callbacks
    //

    Status = CmUnRegisterCallback(CallbackCtxHigh->Cookie);

    if (!NT_SUCCESS(Status)) {
        ErrorPrint("CmUnRegisterCallback failed. Status 0x%x", Status);
    }

    Status = CmUnRegisterCallback(CallbackCtxMid->Cookie);

    if (!NT_SUCCESS(Status)) {
        ErrorPrint("CmUnRegisterCallback failed. Status 0x%x", Status);
    }

    Status = CmUnRegisterCallback(CallbackCtxLow->Cookie);

    if (!NT_SUCCESS(Status)) {
        ErrorPrint("CmUnRegisterCallback failed. Status 0x%x", Status);
    }


    //
    // Verify that the highest alitude callback receives a pre and a post 
    // notification. It receives a post notification because it returned 
    // STATUS_SUCCESS in the pre-notification so it is guaranteed to get a 
    // post notification.
    //
    
    if ((CallbackCtxHigh->PreNotificationCount != 1) ||
        (CallbackCtxHigh->PostNotificationCount != 1)) {
        ErrorPrint("High Callback should have seen 1 pre and 1 post notifications.");
        ErrorPrint("High Callback actually saw %d pre and %d post notifications.",
                   CallbackCtxHigh->PreNotificationCount,
                   CallbackCtxHigh->PostNotificationCount);
        Success = FALSE;
    }

    //
    // Verify the middle callback receives only a pre notification.
    // It does not get a post notification because it return a non-success
    // value in the pre-notification phase.
    //
    
    if ((CallbackCtxMid->PreNotificationCount != 1) ||
        (CallbackCtxMid->PostNotificationCount != 0)) {
        ErrorPrint("Mid Callback should have seen 1 pre and 0 post notifications.");
        ErrorPrint("Mid Callback actually saw %d pre and %d post notifications.",
                   CallbackCtxMid->PreNotificationCount,
                   CallbackCtxMid->PostNotificationCount);
        Success = FALSE;
    }

    //
    // Verify the lowest callback receives no notifications.
    // Once the middle callback blocks, no callbacks at lower altitudes are
    // notified.
    //
    
    if ((CallbackCtxLow->PreNotificationCount != 0) ||
        (CallbackCtxLow->PostNotificationCount != 0)) {
        ErrorPrint("Low Callback should have seen 0 pre and 0 post notifications.");
        ErrorPrint("Low Callback actually saw %d pre and %d post notifications.",
                   CallbackCtxLow->PreNotificationCount,
                   CallbackCtxLow->PostNotificationCount);
        Success = FALSE;
    }

  Exit:

    if (Success) {
        InfoPrint("Multiple Altitude Block During Pre Sample succeeded.");
    } else {
        ErrorPrint("Multiple Altitude Block During Pre Sample FAILED.");
    }

    //
    // Clean up
    //

    if (Key != NULL) {
        ZwDeleteKey(Key);
        ZwClose(Key);
    }

    if (CallbackCtxHigh != NULL) {
        ExFreePoolWithTag(CallbackCtxHigh, REGFLTR_CONTEXT_POOL_TAG);
    }

    if (CallbackCtxMid != NULL) {
        ExFreePoolWithTag(CallbackCtxMid, REGFLTR_CONTEXT_POOL_TAG);
    }

    if (CallbackCtxLow != NULL) {
        ExFreePoolWithTag(CallbackCtxLow, REGFLTR_CONTEXT_POOL_TAG);
    }

    return Success;
}


BOOLEAN 
MultipleAltitudeInternalInvocationSample(
    )
/*++
    This sample features a stack of 3 callbacks at different altitudes and
    demonstrates what happens when the middle callback invokes a registry
    operation. 
--*/
{
    PCALLBACK_CONTEXT CallbackCtxHigh = NULL;
    PCALLBACK_CONTEXT CallbackCtxMid = NULL;
    PCALLBACK_CONTEXT CallbackCtxLow = NULL;
    NTSTATUS Status;
    OBJECT_ATTRIBUTES KeyAttributes;
    UNICODE_STRING Name;
    HANDLE Key = NULL;
    BOOLEAN Success = FALSE;
    

    InfoPrint("");
    InfoPrint("=== Multiple Altitude Internal Invocation Sample ====");

    //
    // Create callback contexts for the 3 callbacks.
    // The high and low callbacks will only monitor how many notifications
    // they receive.
    //
    
    CallbackCtxHigh = CreateCallbackContext(CALLBACK_MODE_MULTIPLE_ALTITUDE_MONITOR,
                                            CALLBACK_HIGH_ALTITUDE);
    CallbackCtxMid = CreateCallbackContext(CALLBACK_MODE_MULTIPLE_ALTITUDE_INTERNAL_INVOCATION,
                                           CALLBACK_ALTITUDE);
    CallbackCtxLow = CreateCallbackContext(CALLBACK_MODE_MULTIPLE_ALTITUDE_MONITOR,
                                           CALLBACK_LOW_ALTITUDE);

    if ((CallbackCtxHigh == NULL) ||
        (CallbackCtxMid == NULL) ||
        (CallbackCtxLow == NULL)) {
        goto Exit;
    }

    //
    // Register the callbacks
    //

    Status = CmRegisterCallbackEx(Callback,
                                  &CallbackCtxHigh->Altitude,
                                  g_DeviceObj->DriverObject,
                                  (PVOID) CallbackCtxHigh,
                                  &CallbackCtxHigh->Cookie, 
                                  NULL);
    if (!NT_SUCCESS(Status)) {
        ErrorPrint("CmRegisterCallback failed. Status 0x%x", Status);
        goto Exit;
    }

    Status = CmRegisterCallbackEx(Callback,
                                  &CallbackCtxMid->Altitude,
                                  g_DeviceObj->DriverObject,
                                  (PVOID) CallbackCtxMid,
                                  &CallbackCtxMid->Cookie, 
                                  NULL);
    if (!NT_SUCCESS(Status)) {
        ErrorPrint("CmRegisterCallback failed. Status 0x%x", Status);
        goto Exit;
    }

    Status = CmRegisterCallbackEx(Callback,
                                  &CallbackCtxLow->Altitude,
                                  g_DeviceObj->DriverObject,
                                  (PVOID) CallbackCtxLow,
                                  &CallbackCtxLow->Cookie, 
                                  NULL);
    if (!NT_SUCCESS(Status)) {
        ErrorPrint("CmRegisterCallback failed. Status 0x%x", Status);
        goto Exit;
    }

    Success = TRUE;

    //
    // Create a key. When the middle callback receives the pre-notification
    // and the post-notification for this create it will perform an open key 
    // and a close key operation.
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
        ErrorPrint("ZwCreateKey returned unexpected status 0x%x", Status);
        Success = FALSE;
    }

    //
    // Unregister the callbacks
    //

    Status = CmUnRegisterCallback(CallbackCtxHigh->Cookie);

    if (!NT_SUCCESS(Status)) {
        ErrorPrint("CmUnRegisterCallback failed. Status 0x%x", Status);
        Success = FALSE;
    }

    Status = CmUnRegisterCallback(CallbackCtxMid->Cookie);

    if (!NT_SUCCESS(Status)) {
        ErrorPrint("CmUnRegisterCallback failed. Status 0x%x", Status);
        Success = FALSE;
    }

    Status = CmUnRegisterCallback(CallbackCtxLow->Cookie);

    if (!NT_SUCCESS(Status)) {
        ErrorPrint("CmUnRegisterCallback failed. Status 0x%x", Status);
        Success = FALSE;
    }


    //
    // Verify the highest altitude callback receives one pre and one post
    // notification. This callback does not get notifications for the 
    // registry operations called by the middle callback.
    //
    
    if ((CallbackCtxHigh->PreNotificationCount != 1) ||
        (CallbackCtxHigh->PostNotificationCount != 1)) {
        ErrorPrint("High Callback should have seen 1 pre and 1 post notifications.");
        ErrorPrint("High Callback actually saw %d pre and %d post notifications.",
                   CallbackCtxHigh->PreNotificationCount,
                   CallbackCtxHigh->PostNotificationCount);
        Success = FALSE;
    }

    //
    // Verify the middle callback receives one pre and one post notification.
    // This callback does not get notifications for the registry operations 
    // that it calls.
    //
    
    if ((CallbackCtxMid->PreNotificationCount != 1) ||
        (CallbackCtxMid->PostNotificationCount != 1)) {
        ErrorPrint("Mid Callback should have seen 1 pre and 1 post notifications.");
        ErrorPrint("Mid Callback actually saw %d pre and %d post notifications.",
                   CallbackCtxMid->PreNotificationCount,
                   CallbackCtxMid->PostNotificationCount);
        Success = FALSE;
    }

    //
    // Verify the lowest callback receives 5 pre-notifications and 5
    // post-notifications. This callback receives 1 pre and 1 post from the 
    // original create key operation. It also receives 2 pre and 2 post for
    // the open key and close key operations called by the middle callback 
    // during the pre phase of the create key and then 2 pre and 2 post again
    // for the calls in the post phase of the create key.
    //
    
    if ((CallbackCtxLow->PreNotificationCount != 5) ||
        (CallbackCtxLow->PostNotificationCount != 5)) {
        ErrorPrint("Low Callback should have seen 5 pre and 5 post notifications.");
        ErrorPrint("Low Callback actually saw %d pre and %d post notifications.",
                   CallbackCtxLow->PreNotificationCount,
                   CallbackCtxLow->PostNotificationCount);
        Success = FALSE;
    }

  Exit:
    
    if (Success) {
        InfoPrint("Multiple Altitude Internal Invocation Sample succeeded.");
    } else {
        ErrorPrint("Multiple Altitude Internal Invocation Sample FAILED.");
    }

    //
    // Clean up
    //

    if (Key != NULL) {
        ZwDeleteKey(Key);
        ZwClose(Key);
    }

    if (CallbackCtxHigh != NULL) {
        ExFreePoolWithTag(CallbackCtxHigh, REGFLTR_CONTEXT_POOL_TAG);
    }

    if (CallbackCtxMid != NULL) {
        ExFreePoolWithTag(CallbackCtxMid, REGFLTR_CONTEXT_POOL_TAG);
    }

    if (CallbackCtxLow != NULL) {
        ExFreePoolWithTag(CallbackCtxLow, REGFLTR_CONTEXT_POOL_TAG);
    }

    return Success;
}


NTSTATUS 
CallbackMonitor(
    _In_ PCALLBACK_CONTEXT CallbackCtx,
    _In_ REG_NOTIFY_CLASS NotifyClass,
    _Inout_ PVOID Argument2
    )
/*++

Routine Description:

    This helper callback routine just monitors how many pre and post registry 
    operations it receives and records it in the callback context. 

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

    Always STATUS_SUCCESS

--*/
{
    UNREFERENCED_PARAMETER(Argument2);
    
    switch(NotifyClass) {
        case RegNtPreDeleteKey:
        case RegNtPreSetValueKey:
        case RegNtPreDeleteValueKey:
        case RegNtPreSetInformationKey:
        case RegNtPreRenameKey:
        case RegNtPreEnumerateKey:
        case RegNtPreEnumerateValueKey:
        case RegNtPreQueryKey:
        case RegNtPreQueryValueKey:
        case RegNtPreQueryMultipleValueKey:
        case RegNtPreKeyHandleClose:
        case RegNtPreCreateKeyEx:
        case RegNtPreOpenKeyEx:
        case RegNtPreFlushKey:
        case RegNtPreLoadKey:
        case RegNtPreUnLoadKey:
        case RegNtPreQueryKeySecurity:
        case RegNtPreSetKeySecurity:
        case RegNtPreRestoreKey:
        case RegNtPreSaveKey:
        case RegNtPreReplaceKey:
            InterlockedIncrement(&CallbackCtx->PreNotificationCount);
            break;
        case RegNtPostDeleteKey:
        case RegNtPostSetValueKey:
        case RegNtPostDeleteValueKey:
        case RegNtPostSetInformationKey:
        case RegNtPostRenameKey:
        case RegNtPostEnumerateKey:
        case RegNtPostEnumerateValueKey:
        case RegNtPostQueryKey:
        case RegNtPostQueryValueKey:
        case RegNtPostQueryMultipleValueKey:
        case RegNtPostKeyHandleClose:
        case RegNtPostCreateKeyEx:
        case RegNtPostOpenKeyEx:
        case RegNtPostFlushKey:
        case RegNtPostLoadKey:
        case RegNtPostUnLoadKey:
        case RegNtPostQueryKeySecurity:
        case RegNtPostSetKeySecurity:
        case RegNtPostRestoreKey:
        case RegNtPostSaveKey:
        case RegNtPostReplaceKey:
            InterlockedIncrement(&CallbackCtx->PostNotificationCount);
            break;
    }

    return STATUS_SUCCESS;
    
}
