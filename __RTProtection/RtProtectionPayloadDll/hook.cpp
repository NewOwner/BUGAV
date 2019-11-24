// BeepHook.cpp : Defines the exported functions for the DLL application.
//

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#include "pch.h"
#include "hook_funcs.h"

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

    perform_hook(TEXT("kernel32"), "Beep", Hook_Beep);

    //Input/output Create 	A 	CreatefileA CreatePipe CreateNamedPipeA ‎Kernel32);
    //perform_hook(TEXT("kernel32"), "CreatefileA", Hook_CreateFileA);
    //perform_hook(TEXT("kernel32"), "CreatefileW", Hook_CreateFileW);
    perform_hook(TEXT("kernel32"), "CreatePipe", Hook_CreatePipe);
    perform_hook(TEXT("kernel32"), "CreateNamedPipeA", Hook_CreateNamedPipeA);
    
    //Input/output Open 	B 	10 	OpenFile, OpenFileMappingA Kernel32         );
    perform_hook(TEXT("kernel32"), "OpenFile", Hook_OpenFile);
    perform_hook(TEXT("kernel32"), "OpenFileMappingA", Hook_OpenFileMappingA);
    
    //Input/output Write 	C 	25 	WriteFile, WriteConsoleW, WriteFileEx       );
    perform_hook(TEXT("kernel32"), "WriteFile", Hook_WriteFile);
    perform_hook(TEXT("kernel32"), "WriteFileEx", Hook_WriteFileEx);
    
    //Input/output Find 	D 	13 	FindFirstFileA, FindNextFileW               );
    perform_hook(TEXT("kernel32"), "FindFirstFileA", Hook_FindFirstFileA);
    perform_hook(TEXT("kernel32"), "FindFirstFileW", Hook_FindFirstFileW);
    
    //Input/output Read 	E 	18 	ReadFile, ReadFileEx, ReadConsoleA          );
    perform_hook(TEXT("kernel32"), "ReadFile", Hook_ReadFile);
    
    //Input/output Access 	F 	19 	SetFileAttributesW, SetConsoleMode          );
    perform_hook(TEXT("kernel32"), "SetFileAttributesW", Hook_SetFileAttributesW);
    
    //Loading Library 	G 	7 	LoadLibraryExW, FreeLibrary                     );
    perform_hook(TEXT("kernel32"), "LoadLibraryExW", Hook_LoadLibraryExW);
    perform_hook(TEXT("kernel32"), "FreeLibrary", Hook_FreeLibrary);
    
    //Registry Read 	H 	15 	RegOpenKeyExW, RegQueryValueA Advapi32          );
    perform_hook(TEXT("Advapi32"), "RegOpenKeyExW", Hook_RegOpenKeyExW);
    perform_hook(TEXT("Advapi32"), "RegQueryValueA", Hook_RegQueryValueA);
    
    //Registry Write 	I 	13 	RegSetValueA, RegSetValueW Advapi32             );
    perform_hook(TEXT("Advapi32"), "RegSetValueA", Hook_RegSetValueA);
    perform_hook(TEXT("Advapi32"), "RegSetValueW", Hook_RegSetValueW);
    
    //Process Create 	K 	10 	CreateProcessA, ShellExecute, WinExec Kernel32  );
    perform_hook(TEXT("kernel32"), "CreateProcessA", Hook_CreateProcessA);
    perform_hook(TEXT("kernel32"), "WinExec", Hook_WinExec);
    
    //Process Read 	L 	33 	GetCurrentThreadId, ReadProcessMemory               );
    //perform_hook(TEXT("kernel32"), "GetCurrentThreadId", Hook_GetCurrentThreadId);
    perform_hook(TEXT("kernel32"), "ReadProcessMemory", Hook_ReadProcessMemory);
    
    //Process Write 	M 	10 	WriteProcessMemory, VirtualAllocEx              );
    perform_hook(TEXT("kernel32"), "WriteProcessMemory", Hook_WriteProcessMemory);
    perform_hook(TEXT("kernel32"), "VirtualAllocEx", Hook_VirtualAllocEx);
    
    //Process Change 	N 	12 	SetThreadContext, SetProcessAffinityMask        );
    perform_hook(TEXT("kernel32"), "SetThreadContext", Hook_SetThreadContext);
    perform_hook(TEXT("kernel32"), "SetProcessAffinityMask", Hook_SetProcessAffinityMask);
    
    //Process Exit 	O 	3 	TerminateProcess, ExitProcess                       );
    perform_hook(TEXT("kernel32"), "TerminateProcess", Hook_TerminateProcess);
    perform_hook(TEXT("kernel32"), "ExitProcess", Hook_ExitProcess);
    
    //Hooking 	P 	5 	SetWindowsHookA, CallNextHookEx User32                  );
    perform_hook(TEXT("User32"), "SetWindowsHookA", Hook_SetWindowsHookExA);
    perform_hook(TEXT("User32"), "CallNextHookEx", Hook_CallNextHookEx);
    
    //Anti-Debugging 	Q 	4 	IsDebuggerPresent, OutputDebugStringA Kernel32  );
    perform_hook(TEXT("kernel32"), "IsDebuggerPresent", Hook_IsDebuggerPresent);
    perform_hook(TEXT("kernel32"), "OutputDebugStringA", Hook_OutputDebugStringA);
    
    //Synchronization 	R 	13 	CreateMutexA, CreateSemaphoreW                  );
    perform_hook(TEXT("kernel32"), "CreateMutexA", Hook_CreateMutexA);
    perform_hook(TEXT("kernel32"), "CreateSemaphoreW", Hook_CreateSemaphoreW);
    
    //Device Control 	S 	6 	DeviceIoControl, GetDriveTypeW                  );
    perform_hook(TEXT("kernel32"), "DeviceIoControl", Hook_DeviceIoControl);
    perform_hook(TEXT("kernel32"), "GetDriveTypeW", Hook_GetDriveTypeW);
    
    //Socket Comm. 	T 	70 	Send, Recv, WSARecv, Connect Ws2_32                 );
    perform_hook(TEXT("Ws2_32"), "send", Hook_send);
    perform_hook(TEXT("Ws2_32"), "recv", Hook_recv);
    perform_hook(TEXT("Ws2_32"), "WSARecv", Hook_WSARecv);
    perform_hook(TEXT("Ws2_32"), "connect", Hook_connect);
    
    //Win-Service Create 	X 	2 	CreateServiceA ‎Advapi32                     );
    perform_hook(TEXT("Advapi32"), "CreateServiceA", Hook_CreateServiceA);
    
    //Win-Service Other 	Y 	11 	StartServiceW, ChangeServiceConfigA ‎Advapi32);
    perform_hook(TEXT("Advapi32"), "StartServiceA", Hook_StartServiceA);
    perform_hook(TEXT("Advapi32"), "ChangeServiceConfigA", Hook_ChangeServiceConfigA);
    
    //System Information 	Z 	35 	GetSystemDirectoryW, GetSystemTime ‎Kernel32 );
    perform_hook(TEXT("kernel32"), "GetSystemDirectoryW", Hook_GetSystemDirectoryW);
    perform_hook(TEXT("kernel32"), "GetSystemTime", Hook_GetSystemTime);
    
    //GetModuleHandle                                                           );
    //perform_hook(TEXT("kernel32"), "GetModuleHandle", Hook_GetModuleHandleA);
    
    //GetProcAddress                                                            );
    perform_hook(TEXT("kernel32"), "GetProcAddress", Hook_GetProcAddress);
    
    //GetModuleFileName                                                         );
    perform_hook(TEXT("kernel32"), "GetModuleFileNameA", Hook_GetModuleFileNameA);

    return;
}

/*
// Perform hooking
    HOOK_TRACE_INFO hHook = { NULL }; // keep track of our hook

    std::cout << "\nNativeInjectionEntryPoint: Win32 Beep found at address: " << GetProcAddress(GetModuleHandle(TEXT("kernel32")), "Beep") << "\n";

    // Install the hook
    NTSTATUS result = LhInstallHook(
        GetProcAddress(GetModuleHandle(TEXT("kernel32")), "Beep"),
        myBeepHook,
        NULL,
        &hHook);
    if (FAILED(result)) {
        std::wstring s(RtlGetLastErrorString());
        std::wcout << "NativeInjectionEntryPoint: Failed to install hook: " << s << "\n";
    } else {
        std::cout << "NativeInjectionEntryPoint: Hook 'myBeepHook installed successfully.\n";
    }

    // If the threadId in the ACL is set to 0,
    // then internally EasyHook uses GetCurrentThreadId()
    ULONG ACLEntries[1] = { 0 };

    // Disable the hook for the provided threadIds, enable for all others
    LhSetExclusiveACL(ACLEntries, 1, &hHook);

*/