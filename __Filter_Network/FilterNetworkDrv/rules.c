#include "precomp.h"

PNET_RULES __ndisNetRules = NULL;

VOID ndisReadCfg() {
    UNICODE_STRING     uniName;
    OBJECT_ATTRIBUTES  objAttr;

    DbgPrint("### ndisReadCfg\n");

    RtlInitUnicodeString(&uniName, L"\\DosDevices\\C:\\bugav_networkfilter.txt");  // or L"\\SystemRoot\\example.txt"
    InitializeObjectAttributes(&objAttr, &uniName, OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE, NULL, NULL);

    HANDLE   handle;
    NTSTATUS ntstatus;
    IO_STATUS_BLOCK    ioStatusBlock;
    UCHAR     buffer[BUFF_SIZE];
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

VOID ndisParseCfg(PUCHAR cfg_buff) {
    DbgPrint("### ndisParseCfg\n");
    if (cfg_buff[0] == '\0') { return; }
    CHAR     line[BUFF_SIZE];
    RtlZeroMemory(line, BUFF_SIZE);
    PNET_RULES cfg_ptr = (PNET_RULES)cfg_buff;
    UCHAR stop = 0xff;
    _dump_bytes(cfg_buff, 17);
    for (size_t i = 0; i < BUFF_SIZE;) {
        _dump_bytes((PUCHAR)&(cfg_buff[i]), 1);
        DbgPrint("### i= %d\n", i);
        if (cfg_buff[i] == stop) { return; }
        ndisPushNetRules(cfg_ptr);
        i += sizeof(NET_RULES) - 2 * sizeof(struct _NET_RULES*);
        cfg_ptr += i;
    }
    
    ndisDumpNetRules();
}

VOID ndisPushNetRules(PNET_RULES newrule) {
    DbgPrint("### ndisPushNetRules\n");
    PNET_RULES flist_ptr = __ndisNetRules;
    if (__ndisNetRules == NULL) {
        __ndisNetRules = (PNET_RULES)ExAllocatePoolWithTag(NonPagedPool, sizeof(NET_RULES), '1geR');
        if (__ndisNetRules != NULL) {
            RtlCopyMemory(__ndisNetRules, newrule, sizeof(NET_RULES)-2*sizeof(struct _NET_RULES*));
            __ndisNetRules->_next = NULL;
            __ndisNetRules->_prev = NULL;
            _dump_bytes((PUCHAR)__ndisNetRules, sizeof(NET_RULES));
            return;
        }
    }
    while (flist_ptr->_next != NULL) { flist_ptr = flist_ptr->_next; }
    flist_ptr->_next = (PNET_RULES)ExAllocatePoolWithTag(NonPagedPool, sizeof(NET_RULES), '1geR');
    if (flist_ptr->_next != NULL) {
        RtlCopyMemory(flist_ptr->_next, newrule, sizeof(NET_RULES) - 2 * sizeof(struct _NET_RULES*));
        flist_ptr->_next->_next = NULL;
        flist_ptr->_next->_prev = flist_ptr;
        _dump_bytes((PUCHAR)flist_ptr->_next, sizeof(NET_RULES));
        return;
    }
}

VOID ndisDumpNetRules() {
    DbgPrint("### ndisDumpNetRules\n");
    PNET_RULES flist_ptr = __ndisNetRules;
    while (flist_ptr != NULL) {
        DbgPrint("\taction: ");             _dump_bytes(&flist_ptr->action, 1);
        DbgPrint("\tether_type: ");         _dump_bytes(flist_ptr->ether_type, 2);
        DbgPrint("\tip_next_protocol: ");   _dump_bytes(flist_ptr->ip_next_protocol, 1);
        DbgPrint("\tsource_ip: ");          _dump_bytes(flist_ptr->source_ip, 4);
        DbgPrint("\tdestination_ip: ");     _dump_bytes(flist_ptr->destination_ip, 4);
        DbgPrint("\tsource_port: ");        _dump_bytes(flist_ptr->source_port, 2);
        DbgPrint("\tdestination_port: ");   _dump_bytes(flist_ptr->destination_port, 2);
        flist_ptr = flist_ptr->_next;
    }
}

VOID ndisDestroyNetRules() {
    DbgPrint("### ndisDestroyNetRules\n");
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

VOID ndisUpdateNetRules() {
    DbgPrint("### ndisUpdateNetRules\n");
    ndisDestroyNetRules();
    ndisReadCfg();
}