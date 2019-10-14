#include <fltKernel.h>
#include <dontuse.h>
#include <suppress.h>

#include "passThrough.h"

#define SIOCTL_KDPRINT(_x_) \
                DbgPrint("SIOCTL.SYS: ");\
                DbgPrint _x_;

#define PASSFLT_PORT_NAME                   L"\\PassFltPort"

#pragma prefast(disable:__WARNING_ENCODE_MEMBER_FUNCTION_POINTER, "Not valid for kernel mode drivers")


PASSTHROUGH_DATA PassThroughData;
ULONG_PTR OperationStatusCtx = 1;
PPROTECTED_FILES FltProtectedFiles = NULL;

#define PTDBG_TRACE_ROUTINES            0x00000001
#define PTDBG_TRACE_OPERATION_STATUS    0x00000002

ULONG gTraceFlags = 0;


#define PT_DBG_PRINT( _dbgLevel, _string )          \
    (FlagOn(gTraceFlags,(_dbgLevel)) ?              \
        DbgPrint _string :                          \
        ((int)0))

/*************************************************************************
    Prototypes
*************************************************************************/

DRIVER_INITIALIZE DriverEntry;
NTSTATUS
DriverEntry(
    _In_ PDRIVER_OBJECT DriverObject,
    _In_ PUNICODE_STRING RegistryPath
);

NTSTATUS
PassMessage(
    _In_ PVOID ConnectionCookie,
    _In_reads_bytes_opt_(InputBufferSize) PVOID InputBuffer,
    _In_ ULONG InputBufferSize,
    _Out_writes_bytes_to_opt_(OutputBufferSize, *ReturnOutputBufferLength) PVOID OutputBuffer,
    _In_ ULONG OutputBufferSize,
    _Out_ PULONG ReturnOutputBufferLength
);

NTSTATUS
PassConnect(
    _In_ PFLT_PORT ClientPort,
    _In_ PVOID ServerPortCookie,
    _In_reads_bytes_(SizeOfContext) PVOID ConnectionContext,
    _In_ ULONG SizeOfContext,
    _Flt_ConnectionCookie_Outptr_ PVOID* ConnectionCookie
);

VOID
PassDisconnect(
    _In_opt_ PVOID ConnectionCookie
);

VOID
PassReadCfg();

VOID
PassParseCfg(CHAR* cfg_buff);

VOID
PassPushProtectedFileCfg(UNICODE_STRING newstr);

VOID
PassDumpProtectedFileCfg();

VOID
PassDestroyProtectedFileCfg();

VOID
PassUpdateCfg();

NTSTATUS
PtInstanceSetup(
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_ FLT_INSTANCE_SETUP_FLAGS Flags,
    _In_ DEVICE_TYPE VolumeDeviceType,
    _In_ FLT_FILESYSTEM_TYPE VolumeFilesystemType
);

VOID
PtInstanceTeardownStart(
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_ FLT_INSTANCE_TEARDOWN_FLAGS Flags
);

VOID
PtInstanceTeardownComplete(
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_ FLT_INSTANCE_TEARDOWN_FLAGS Flags
);

NTSTATUS
PtUnload(
    _In_ FLT_FILTER_UNLOAD_FLAGS Flags
);

NTSTATUS
PtInstanceQueryTeardown(
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_ FLT_INSTANCE_QUERY_TEARDOWN_FLAGS Flags
);

FLT_PREOP_CALLBACK_STATUS
PtPreOperationPassThrough(
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _Flt_CompletionContext_Outptr_ PVOID* CompletionContext
);

VOID
PtOperationStatusCallback(
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_ PFLT_IO_PARAMETER_BLOCK ParameterSnapshot,
    _In_ NTSTATUS OperationStatus,
    _In_ PVOID RequesterContext
);

FLT_POSTOP_CALLBACK_STATUS
PtPostOperationPassThrough(
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_opt_ PVOID CompletionContext,
    _In_ FLT_POST_OPERATION_FLAGS Flags
);

FLT_PREOP_CALLBACK_STATUS
PtPreOperationNoPostOperationPassThrough(
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _Flt_CompletionContext_Outptr_ PVOID* CompletionContext
);

BOOLEAN
PtDoRequestOperationStatus(
    _In_ PFLT_CALLBACK_DATA Data
);

//
//  Assign text sections for each routine.
//

#ifdef ALLOC_PRAGMA
#pragma alloc_text(INIT, DriverEntry)
#pragma alloc_text(PAGE, PtUnload)
#pragma alloc_text(PAGE, PtInstanceQueryTeardown)
#pragma alloc_text(PAGE, PtInstanceSetup)
#pragma alloc_text(PAGE, PtInstanceTeardownStart)
#pragma alloc_text(PAGE, PtInstanceTeardownComplete)
#endif

//
//  operation registration
//

CONST FLT_OPERATION_REGISTRATION Callbacks[] = {
    { IRP_MJ_CREATE,
      0,
      PtPreOperationPassThrough,
      PtPostOperationPassThrough },

    { IRP_MJ_CREATE_NAMED_PIPE,
      0,
      PtPreOperationPassThrough,
      PtPostOperationPassThrough },

    { IRP_MJ_CLOSE,
      0,
      PtPreOperationPassThrough,
      PtPostOperationPassThrough },

    { IRP_MJ_READ,
      0,
      PtPreOperationPassThrough,
      PtPostOperationPassThrough },

    { IRP_MJ_WRITE,
      0,
      PtPreOperationPassThrough,
      PtPostOperationPassThrough },

    { IRP_MJ_QUERY_INFORMATION,
      0,
      PtPreOperationPassThrough,
      PtPostOperationPassThrough },

    { IRP_MJ_SET_INFORMATION,
      0,
      PtPreOperationPassThrough,
      PtPostOperationPassThrough },

    { IRP_MJ_QUERY_VOLUME_INFORMATION,
      0,
      PtPreOperationPassThrough,
      PtPostOperationPassThrough },

    { IRP_MJ_SET_VOLUME_INFORMATION,
      0,
      PtPreOperationPassThrough,
      PtPostOperationPassThrough },

    { IRP_MJ_DIRECTORY_CONTROL,
      0,
      PtPreOperationPassThrough,
      PtPostOperationPassThrough },

    { IRP_MJ_FILE_SYSTEM_CONTROL,
      0,
      PtPreOperationPassThrough,
      PtPostOperationPassThrough },

    { IRP_MJ_OPERATION_END }
};

//  This defines what we want to filter with FltMgr
//

CONST FLT_REGISTRATION FilterRegistration = {

    sizeof(FLT_REGISTRATION),         //  Size
    FLT_REGISTRATION_VERSION,           //  Version
    0,                                  //  Flags

    NULL,                               //  Context
    Callbacks,                          //  Operation callbacks

    PtUnload,                           //  MiniFilterUnload

    PtInstanceSetup,                    //  InstanceSetup
    PtInstanceQueryTeardown,            //  InstanceQueryTeardown
    PtInstanceTeardownStart,            //  InstanceTeardownStart
    PtInstanceTeardownComplete,         //  InstanceTeardownComplete

    NULL,                               //  GenerateFileName
    NULL,                               //  GenerateDestinationFileName
    NULL                                //  NormalizeNameComponent

};

/*************************************************************************
    MiniFilter initialization and unload routines.
*************************************************************************/

NTSTATUS
DriverEntry(
    _In_ PDRIVER_OBJECT DriverObject,
    _In_ PUNICODE_STRING RegistryPath
) {
    NTSTATUS status;
    PSECURITY_DESCRIPTOR sd;
    OBJECT_ATTRIBUTES oa;
    UNICODE_STRING uniString;

    UNREFERENCED_PARAMETER(RegistryPath);

    DbgPrint("############################### PassThrough!DriverEntry: Entered ###############################\n");

    PassReadCfg();

    PassThroughData.DriverObject = DriverObject;

    DbgPrint("### PassThrough!FltRegisterFilter\n");
    status = FltRegisterFilter(DriverObject,
        &FilterRegistration,
        &PassThroughData.Filter);

    FLT_ASSERT(NT_SUCCESS(status));
    if (!NT_SUCCESS(status)) { FltUnregisterFilter(PassThroughData.Filter); }

    DbgPrint("### PassThrough!FltBuildDefaultSecurityDescriptor\n");
    status = FltBuildDefaultSecurityDescriptor(&sd, FLT_PORT_ALL_ACCESS);
    FLT_ASSERT(NT_SUCCESS(status));

    RtlInitUnicodeString(&uniString, PASSFLT_PORT_NAME);

    DbgPrint("### PassThrough!InitializeObjectAttributes\n");
    InitializeObjectAttributes(&oa,
        &uniString,
        OBJ_KERNEL_HANDLE | OBJ_CASE_INSENSITIVE,
        NULL,
        sd);

    PassThroughData.ServerPort = NULL;
    PassThroughData.ClientPort = NULL;

    DbgPrint("### PassThrough!FltCreateCommunicationPort\n");
    status = FltCreateCommunicationPort(PassThroughData.Filter,
        &PassThroughData.ServerPort,
        &oa,
        NULL,
        PassConnect,
        PassDisconnect,
        PassMessage,
        1);
    FLT_ASSERT(NT_SUCCESS(status));

    DbgPrint("### PassThrough!FltFreeSecurityDescriptor\n");
    FltFreeSecurityDescriptor(sd);

    if (!NT_SUCCESS(status)) {
        //leave;
    }

    DbgPrint("### PassThrough!FltStartFiltering\n");
    status = FltStartFiltering(PassThroughData.Filter);
    FLT_ASSERT(NT_SUCCESS(status));

    if (!NT_SUCCESS(status)) { FltUnregisterFilter(PassThroughData.Filter); }

    return status;
}

NTSTATUS PtUnload(_In_ FLT_FILTER_UNLOAD_FLAGS Flags) {
    UNREFERENCED_PARAMETER(Flags);
    PAGED_CODE();

    DbgPrint("### PassThrough!PtUnload: Entered\n");

    FltCloseCommunicationPort(PassThroughData.ServerPort);
    DbgPrint("### PassThrough!FltCloseCommunicationPort\n");

    FltUnregisterFilter(PassThroughData.Filter);
    DbgPrint("### PassThrough!FltUnregisterFilter\n");

    return STATUS_SUCCESS;
}

/*************************************************************************
    MiniFilter callback routines.
*************************************************************************/

DECLARE_GLOBAL_CONST_UNICODE_STRING(gcookie_str, L"\\Device\\HarddiskVolume2\\google_cookies.txt");

FLT_PREOP_CALLBACK_STATUS
PtPreOperationPassThrough(
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _Flt_CompletionContext_Outptr_ PVOID* CompletionContext
)
/*++

    This routine is the main pre-operation dispatch routine for this
    miniFilter. Since this is just a simple passThrough miniFilter it
    does not do anything with the callbackData but rather return
    FLT_PREOP_SUCCESS_WITH_CALLBACK thereby passing it down to the next
    miniFilter in the chain.

    Data - Pointer to the filter callbackData that is passed to us.

    FltObjects - Pointer to the FLT_RELATED_OBJECTS data structure containing
        opaque handles to this filter, instance, its associated volume and
        file object.

    CompletionContext - The context for the completion routine for this
        operation.
--*/
{
    UNREFERENCED_PARAMETER(FltObjects);
    UNREFERENCED_PARAMETER(CompletionContext);

    NTSTATUS status;

    PPROTECTED_FILES flist_ptr = FltProtectedFiles;
    while (flist_ptr != NULL) {
        PFLT_FILE_NAME_INFORMATION nameInfo = NULL;
        status = FltGetFileNameInformation(Data, FLT_FILE_NAME_NORMALIZED, &nameInfo);
        if (status == STATUS_SUCCESS) {
            BOOLEAN comp_res = RtlEqualUnicodeString(&nameInfo->Name, &flist_ptr->f_name, TRUE);
            if (comp_res == TRUE) {

                DbgPrint("### Fname %wZ, volume %wZ\n", nameInfo->Name, nameInfo->Volume);

                Data->IoStatus.Status = STATUS_ACCESS_DENIED;
                return FLT_PREOP_COMPLETE;
            }
        }
        flist_ptr = flist_ptr->f_next;
    }

    return FLT_PREOP_SUCCESS_WITH_CALLBACK;
}

NTSTATUS
PassConnect(
    _In_ PFLT_PORT ClientPort,
    _In_ PVOID ServerPortCookie,
    _In_reads_bytes_(SizeOfContext) PVOID ConnectionContext,
    _In_ ULONG SizeOfContext,
    _Flt_ConnectionCookie_Outptr_ PVOID* ConnectionCookie
)
/*++

Routine Description

    This is called when user-mode connects to the server
    port - to establish a connection

Arguments

    ClientPort - This is the pointer to the client port that
        will be used to send messages from the filter.
    ServerPortCookie - unused
    ConnectionContext - unused
    SizeofContext   - unused
    ConnectionCookie - unused

Return Value

    STATUS_SUCCESS - to accept the connection
--*/
{

    PAGED_CODE();

    UNREFERENCED_PARAMETER(ServerPortCookie);
    UNREFERENCED_PARAMETER(ConnectionContext);
    UNREFERENCED_PARAMETER(SizeOfContext);
    UNREFERENCED_PARAMETER(ConnectionCookie);

    DbgPrint("### PassThrough!PassConnect: Entered\n");

    FLT_ASSERT(PassThroughData.ClientPort == NULL);
    PassThroughData.ClientPort = ClientPort;
    return STATUS_SUCCESS;
}


VOID
PassDisconnect(
    _In_opt_ PVOID ConnectionCookie
)
/*++
    This is called when the connection is torn-down. We use it to close our handle to the connection. ConnectionCookie - unused
--*/
{
    PAGED_CODE();
    UNREFERENCED_PARAMETER(ConnectionCookie);

    DbgPrint("### PassThrough!PassDisconnect: Entered\n");

    if (PassThroughData.ClientPort != NULL) {
        DbgPrint("### PassThrough!FltCloseClientPort\n");
        FltCloseClientPort(PassThroughData.Filter, &PassThroughData.ClientPort);
        DbgPrint("### PassThrough!FltCloseClientPort PASSED\n");
    }
}

DECLARE_GLOBAL_CONST_UNICODE_STRING(cmdupd_str, L"updfcfg");

NTSTATUS
PassMessage(
    _In_ PVOID ConnectionCookie,
    _In_reads_bytes_opt_(InputBufferSize) PVOID InputBuffer,
    _In_ ULONG InputBufferSize,
    _Out_writes_bytes_to_opt_(OutputBufferSize, *ReturnOutputBufferLength) PVOID OutputBuffer,
    _In_ ULONG OutputBufferSize,
    _Out_ PULONG ReturnOutputBufferLength
)
/*++
    This is called whenever a user mode application wishes to communicate
    with this minifilter.

    ConnectionCookie - unused
    InputBuffer - A buffer containing input data, can be NULL if there
        is no input data.
    InputBufferSize - The size in bytes of the InputBuffer.
    OutputBuffer - A buffer provided by the application that originated
        the communication in which to store data to be returned to this
        application.
    OutputBufferSize - The size in bytes of the OutputBuffer.
    ReturnOutputBufferSize - The size in bytes of meaningful data
        returned in the OutputBuffer.

Return Value:

    Returns the status of processing the message.

--*/
{
    NTSTATUS status = STATUS_SUCCESS;
    //PASSTHROUGH_COMMAND command;

    PAGED_CODE();

    UNREFERENCED_PARAMETER(ConnectionCookie);
    UNREFERENCED_PARAMETER(ReturnOutputBufferLength);
    UNREFERENCED_PARAMETER(OutputBufferSize);
    UNREFERENCED_PARAMETER(OutputBuffer);
    UNREFERENCED_PARAMETER(InputBufferSize);

    DbgPrint("### PassThrough!PassMessage: Entered\n");

    //                      **** PLEASE READ ****
    //  The INPUT and OUTPUT buffers are raw user mode addresses.  The filter
    //  manager has already done a ProbedForRead (on InputBuffer) and
    //  ProbedForWrite (on OutputBuffer) which guarentees they are valid
    //  addresses based on the access (user mode vs. kernel mode).  The
    //  minifilter does not need to do their own probe.
    //
    //  The filter manager is NOT doing any alignment checking on the pointers.
    //  The minifilter must do this themselves if they care (see below).
    //
    //  The minifilter MUST continue to use a try/except around any access to
    //  these buffers.


    DbgPrint("### PassThrough!PassMessage: %s\n", (PCHAR)InputBuffer);
    ANSI_STRING AS;
    UNICODE_STRING US;
    RtlInitAnsiString(&AS, InputBuffer);
    RtlAnsiStringToUnicodeString(&US, &AS, TRUE);

    BOOLEAN comp_res = RtlEqualUnicodeString(&cmdupd_str, &US, TRUE);
    if (comp_res == TRUE) {
        DbgPrint("### UpdateConfig cmd\n");
        PassUpdateCfg();
    }

    return status;
}

VOID PassReadCfg() {
    UNICODE_STRING     uniName;
    OBJECT_ATTRIBUTES  objAttr;

    RtlInitUnicodeString(&uniName, L"\\DosDevices\\C:\\bugav.txt");  // or L"\\SystemRoot\\example.txt"
    InitializeObjectAttributes(&objAttr, &uniName, OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE, NULL, NULL);

    HANDLE   handle;
    NTSTATUS ntstatus;
    IO_STATUS_BLOCK    ioStatusBlock;

#define  BUFF_SIZE 512
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
            PassParseCfg(buffer);

        }
        ZwClose(handle);
    }
}

VOID PassParseCfg(CHAR* cfg_buff) {
    DbgPrint("### PassParseCfg\n");
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
            PassPushProtectedFileCfg(US);
            bptr = i + 1;
        }
    }

    PassDumpProtectedFileCfg();
}

VOID PassPushProtectedFileCfg(UNICODE_STRING newstr) {
    DbgPrint("### PassPushProtectedFileCfg\n");
    PPROTECTED_FILES flist_ptr = FltProtectedFiles;
    if (FltProtectedFiles == NULL) {
        FltProtectedFiles = (PPROTECTED_FILES)ExAllocatePoolWithTag(NonPagedPool, sizeof(PROTECTED_FILES), '1liF');
        if (FltProtectedFiles != NULL) {
            FltProtectedFiles->f_next = NULL;
            FltProtectedFiles->f_prev = NULL;
            FltProtectedFiles->f_name = newstr;
            return;
        }
    }
    while (flist_ptr->f_next != NULL) { flist_ptr = flist_ptr->f_next; }
    flist_ptr->f_next = (PPROTECTED_FILES)ExAllocatePoolWithTag(NonPagedPool, sizeof(PROTECTED_FILES), '1liF');
    if (flist_ptr->f_next != NULL) {
        flist_ptr->f_next->f_next = NULL;
        flist_ptr->f_next->f_prev = flist_ptr;
        flist_ptr->f_next->f_name = newstr;
        return;
    }
}

VOID PassDumpProtectedFileCfg() {
    DbgPrint("### PassDumpProtectedFileCfg\n");
    PPROTECTED_FILES flist_ptr = FltProtectedFiles;
    while (flist_ptr != NULL) {
        DbgPrint("===== %wZ\n", flist_ptr->f_name);
        flist_ptr = flist_ptr->f_next;
    }
}

VOID PassDestroyProtectedFileCfg() {
    DbgPrint("### PassDestroyProtectedFileCfg\n");
    PPROTECTED_FILES flist_ptr = FltProtectedFiles;

    if (flist_ptr == NULL) { return; }

    while (flist_ptr->f_next != NULL) { flist_ptr = flist_ptr->f_next; }

    while (flist_ptr->f_prev != NULL) {
        flist_ptr = flist_ptr->f_prev;
        ExFreePoolWithTag(flist_ptr->f_next, '1liF');
    }
    ExFreePoolWithTag(flist_ptr, '1liF');
    FltProtectedFiles = NULL;
}

VOID PassUpdateCfg() {
    PassDestroyProtectedFileCfg();
    PassReadCfg();
}

#pragma region kernel_other

VOID
PtOperationStatusCallback(
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_ PFLT_IO_PARAMETER_BLOCK ParameterSnapshot,
    _In_ NTSTATUS OperationStatus,
    _In_ PVOID RequesterContext
) {
    UNREFERENCED_PARAMETER(FltObjects);

    DbgPrint("############################### PassThrough!PtOperationStatusCallback: Entered ###############################\n");

    DbgPrint("############################### PassThrough!PtOperationStatusCallback: Status=%08x ctx=%p IrpMj=%02x.%02x \"%s\" ###############################\n",
        OperationStatus,
        RequesterContext,
        ParameterSnapshot->MajorFunction,
        ParameterSnapshot->MinorFunction,
        FltGetIrpName(ParameterSnapshot->MajorFunction));
}


FLT_POSTOP_CALLBACK_STATUS
PtPostOperationPassThrough(
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_opt_ PVOID CompletionContext,
    _In_ FLT_POST_OPERATION_FLAGS Flags
) {
    UNREFERENCED_PARAMETER(Data);
    UNREFERENCED_PARAMETER(FltObjects);
    UNREFERENCED_PARAMETER(CompletionContext);
    UNREFERENCED_PARAMETER(Flags);

    return FLT_POSTOP_FINISHED_PROCESSING;
}


FLT_PREOP_CALLBACK_STATUS
PtPreOperationNoPostOperationPassThrough(
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _Flt_CompletionContext_Outptr_ PVOID* CompletionContext
) {
    UNREFERENCED_PARAMETER(Data);
    UNREFERENCED_PARAMETER(FltObjects);
    UNREFERENCED_PARAMETER(CompletionContext);

    DbgPrint("############################### PassThrough!PtPreOperationNoPostOperationPassThrough: Entered ###############################\n");

    return FLT_PREOP_SUCCESS_NO_CALLBACK;
}


BOOLEAN
PtDoRequestOperationStatus(
    _In_ PFLT_CALLBACK_DATA Data
)
/*++
    This identifies those operations we want the operation status for.  These
    are typically operations that return STATUS_PENDING as a normal completion
    status.
--*/
{
    PFLT_IO_PARAMETER_BLOCK iopb = Data->Iopb;
    return (BOOLEAN)
        //  Check for oplock operations
        (((iopb->MajorFunction == IRP_MJ_FILE_SYSTEM_CONTROL) &&
        ((iopb->Parameters.FileSystemControl.Common.FsControlCode == FSCTL_REQUEST_FILTER_OPLOCK) ||
            (iopb->Parameters.FileSystemControl.Common.FsControlCode == FSCTL_REQUEST_BATCH_OPLOCK) ||
            (iopb->Parameters.FileSystemControl.Common.FsControlCode == FSCTL_REQUEST_OPLOCK_LEVEL_1) ||
            (iopb->Parameters.FileSystemControl.Common.FsControlCode == FSCTL_REQUEST_OPLOCK_LEVEL_2)))
            ||
            //    Check for directy change notification
            ((iopb->MajorFunction == IRP_MJ_DIRECTORY_CONTROL) &&
            (iopb->MinorFunction == IRP_MN_NOTIFY_CHANGE_DIRECTORY))
            );
}


NTSTATUS
PtInstanceSetup(
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_ FLT_INSTANCE_SETUP_FLAGS Flags,
    _In_ DEVICE_TYPE VolumeDeviceType,
    _In_ FLT_FILESYSTEM_TYPE VolumeFilesystemType
)
/*++
    This routine is called whenever a new instance is created on a volume. This
    gives us a chance to decide if we need to attach to this volume or not.
    If this routine is not defined in the registration structure, automatic
    instances are alwasys created.
--*/
{
    UNREFERENCED_PARAMETER(FltObjects);
    UNREFERENCED_PARAMETER(Flags);
    UNREFERENCED_PARAMETER(VolumeDeviceType);
    UNREFERENCED_PARAMETER(VolumeFilesystemType);
    PAGED_CODE();
    PT_DBG_PRINT(PTDBG_TRACE_ROUTINES, ("PassThrough!PtInstanceSetup: Entered\n"));
    return STATUS_SUCCESS;
}


NTSTATUS
PtInstanceQueryTeardown(
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_ FLT_INSTANCE_QUERY_TEARDOWN_FLAGS Flags
)
/*++
    This is called when an instance is being manually deleted by a
    call to FltDetachVolume or FilterDetach thereby giving us a
    chance to fail that detach request.
--*/
{
    UNREFERENCED_PARAMETER(FltObjects);
    UNREFERENCED_PARAMETER(Flags);
    PAGED_CODE();
    PT_DBG_PRINT(PTDBG_TRACE_ROUTINES, ("PassThrough!PtInstanceQueryTeardown: Entered\n"));
    return STATUS_SUCCESS;
}


VOID
PtInstanceTeardownStart(
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_ FLT_INSTANCE_TEARDOWN_FLAGS Flags
)
/*++
    This routine is called at the start of instance teardown.

    FltObjects - Pointer to the FLT_RELATED_OBJECTS data structure containing
        opaque handles to this filter, instance and its associated volume.
    Flags - Reason why this instance is been deleted.
--*/
{
    UNREFERENCED_PARAMETER(FltObjects);
    UNREFERENCED_PARAMETER(Flags);
    PAGED_CODE();
    PT_DBG_PRINT(PTDBG_TRACE_ROUTINES, ("PassThrough!PtInstanceTeardownStart: Entered\n"));
}


VOID
PtInstanceTeardownComplete(
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_ FLT_INSTANCE_TEARDOWN_FLAGS Flags
)
/*++
    This routine is called at the end of instance teardown.
--*/
{
    UNREFERENCED_PARAMETER(FltObjects);
    UNREFERENCED_PARAMETER(Flags);
    PAGED_CODE();
    PT_DBG_PRINT(PTDBG_TRACE_ROUTINES, ("PassThrough!PtInstanceTeardownComplete: Entered\n"));
}

#pragma endregion