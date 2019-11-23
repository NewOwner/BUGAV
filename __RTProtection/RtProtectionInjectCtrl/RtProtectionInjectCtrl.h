#pragma once

#include <tchar.h>

#include <iostream>
#include <string>
#include <cstring>

#include <easyhook.h>

class RtProtectionInjectCtrl {
public:
    RtProtectionInjectCtrl();
    ~RtProtectionInjectCtrl();

    VOID InjectLib(DWORD pid, PWCHAR dll_to_inject, PVOID dll_data, ULONG data_sz);
};


/*
Input/output Create 	A 	14 	CreatefileA, CreatePipe, CreateNamedPipeA
Input/output Open 	B 	10 	OpenFile, OpenFileMappingA
Input/output Write 	C 	25 	WriteFile, WriteConsoleW, WriteFileEx
Input/output Find 	D 	13 	FindFirstFileA, FindNextFileW
Input/output Read 	E 	18 	ReadFile, ReadFileEx, ReadConsoleA
Input/output Access 	F 	19 	SetFileAttributesW, SetConsoleMode
Loading Library 	G 	7 	LoadLibraryExW, FreeLibrary
Registry Read 	H 	15 	RegOpenKeyExW, RegQueryValueA
Registry Write 	I 	13 	RegSetValueA, RegSetValueW
COM/OLE/DDE 	J 	154 	OleCreate, OleLoad, CoBuildVersion
Process Create 	K 	10 	CreateProcessA, ShellExecute, WinExec
Process Read 	L 	33 	GetCurrentThreadId, ReadProcessMemory
Process Write 	M 	10 	WriteProcessMemory, VirtualAllocEx
Process Change 	N 	12 	SetThreadContext, SetProcessAffinityMask
Process Exit 	O 	3 	TerminateProcess, ExitProcess
Hooking 	P 	5 	SetWindowsHookA, CallNextHookEx
Anti-Debugging 	Q 	4 	IsDebuggerPresent, OutputDebugStringA
Synchronization 	R 	13 	CreateMutexA, CreateSemaphoreW
Device Control 	S 	6 	DeviceIoControl, GetDriveTypeW
Socket Comm. 	T 	70 	Send, Recv, WSARecv, Connect
Network Information 	U 	17 	Gethostbyname, InternetGetConnectedState
Internet Open/ Read 	V 	13 	InternetOpenUrlA, InternetReadFile
Internet Write 	W 	2 	InternetWriteFile, TransactNamedPipe
Win-Service Create 	X 	2 	CreateServiceW, CreateServiceA
Win-Service Other 	Y 	11 	StartServiceW, ChangeServiceConfigA
System Information 	Z 	35 	GetSystemDirectoryW, GetSystemTime
*/

struct InjectInfo{
    enum ActEnum{spy};
    std::string func_name;
    std::string func_module;
};