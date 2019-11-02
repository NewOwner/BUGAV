/*++
    Samples that show what callbacks can do during the pre-notification
    phase.
--*/

#include "FilterRegistryDrv.h"

DECLARE_GLOBAL_CONST_UNICODE_STRING(str_tstval, L"tstval");
DECLARE_GLOBAL_CONST_UNICODE_STRING(str_tstkey, L"tstkey");
#define MAX_PATH 512
LARGE_INTEGER g_RegCookie;

NTSTATUS TlGetObjectFullName(PVOID Object, PUNICODE_STRING Name) {
    PUNICODE_STRING         pKeyName = NULL;
    NTSTATUS                ntStatus = 0;


    if (Object == NULL || Name == NULL)
        return STATUS_INVALID_PARAMETER;


    ntStatus = CmCallbackGetKeyObjectID(&g_RegCookie,
        Object,
        NULL,
        &pKeyName);


    if (NT_SUCCESS(ntStatus) == FALSE) {
        return ntStatus;
    }


    Name->Buffer = (PWCHAR)ExAllocatePoolWithTag(
        PagedPool,
        pKeyName->Length,
        'RFLM'
    );


    if (Name->Buffer == NULL) {
        return STATUS_INSUFFICIENT_RESOURCES;
    }


    RtlZeroMemory(Name->Buffer, pKeyName->Length);


    Name->Length = 0;
    Name->MaximumLength = pKeyName->Length;


    RtlCopyUnicodeString(Name, pKeyName);
    return STATUS_SUCCESS;
}

//XXX
PUNICODE_STRING QueryObjectFullPath(PVOID object) {
    PUNICODE_STRING path = NULL;
    ULONG returnLength = 0;
    POBJECT_NAME_INFORMATION info;
    NTSTATUS status;

    if (KeGetCurrentIrql() < DISPATCH_LEVEL) {

        // This is where the exception and PAGE_FAULT occurs
        status = ObQueryNameString(object, (POBJECT_NAME_INFORMATION)NULL, 0, &returnLength);

        if (returnLength > 0) {

            info = (POBJECT_NAME_INFORMATION)ExAllocatePoolWithTag(NonPagedPool, returnLength * sizeof(WCHAR), 'Egap');

            // This is where PAGE_FAULT occurs
            if (ObQueryNameString(object,
                info,
                returnLength,
                &returnLength) ==
                STATUS_INFO_LENGTH_MISMATCH) {

                return NULL;
            }

            path = (PUNICODE_STRING)ExAllocatePoolWithTag(NonPagedPool, returnLength, 'Egap');
            RtlCopyUnicodeString(path, &(info->Name));

            ExFreePoolWithTag(info, 'Egap');
        }
    }

    return path;
}

NTSTATUS MyDeleteValueKey(PREG_DELETE_VALUE_KEY_INFORMATION Data) {
    UNICODE_STRING          ustrKeyName = { 0 };
    UNICODE_STRING          ustrTarget = { 0 };
    WCHAR                   wszKeyPath[MAX_PATH] = { 0 };


    __try {


        if ((ExGetPreviousMode() == KernelMode)) {
            return STATUS_SUCCESS;
        }


        if (NT_SUCCESS(TlGetObjectFullName(Data->Object, &ustrKeyName)) == FALSE) {
            return STATUS_SUCCESS;
        }


        ustrTarget.Buffer = wszKeyPath;
        ustrTarget.MaximumLength = MAX_PATH * sizeof(WCHAR);

        RtlCopyUnicodeString(&ustrTarget, &ustrKeyName);


        ExFreePool(ustrKeyName.Buffer);


        if (ustrTarget.Buffer[ustrTarget.Length / sizeof(WCHAR) - 1] != L'\\')
            RtlAppendUnicodeToString(&ustrTarget, L"\\");


        RtlAppendUnicodeStringToString(&ustrTarget, Data->ValueName);
        DbgPrint("$$$ DeleteValueKey Key:%wZ\n", &ustrTarget);


    } __except (EXCEPTION_EXECUTE_HANDLER) {


    }


    return STATUS_SUCCESS;
}

NTSTATUS MyDeleteKey(PREG_DELETE_KEY_INFORMATION Data) {
    UNICODE_STRING      ustrKeyName = { 0 };


    __try {


        if ((ExGetPreviousMode() == KernelMode)) {
            return STATUS_SUCCESS;
        }


        if (NT_SUCCESS(TlGetObjectFullName(Data->Object, &ustrKeyName)) == FALSE) {
            return STATUS_SUCCESS;
        }
        DbgPrint("$$$ DeleteKey Key:%wZ\n", &ustrKeyName);


        ExFreePool(ustrKeyName.Buffer);


    } __except (EXCEPTION_EXECUTE_HANDLER) {
    }


    return STATUS_SUCCESS;
}

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

    PREG_CREATE_KEY_INFORMATION PreCreateKeyInfo;
    PREG_SET_VALUE_KEY_INFORMATION PreSetValueKeyInfo;
    PREG_DELETE_VALUE_KEY_INFORMATION PreDeleteValueKeyInfo;
    PREG_RENAME_KEY_INFORMATION PreRenameKeyInfo;
    PREG_QUERY_VALUE_KEY_INFORMATION PreQueryValueKeyInfo;
    PREG_OPEN_KEY_INFORMATION PreOpenKeyInfo;
    PREG_LOAD_KEY_INFORMATION PreLoadKeyInfo;
    PREG_DELETE_KEY_INFORMATION PreDeleteKeyInfo;



    //PREG_QUERY_KEY_INFORMATION PreQueryKeyInfo;
    //PREG_FLUSH_KEY_INFORMATION PreFlushKeyInfo;
    //PREG_UNLOAD_KEY_INFORMATION PreUnloadKeyInfo;


    UNREFERENCED_PARAMETER(CallbackCtx);

    //PPROTECTED_REGKEYS flist_ptr = RegctrlProtectedKeys;

    switch (NotifyClass) {
    case RegNtPreCreateKeyEx:

        PreCreateKeyInfo = (PREG_CREATE_KEY_INFORMATION)Argument2;
        //InfoPrint("#### Access to %wZ key.", PreCreateKeyInfo->CompleteName);
        //InfoPrint("\tCallback: NotifyClass-%S.", GetNotifyClassString(NotifyClass));
        //while (flist_ptr != NULL) {
        //    if (RtlEqualUnicodeString(&flist_ptr->k_name, (PCUNICODE_STRING)PreCreateKeyInfo->CompleteName, TRUE)) {
        //        InfoPrint("\tCallback: Create key %wZ blocked.", PreCreateKeyInfo->CompleteName);
        //        Status = STATUS_ACCESS_DENIED;
        //        break;
        //    }
        //    flist_ptr = flist_ptr->k_next;
        //}

        if (RtlEqualUnicodeString(&str_tstkey, (PCUNICODE_STRING)PreCreateKeyInfo->CompleteName, TRUE)) {
            InfoPrint("\tCallback: key %wZ blocked.", PreCreateKeyInfo->CompleteName);
            Status = STATUS_ACCESS_DENIED;
            InfoPrint("#### Access to %wZ value.", PreCreateKeyInfo->CompleteName);
            InfoPrint("\tCallback: NotifyClass-%S.", GetNotifyClassString(NotifyClass));
        }
        break;

    case RegNtPreSetValueKey:

        PreSetValueKeyInfo = (PREG_SET_VALUE_KEY_INFORMATION)Argument2;

        //while (flist_ptr != NULL) {
        //    if (RtlEqualUnicodeString(&flist_ptr->k_name, (PCUNICODE_STRING)PreSetValueKeyInfo->ValueName, TRUE)) {
        //        InfoPrint("\tCallback: Set value %wZ blocked.", PreSetValueKeyInfo->ValueName);
        //        Status = STATUS_ACCESS_DENIED;
        //        break;
        //    }
        //    flist_ptr = flist_ptr->k_next;
        //}

        if (RtlEqualUnicodeString(&str_tstval, (PCUNICODE_STRING)PreSetValueKeyInfo->ValueName, TRUE)) {
            InfoPrint("#### Access to %wZ value.", PreSetValueKeyInfo->ValueName);
            InfoPrint("\tCallback: Set value %wZ blocked.", PreSetValueKeyInfo->ValueName);
            Status = STATUS_ACCESS_DENIED;
        }
        break;



    case RegNtPreDeleteValueKey:
        PreDeleteValueKeyInfo = (PREG_DELETE_VALUE_KEY_INFORMATION)Argument2;
        if (RtlEqualUnicodeString(&str_tstval, (PCUNICODE_STRING)PreDeleteValueKeyInfo->ValueName, TRUE)) {
            InfoPrint("\tCallback: value %wZ blocked.", PreDeleteValueKeyInfo->ValueName);
            Status = STATUS_ACCESS_DENIED;
            InfoPrint("#### Access to %wZ value.", PreDeleteValueKeyInfo->ValueName);
            InfoPrint("\tCallback: NotifyClass-%S.", GetNotifyClassString(NotifyClass));
        }
        break;

    case RegNtPreRenameKey:
        PreRenameKeyInfo = (PREG_RENAME_KEY_INFORMATION)Argument2;
        if (RtlEqualUnicodeString(&str_tstkey, (PCUNICODE_STRING)PreRenameKeyInfo->NewName, TRUE)) {
            InfoPrint("\tCallback: key %wZ blocked.", PreRenameKeyInfo->NewName);
            Status = STATUS_ACCESS_DENIED;
            InfoPrint("#### Access to %wZ key.", PreRenameKeyInfo->NewName);
            InfoPrint("\tCallback: NotifyClass-%S.", GetNotifyClassString(NotifyClass));
        }
        break;

    case RegNtPreQueryValueKey:
        PreQueryValueKeyInfo = (PREG_QUERY_VALUE_KEY_INFORMATION)Argument2;
        if (RtlEqualUnicodeString(&str_tstval, (PCUNICODE_STRING)PreQueryValueKeyInfo->ValueName, TRUE)) {
            InfoPrint("\tCallback: value %wZ blocked.", PreQueryValueKeyInfo->ValueName);
            Status = STATUS_ACCESS_DENIED;
            InfoPrint("#### Access to %wZ value.", PreQueryValueKeyInfo->ValueName);
            InfoPrint("\tCallback: NotifyClass-%S.", GetNotifyClassString(NotifyClass));
        }
        break;

    case RegNtPreCreateKey:
        PreCreateKeyInfo = (PREG_CREATE_KEY_INFORMATION)Argument2;
        if (RtlEqualUnicodeString(&str_tstkey, (PCUNICODE_STRING)PreCreateKeyInfo->CompleteName, TRUE)) {
            InfoPrint("\tCallback: key %wZ blocked.", PreCreateKeyInfo->CompleteName);
            Status = STATUS_ACCESS_DENIED;
            InfoPrint("#### Access to %wZ key.", PreCreateKeyInfo->CompleteName);
            InfoPrint("\tCallback: NotifyClass-%S.", GetNotifyClassString(NotifyClass));
        }
        break;

    case RegNtPreOpenKey:
        PreOpenKeyInfo = (PREG_OPEN_KEY_INFORMATION)Argument2;
        if (RtlEqualUnicodeString(&str_tstkey, (PCUNICODE_STRING)PreOpenKeyInfo->CompleteName, TRUE)) {
            InfoPrint("\tCallback: key %wZ blocked.", PreOpenKeyInfo->CompleteName);
            Status = STATUS_ACCESS_DENIED;
            InfoPrint("#### Access to %wZ key.", PreOpenKeyInfo->CompleteName);
            InfoPrint("\tCallback: NotifyClass-%S.", GetNotifyClassString(NotifyClass));
        }
        break;

    case RegNtPreLoadKey:
        PreLoadKeyInfo = (PREG_LOAD_KEY_INFORMATION)Argument2;
        if (RtlEqualUnicodeString(&str_tstkey, (PCUNICODE_STRING)PreLoadKeyInfo->KeyName, TRUE)) {
            InfoPrint("\tCallback: key %wZ blocked.", PreLoadKeyInfo->KeyName);
            Status = STATUS_ACCESS_DENIED;
            InfoPrint("#### Access to %wZ key.", PreLoadKeyInfo->KeyName);
            InfoPrint("\tCallback: NotifyClass-%S.", GetNotifyClassString(NotifyClass));
        }
        break;











    case RegNtPreDeleteKey:
            PreDeleteKeyInfo = (PREG_DELETE_KEY_INFORMATION)Argument2;
            MyDeleteKey(PreDeleteKeyInfo);
            //PUNICODE_STRING keypath = QueryObjectFullPath(*((PVOID*)PreDeleteKeyInfo->Object));

            //InfoPrint("#### Access to %wZ key.", keypath);
            //InfoPrint("\tCallback: NotifyClass-%S.", GetNotifyClassString(NotifyClass));

        break;
        //case RegNtPreQueryKey:
        //    PreQueryKeyInfo = (PREG_QUERY_KEY_INFORMATION)Argument2;
        //    InfoPrint("#### Access to %wZ key.", PreQueryKeyInfo->CompleteName);
        //    InfoPrint("\tCallback: NotifyClass-%S.", GetNotifyClassString(NotifyClass));
        //    break;
        //case RegNtPreFlushKey:
        //    PreFlushKeyInfo = (PREG_FLUSH_KEY_INFORMATION)Argument2;
        //    InfoPrint("#### Access to %wZ key.", PreFlushKeyInfo->CompleteName);
        //    InfoPrint("\tCallback: NotifyClass-%S.", GetNotifyClassString(NotifyClass));
        //    break;
        //case RegNtPreUnLoadKey:
        //    PreUnloadKeyInfo = (PREG_UNLOAD_KEY_INFORMATION)Argument2;
        //    InfoPrint("#### Access to %wZ key.", PreUnloadKeyInfo->CompleteName);
        //    InfoPrint("\tCallback: NotifyClass-%S.", GetNotifyClassString(NotifyClass));
        //    break;

    default:
        break;
    }
    return Status;
}
