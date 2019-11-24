#include "pch.h"
#include "hook_funcs.h"

extern HANDLE hPipe1;
std::mutex m;

BOOL WINAPI Hook_Beep(DWORD dwFreq, DWORD dwDuration) {
    std::cout << "\n Hook_Beep \n\n";
    char buf[500] = "Beep";
    DWORD cbWritten;
    DWORD dwBytesToWrite = (DWORD)strlen(buf);
    WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
    return Beep(dwFreq + 1000, dwDuration);
}

HANDLE __stdcall Hook_CreateFileA(LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile) {
    std::cout << "\n Hook_CreateFileA \n\n";
    //char buf[500] = "CreateFileA";
    //DWORD cbWritten;
    //DWORD dwBytesToWrite = (DWORD)strlen(buf);
    //WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
    return CreateFileA(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
}

HANDLE __stdcall Hook_CreateFileW(LPCWSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile) {
    std::cout << "\n Hook_CreateFileW \n\n";
    //char buf[500] = "CreateFileW";
    //DWORD cbWritten;
    //DWORD dwBytesToWrite = (DWORD)strlen(buf);
    //WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
    return CreateFileW(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
}

BOOL __stdcall Hook_CreatePipe(PHANDLE hReadPipe, PHANDLE hWritePipe, LPSECURITY_ATTRIBUTES lpPipeAttributes, DWORD nSize) {
    std::cout << "\n Hook_CreatePipe \n\n";
    //char buf[500] = "CreatePipe";
    //DWORD cbWritten;
    //DWORD dwBytesToWrite = (DWORD)strlen(buf);
    //WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
    return CreatePipe(hReadPipe, hWritePipe, lpPipeAttributes, nSize);
}

HANDLE __stdcall Hook_CreateNamedPipeA(LPCSTR lpName, DWORD dwOpenMode, DWORD dwPipeMode, DWORD nMaxInstances, DWORD nOutBufferSize, DWORD nInBufferSize, DWORD nDefaultTimeOut, LPSECURITY_ATTRIBUTES lpSecurityAttributes) {
    std::cout << "\n Hook_CreateNamedPipeA \n\n";
    char buf[500] = "CreateNamedPipeA";
    DWORD cbWritten;
    DWORD dwBytesToWrite = (DWORD)strlen(buf);
    WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
    return CreateNamedPipeA(lpName, dwOpenMode, dwPipeMode, nMaxInstances, nOutBufferSize, nInBufferSize, nDefaultTimeOut, lpSecurityAttributes);
}

HFILE Hook_OpenFile(LPCSTR lpFileName, LPOFSTRUCT lpReOpenBuff, UINT uStyle) {
    std::cout << "\n Hook_OpenFile \n\n";
    //char buf[500] = "OpenFile";
    //DWORD cbWritten;
    //DWORD dwBytesToWrite = (DWORD)strlen(buf);
    //WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
    return OpenFile(lpFileName, lpReOpenBuff, uStyle);
}

HANDLE Hook_OpenFileMappingA(DWORD dwDesiredAccess, BOOL bInheritHandle, LPCSTR lpName) {
    std::cout << "\n Hook_OpenFileMappingA \n\n";
    return OpenFileMappingA(dwDesiredAccess, bInheritHandle, lpName);
}

BOOL Hook_WriteFile(HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPDWORD lpNumberOfBytesWritten, LPOVERLAPPED lpOverlapped) {
    std::cout << "\n Hook_WriteFile \n\n";
    //char buf[500] = "WriteFile";
    //DWORD cbWritten;
    //DWORD dwBytesToWrite = (DWORD)strlen(buf);
    //WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
    return WriteFile(hFile, lpBuffer, nNumberOfBytesToWrite, lpNumberOfBytesWritten, lpOverlapped);
}

BOOL __stdcall Hook_WriteConsole(HANDLE hConsoleOutput, const VOID* lpBuffer, DWORD nNumberOfCharsToWrite, LPDWORD lpNumberOfCharsWritten, LPVOID lpReserved) {
    std::cout << "\n Hook_WriteConsole \n\n";
    return WriteConsole(hConsoleOutput, lpBuffer, nNumberOfCharsToWrite, lpNumberOfCharsWritten, lpReserved);
}

BOOL Hook_WriteFileEx(HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPOVERLAPPED lpOverlapped, LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine) {
    std::cout << "\n Hook_WriteFileEx \n\n";
    //char buf[500] = "WriteFileEx";
    //DWORD cbWritten;
    //DWORD dwBytesToWrite = (DWORD)strlen(buf);
    //WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
    return WriteFileEx(hFile, lpBuffer, nNumberOfBytesToWrite, lpOverlapped, lpCompletionRoutine);
}

HANDLE Hook_FindFirstFileA(LPCSTR lpFileName, LPWIN32_FIND_DATAA lpFindFileData) {
    std::cout << "\n Hook_FindFirstFileA \n\n";
    return FindFirstFileA(lpFileName, lpFindFileData);
}

HANDLE Hook_FindFirstFileW(LPCWSTR lpFileName, LPWIN32_FIND_DATAW lpFindFileData) {
    std::cout << "\n Hook_FindFirstFileW \n\n";
    return FindFirstFileW(lpFileName, lpFindFileData);
}

BOOL Hook_ReadFile(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPDWORD lpNumberOfBytesRead, LPOVERLAPPED lpOverlapped) {
    std::cout << "\n Hook_ReadFile \n\n";
    //char buf[500] = "ReadFile";
    //DWORD cbWritten;
    //DWORD dwBytesToWrite = (DWORD)strlen(buf);
    //WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
    return ReadFile(hFile, lpBuffer, nNumberOfBytesToRead, lpNumberOfBytesRead, lpOverlapped);
}

BOOL Hook_SetFileAttributesW(LPCWSTR lpFileName, DWORD dwFileAttributes) {
    std::cout << "\n Hook_SetFileAttributesW \n\n";
    return SetFileAttributesW(lpFileName, dwFileAttributes);
}

HMODULE Hook_LoadLibraryExW(LPCWSTR lpLibFileName, HANDLE hFile, DWORD dwFlags) {
    std::cout << "\n Hook_LoadLibraryExW \n\n";
    char buf[500] = "LoadLibraryExW";
    DWORD cbWritten;
    DWORD dwBytesToWrite = (DWORD)strlen(buf);
    WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
    return LoadLibraryExW(lpLibFileName, hFile, dwFlags);
}

BOOL Hook_FreeLibrary(HMODULE hLibModule) {
    std::cout << "\n Hook_FreeLibrary \n\n";
    return FreeLibrary(hLibModule);
}

LSTATUS Hook_RegOpenKeyExW(HKEY hKey, LPCWSTR lpSubKey, DWORD ulOptions, REGSAM samDesired, PHKEY phkResult) {
    std::cout << "\n Hook_RegOpenKeyExW \n\n";
    //char buf[500] = "RegOpenKeyExW";
    //DWORD cbWritten;
    //DWORD dwBytesToWrite = (DWORD)strlen(buf);
    //WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
    return RegOpenKeyExW(hKey, lpSubKey, ulOptions, samDesired, phkResult);
}

LSTATUS Hook_RegQueryValueA(HKEY hKey, LPCSTR lpSubKey, LPSTR lpData, PLONG lpcbData) {
    std::cout << "\n Hook_RegQueryValueA \n\n";
    return RegQueryValueA(hKey, lpSubKey, lpData, lpcbData);
}

LSTATUS Hook_RegSetValueA(HKEY hKey, LPCSTR lpSubKey, DWORD dwType, LPCSTR lpData, DWORD cbData) {
    std::cout << "\n Hook_RegSetValueA \n\n";
    return RegSetValueA(hKey, lpSubKey, dwType, lpData, cbData);
}

LSTATUS Hook_RegSetValueW(HKEY hKey, LPCWSTR lpSubKey, DWORD dwType, LPCWSTR lpData, DWORD cbData) {
    std::cout << "\n Hook_RegSetValueW \n\n";
    return RegSetValueW(hKey, lpSubKey, dwType, lpData, cbData);
}

BOOL Hook_CreateProcessA(LPCSTR lpApplicationName, LPSTR lpCommandLine, LPSECURITY_ATTRIBUTES lpProcessAttributes, LPSECURITY_ATTRIBUTES lpThreadAttributes, BOOL bInheritHandles, DWORD dwCreationFlags, LPVOID lpEnvironment, LPCSTR lpCurrentDirectory, LPSTARTUPINFOA lpStartupInfo, LPPROCESS_INFORMATION lpProcessInformation) {
    std::cout << "\n Hook_CreateProcessA \n\n";
    char buf[500] = "CreateProcessA";
    DWORD cbWritten;
    DWORD dwBytesToWrite = (DWORD)strlen(buf);
    WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
    return CreateProcessA(lpApplicationName, lpCommandLine, lpProcessAttributes, lpThreadAttributes, bInheritHandles, dwCreationFlags, lpEnvironment, lpCurrentDirectory, lpStartupInfo, lpProcessInformation);
}

UINT Hook_WinExec(LPCSTR lpCmdLine, UINT uCmdShow) {
    std::cout << "\n Hook_WinExec \n\n";
    char buf[500] = "WinExec";
    DWORD cbWritten;
    DWORD dwBytesToWrite = (DWORD)strlen(buf);
    WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
    return WinExec(lpCmdLine, uCmdShow);
}

DWORD Hook_GetCurrentThreadId() {
    std::cout << "\n Hook_GetCurrentThreadId \n\n";
    char buf[500] = "GetCurrentThreadId";
    DWORD cbWritten;
    DWORD dwBytesToWrite = (DWORD)strlen(buf);
    WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
    return GetCurrentThreadId();
}

BOOL Hook_ReadProcessMemory(HANDLE hProcess, LPCVOID lpBaseAddress, LPVOID lpBuffer, SIZE_T nSize, SIZE_T* lpNumberOfBytesRead) {
    std::cout << "\n Hook_ReadProcessMemory \n\n";
    char buf[500] = "ReadProcessMemory";
    DWORD cbWritten;
    DWORD dwBytesToWrite = (DWORD)strlen(buf);
    WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
    return ReadProcessMemory(hProcess, lpBaseAddress, lpBuffer, nSize, lpNumberOfBytesRead);
}

BOOL Hook_WriteProcessMemory(HANDLE hProcess, LPVOID lpBaseAddress, LPCVOID lpBuffer, SIZE_T nSize, SIZE_T* lpNumberOfBytesWritten) {
    std::cout << "\n Hook_WriteProcessMemory \n\n";
    char buf[500] = "WriteProcessMemory";
    DWORD cbWritten;
    DWORD dwBytesToWrite = (DWORD)strlen(buf);
    WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
    return WriteProcessMemory(hProcess, lpBaseAddress, lpBuffer, nSize, lpNumberOfBytesWritten);
}

LPVOID Hook_VirtualAllocEx(HANDLE hProcess, LPVOID lpAddress, SIZE_T dwSize, DWORD flAllocationType, DWORD flProtect) {
    std::cout << "\n Hook_VirtualAllocEx \n\n";
    return VirtualAllocEx(hProcess, lpAddress, dwSize, flAllocationType, flProtect);
}

BOOL Hook_SetThreadContext(HANDLE hThread, const CONTEXT* lpContext) {
    std::cout << "\n Hook_SetThreadContext \n\n";
    char buf[500] = "SetThreadContext";
    DWORD cbWritten;
    DWORD dwBytesToWrite = (DWORD)strlen(buf);
    WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
    return SetThreadContext(hThread, lpContext);
}

BOOL Hook_SetProcessAffinityMask(HANDLE hProcess, DWORD_PTR dwProcessAffinityMask) {
    std::cout << "\n Hook_SetProcessAffinityMask \n\n";
    char buf[500] = "SetProcessAffinityMask";
    DWORD cbWritten;
    DWORD dwBytesToWrite = (DWORD)strlen(buf);
    WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
    return SetProcessAffinityMask(hProcess, dwProcessAffinityMask);
}

BOOL Hook_TerminateProcess(HANDLE hProcess, UINT uExitCode) {
    std::cout << "\n Hook_TerminateProcess \n\n";
    char buf[500] = "TerminateProcess";
    DWORD cbWritten;
    DWORD dwBytesToWrite = (DWORD)strlen(buf);
    WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
    return TerminateProcess(hProcess, uExitCode);
}

void Hook_ExitProcess(UINT uExitCode) {
    std::cout << "\n Hook_ExitProcess \n\n";
    ExitProcess(uExitCode);
}

HHOOK Hook_SetWindowsHookExA(int idHook, HOOKPROC lpfn, HINSTANCE hmod, DWORD dwThreadId) {
    std::cout << "\n Hook_SetWindowsHookExA \n\n";
    char buf[500] = "SetWindowsHookExA";
    DWORD cbWritten;
    DWORD dwBytesToWrite = (DWORD)strlen(buf);
    WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
    return SetWindowsHookExA(idHook, lpfn, hmod, dwThreadId);
}

LRESULT Hook_CallNextHookEx(HHOOK hhk, int nCode, WPARAM wParam, LPARAM lParam) {
    std::cout << "\n Hook_CallNextHookEx \n\n";
    char buf[500] = "CallNextHookEx";
    DWORD cbWritten;
    DWORD dwBytesToWrite = (DWORD)strlen(buf);
    WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
    return CallNextHookEx(hhk, nCode, wParam, lParam);
}

BOOL Hook_IsDebuggerPresent() {
    std::cout << "\n Hook_IsDebuggerPresent \n\n";
    char buf[500] = "IsDebuggerPresent";
    DWORD cbWritten;
    DWORD dwBytesToWrite = (DWORD)strlen(buf);
    WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
    return IsDebuggerPresent();
}

void Hook_OutputDebugStringA(LPCSTR lpOutputString) {
    std::cout << "\n Hook_OutputDebugStringA \n\n";
    char buf[500] = "OutputDebugStringA";
    DWORD cbWritten;
    DWORD dwBytesToWrite = (DWORD)strlen(buf);
    WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
    OutputDebugStringA(lpOutputString);
}

HANDLE Hook_CreateMutexA(LPSECURITY_ATTRIBUTES lpMutexAttributes, BOOL bInitialOwner, LPCSTR lpName) {
    std::cout << "\n Hook_CreateMutexA \n\n";
    return CreateMutexA(lpMutexAttributes, bInitialOwner, lpName);
}

HANDLE Hook_CreateSemaphoreW(LPSECURITY_ATTRIBUTES lpSemaphoreAttributes, LONG lInitialCount, LONG lMaximumCount, LPCWSTR lpName) {
    std::cout << "\n Hook_CreateSemaphoreW \n\n";
    return CreateSemaphoreW(lpSemaphoreAttributes, lInitialCount, lMaximumCount, lpName);
}

BOOL Hook_DeviceIoControl(HANDLE hDevice, DWORD dwIoControlCode, LPVOID lpInBuffer, DWORD nInBufferSize, LPVOID lpOutBuffer, DWORD nOutBufferSize, LPDWORD lpBytesReturned, LPOVERLAPPED lpOverlapped) {
    std::cout << "\n Hook_DeviceIoControl \n\n";
    char buf[500] = "DeviceIoControl";
    DWORD cbWritten;
    DWORD dwBytesToWrite = (DWORD)strlen(buf);
    WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
    return DeviceIoControl(hDevice, dwIoControlCode, lpInBuffer, nInBufferSize, lpOutBuffer, nOutBufferSize, lpBytesReturned, lpOverlapped);
}

UINT Hook_GetDriveTypeW(LPCWSTR lpRootPathName) {
    std::cout << "\n Hook_GetDriveTypeW \n\n";
    return GetDriveTypeW(lpRootPathName);
}

int WSAAPI Hook_send(SOCKET s, const char* buf, int len, int flags) {
    std::cout << "\n Hook_send \n\n";
    return send(s, buf, len, flags);
}

int Hook_recv(SOCKET s, char* buf, int len, int flags) {
    std::cout << "\n Hook_recv \n\n";
    return recv(s, buf, len, flags);
}

int WSAAPI Hook_WSARecv(SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount, LPDWORD lpNumberOfBytesRecvd, LPDWORD lpFlags, LPWSAOVERLAPPED lpOverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine) {
    std::cout << "\n Hook_WSARecv \n\n";
    return WSARecv(s, lpBuffers, dwBufferCount, lpNumberOfBytesRecvd, lpFlags, lpOverlapped, lpCompletionRoutine);
}

int WSAAPI Hook_connect(SOCKET s, const sockaddr* name, int namelen) {
    std::cout << "\n Hook_connect \n\n";
    return connect(s, name, namelen);
}

SC_HANDLE Hook_CreateServiceA(SC_HANDLE hSCManager, LPCSTR lpServiceName, LPCSTR lpDisplayName, DWORD dwDesiredAccess, DWORD dwServiceType, DWORD dwStartType, DWORD dwErrorControl, LPCSTR lpBinaryPathName, LPCSTR lpLoadOrderGroup, LPDWORD lpdwTagId, LPCSTR lpDependencies, LPCSTR lpServiceStartName, LPCSTR lpPassword) {
    std::cout << "\n Hook_CreateServiceA \n\n";
    char buf[500] = "CreateServiceA";
    DWORD cbWritten;
    DWORD dwBytesToWrite = (DWORD)strlen(buf);
    WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
    return CreateServiceA(hSCManager, lpServiceName, lpDisplayName, dwDesiredAccess, dwServiceType, dwStartType, dwErrorControl, lpBinaryPathName, lpLoadOrderGroup, lpdwTagId, lpDependencies, lpServiceStartName, lpPassword);
}

BOOL Hook_StartServiceA(SC_HANDLE hService, DWORD dwNumServiceArgs, LPCSTR* lpServiceArgVectors) {
    std::cout << "\n Hook_StartServiceA \n\n";
    char buf[500] = "StartServiceA";
    DWORD cbWritten;
    DWORD dwBytesToWrite = (DWORD)strlen(buf);
    WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
    return StartServiceA(hService, dwNumServiceArgs, lpServiceArgVectors);
}

BOOL Hook_ChangeServiceConfigA(SC_HANDLE hService, DWORD dwServiceType, DWORD dwStartType, DWORD dwErrorControl, LPCSTR lpBinaryPathName, LPCSTR lpLoadOrderGroup, LPDWORD lpdwTagId, LPCSTR lpDependencies, LPCSTR lpServiceStartName, LPCSTR lpPassword, LPCSTR lpDisplayName) {
    std::cout << "\n Hook_ChangeServiceConfigA \n\n";
    //char buf[500] = "ChangeServiceConfigA";
    //DWORD cbWritten;
    //DWORD dwBytesToWrite = (DWORD)strlen(buf);
    //WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
    return ChangeServiceConfigA(hService, dwServiceType, dwStartType, dwErrorControl, lpBinaryPathName, lpLoadOrderGroup, lpdwTagId, lpDependencies, lpServiceStartName, lpPassword, lpDisplayName);
}

UINT Hook_GetSystemDirectoryW(LPWSTR lpBuffer, UINT uSize) {
    std::cout << "\n Hook_GetSystemDirectoryW \n\n";
    return GetSystemDirectoryW(lpBuffer, uSize);
}

void Hook_GetSystemTime(LPSYSTEMTIME lpSystemTime) {
    std::cout << "\n Hook_GetSystemTime \n\n";
    GetSystemTime(lpSystemTime);
}

HMODULE Hook_GetModuleHandleA(LPCSTR lpModuleName) {
    std::cout << "\n Hook_GetModuleHandleA \n\n";
    return GetModuleHandleA(lpModuleName);
}

FARPROC Hook_GetProcAddress(HMODULE hModule, LPCSTR lpProcName) {
    std::cout << "\n Hook_GetProcAddress \n\n";
    char buf[500] = "GetProcAddress";
    DWORD cbWritten;
    DWORD dwBytesToWrite = (DWORD)strlen(buf);
    WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
    return GetProcAddress(hModule, lpProcName);
}

DWORD Hook_GetModuleFileNameA(HMODULE hModule, LPSTR lpFilename, DWORD nSize) {
    std::cout << "\n Hook_GetModuleFileNameA \n\n";
    char buf[500] = "GetModuleFileNameA";
    DWORD cbWritten;
    DWORD dwBytesToWrite = (DWORD)strlen(buf);
    WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
    return GetModuleFileNameA(hModule, lpFilename, nSize);
}

HMODULE Hook_LoadLibraryA(LPCSTR lpLibFileName) {
    std::cout << "\n Hook_LoadLibraryA \n\n";
    char buf[500] = "LoadLibraryA";
    DWORD cbWritten;
    DWORD dwBytesToWrite = (DWORD)strlen(buf);
    WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
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

