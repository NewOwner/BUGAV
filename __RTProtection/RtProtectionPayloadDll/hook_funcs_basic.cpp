#include "pch.h"
#include "hook_funcs_basic.h"

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

HMODULE Hook_LoadLibraryExW(LPCWSTR lpLibFileName, HANDLE hFile, DWORD dwFlags) {
    std::cout << "\n Hook_LoadLibraryExW \n\n";
    char buf[500] = "LoadLibraryExW";
    DWORD cbWritten;
    DWORD dwBytesToWrite = (DWORD)strlen(buf);
    WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
    return LoadLibraryExW(lpLibFileName, hFile, dwFlags);
}

UINT Hook_WinExec(LPCSTR lpCmdLine, UINT uCmdShow) {
    std::cout << "\n Hook_WinExec \n\n";
    char buf[500] = "WinExec";
    DWORD cbWritten;
    DWORD dwBytesToWrite = (DWORD)strlen(buf);
    WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
    return WinExec(lpCmdLine, uCmdShow);
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

SC_HANDLE Hook_CreateServiceA(SC_HANDLE hSCManager, LPCSTR lpServiceName, LPCSTR lpDisplayName, DWORD dwDesiredAccess, DWORD dwServiceType, DWORD dwStartType, DWORD dwErrorControl, LPCSTR lpBinaryPathName, LPCSTR lpLoadOrderGroup, LPDWORD lpdwTagId, LPCSTR lpDependencies, LPCSTR lpServiceStartName, LPCSTR lpPassword) {
    std::cout << "\n Hook_CreateServiceA \n\n";
    char buf[500] = "CreateServiceA";
    DWORD cbWritten;
    DWORD dwBytesToWrite = (DWORD)strlen(buf);
    WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
    return CreateServiceA(hSCManager, lpServiceName, lpDisplayName, dwDesiredAccess, dwServiceType, dwStartType, dwErrorControl, lpBinaryPathName, lpLoadOrderGroup, lpdwTagId, lpDependencies, lpServiceStartName, lpPassword);
}

UINT Hook_GetSystemDirectoryW(LPWSTR lpBuffer, UINT uSize) {
    std::cout << "\n Hook_GetSystemDirectoryW \n\n";
    return GetSystemDirectoryW(lpBuffer, uSize);
}

void Hook_GetSystemTime(LPSYSTEMTIME lpSystemTime) {
    std::cout << "\n Hook_GetSystemTime \n\n";
    GetSystemTime(lpSystemTime);
}

FARPROC Hook_GetProcAddress(HMODULE hModule, LPCSTR lpProcName) {
    std::cout << "\n Hook_GetProcAddress \n\n";
    char buf[500] = "GetProcAddress";
    DWORD cbWritten;
    DWORD dwBytesToWrite = (DWORD)strlen(buf);
    WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
    return GetProcAddress(hModule, lpProcName);
}

