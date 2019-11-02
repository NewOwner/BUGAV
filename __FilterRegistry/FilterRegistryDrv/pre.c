#include "FilterRegistryDrv.h"

DECLARE_GLOBAL_CONST_UNICODE_STRING(str_tstval, L"tstval");
DECLARE_GLOBAL_CONST_UNICODE_STRING(str_tstkey, L"tstkey");
#define MAX_PATH 512
LARGE_INTEGER g_RegCookie;

BOOLEAN checkConfig(PUNICODE_STRING regPath) {
    PPROTECTED_REGKEYS flist_ptr = RegctrlProtectedKeys;
    
    while (flist_ptr != NULL) {
    
        if (RtlEqualUnicodeString(&flist_ptr->k_name, regPath, TRUE)) {
            InfoPrint("\tCallback: #### %wZ blocked.", regPath);
            return TRUE;
        }
        flist_ptr = flist_ptr->k_next;
    }
    return FALSE;
}

NTSTATUS TlGetObjectFullName(PVOID Object, PUNICODE_STRING Name) {
    PUNICODE_STRING         pKeyName = NULL;
    NTSTATUS                ntStatus = 0;

    if (Object == NULL || Name == NULL) {
        return STATUS_INVALID_PARAMETER;
    }

    ntStatus = CmCallbackGetKeyObjectID(&g_RegCookie, Object, NULL, &pKeyName);

    if (NT_SUCCESS(ntStatus) == FALSE) {
        return ntStatus;
    }

    Name->Buffer = (PWCHAR)ExAllocatePoolWithTag(PagedPool, pKeyName->Length, 'RFLM');

    if (Name->Buffer == NULL) {
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    RtlZeroMemory(Name->Buffer, pKeyName->Length);

    Name->Length = 0;
    Name->MaximumLength = pKeyName->Length;

    RtlCopyUnicodeString(Name, pKeyName);
    return STATUS_SUCCESS;
}

NTSTATUS MySetValueKey(PREG_SET_VALUE_KEY_INFORMATION Data) {
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

        if (ustrTarget.Buffer[ustrTarget.Length / sizeof(WCHAR) - 1] != L'\\') {
            RtlAppendUnicodeToString(&ustrTarget, L"\\");
        }

        RtlAppendUnicodeStringToString(&ustrTarget, Data->ValueName);
        
        DbgPrint("SetValueKey Key:%wZ\n", &ustrTarget);
        if (checkConfig(&ustrTarget)) {
            return STATUS_ACCESS_DENIED;
        }

    } __except (EXCEPTION_EXECUTE_HANDLER) { }

    return STATUS_SUCCESS;
}

NTSTATUS MyRenameKey(PREG_RENAME_KEY_INFORMATION Data) {
    UNICODE_STRING          ustrKeyName = { 0 };

    __try {
    
        if ((ExGetPreviousMode() == KernelMode)) {
            return STATUS_SUCCESS;
        }

        if (NT_SUCCESS(TlGetObjectFullName(Data->Object, &ustrKeyName)) == FALSE) {
            return STATUS_SUCCESS;
        }

        DbgPrint("RenameKey Key:%wZ\n", &ustrKeyName);
        if (checkConfig(&ustrKeyName)) {
            ExFreePool(ustrKeyName.Buffer);
            return STATUS_ACCESS_DENIED;
        }
        ExFreePool(ustrKeyName.Buffer);

    } __except (EXCEPTION_EXECUTE_HANDLER) { }

    return STATUS_SUCCESS;
}

NTSTATUS MyCreateKey(PREG_PRE_CREATE_KEY_INFORMATION Data) {
    UNICODE_STRING      ustrTarget = { 0 };
    WCHAR               wszKeyName[MAX_PATH] = { 0 };

    __try {
    
        if ((ExGetPreviousMode() == KernelMode)) {
            return STATUS_SUCCESS;
        }

        ustrTarget.Buffer = wszKeyName;
        ustrTarget.MaximumLength = MAX_PATH * sizeof(WCHAR);

        RtlCopyUnicodeString(&ustrTarget, Data->CompleteName);
        
        DbgPrint("CreateKey Key:%wZ\n", &ustrTarget);
        if (checkConfig(&ustrTarget)) {
            return STATUS_ACCESS_DENIED;
        }

    } __except (EXCEPTION_EXECUTE_HANDLER) { }

    return STATUS_SUCCESS;
}

NTSTATUS MyCreateKeyEx(PREG_CREATE_KEY_INFORMATION Data) {
    UNICODE_STRING      ustrKeyName = { 0 };
    UNICODE_STRING      ustrTarget = { 0 };

    __try {
    
        if ((ExGetPreviousMode() == KernelMode)) {
            return STATUS_SUCCESS;
        }

        if (NT_SUCCESS(TlGetObjectFullName(Data->RootObject, &ustrKeyName)) == FALSE) {
            return STATUS_SUCCESS;
        }

        ustrTarget.MaximumLength = MAX_PATH * sizeof(WCHAR);

        RtlCopyUnicodeString(&ustrTarget, &ustrKeyName);
        ExFreePool(ustrKeyName.Buffer);

        if (Data->CompleteName) {
            RtlAppendUnicodeToString(&ustrTarget, L"\\");
            RtlAppendUnicodeStringToString(&ustrTarget, Data->CompleteName);
        }

        DbgPrint("CreateKeyEx :%wZ\n", ustrTarget);
        if (checkConfig(&ustrTarget)) {
            return STATUS_ACCESS_DENIED;
        }

    } __except (EXCEPTION_EXECUTE_HANDLER) { }

    return STATUS_SUCCESS;
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

        if (ustrTarget.Buffer[ustrTarget.Length / sizeof(WCHAR) - 1] != L'\\') {
            RtlAppendUnicodeToString(&ustrTarget, L"\\");
        }

        RtlAppendUnicodeStringToString(&ustrTarget, Data->ValueName);
        
        DbgPrint("DeleteValueKey Key:%wZ\n", &ustrTarget);
        if (checkConfig(&ustrTarget)) {
            return STATUS_ACCESS_DENIED;
        }

    } __except (EXCEPTION_EXECUTE_HANDLER) { }

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
        
        DbgPrint("DeleteKey Key:%wZ\n", &ustrKeyName);
        if (checkConfig(&ustrKeyName)) {
            ExFreePool(ustrKeyName.Buffer);
            return STATUS_ACCESS_DENIED;
        }
        ExFreePool(ustrKeyName.Buffer);

    } __except (EXCEPTION_EXECUTE_HANDLER) { }
    
    return STATUS_SUCCESS;
}

NTSTATUS
CallbackPreNotificationBlock(
    _In_ PCALLBACK_CONTEXT CallbackCtx,
    _In_ REG_NOTIFY_CLASS NotifyClass,
    _Inout_ PVOID Argument2
) {
    UNREFERENCED_PARAMETER(CallbackCtx);

    switch (NotifyClass) {
    case RegNtPreDeleteKey:
        return MyDeleteKey((PREG_DELETE_KEY_INFORMATION)Argument2);
    case RegNtPreSetValueKey:
        return MySetValueKey((PREG_SET_VALUE_KEY_INFORMATION)Argument2);
    case RegNtPreDeleteValueKey:
        return MyDeleteValueKey((PREG_DELETE_VALUE_KEY_INFORMATION)Argument2);
    case RegNtPreRenameKey:
        return MyRenameKey((PREG_RENAME_KEY_INFORMATION)Argument2);
    case RegNtPreCreateKey:
        return MyCreateKey((PREG_PRE_CREATE_KEY_INFORMATION)Argument2);
    case RegNtPreCreateKeyEx:
        return MyCreateKeyEx((PREG_CREATE_KEY_INFORMATION)Argument2);
    }
    return STATUS_SUCCESS;
}
