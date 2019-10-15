/*++
    Utility functions for working with transaction registry operations
--*/

#include "regfltr.h"


static HANDLE ResourceManager = NULL;
static HANDLE TransactionManager = NULL;


NTSTATUS
CreateKTMResourceManager(
    _In_ PTM_RM_NOTIFICATION CallbackRoutine,
    _In_opt_ PVOID RMKey
    )
/*++

Routine Description:

    This method will create a volatile Transaction Manager (TM) and a volatile
    Resource Manager (RM) and enable callback notification through them.
    The RM created here is used to enlist onto a transaction so that the 
    RMCallback routine will be called when the transaction commits or aborts. 

Arguments:

    CallbackRoutine - Pointer to a ResourceManagerNotification Routine

    RMKey - A caller-defined context value that uniquely identifies the 
            resource manager. The callback routine receives this value as 
            input.
            Note: When you are enlisting to a transaction, you can pass in a 
            context that is specific to that particular enlistment.

Return Value:

    NTSTATUS

--*/
{
    OBJECT_ATTRIBUTES ObjAttributes;
    PKRESOURCEMANAGER RMObject;
    NTSTATUS Status = STATUS_SUCCESS;
    HANDLE TMHandle = NULL;
    HANDLE RMHandle = NULL;
    GUID RMGuid;

    InfoPrint("Creating KTM Resource Manager");

    //
    // Create the volatile TM
    //
    
    InitializeObjectAttributes(&ObjAttributes,
                               NULL,
                               OBJ_KERNEL_HANDLE,
                               NULL,
                               NULL);

    Status = ZwCreateTransactionManager(&TMHandle,
                                        TRANSACTIONMANAGER_ALL_ACCESS,
                                        &ObjAttributes,
                                        NULL,
                                        TRANSACTION_MANAGER_VOLATILE,
                                        0);

    if (!NT_SUCCESS(Status)) {
        ErrorPrint("CreateTransactionManager failed. Status 0x%x", Status);
        goto Exit;
    }

    //
    // Create the volatile RM
    //
    
    Status = ExUuidCreate(&RMGuid);

    if (!NT_SUCCESS(Status)) {
        ErrorPrint("ExUuidCreate failed. Status 0x%x", Status);
        goto Exit;
    }

    InitializeObjectAttributes(&ObjAttributes,
                               NULL,
                               OBJ_KERNEL_HANDLE,
                               NULL,
                               NULL);

    Status = ZwCreateResourceManager(&RMHandle,
                                     RESOURCEMANAGER_ALL_ACCESS,
                                     TMHandle,
                                     &RMGuid,
                                     &ObjAttributes,

                                     RESOURCE_MANAGER_VOLATILE,
                                     NULL);

    if (!NT_SUCCESS(Status)) {
        ErrorPrint("CreateResourceManager failed. Status 0x%x", Status);
        goto Exit;
    }

    //
    // Grab the RM object from the handle
    //

    Status = ObReferenceObjectByHandle(RMHandle,
                                       0,
                                       NULL,
                                       KernelMode,
                                       (PVOID *) &RMObject,
                                       NULL);
    
    if (!NT_SUCCESS(Status)) {
        ErrorPrint("ObReferenceObjectbyHandle failed. Status 0x%x", Status);
        goto Exit;
    }

    //
    // Enable callbacks and pass in our notification routine
    //
    
    Status = TmEnableCallbacks(RMObject,
                               CallbackRoutine,
                               RMKey);

    ObDereferenceObject(RMObject);
    
    if (!NT_SUCCESS(Status)) {
        ErrorPrint("TmEnableCallbacks failed. Status 0x%x", Status);
        goto Exit;
    }

  Exit:

    if (!NT_SUCCESS(Status)) {
        if (RMHandle != NULL) {
            ZwClose(RMHandle);
        }
        if (TMHandle!= NULL) {
            ZwClose(TMHandle);
        }
    } else {
        ResourceManager = RMHandle;
        TransactionManager = TMHandle;
    }
    
    return Status;    
}


VOID
DeleteKTMResourceManager(
    )
/*++

Routine Description:

    Clean up any resources associated wtih the resource manager.

--*/
{
    if (ResourceManager != NULL) {
        ZwClose(ResourceManager);
        ResourceManager = NULL;
    }
    if (TransactionManager != NULL) {
        ZwClose(TransactionManager);
        TransactionManager = NULL;
    }
}
