/*++
    Samples that show what callbacks can do during the pre-notification
    phase.
--*/

#include "regfltr.h"

NTSTATUS 
CallbackPreNotificationBlock(
    _In_ PCALLBACK_CONTEXT CallbackCtx,
    _In_ REG_NOTIFY_CLASS NotifyClass,
    _Inout_ PVOID Argument2
    )
/*++
    This helper callback routine shows hot to fail a registry operation
    in the pre-notification phase.
--*/
{
    NTSTATUS Status = STATUS_SUCCESS;
    PREG_CREATE_KEY_INFORMATION PreCreateInfo;
    PREG_SET_VALUE_KEY_INFORMATION PreSetValueInfo;

    UNREFERENCED_PARAMETER(CallbackCtx);
    
    PPROTECTED_REGKEYS flist_ptr = RegctrlProtectedKeys;

    switch(NotifyClass) {
        case RegNtPreCreateKeyEx:

            PreCreateInfo = (PREG_CREATE_KEY_INFORMATION) Argument2;
            
            InfoPrint("#### Access to %wZ key.", PreCreateInfo->CompleteName);

            while (flist_ptr != NULL) {
                    if (RtlEqualUnicodeString(&flist_ptr->k_name, (PCUNICODE_STRING)PreCreateInfo->CompleteName, TRUE)) {
                        InfoPrint("\tCallback: Create key %wZ blocked.", PreCreateInfo->CompleteName);
                        Status = STATUS_ACCESS_DENIED;
                    }
                flist_ptr = flist_ptr->k_next;
            }
            break;

        case RegNtPreSetValueKey:
            
            PreSetValueInfo = (PREG_SET_VALUE_KEY_INFORMATION) Argument2;

            InfoPrint("#### Access to %wZ value.", PreSetValueInfo->ValueName);
            
            while (flist_ptr != NULL) {
                if (RtlEqualUnicodeString(&flist_ptr->k_name, (PCUNICODE_STRING)PreSetValueInfo->ValueName, TRUE)) {
                    InfoPrint("\tCallback: Set value %wZ blocked.", PreSetValueInfo->ValueName);
                    Status = STATUS_ACCESS_DENIED;
                }
                flist_ptr = flist_ptr->k_next;
            }
            break;
            
        default:
            // Do nothing for other notifications
            break;
    }
    return Status;
}
