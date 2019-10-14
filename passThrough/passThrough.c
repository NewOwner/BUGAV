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

    { IRP_MJ_QUERY_EA,
      0,
      PtPreOperationPassThrough,
      PtPostOperationPassThrough },

    { IRP_MJ_SET_EA,
      0,
      PtPreOperationPassThrough,
      PtPostOperationPassThrough },

    { IRP_MJ_FLUSH_BUFFERS,
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


//
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
)
{
    NTSTATUS status;
    PSECURITY_DESCRIPTOR sd;
    OBJECT_ATTRIBUTES oa;
    UNICODE_STRING uniString;

    UNREFERENCED_PARAMETER(RegistryPath);

    DbgPrint("############################### PassThrough!DriverEntry: Entered ###############################\n");

    PassThroughData.DriverObject = DriverObject;

    status = FltRegisterFilter(DriverObject,
        &FilterRegistration,
        &PassThroughData.Filter);

    FLT_ASSERT(NT_SUCCESS(status));
    if (!NT_SUCCESS(status)) { FltUnregisterFilter(PassThroughData.Filter); }

    status = FltBuildDefaultSecurityDescriptor(&sd, FLT_PORT_ALL_ACCESS);

    RtlInitUnicodeString(&uniString, PASSFLT_PORT_NAME);

    InitializeObjectAttributes(&oa,
        &uniString,
        OBJ_KERNEL_HANDLE | OBJ_CASE_INSENSITIVE,
        NULL,
        sd);

    status = FltCreateCommunicationPort(PassThroughData.Filter,
        &PassThroughData.ServerPort,
        &oa,
        NULL,
        PassConnect,
        PassDisconnect,
        PassMessage,
        1);

    FltFreeSecurityDescriptor(sd);

    if (!NT_SUCCESS(status)) {
        //leave;
    }

    status = FltStartFiltering(PassThroughData.Filter);

    if (!NT_SUCCESS(status)) { FltUnregisterFilter(PassThroughData.Filter); }

    return status;
}

NTSTATUS PtUnload(_In_ FLT_FILTER_UNLOAD_FLAGS Flags) {
    UNREFERENCED_PARAMETER(Flags);
    PAGED_CODE();
    PT_DBG_PRINT(PTDBG_TRACE_ROUTINES, ("PassThrough!PtUnload: Entered\n"));
    FltUnregisterFilter(PassThroughData.Filter);

    return STATUS_SUCCESS;
}

/*************************************************************************
    MiniFilter callback routines.
*************************************************************************/

DECLARE_GLOBAL_CONST_UNICODE_STRING(gcookie_str, L"\\google_cookies.txt");

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

    PUNICODE_STRING f_name = &Data->Iopb->TargetFileObject->FileName;
    if (f_name->Buffer != NULL) {
        BOOLEAN comp_res = RtlEqualUnicodeString(f_name, &gcookie_str, TRUE);

        if (comp_res == TRUE) {
            PFLT_FILE_NAME_INFORMATION nameInfo = NULL;
            status = FltGetFileNameInformation(Data, FLT_FILE_NAME_NORMALIZED, &nameInfo);
            DbgPrint("### Fname %wZ, volume %wZ\n", f_name, nameInfo->Volume);

            Data->IoStatus.Status = STATUS_ACCESS_DENIED;
            return FLT_PREOP_COMPLETE;
        }

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
    FltCloseClientPort(PassThroughData.Filter, &PassThroughData.ClientPort);
}

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
    OperationCode - An identifier describing what type of message this
        is.  These codes are defined by the MiniFilter.
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
    PASSTHROUGH_COMMAND command;

    PAGED_CODE();

    UNREFERENCED_PARAMETER(ConnectionCookie);
    UNREFERENCED_PARAMETER(ReturnOutputBufferLength);

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

    if ((InputBuffer != NULL) &&
        (InputBufferSize >= (FIELD_OFFSET(COMMAND_MESSAGE, Command) +
            sizeof(PASSTHROUGH_COMMAND)))) {

            //  Probe and capture input message: the message is raw user mode
            //  buffer, so need to protect with exception handler

            command = ((PCOMMAND_MESSAGE)InputBuffer)->Command;

        //  Return as many log records as can fit into the OutputBuffer

        if ((OutputBuffer == NULL) || (OutputBufferSize == 0)) {

            status = STATUS_INVALID_PARAMETER;
        }

        PassUpdateCfg();
    }
    else {
        status = STATUS_INVALID_PARAMETER;
    }
    return status;
}

VOID PassUpdateCfg() {

}

#pragma region kernel_other

VOID
PtOperationStatusCallback(
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_ PFLT_IO_PARAMETER_BLOCK ParameterSnapshot,
    _In_ NTSTATUS OperationStatus,
    _In_ PVOID RequesterContext
)
{
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
)
{
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
)
{
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