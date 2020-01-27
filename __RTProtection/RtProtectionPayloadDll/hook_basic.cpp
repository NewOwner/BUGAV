#define WIN32_LEAN_AND_MEAN
#include "pch.h"
#include "hook_funcs_basic.h"

HANDLE hPipe1;

extern "C" void __declspec(dllexport) __stdcall NativeInjectionEntryPoint(REMOTE_ENTRY_INFO * inRemoteInfo);

void perform_hook(LPCWSTR _module_name, LPCSTR _func_name, void* _hook_ptr) {

    HOOK_TRACE_INFO hHook = { NULL };
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
    
    ULONG ACLEntries[1] = { 0 };                // If the threadId in the ACL is set to 0, then internally EasyHook uses GetCurrentThreadId()
    LhSetExclusiveACL(ACLEntries, 1, &hHook);   // Disable the hook for the provided threadIds, enable for all others
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
    //WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);

    perform_hook(TEXT("kernel32"), "LoadLibraryExW", Hook_LoadLibraryExW);
    perform_hook(TEXT("kernel32"), "WinExec", Hook_WinExec);
    perform_hook(TEXT("kernel32"), "ReadProcessMemory", Hook_ReadProcessMemory);
    perform_hook(TEXT("kernel32"), "WriteProcessMemory", Hook_WriteProcessMemory);
    perform_hook(TEXT("User32"), "SetWindowsHookA", Hook_SetWindowsHookExA);
    perform_hook(TEXT("kernel32"), "IsDebuggerPresent", Hook_IsDebuggerPresent);
    perform_hook(TEXT("Advapi32"), "CreateServiceA", Hook_CreateServiceA);
    perform_hook(TEXT("kernel32"), "GetSystemDirectoryW", Hook_GetSystemDirectoryW);
    perform_hook(TEXT("kernel32"), "GetSystemTime", Hook_GetSystemTime);
    return;
}