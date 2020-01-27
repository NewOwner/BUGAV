#include <fltKernel.h>
#include <dontuse.h>
#include <suppress.h>

#include "FilterFileDrv.h"

#define SIOCTL_KDPRINT(_x_) \
                DbgPrint("NewFileDrv.sys: ");\
                DbgPrint _x_;

#define PASSFLT_PORT_NAME                   L"\\NewFilePort"

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

FLT_PREOP_CALLBACK_STATUS
PtPreOperationPassThrough(
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _Flt_CompletionContext_Outptr_ PVOID* CompletionContext
);

#pragma region kernel_declaration

NTSTATUS
PassConnect(
    _In_ PFLT_PORT ClientPort,
    _In_ PVOID ServerPortCookie,
    _In_reads_bytes_(SizeOfContext) PVOID ConnectionContext,
    _In_ ULONG SizeOfContext,
    _Flt_ConnectionCookie_Outptr_ PVOID* ConnectionCookie
);

VOID PassDisconnect(_In_opt_ PVOID ConnectionCookie);

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

//  Assign text sections for each routine.
#ifdef ALLOC_PRAGMA
#pragma alloc_text(INIT, DriverEntry)
#pragma alloc_text(PAGE, PtUnload)
#pragma alloc_text(PAGE, PtInstanceQueryTeardown)
#pragma alloc_text(PAGE, PtInstanceSetup)
#pragma alloc_text(PAGE, PtInstanceTeardownStart)
#pragma alloc_text(PAGE, PtInstanceTeardownComplete)
#endif

//  operation registration
CONST FLT_OPERATION_REGISTRATION Callbacks[] = {
    { IRP_MJ_WRITE,
      0,
      PtPreOperationPassThrough,
      PtPostOperationPassThrough },

    { IRP_MJ_OPERATION_END }
};

//  This defines what we want to filter with FltMgr
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

#pragma endregion

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

    DbgPrint("## RtNewFile!DriverEntry: Entered ###############################\n");

    PassThroughData.DriverObject = DriverObject;

    DbgPrint("### FilterFileDrv!FltRegisterFilter\n");
    status = FltRegisterFilter(DriverObject,
        &FilterRegistration,
        &PassThroughData.Filter);

    //FLT_ASSERT(NT_SUCCESS(status));
    if (!NT_SUCCESS(status)) { return status;}

    DbgPrint("### FilterFileDrv!FltBuildDefaultSecurityDescriptor\n");
    status = FltBuildDefaultSecurityDescriptor(&sd, FLT_PORT_ALL_ACCESS);
    FLT_ASSERT(NT_SUCCESS(status));

    RtlInitUnicodeString(&uniString, PASSFLT_PORT_NAME);

    DbgPrint("### FilterFileDrv!InitializeObjectAttributes\n");
    InitializeObjectAttributes(&oa,
        &uniString,
        OBJ_KERNEL_HANDLE | OBJ_CASE_INSENSITIVE,
        NULL,
        sd);

    PassThroughData.ServerPort = NULL;
    PassThroughData.ClientPort = NULL;

    DbgPrint("### FilterFileDrv!FltCreateCommunicationPort\n");
    status = FltCreateCommunicationPort(PassThroughData.Filter,
        &PassThroughData.ServerPort,
        &oa,
        NULL,
        PassConnect,
        PassDisconnect,
        PassMessage,
        1);
    FLT_ASSERT(NT_SUCCESS(status));

    DbgPrint("### FilterFileDrv!FltFreeSecurityDescriptor\n");
    FltFreeSecurityDescriptor(sd);

    if (!NT_SUCCESS(status)) {
        //leave;
    }

    DbgPrint("### FilterFileDrv!FltStartFiltering\n");
    status = FltStartFiltering(PassThroughData.Filter);
    FLT_ASSERT(NT_SUCCESS(status));

    if (!NT_SUCCESS(status)) { FltUnregisterFilter(PassThroughData.Filter); }

    return status;
}

/*************************************************************************
    MiniFilter callback routines.
*************************************************************************/

DECLARE_GLOBAL_CONST_UNICODE_STRING(exe_str, L"exe");
DECLARE_GLOBAL_CONST_UNICODE_STRING(dll_str, L"dll");
DECLARE_GLOBAL_CONST_UNICODE_STRING(sys_str, L"sys");

FLT_PREOP_CALLBACK_STATUS
PtPreOperationPassThrough(
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _Flt_CompletionContext_Outptr_ PVOID* CompletionContext
)
{
    UNREFERENCED_PARAMETER(Data);

    UNREFERENCED_PARAMETER(FltObjects);
    UNREFERENCED_PARAMETER(CompletionContext);

   

    return FLT_PREOP_SUCCESS_WITH_CALLBACK;
}

FLT_POSTOP_CALLBACK_STATUS
PtPostOperationPassThrough(
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_opt_ PVOID CompletionContext,
    _In_ FLT_POST_OPERATION_FLAGS Flags
) {
    //UNREFERENCED_PARAMETER(Data);
    UNREFERENCED_PARAMETER(FltObjects);
    UNREFERENCED_PARAMETER(CompletionContext);
    UNREFERENCED_PARAMETER(Flags);

    NTSTATUS status;

    PFLT_FILE_NAME_INFORMATION nameInfo = NULL;
    status = FltGetFileNameInformation(Data, FLT_FILE_NAME_NORMALIZED | FLT_FILE_NAME_QUERY_FILESYSTEM_ONLY, &nameInfo);
    if (status == STATUS_SUCCESS) {
        status = FltParseFileNameInformation(nameInfo);
    }
    if (status == STATUS_SUCCESS && nameInfo) {
        BOOLEAN comp_res =
            RtlEqualUnicodeString(&nameInfo->Extension, &exe_str, TRUE) ||
            RtlEqualUnicodeString(&nameInfo->Extension, &dll_str, TRUE) ||
            RtlEqualUnicodeString(&nameInfo->Extension, &sys_str, TRUE);

        if (comp_res == TRUE) {
            if (PassThroughData.ClientPort) {

                ANSI_STRING AS;
                RtlUnicodeStringToAnsiString(&AS, &nameInfo->Name, TRUE);
                DbgPrint("### ANSI Fname %Z\n", &AS);

                FltSendMessage(
                    PassThroughData.Filter,
                    &PassThroughData.ClientPort,
                    AS.Buffer,
                    AS.Length,
                    NULL, 0, NULL);
            }
        }

        //Data->IoStatus.Status = STATUS_ACCESS_DENIED;
        //return FLT_PREOP_SUCCESS_WITH_CALLBACK;
        return FLT_POSTOP_FINISHED_PROCESSING;
    }

    return FLT_POSTOP_FINISHED_PROCESSING;
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
) {
    NTSTATUS status = STATUS_SUCCESS;

    PAGED_CODE();

    UNREFERENCED_PARAMETER(ConnectionCookie);
    UNREFERENCED_PARAMETER(ReturnOutputBufferLength);
    UNREFERENCED_PARAMETER(OutputBufferSize);
    UNREFERENCED_PARAMETER(OutputBuffer);
    UNREFERENCED_PARAMETER(InputBufferSize);

    DbgPrint("### FilterFileDrv!PassMessage: Entered\n");

    DbgPrint("### FilterFileDrv!PassMessage: %s\n", (PCHAR)InputBuffer);
    ANSI_STRING AS;
    UNICODE_STRING US;
    RtlInitAnsiString(&AS, InputBuffer);
    RtlAnsiStringToUnicodeString(&US, &AS, TRUE);

    BOOLEAN comp_res = RtlEqualUnicodeString(&cmdupd_str, &US, TRUE);
    if (comp_res == TRUE) {
        DbgPrint("### UpdateConfig cmd\n");
    }

    return status;
}

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

#pragma region kernel_other

NTSTATUS PtUnload(_In_ FLT_FILTER_UNLOAD_FLAGS Flags) {
    UNREFERENCED_PARAMETER(Flags);
    PAGED_CODE();

    DbgPrint("### FilterFileDrv!PtUnload: Entered\n");

    FltCloseCommunicationPort(PassThroughData.ServerPort);
    FltUnregisterFilter(PassThroughData.Filter);

    return STATUS_SUCCESS;
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
    ClientPort - This is the pointer to the client port that
        will be used to send messages from the filter.
    ServerPortCookie ConnectionContext SizeofContext  ConnectionCookie - unused
--*/
{

    PAGED_CODE();

    UNREFERENCED_PARAMETER(ServerPortCookie);
    UNREFERENCED_PARAMETER(ConnectionContext);
    UNREFERENCED_PARAMETER(SizeOfContext);
    UNREFERENCED_PARAMETER(ConnectionCookie);

    DbgPrint("### FilterFileDrv!PassConnect: Entered\n");

    FLT_ASSERT(PassThroughData.ClientPort == NULL);
    PassThroughData.ClientPort = ClientPort;
    return STATUS_SUCCESS;
}


VOID PassDisconnect(_In_opt_ PVOID ConnectionCookie) {
    PAGED_CODE();
    UNREFERENCED_PARAMETER(ConnectionCookie);

    DbgPrint("### FilterFileDrv!PassDisconnect: Entered\n");

    if (PassThroughData.ClientPort != NULL) {
        DbgPrint("### FilterFileDrv!FltCloseClientPort\n");
        FltCloseClientPort(PassThroughData.Filter, &PassThroughData.ClientPort);
        DbgPrint("### FilterFileDrv!FltCloseClientPort PASSED\n");
    }
}

VOID
PtOperationStatusCallback(
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_ PFLT_IO_PARAMETER_BLOCK ParameterSnapshot,
    _In_ NTSTATUS OperationStatus,
    _In_ PVOID RequesterContext
) {
    UNREFERENCED_PARAMETER(FltObjects);
    UNREFERENCED_PARAMETER(ParameterSnapshot);
    UNREFERENCED_PARAMETER(OperationStatus);
    UNREFERENCED_PARAMETER(RequesterContext);
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
    PT_DBG_PRINT(PTDBG_TRACE_ROUTINES, ("FilterFileDrv!PtInstanceSetup: Entered\n"));
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
    PT_DBG_PRINT(PTDBG_TRACE_ROUTINES, ("FilterFileDrv!PtInstanceQueryTeardown: Entered\n"));
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
    PT_DBG_PRINT(PTDBG_TRACE_ROUTINES, ("FilterFileDrv!PtInstanceTeardownStart: Entered\n"));
}


VOID
PtInstanceTeardownComplete(
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_ FLT_INSTANCE_TEARDOWN_FLAGS Flags
)
/*++ This routine is called at the end of instance teardown. --*/
{
    UNREFERENCED_PARAMETER(FltObjects);
    UNREFERENCED_PARAMETER(Flags);
    PAGED_CODE();
    PT_DBG_PRINT(PTDBG_TRACE_ROUTINES, ("FilterFileDrv!PtInstanceTeardownComplete: Entered\n"));
}

#pragma endregion