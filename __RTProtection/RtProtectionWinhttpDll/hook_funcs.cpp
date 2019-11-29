#include "pch.h"
#include "hook_funcs.h"

extern HANDLE hPipe1;

BOOL winhttp_ns::Hook_WinHttpAddRequestHeaders(
    IN winhttp_ns::HINTERNET hRequest,
    LPCWSTR      lpszHeaders,
    IN DWORD     dwHeadersLength,
    IN DWORD     dwModifiers
) {
    std::cout << "\n Hook_WinHttpAddRequestHeaders \n\n";
    char buf[500] = "WinHttpAddRequestHeaders";
    DWORD cbWritten;
    DWORD dwBytesToWrite = (DWORD)strlen(buf);
    WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
    return winhttp_ns::WinHttpAddRequestHeaders(hRequest, lpszHeaders, dwHeadersLength, dwModifiers);
}

winhttp_ns::HINTERNET winhttp_ns::Hook_WinHttpConnect(
    IN winhttp_ns::HINTERNET     hSession,
    IN LPCWSTR       pswzServerName,
    IN winhttp_ns::INTERNET_PORT nServerPort,
    IN DWORD         dwReserved
) {
    std::cout << "\n Hook_WinHttpConnect \n\n";
    char buf[500] = "WinHttpConnect";
    DWORD cbWritten;
    DWORD dwBytesToWrite = (DWORD)strlen(buf);
    WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
    return winhttp_ns::WinHttpConnect(hSession, pswzServerName, nServerPort, dwReserved);
}
