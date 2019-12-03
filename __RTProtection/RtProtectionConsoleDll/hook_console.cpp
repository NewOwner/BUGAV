// BeepHook.cpp : Defines the exported functions for the DLL application.
//

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#include "pch.h"
#include "hook_funcs_console.h"

HANDLE hPipe1;

extern "C" void __declspec(dllexport) __stdcall NativeInjectionEntryPoint(REMOTE_ENTRY_INFO * inRemoteInfo);

void perform_hook(LPCWSTR _module_name, LPCSTR _func_name, void* _hook_ptr) {

    HOOK_TRACE_INFO hHook = { NULL };

    std::cout << _func_name << " found at address: " << GetProcAddress(GetModuleHandle(_module_name), _func_name) << "\n";

    // Install the hook
    NTSTATUS result = LhInstallHook(
        GetProcAddress(GetModuleHandle(_module_name), _func_name),
        _hook_ptr,
        NULL,
        &hHook);

    if (FAILED(result)) {
        std::wstring s(RtlGetLastErrorString());
        std::wcout << "NativeInjectionEntryPoint: Failed to install hook: " << s << "\n";
    } else {
        std::cout << "NativeInjectionEntryPoint: Hook for "<< _func_name <<" installed successfully.\n";
    }

    // If the threadId in the ACL is set to 0,
    // then internally EasyHook uses GetCurrentThreadId()
    ULONG ACLEntries[1] = { 0 };

    // Disable the hook for the provided threadIds, enable for all others
    LhSetExclusiveACL(ACLEntries, 1, &hHook);
}

void __stdcall NativeInjectionEntryPoint(REMOTE_ENTRY_INFO* inRemoteInfo) {
    std::cout << "NativeInjectionEntryPoint: Injected by process Id: " << inRemoteInfo->HostPID << "\n";
    std::cout << "NativeInjectionEntryPoint: Passed in data size: " << inRemoteInfo->UserDataSize << "\n";
    DWORD inRemotePid=0;
    if (inRemoteInfo->UserDataSize == sizeof(DWORD)) {
        inRemotePid = *reinterpret_cast<DWORD*>(inRemoteInfo->UserData);
    }
    std::cout << "NativeInjectionEntryPoint: Target Pid: " << inRemotePid << "\n";
    
    char buf[500] = "hook msg";
    DWORD cbWritten;
    DWORD dwBytesToWrite = (DWORD)strlen(buf);
    
    std::wstring pipename = TEXT("\\\\.\\pipe\\myNamedPipe");
    pipename += std::to_wstring(inRemotePid);
    
    hPipe1 = CreateFile(pipename.c_str(), GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);
    if ((hPipe1 == NULL || hPipe1 == INVALID_HANDLE_VALUE)) {
        printf("Could not open the pipe  - (error %d)\n", GetLastError());
    }
    WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);

    perform_hook(TEXT("Kernel32"), "ReadConsoleA", Hook_ReadConsoleA);
    perform_hook(TEXT("Kernel32"), "ReadConsoleW", Hook_ReadConsoleW);
    perform_hook(TEXT("Kernel32"), "ReadConsoleInputA", Hook_ReadConsoleInputA);
    perform_hook(TEXT("Kernel32"), "ReadConsoleInputW", Hook_ReadConsoleInputW);
    perform_hook(TEXT("Kernel32"), "ReadConsoleOutputA", Hook_ReadConsoleOutputA);
    perform_hook(TEXT("Kernel32"), "ReadConsoleOutputW", Hook_ReadConsoleOutputW);
    perform_hook(TEXT("Kernel32"), "ReadConsoleOutputCharacterA", Hook_ReadConsoleOutputCharacterA);
    perform_hook(TEXT("Kernel32"), "ReadConsoleOutputCharacterW", Hook_ReadConsoleOutputCharacterW);
    //perform_hook(TEXT("Kernel32"), "SetConsoleMode", Hook_SetConsoleMode);
    perform_hook(TEXT("Kernel32"), "WriteConsoleOutputCharacterA", Hook_WriteConsoleOutputCharacterA);
    perform_hook(TEXT("Kernel32"), "WriteConsoleOutputCharacterW", Hook_WriteConsoleOutputCharacterW);
    
    return;
}