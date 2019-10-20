#include "precomp.h"

PNET_RULES __ndisNetRules = NULL;

VOID ndisReadCfg() {
    UNICODE_STRING     uniName;
    OBJECT_ATTRIBUTES  objAttr;

    DbgPrint("### RegctrlReadCfg\n");

    RtlInitUnicodeString(&uniName, L"\\DosDevices\\C:\\ndisbugav.txt");  // or L"\\SystemRoot\\example.txt"
    InitializeObjectAttributes(&objAttr, &uniName, OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE, NULL, NULL);

    HANDLE   handle;
    NTSTATUS ntstatus;
    IO_STATUS_BLOCK    ioStatusBlock;
    CHAR     buffer[BUFF_SIZE];
    LARGE_INTEGER      byteOffset;
    
    RtlZeroMemory(buffer, BUFF_SIZE);

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
            ndisParseCfg(buffer);
        }
        ZwClose(handle);
    }
}

VOID ndisParseCfg(CHAR* cfg_buff) {
    DbgPrint("### RegctrlParseCfg\n");
    if (cfg_buff[0] == '\0') { return; }
    CHAR     line[BUFF_SIZE];
    RtlZeroMemory(line, BUFF_SIZE);
    size_t bptr = 0;
    for (size_t i = 0; i < BUFF_SIZE; i++) {
        if (cfg_buff[i] == '\n') {
            size_t linesz = i - bptr - 1;
            RtlCopyMemory(line, cfg_buff + bptr, linesz);
            NET_RULES newrule = { 0 };
            ndisPushRule(newrule);
            bptr = i + 1;
        }
    }

    ndisDumpProtectedFileCfg();
}

VOID ndisPushRule(NET_RULES newrule) {
    DbgPrint("### RegctrlPushProtectedFileCfg\n");
    PNET_RULES flist_ptr = __ndisNetRules;
    if (__ndisNetRules == NULL) {
        __ndisNetRules = (PNET_RULES)ExAllocatePoolWithTag(NonPagedPool, sizeof(NET_RULES), '1geR');
        if (__ndisNetRules != NULL) {
            __ndisNetRules->_next = NULL;
            __ndisNetRules->_prev = NULL;
            __ndisNetRules->action = newrule.action;
            return;
        }
    }
    while (flist_ptr->_next != NULL) { flist_ptr = flist_ptr->_next; }
    flist_ptr->_next = (PNET_RULES)ExAllocatePoolWithTag(NonPagedPool, sizeof(NET_RULES), '1geR');
    if (flist_ptr->_next != NULL) {
        flist_ptr->_next->_next = NULL;
        flist_ptr->_next->_prev = flist_ptr;
        flist_ptr->_next->action = newrule.action;
        return;
    }
}

VOID ndisDumpProtectedFileCfg() {
    DbgPrint("### RegctrlDumpProtectedFileCfg\n");
    PNET_RULES flist_ptr = __ndisNetRules;
    while (flist_ptr != NULL) {
        DbgPrint("=====\n");
        flist_ptr = flist_ptr->_next;
    }
}

VOID ndisDestroyProtectedFileCfg() {
    DbgPrint("### RegctrlDestroyProtectedFileCfg\n");
    PNET_RULES flist_ptr = __ndisNetRules;

    if (flist_ptr == NULL) { return; }

    while (flist_ptr->_next != NULL) { flist_ptr = flist_ptr->_next; }

    while (flist_ptr->_prev != NULL) {
        flist_ptr = flist_ptr->_prev;
        ExFreePoolWithTag(flist_ptr->_next, '1geR');
    }
    ExFreePoolWithTag(flist_ptr, '1geR');
    __ndisNetRules = NULL;
}

VOID ndisUpdateCfg() {
    ndisDestroyProtectedFileCfg();
    ndisReadCfg();
}