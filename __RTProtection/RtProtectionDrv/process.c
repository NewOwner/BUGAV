#include <ntddk.h>
#include "RtProtectionDrv.h"
#include "NtDefinitions.h"
#include "process.h"

#define SIOCTL_KDPRINT(_x_) \
                DbgPrint("SIOCTL.SYS: ");\
                DbgPrint _x_;

NTSTATUS InitializeProcessNotify() {
    SIOCTL_KDPRINT(("ProcMonDrv ===> InitializeProcessNotify\n"));
    NTSTATUS status = STATUS_UNSUCCESSFUL;

    status = PsSetCreateProcessNotifyRoutine(&CreateProcessNotifyRoutine, FALSE);
    if (status == STATUS_SUCCESS) {
        status = PsSetLoadImageNotifyRoutine(&LoadImageNotifyRoutine);
    }
    if (status == STATUS_SUCCESS) {
    }
    DbgPrint("ProcMonDrv <=== InitializeProcessNotify\n");
    return status;
}

VOID CleanupProcessNotify() {
    DbgPrint("ProcMonDrv ===> CleanupProcessNotify\n");
    PsRemoveLoadImageNotifyRoutine(&LoadImageNotifyRoutine);
    PsSetCreateProcessNotifyRoutine(&CreateProcessNotifyRoutine, TRUE);

    DbgPrint("ProcMonDrv <=== CleanupProcessNotify\n");
}

PIRP cur_Irp = NULL;
VOID CreateProcessNotifyRoutine(IN HANDLE ParentId, IN HANDLE ProcessId, IN BOOLEAN Create) {
    UNREFERENCED_PARAMETER(ParentId);
    UNREFERENCED_PARAMETER(ProcessId);
    DbgPrint("ProcMonDrv ===> CreateProcessNotifyRoutine\n");
    DbgPrint("parentid: %d, processid: %d, create: %d\n", ParentId, ProcessId, Create);
    if (Create) {
    } else {
    }

    if (cur_Irp) {
        DbgPrint("!!!! IoCompleteRequest\n");
        PUCHAR                      OutputBuffer;
        OutputBuffer = (PUCHAR)cur_Irp->AssociatedIrp.SystemBuffer;
        CHAR data[100];
        //NEWPROC_INFO procInfo;
        //procInfo.ParentId = ParentId;
        //procInfo.ProcessId = ProcessId;
        //procInfo.Create = Create;

        ((PNEWPROC_INFO)data)->ParentId = ParentId;
        ((PNEWPROC_INFO)data)->ProcessId = ProcessId;
        ((PNEWPROC_INFO)data)->Create = Create;
    
        RtlCopyMemory(OutputBuffer, data, sizeof(NEWPROC_INFO));

        cur_Irp->IoStatus.Information = sizeof(NEWPROC_INFO);
        cur_Irp->IoStatus.Status = STATUS_SUCCESS;
        IoCompleteRequest(cur_Irp, IO_NO_INCREMENT);
        cur_Irp = NULL;
    }

    DbgPrint("ProcMonDrv <=== CreateProcessNotifyRoutine\n");
}

VOID LoadImageNotifyRoutine(IN PUNICODE_STRING FullImageName, IN HANDLE ProcessId, IN PIMAGE_INFO ImageInfo) {

    //DbgPrint("ProcMonDrv ===> LoadImageNotifyRoutine\n");

    // The FullImageName parameter can be NULL in cases in which the operating 
    // system is unable to obtain the full name of the image at process creation time.
    if (!FullImageName) {
        return;
    }

    // Handle is zero if the newly loaded image is a driver
    if (!ProcessId || ImageInfo->SystemModeImage) {
        return;
    }

    //DbgPrint("img loaded: %wZ\n", FullImageName);
    BOOLEAN Terminate = FALSE;

    if (Terminate) {
    }
    //DbgPrint("ProcMonDrv <=== LoadImageNotifyRoutine\n");
}