/*++
    Samples that feature multiple callbacks registered at different
    altitudes and show what notifications they do and don't recieve.
--*/

#include "FilterRegistryDrv.h"


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
