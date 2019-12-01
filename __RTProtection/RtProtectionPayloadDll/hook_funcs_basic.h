#pragma once
BOOL WINAPI Hook_Beep(DWORD dwFreq, DWORD dwDuration);

//Input/output Create 	A 	CreatefileA CreatePipe CreateNamedPipeA ‎Kernel32
HANDLE WINAPI Hook_CreateFileA(
    LPCSTR                lpFileName,
    DWORD                 dwDesiredAccess,
    DWORD                 dwShareMode,
    LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    DWORD                 dwCreationDisposition,
    DWORD                 dwFlagsAndAttributes,
    HANDLE                hTemplateFile
);

HANDLE WINAPI Hook_CreateFileW(
    LPCWSTR               lpFileName,
    DWORD                 dwDesiredAccess,
    DWORD                 dwShareMode,
    LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    DWORD                 dwCreationDisposition,
    DWORD                 dwFlagsAndAttributes,
    HANDLE                hTemplateFile
);

BOOL WINAPI Hook_CreatePipe(
    PHANDLE               hReadPipe,
    PHANDLE               hWritePipe,
    LPSECURITY_ATTRIBUTES lpPipeAttributes,
    DWORD                 nSize
);

HANDLE WINAPI Hook_CreateNamedPipeA(
    LPCSTR                lpName,
    DWORD                 dwOpenMode,
    DWORD                 dwPipeMode,
    DWORD                 nMaxInstances,
    DWORD                 nOutBufferSize,
    DWORD                 nInBufferSize,
    DWORD                 nDefaultTimeOut,
    LPSECURITY_ATTRIBUTES lpSecurityAttributes
);


//Input/output Open 	B 	10 	OpenFile, OpenFileMappingA Kernel32
HFILE Hook_OpenFile(
    LPCSTR     lpFileName,
    LPOFSTRUCT lpReOpenBuff,
    UINT       uStyle
);

HANDLE Hook_OpenFileMappingA(
    DWORD  dwDesiredAccess,
    BOOL   bInheritHandle,
    LPCSTR lpName
);

//Input/output Write 	C 	25 	WriteFile, WriteConsoleW, WriteFileEx
BOOL Hook_WriteFile(
    HANDLE       hFile,
    LPCVOID      lpBuffer,
    DWORD        nNumberOfBytesToWrite,
    LPDWORD      lpNumberOfBytesWritten,
    LPOVERLAPPED lpOverlapped
);

BOOL WINAPI Hook_WriteConsole(
    _In_             HANDLE  hConsoleOutput,
    _In_       const VOID* lpBuffer,
    _In_             DWORD   nNumberOfCharsToWrite,
    _Out_            LPDWORD lpNumberOfCharsWritten,
    _Reserved_       LPVOID  lpReserved
);

BOOL Hook_WriteFileEx(
    HANDLE                          hFile,
    LPCVOID                         lpBuffer,
    DWORD                           nNumberOfBytesToWrite,
    LPOVERLAPPED                    lpOverlapped,
    LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
);

//Input/output Find 	D 	13 	FindFirstFileA, FindNextFileW
HANDLE Hook_FindFirstFileA(
    LPCSTR             lpFileName,
    LPWIN32_FIND_DATAA lpFindFileData
);

HANDLE Hook_FindFirstFileW(
    LPCWSTR            lpFileName,
    LPWIN32_FIND_DATAW lpFindFileData
);

//Input/output Read 	E 	18 	ReadFile, ReadFileEx, ReadConsoleA
BOOL Hook_ReadFile(
    HANDLE       hFile,
    LPVOID       lpBuffer,
    DWORD        nNumberOfBytesToRead,
    LPDWORD      lpNumberOfBytesRead,
    LPOVERLAPPED lpOverlapped
);

//Input/output Access 	F 	19 	SetFileAttributesW, SetConsoleMode
BOOL Hook_SetFileAttributesW(
    LPCWSTR lpFileName,
    DWORD   dwFileAttributes
);

//Loading Library 	G 	7 	LoadLibraryExW, FreeLibrary
HMODULE Hook_LoadLibraryExW(
    LPCWSTR lpLibFileName,
    HANDLE  hFile,
    DWORD   dwFlags
);
BOOL Hook_FreeLibrary(
    HMODULE hLibModule
);

//Registry Read 	H 	15 	RegOpenKeyExW, RegQueryValueA Advapi32
LSTATUS Hook_RegOpenKeyExW(
    HKEY    hKey,
    LPCWSTR lpSubKey,
    DWORD   ulOptions,
    REGSAM  samDesired,
    PHKEY   phkResult
);
LSTATUS Hook_RegQueryValueA(
    HKEY   hKey,
    LPCSTR lpSubKey,
    LPSTR  lpData,
    PLONG  lpcbData
);


//Registry Write 	I 	13 	RegSetValueA, RegSetValueW Advapi32
LSTATUS Hook_RegSetValueA(
    HKEY   hKey,
    LPCSTR lpSubKey,
    DWORD  dwType,
    LPCSTR lpData,
    DWORD  cbData
);
LSTATUS Hook_RegSetValueW(
    HKEY    hKey,
    LPCWSTR lpSubKey,
    DWORD   dwType,
    LPCWSTR lpData,
    DWORD   cbData
);

//Process Create 	K 	10 	CreateProcessA, ShellExecute, WinExec Kernel32
BOOL Hook_CreateProcessA(
    LPCSTR                lpApplicationName,
    LPSTR                 lpCommandLine,
    LPSECURITY_ATTRIBUTES lpProcessAttributes,
    LPSECURITY_ATTRIBUTES lpThreadAttributes,
    BOOL                  bInheritHandles,
    DWORD                 dwCreationFlags,
    LPVOID                lpEnvironment,
    LPCSTR                lpCurrentDirectory,
    LPSTARTUPINFOA        lpStartupInfo,
    LPPROCESS_INFORMATION lpProcessInformation
);
UINT Hook_WinExec(
    LPCSTR lpCmdLine,
    UINT   uCmdShow
);

//Process Read 	L 	33 	GetCurrentThreadId, ReadProcessMemory
DWORD Hook_GetCurrentThreadId(

);

BOOL Hook_ReadProcessMemory(
    HANDLE  hProcess,
    LPCVOID lpBaseAddress,
    LPVOID  lpBuffer,
    SIZE_T  nSize,
    SIZE_T* lpNumberOfBytesRead
);

//Process Write 	M 	10 	WriteProcessMemory, VirtualAllocEx
BOOL Hook_WriteProcessMemory(
    HANDLE  hProcess,
    LPVOID  lpBaseAddress,
    LPCVOID lpBuffer,
    SIZE_T  nSize,
    SIZE_T* lpNumberOfBytesWritten
);
LPVOID Hook_VirtualAllocEx(
    HANDLE hProcess,
    LPVOID lpAddress,
    SIZE_T dwSize,
    DWORD  flAllocationType,
    DWORD  flProtect
);

//Process Change 	N 	12 	SetThreadContext, SetProcessAffinityMask
BOOL Hook_SetThreadContext(
    HANDLE        hThread,
    const CONTEXT* lpContext
);
BOOL Hook_SetProcessAffinityMask(
    HANDLE    hProcess,
    DWORD_PTR dwProcessAffinityMask
);

//Process Exit 	O 	3 	TerminateProcess, ExitProcess
BOOL Hook_TerminateProcess(
    HANDLE hProcess,
    UINT   uExitCode
);
void Hook_ExitProcess(
    UINT uExitCode
);

//Hooking 	P 	5 	SetWindowsHookA, CallNextHookEx User32
HHOOK Hook_SetWindowsHookExA(
    int       idHook,
    HOOKPROC  lpfn,
    HINSTANCE hmod,
    DWORD     dwThreadId
);
LRESULT Hook_CallNextHookEx(
    HHOOK  hhk,
    int    nCode,
    WPARAM wParam,
    LPARAM lParam
);

//Anti-Debugging 	Q 	4 	IsDebuggerPresent, OutputDebugStringA Kernel32
BOOL Hook_IsDebuggerPresent(

);
void Hook_OutputDebugStringA(
    LPCSTR lpOutputString
);

//Synchronization 	R 	13 	CreateMutexA, CreateSemaphoreW
HANDLE Hook_CreateMutexA(
    LPSECURITY_ATTRIBUTES lpMutexAttributes,
    BOOL                  bInitialOwner,
    LPCSTR                lpName
);
HANDLE Hook_CreateSemaphoreW(
    LPSECURITY_ATTRIBUTES lpSemaphoreAttributes,
    LONG                  lInitialCount,
    LONG                  lMaximumCount,
    LPCWSTR               lpName
);

//Device Control 	S 	6 	DeviceIoControl, GetDriveTypeW
BOOL Hook_DeviceIoControl(
    HANDLE       hDevice,
    DWORD        dwIoControlCode,
    LPVOID       lpInBuffer,
    DWORD        nInBufferSize,
    LPVOID       lpOutBuffer,
    DWORD        nOutBufferSize,
    LPDWORD      lpBytesReturned,
    LPOVERLAPPED lpOverlapped
);
UINT Hook_GetDriveTypeW(
    LPCWSTR lpRootPathName
);

//Socket Comm. 	T 	70 	Send, Recv, WSARecv, Connect Ws2_32
int WSAAPI Hook_send(
    SOCKET     s,
    const char* buf,
    int        len,
    int        flags
);
int Hook_recv(
    SOCKET s,
    char* buf,
    int    len,
    int    flags
);
int WSAAPI Hook_WSARecv(
    SOCKET                             s,
    LPWSABUF                           lpBuffers,
    DWORD                              dwBufferCount,
    LPDWORD                            lpNumberOfBytesRecvd,
    LPDWORD                            lpFlags,
    LPWSAOVERLAPPED                    lpOverlapped,
    LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
);
int WSAAPI Hook_connect(
    SOCKET         s,
    const sockaddr* name,
    int            namelen
);

//Win-Service Create 	X 	2 	CreateServiceA ‎Advapi32
SC_HANDLE Hook_CreateServiceA(
    SC_HANDLE hSCManager,
    LPCSTR    lpServiceName,
    LPCSTR    lpDisplayName,
    DWORD     dwDesiredAccess,
    DWORD     dwServiceType,
    DWORD     dwStartType,
    DWORD     dwErrorControl,
    LPCSTR    lpBinaryPathName,
    LPCSTR    lpLoadOrderGroup,
    LPDWORD   lpdwTagId,
    LPCSTR    lpDependencies,
    LPCSTR    lpServiceStartName,
    LPCSTR    lpPassword
);

//Win-Service Other 	Y 	11 	StartServiceW, ChangeServiceConfigA ‎Advapi32
BOOL Hook_StartServiceA(
    SC_HANDLE hService,
    DWORD     dwNumServiceArgs,
    LPCSTR* lpServiceArgVectors
);
BOOL Hook_ChangeServiceConfigA(
    SC_HANDLE hService,
    DWORD     dwServiceType,
    DWORD     dwStartType,
    DWORD     dwErrorControl,
    LPCSTR    lpBinaryPathName,
    LPCSTR    lpLoadOrderGroup,
    LPDWORD   lpdwTagId,
    LPCSTR    lpDependencies,
    LPCSTR    lpServiceStartName,
    LPCSTR    lpPassword,
    LPCSTR    lpDisplayName
);

//System Information 	Z 	35 	GetSystemDirectoryW, GetSystemTime ‎Kernel32
UINT Hook_GetSystemDirectoryW(
    LPWSTR lpBuffer,
    UINT   uSize
);
void Hook_GetSystemTime(
    LPSYSTEMTIME lpSystemTime
);

//GetModuleHandle
HMODULE Hook_GetModuleHandleA(
    LPCSTR lpModuleName
);

//GetProcAddress
FARPROC Hook_GetProcAddress(
    HMODULE hModule,
    LPCSTR  lpProcName
);

//GetModuleFileName
DWORD Hook_GetModuleFileNameA(
    HMODULE hModule,
    LPSTR   lpFilename,
    DWORD   nSize
);

//LoadLibrary
HMODULE Hook_LoadLibraryA(
    LPCSTR lpLibFileName
);
