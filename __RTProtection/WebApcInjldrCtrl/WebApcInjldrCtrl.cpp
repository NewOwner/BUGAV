#include "WebApcInjldrCtrl.h"

GUID ProviderGuid = {
  0xa4b4ba50, 0xa667, 0x43f5, { 0x91, 0x9b, 0x1e, 0x52, 0xa6, 0xd6, 0x9b, 0xd5 }
};

//
// GUID:
//   {53d82d11-cede-4dff-8eb4-f06631800128}
//

GUID SessionGuid = {
  0x53d82d11, 0xcede, 0x4dff, { 0x8e, 0xb4, 0xf0, 0x66, 0x31, 0x80, 0x1, 0x28 }
};

TCHAR SessionName[] = TEXT("InjSession");

VOID WINAPI TraceEventCallback(_In_ PEVENT_RECORD EventRecord) {
    //if (!EventRecord->UserData)
//{
//  return;
//}

//
// TODO: Check that EventRecord contains only WCHAR string.
//

//std::string hex_str = "WSARecv ";
//hex_str += hexStr((BYTE*)EventRecord->UserData, 1024);
//std::cout
//  << " PID:" << EventRecord->EventHeader.ProcessId
//  << " TID:" << EventRecord->EventHeader.ThreadId
//  << " data:" << hex_str
//  << std::endl;


    std::string ansi_str((CHAR*)EventRecord->UserData);
    std::cout
        << "ANSI PID:" << EventRecord->EventHeader.ProcessId
        << " TID:" << EventRecord->EventHeader.ThreadId
        << " data:" << ansi_str
        << std::endl;

    //((WCHAR*)EventRecord->UserData)[1023] = 0;
    //std::wcout
    //  << L"WSTR PID:" << EventRecord->EventHeader.ProcessId
    //  << L" TID:" << EventRecord->EventHeader.ThreadId
    //  << L" data:" << (WCHAR*)EventRecord->UserData
    //  << std::endl;

}

ULONG NTAPI TraceStart(VOID) {
    //
  // Start new trace session.
  // For an awesome blogpost on ETW API, see:
  // https://caseymuratori.com/blog_0025
  //

    ULONG ErrorCode;

    TRACEHANDLE TraceSessionHandle = INVALID_PROCESSTRACE_HANDLE;

    EVENT_TRACE_LOGFILE TraceLogfile = { 0 };
    TRACEHANDLE TraceHandle = 0;

    BYTE Buffer[sizeof(EVENT_TRACE_PROPERTIES) + 4096];
    RtlZeroMemory(Buffer, sizeof(Buffer));

    PEVENT_TRACE_PROPERTIES EventTraceProperties = (PEVENT_TRACE_PROPERTIES)Buffer;
    EventTraceProperties->Wnode.BufferSize = sizeof(Buffer);
    EventTraceProperties->Wnode.ClientContext = 1; // Use QueryPerformanceCounter, see MSDN
    EventTraceProperties->Wnode.Flags = WNODE_FLAG_TRACED_GUID;
    EventTraceProperties->LogFileMode = PROCESS_TRACE_MODE_REAL_TIME;
    EventTraceProperties->LoggerNameOffset = sizeof(EVENT_TRACE_PROPERTIES);

    ErrorCode = StartTrace(&TraceSessionHandle, SessionName, EventTraceProperties);
    if (ErrorCode != ERROR_SUCCESS) {
        goto Exit;
    }

    //
    // Enable tracing of our provider.
    //

    ErrorCode = EnableTrace(TRUE, 0, 0, &ProviderGuid, TraceSessionHandle);
    if (ErrorCode != ERROR_SUCCESS) {
        goto Exit;
    }

    TraceLogfile.LoggerName = SessionName;
    TraceLogfile.ProcessTraceMode = PROCESS_TRACE_MODE_EVENT_RECORD | PROCESS_TRACE_MODE_REAL_TIME;
    TraceLogfile.EventRecordCallback = &TraceEventCallback;

    //
    // Open real-time tracing session.
    //

    TraceHandle = OpenTrace(&TraceLogfile);
    if (TraceHandle == INVALID_PROCESSTRACE_HANDLE) {
        //
        // Synthetic error code.
        //
        ErrorCode = ERROR_FUNCTION_FAILED;
        goto Exit;
    }

    //
    // Process trace events.  This call is blocking.
    //

    ErrorCode = ProcessTrace(&TraceHandle, 1, NULL, NULL);

Exit:
    if (TraceHandle) {
        CloseTrace(TraceHandle);
    }

    if (TraceSessionHandle) {
        CloseTrace(TraceSessionHandle);
    }

    RtlZeroMemory(Buffer, sizeof(Buffer));
    EventTraceProperties->Wnode.BufferSize = sizeof(Buffer);
    StopTrace(0, SessionName, EventTraceProperties);

    if (ErrorCode != ERROR_SUCCESS) {
        printf("Error: %08x\n", ErrorCode);
    }

    return ErrorCode;
}

VOID NTAPI TraceStop(VOID) {
    BYTE Buffer[sizeof(EVENT_TRACE_PROPERTIES) + 4096];
    RtlZeroMemory(Buffer, sizeof(Buffer));

    PEVENT_TRACE_PROPERTIES EventTraceProperties = (PEVENT_TRACE_PROPERTIES)Buffer;
    EventTraceProperties->Wnode.BufferSize = sizeof(Buffer);

    StopTrace(0, SessionName, EventTraceProperties);
}

BOOLEAN DoInstallUninstall(_In_ BOOLEAN Install, LPCTSTR drvName, CHAR basicOrWeb) {
    TCHAR driverLocation[MAX_PATH] = { 0 };

    if (basicOrWeb == 'b') {
        if (!SetupDriverNameBasic(driverLocation, sizeof(driverLocation))) {
            return FALSE;
        }
    } else if (basicOrWeb == 'w') {
        if (!SetupDriverNameWeb(driverLocation, sizeof(driverLocation))) {
            return FALSE;
        }
    }

    if (Install) {
        if (!ManageDriver(drvName,
            driverLocation,
            DRIVER_FUNC_INSTALL)) {
            printf("Unable to install driver.\n");
            ManageDriver(drvName,
                driverLocation,
                DRIVER_FUNC_REMOVE);

            return FALSE;
        }
    } else {
        ManageDriver(drvName,
            driverLocation,
            DRIVER_FUNC_REMOVE);
    }

    return TRUE;
}

WebApcInjldrCtrl::WebApcInjldrCtrl()
    :
    installed(false),
    session_started(false)
{}
WebApcInjldrCtrl::~WebApcInjldrCtrl() {}

BOOL WebApcInjldrCtrl::Load() {
    if (installed) {
        std::cout << "driver already installed" << std::endl;
        return EXIT_SUCCESS;
    }
    TraceStop();
    std::cout << "Installing driver..." << std::endl;

    if (DoInstallUninstall(TRUE, DRIVER_NAME_WEB, 'w')) {
        std::cout << "Web Driver installed!" << std::endl;
        installed = TRUE;
    } else {
        std::cout << "Error!" << std::endl;
        installed = FALSE;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

BOOL WebApcInjldrCtrl::StartSession() {
    if (!installed) {
        std::cout << "driver not installed!" << std::endl;
        return EXIT_SUCCESS;
    }

    std::cout << "Starting tracing session..." << std::endl;

    ULONG ErrorCode = TraceStart();

    if (ErrorCode == ERROR_SUCCESS) {
        session_started = true;
    } else {
        session_started = false;
    }
    return ErrorCode;
}

BOOL WebApcInjldrCtrl::StopSession() {
    TraceStop();
    session_started = false;
    std::cout << "Uninstalling driver..." << std::endl;
    installed = false; 
    return DoInstallUninstall(FALSE, DRIVER_NAME_WEB, 'w');;
    
}
