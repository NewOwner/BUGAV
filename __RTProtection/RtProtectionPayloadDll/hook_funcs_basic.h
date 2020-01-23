#pragma once
BOOL WINAPI Hook_Beep(DWORD dwFreq, DWORD dwDuration);

HMODULE Hook_LoadLibraryExW(LPCWSTR lpLibFileName, HANDLE hFile, DWORD dwFlags);
UINT Hook_WinExec(LPCSTR lpCmdLine, UINT uCmdShow);
BOOL Hook_ReadProcessMemory(HANDLE hProcess, LPCVOID lpBaseAddress, LPVOID lpBuffer, SIZE_T nSize, SIZE_T* lpNumberOfBytesRead);
BOOL Hook_WriteProcessMemory(HANDLE hProcess, LPVOID lpBaseAddress, LPCVOID lpBuffer, SIZE_T nSize, SIZE_T* lpNumberOfBytesWritten);
HHOOK Hook_SetWindowsHookExA(int idHook, HOOKPROC lpfn, HINSTANCE hmod, DWORD dwThreadId);
LRESULT Hook_CallNextHookEx(HHOOK hhk, int nCode, WPARAM wParam, LPARAM lParam);
BOOL Hook_IsDebuggerPresent();
SC_HANDLE Hook_CreateServiceA(SC_HANDLE hSCManager, LPCSTR lpServiceName, LPCSTR lpDisplayName, DWORD dwDesiredAccess, DWORD dwServiceType, DWORD dwStartType, DWORD dwErrorControl, LPCSTR lpBinaryPathName, LPCSTR lpLoadOrderGroup, LPDWORD lpdwTagId, LPCSTR lpDependencies, LPCSTR lpServiceStartName, LPCSTR lpPassword);
UINT Hook_GetSystemDirectoryW(LPWSTR lpBuffer, UINT uSize);
void Hook_GetSystemTime(LPSYSTEMTIME lpSystemTime);
FARPROC Hook_GetProcAddress(HMODULE hModule, LPCSTR lpProcName);