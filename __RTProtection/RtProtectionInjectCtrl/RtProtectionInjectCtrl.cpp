#include "pch.h"
#include "RtProtectionInjectCtrl.h"

RtProtectionInjectCtrl::RtProtectionInjectCtrl() {}

RtProtectionInjectCtrl::~RtProtectionInjectCtrl() {}

VOID RtProtectionInjectCtrl::InjectLib(DWORD pid, PWCHAR dll_to_inject, PVOID dll_data, ULONG data_sz) {
    
    NTSTATUS nt = RhInjectLibrary(
        pid,                        // The process to inject into
        0,                          // ThreadId to wake up upon injection
        EASYHOOK_INJECT_DEFAULT,
        NULL,                       // 32-bit
        dll_to_inject,              // 64-bit
        dll_data,                   // data to send to injected DLL entry point
        data_sz                     // size of data to send
    );

    if (nt != 0) {
        printf("RhInjectLibrary failed with error code = %d\n", nt);
        PWCHAR err = RtlGetLastErrorString();
        std::wcout << err << "\n";
    } else {
        std::wcout << L"Library injected successfully.\n";
    }
}
