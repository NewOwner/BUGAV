#include "pch.h"
#include "hook_funcs.h"

BOOL WINAPI Hook_Beep(DWORD dwFreq, DWORD dwDuration) {
    std::cout << "\n BeepHook \n\n";
    return Beep(dwFreq + 1000, dwDuration);
}

HANDLE __stdcall Hook_CreateFileA(LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile) {
    return CreateFileA(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
}

HANDLE __stdcall Hook_CreateFileW(LPCWSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile) {
    return CreateFileW(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
}

BOOL __stdcall Hook_CreatePipe(PHANDLE hReadPipe, PHANDLE hWritePipe, LPSECURITY_ATTRIBUTES lpPipeAttributes, DWORD nSize) {
    return CreatePipe(hReadPipe, hWritePipe, lpPipeAttributes, nSize);
}

HANDLE __stdcall Hook_CreateNamedPipeA(LPCSTR lpName, DWORD dwOpenMode, DWORD dwPipeMode, DWORD nMaxInstances, DWORD nOutBufferSize, DWORD nInBufferSize, DWORD nDefaultTimeOut, LPSECURITY_ATTRIBUTES lpSecurityAttributes) {
    return CreateNamedPipeA(lpName, dwOpenMode, dwPipeMode, nMaxInstances, nOutBufferSize, nInBufferSize, nDefaultTimeOut, lpSecurityAttributes);
}

HFILE Hook_OpenFile(LPCSTR lpFileName, LPOFSTRUCT lpReOpenBuff, UINT uStyle) {
    return OpenFile(lpFileName, lpReOpenBuff, uStyle);
}

HANDLE Hook_OpenFileMappingA(DWORD dwDesiredAccess, BOOL bInheritHandle, LPCSTR lpName) {
    return OpenFileMappingA(dwDesiredAccess, bInheritHandle, lpName);
}

BOOL Hook_WriteFile(HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPDWORD lpNumberOfBytesWritten, LPOVERLAPPED lpOverlapped) {
    return WriteFile(hFile, lpBuffer, nNumberOfBytesToWrite, lpNumberOfBytesWritten, lpOverlapped);
}

BOOL __stdcall Hook_WriteConsole(HANDLE hConsoleOutput, const VOID* lpBuffer, DWORD nNumberOfCharsToWrite, LPDWORD lpNumberOfCharsWritten, LPVOID lpReserved) {
    return WriteConsole(hConsoleOutput, lpBuffer, nNumberOfCharsToWrite, lpNumberOfCharsWritten, lpReserved);
}

BOOL Hook_WriteFileEx(HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPOVERLAPPED lpOverlapped, LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine) {
    return WriteFileEx(hFile, lpBuffer, nNumberOfBytesToWrite, lpOverlapped, lpCompletionRoutine);
}

HANDLE Hook_FindFirstFileA(LPCSTR lpFileName, LPWIN32_FIND_DATAA lpFindFileData) {
    return FindFirstFileA(lpFileName, lpFindFileData);
}

HANDLE Hook_FindFirstFileW(LPCWSTR lpFileName, LPWIN32_FIND_DATAW lpFindFileData) {
    return FindFirstFileW(lpFileName, lpFindFileData);
}

BOOL Hook_ReadFile(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPDWORD lpNumberOfBytesRead, LPOVERLAPPED lpOverlapped) {
    return ReadFile(hFile, lpBuffer, nNumberOfBytesToRead, lpNumberOfBytesRead, lpOverlapped);
}

BOOL Hook_SetFileAttributesW(LPCWSTR lpFileName, DWORD dwFileAttributes) {
    return SetFileAttributesW(lpFileName, dwFileAttributes);
}

HMODULE Hook_LoadLibraryExW(LPCWSTR lpLibFileName, HANDLE hFile, DWORD dwFlags) {
    return LoadLibraryExW(lpLibFileName, hFile, dwFlags);
}

BOOL Hook_FreeLibrary(HMODULE hLibModule) {
    return FreeLibrary(hLibModule);
}

LSTATUS Hook_RegOpenKeyExW(HKEY hKey, LPCWSTR lpSubKey, DWORD ulOptions, REGSAM samDesired, PHKEY phkResult) {
    return RegOpenKeyExW(hKey, lpSubKey, ulOptions, samDesired, phkResult);
}

LSTATUS Hook_RegQueryValueA(HKEY hKey, LPCSTR lpSubKey, LPSTR lpData, PLONG lpcbData) {
    return RegQueryValueA(hKey, lpSubKey, lpData, lpcbData);
}

LSTATUS Hook_RegSetValueA(HKEY hKey, LPCSTR lpSubKey, DWORD dwType, LPCSTR lpData, DWORD cbData) {
    return RegSetValueA(hKey, lpSubKey, dwType, lpData, cbData);
}

LSTATUS Hook_RegSetValueW(HKEY hKey, LPCWSTR lpSubKey, DWORD dwType, LPCWSTR lpData, DWORD cbData) {
    return RegSetValueW(hKey, lpSubKey, dwType, lpData, cbData);
}

BOOL Hook_CreateProcessA(LPCSTR lpApplicationName, LPSTR lpCommandLine, LPSECURITY_ATTRIBUTES lpProcessAttributes, LPSECURITY_ATTRIBUTES lpThreadAttributes, BOOL bInheritHandles, DWORD dwCreationFlags, LPVOID lpEnvironment, LPCSTR lpCurrentDirectory, LPSTARTUPINFOA lpStartupInfo, LPPROCESS_INFORMATION lpProcessInformation) {
    return CreateProcessA(lpApplicationName, lpCommandLine, lpProcessAttributes, lpThreadAttributes, bInheritHandles, dwCreationFlags, lpEnvironment, lpCurrentDirectory, lpStartupInfo, lpProcessInformation);
}

UINT Hook_WinExec(LPCSTR lpCmdLine, UINT uCmdShow) {
    return WinExec(lpCmdLine, uCmdShow);
}

DWORD Hook_GetCurrentThreadId() {
    return GetCurrentThreadId();
}

BOOL Hook_ReadProcessMemory(HANDLE hProcess, LPCVOID lpBaseAddress, LPVOID lpBuffer, SIZE_T nSize, SIZE_T* lpNumberOfBytesRead) {
    return ReadProcessMemory(hProcess, lpBaseAddress, lpBuffer, nSize, lpNumberOfBytesRead);
}

BOOL Hook_WriteProcessMemory(HANDLE hProcess, LPVOID lpBaseAddress, LPCVOID lpBuffer, SIZE_T nSize, SIZE_T* lpNumberOfBytesWritten) {
    return WriteProcessMemory(hProcess, lpBaseAddress, lpBuffer, nSize, lpNumberOfBytesWritten);
}

LPVOID Hook_VirtualAllocEx(HANDLE hProcess, LPVOID lpAddress, SIZE_T dwSize, DWORD flAllocationType, DWORD flProtect) {
    return VirtualAllocEx(hProcess, lpAddress, dwSize, flAllocationType, flProtect);
}

BOOL Hook_SetThreadContext(HANDLE hThread, const CONTEXT* lpContext) {
    return SetThreadContext(hThread, lpContext);
}

BOOL Hook_SetProcessAffinityMask(HANDLE hProcess, DWORD_PTR dwProcessAffinityMask) {
    return SetProcessAffinityMask(hProcess, dwProcessAffinityMask);
}

BOOL Hook_TerminateProcess(HANDLE hProcess, UINT uExitCode) {
    return TerminateProcess(hProcess, uExitCode);
}

void Hook_ExitProcess(UINT uExitCode) {
    ExitProcess(uExitCode);
}

HHOOK Hook_SetWindowsHookExA(int idHook, HOOKPROC lpfn, HINSTANCE hmod, DWORD dwThreadId) {
    return SetWindowsHookExA(idHook, lpfn, hmod, dwThreadId);
}

LRESULT Hook_CallNextHookEx(HHOOK hhk, int nCode, WPARAM wParam, LPARAM lParam) {
    return CallNextHookEx(hhk, nCode, wParam, lParam);
}

BOOL Hook_IsDebuggerPresent() {
    return IsDebuggerPresent();
}

void Hook_OutputDebugStringA(LPCSTR lpOutputString) {
    OutputDebugStringA(lpOutputString);
}

HANDLE Hook_CreateMutexA(LPSECURITY_ATTRIBUTES lpMutexAttributes, BOOL bInitialOwner, LPCSTR lpName) {
    return CreateMutexA(lpMutexAttributes, bInitialOwner, lpName);
}

HANDLE Hook_CreateSemaphoreW(LPSECURITY_ATTRIBUTES lpSemaphoreAttributes, LONG lInitialCount, LONG lMaximumCount, LPCWSTR lpName) {
    return CreateSemaphoreW(lpSemaphoreAttributes, lInitialCount, lMaximumCount, lpName);
}

BOOL Hook_DeviceIoControl(HANDLE hDevice, DWORD dwIoControlCode, LPVOID lpInBuffer, DWORD nInBufferSize, LPVOID lpOutBuffer, DWORD nOutBufferSize, LPDWORD lpBytesReturned, LPOVERLAPPED lpOverlapped) {
    return DeviceIoControl(hDevice, dwIoControlCode, lpInBuffer, nInBufferSize, lpOutBuffer, nOutBufferSize, lpBytesReturned, lpOverlapped);
}

UINT Hook_GetDriveTypeW(LPCWSTR lpRootPathName) {
    return GetDriveTypeW(lpRootPathName);
}

int WSAAPI Hook_send(SOCKET s, const char* buf, int len, int flags) {
    return send(s, buf, len, flags);
}

int Hook_recv(SOCKET s, char* buf, int len, int flags) {
    return recv(s, buf, len, flags);
}

int WSAAPI Hook_WSARecv(SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount, LPDWORD lpNumberOfBytesRecvd, LPDWORD lpFlags, LPWSAOVERLAPPED lpOverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine) {
    return WSARecv(s, lpBuffers, dwBufferCount, lpNumberOfBytesRecvd, lpFlags, lpOverlapped, lpCompletionRoutine);
}

int WSAAPI Hook_connect(SOCKET s, const sockaddr* name, int namelen) {
    return connect(s, name, namelen);
}

SC_HANDLE Hook_CreateServiceA(SC_HANDLE hSCManager, LPCSTR lpServiceName, LPCSTR lpDisplayName, DWORD dwDesiredAccess, DWORD dwServiceType, DWORD dwStartType, DWORD dwErrorControl, LPCSTR lpBinaryPathName, LPCSTR lpLoadOrderGroup, LPDWORD lpdwTagId, LPCSTR lpDependencies, LPCSTR lpServiceStartName, LPCSTR lpPassword) {
    return CreateServiceA(hSCManager, lpServiceName, lpDisplayName, dwDesiredAccess, dwServiceType, dwStartType, dwErrorControl, lpBinaryPathName, lpLoadOrderGroup, lpdwTagId, lpDependencies, lpServiceStartName, lpPassword);
}

BOOL Hook_StartServiceA(SC_HANDLE hService, DWORD dwNumServiceArgs, LPCSTR* lpServiceArgVectors) {
    return StartServiceA(hService, dwNumServiceArgs, lpServiceArgVectors);
}

BOOL Hook_ChangeServiceConfigA(SC_HANDLE hService, DWORD dwServiceType, DWORD dwStartType, DWORD dwErrorControl, LPCSTR lpBinaryPathName, LPCSTR lpLoadOrderGroup, LPDWORD lpdwTagId, LPCSTR lpDependencies, LPCSTR lpServiceStartName, LPCSTR lpPassword, LPCSTR lpDisplayName) {
    return ChangeServiceConfigA(hService, dwServiceType, dwStartType, dwErrorControl, lpBinaryPathName, lpLoadOrderGroup, lpdwTagId, lpDependencies, lpServiceStartName, lpPassword, lpDisplayName);
}

UINT Hook_GetSystemDirectoryW(LPWSTR lpBuffer, UINT uSize) {
    return GetSystemDirectoryW(lpBuffer, uSize);
}

void Hook_GetSystemTime(LPSYSTEMTIME lpSystemTime) {
    GetSystemTime(lpSystemTime);
}

HMODULE Hook_GetModuleHandleA(LPCSTR lpModuleName) {
    return GetModuleHandleA(lpModuleName);
}

FARPROC Hook_GetProcAddress(HMODULE hModule, LPCSTR lpProcName) {
    return GetProcAddress(hModule, lpProcName);
}

DWORD Hook_GetModuleFileNameA(HMODULE hModule, LPSTR lpFilename, DWORD nSize) {
    return GetModuleFileNameA(hModule, lpFilename, nSize);
}

HMODULE Hook_LoadLibraryA(LPCSTR lpLibFileName) {
    return LoadLibraryA(lpLibFileName);
}


//Input/output Create 	A 	CreatefileA CreatePipe CreateNamedPipeA
//Input/output Open 	B 	10 	OpenFile, OpenFileMappingA
//Input/output Write 	C 	25 	WriteFile, WriteConsoleW, WriteFileEx
//Input/output Find 	D 	13 	FindFirstFileA, FindNextFileW
//Input/output Read 	E 	18 	ReadFile, ReadFileEx, ReadConsoleA
//Input/output Access 	F 	19 	SetFileAttributesW, SetConsoleMode
//Loading Library 	G 	7 	LoadLibraryExW, FreeLibrary
//Registry Read 	H 	15 	RegOpenKeyExW, RegQueryValueA
//Registry Write 	I 	13 	RegSetValueA, RegSetValueW
//COM/OLE/DDE 	J 	154 	OleCreate, OleLoad, CoBuildVersion
//Process Create 	K 	10 	CreateProcessA, ShellExecute, WinExec
//Process Read 	L 	33 	GetCurrentThreadId, ReadProcessMemory
//Process Write 	M 	10 	WriteProcessMemory, VirtualAllocEx
//Process Change 	N 	12 	SetThreadContext, SetProcessAffinityMask
//Process Exit 	O 	3 	TerminateProcess, ExitProcess
//Hooking 	P 	5 	SetWindowsHookA, CallNextHookEx
//Anti-Debugging 	Q 	4 	IsDebuggerPresent, OutputDebugStringA
//Synchronization 	R 	13 	CreateMutexA, CreateSemaphoreW
//Device Control 	S 	6 	DeviceIoControl, GetDriveTypeW
//Socket Comm. 	T 	70 	Send, Recv, WSARecv, Connect
//Network Information 	U 	17 	Gethostbyname, InternetGetConnectedState
//Internet Open/ Read 	V 	13 	InternetOpenUrlA, InternetReadFile
//Internet Write 	W 	2 	InternetWriteFile, TransactNamedPipe
//Win-Service Create 	X 	2 	CreateServiceW, CreateServiceA
//Win-Service Other 	Y 	11 	StartServiceW, ChangeServiceConfigA
//System Information 	Z 	35 	GetSystemDirectoryW, GetSystemTime
//GetModuleHandle
//GetProcAddress
//CreateStreamOnHGlobal
//WinHttpOpen
//GetModuleFileName
//LoadLibrary
//GetModuleFileName

