#pragma once

#define _ARM_WINAPI_PARTITION_DESKTOP_SDK_AVAILABLE 1

#include <stdio.h>
#include <windows.h>
#include <evntrace.h>
#include <evntcons.h>

#include "install.h"


#include <algorithm>
#include <iostream>
#include <iomanip>
#include <sstream>

//
// GUID:
//   {a4b4ba50-a667-43f5-919b-1e52a6d69bd5}
//

extern GUID ProviderGuid;

//
// GUID:
//   {53d82d11-cede-4dff-8eb4-f06631800128}
//

extern GUID SessionGuid;

extern TCHAR SessionName[];

VOID WINAPI TraceEventCallback(_In_ PEVENT_RECORD EventRecord);

ULONG NTAPI TraceStart(VOID);

VOID NTAPI TraceStop(VOID);

BOOLEAN DoInstallUninstall(_In_ BOOLEAN Install, LPCTSTR drvName, CHAR basicOrWeb);

class WebApcInjldrCtrl {

public:

    BOOL installed;
    BOOL session_started;

    WebApcInjldrCtrl();

    ~WebApcInjldrCtrl();
    
    BOOL Load();

    BOOL StartSession();

    BOOL StopSession();

};

