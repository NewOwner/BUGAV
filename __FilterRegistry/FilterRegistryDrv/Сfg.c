#include "FilterRegistryDrv.h"
#define  BUFF_SIZE 512

VOID RegctrlReadCfg() {
    UNICODE_STRING     uniName;
    OBJECT_ATTRIBUTES  objAttr;

    DbgPrint("### RegctrlReadCfg\n");

    RtlInitUnicodeString(&uniName, L"\\DosDevices\\E:\\bugav_registryfilter.txt");
    InitializeObjectAttributes(&objAttr, &uniName, OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE, NULL, NULL);

    HANDLE   handle;
    NTSTATUS ntstatus;
    IO_STATUS_BLOCK    ioStatusBlock;

    CHAR     buffer[BUFF_SIZE];
    RtlZeroMemory(buffer, BUFF_SIZE);
    //size_t  cb;

    LARGE_INTEGER      byteOffset;

    ntstatus = ZwCreateFile(&handle,
        GENERIC_READ,
        &objAttr, &ioStatusBlock,
        NULL,
        FILE_ATTRIBUTE_NORMAL,
        0,
        FILE_OPEN,
        FILE_SYNCHRONOUS_IO_NONALERT,
        NULL, 0);

    if (NT_SUCCESS(ntstatus)) {
        byteOffset.LowPart = byteOffset.HighPart = 0;
        ntstatus = ZwReadFile(handle, NULL, NULL, NULL, &ioStatusBlock,
            buffer, BUFF_SIZE, &byteOffset, NULL);
        if (NT_SUCCESS(ntstatus)) {
            buffer[BUFF_SIZE - 1] = '\0';
            RegctrlParseCfg(buffer);
        }
        ZwClose(handle);
    }
}

VOID RegctrlParseCfg(CHAR* cfg_buff) {
    DbgPrint("### RegctrlParseCfg\n");
    if (cfg_buff[0] == '\0') { return; }
    CHAR     line[BUFF_SIZE];
    RtlZeroMemory(line, BUFF_SIZE);
    size_t bptr = 0;
    ANSI_STRING AS;
    UNICODE_STRING US;
    for (size_t i = 0; i < BUFF_SIZE; i++) {
        if (cfg_buff[i] == '\n') {
            size_t linesz = i - bptr - 1;
            RtlCopyMemory(line, cfg_buff + bptr, linesz);

            RtlInitAnsiString(&AS, line);
            RtlAnsiStringToUnicodeString(&US, &AS, TRUE);
            RegctrlPushProtectedFileCfg(US);
            bptr = i + 1;
        }
    }

    RegctrlDumpProtectedFileCfg();
}

VOID RegctrlPushProtectedFileCfg(UNICODE_STRING newstr) {
    DbgPrint("### RegctrlPushProtectedFileCfg\n");
    PPROTECTED_REGKEYS flist_ptr = RegctrlProtectedKeys;
    if (RegctrlProtectedKeys == NULL) {
        RegctrlProtectedKeys = (PPROTECTED_REGKEYS)ExAllocatePoolWithTag(NonPagedPool, sizeof(PROTECTED_REGKEYS), '1geR');
        if (RegctrlProtectedKeys != NULL) {
            RegctrlProtectedKeys->k_next = NULL;
            RegctrlProtectedKeys->k_prev = NULL;
            RegctrlProtectedKeys->k_name = newstr;
            return;
        }
    }
    while (flist_ptr->k_next != NULL) { flist_ptr = flist_ptr->k_next; }
    flist_ptr->k_next = (PPROTECTED_REGKEYS)ExAllocatePoolWithTag(NonPagedPool, sizeof(PROTECTED_REGKEYS), '1geR');
    if (flist_ptr->k_next != NULL) {
        flist_ptr->k_next->k_next = NULL;
        flist_ptr->k_next->k_prev = flist_ptr;
        flist_ptr->k_next->k_name = newstr;
        return;
    }
}

VOID RegctrlDumpProtectedFileCfg() {
    DbgPrint("### RegctrlDumpProtectedFileCfg\n");
    PPROTECTED_REGKEYS flist_ptr = RegctrlProtectedKeys;
    while (flist_ptr != NULL) {
        DbgPrint("===== %wZ\n", flist_ptr->k_name);
        flist_ptr = flist_ptr->k_next;
    }
}

VOID RegctrlDestroyProtectedFileCfg() {
    DbgPrint("### RegctrlDestroyProtectedFileCfg\n");
    PPROTECTED_REGKEYS flist_ptr = RegctrlProtectedKeys;

    if (flist_ptr == NULL) { return; }

    while (flist_ptr->k_next != NULL) { flist_ptr = flist_ptr->k_next; }

    while (flist_ptr->k_prev != NULL) {
        flist_ptr = flist_ptr->k_prev;
        ExFreePoolWithTag(flist_ptr->k_next, '1geR');
    }
    ExFreePoolWithTag(flist_ptr, '1geR');
    RegctrlProtectedKeys = NULL;
}

VOID RegctrlUpdateCfg() {
    RegctrlDestroyProtectedFileCfg();
    RegctrlReadCfg();
}