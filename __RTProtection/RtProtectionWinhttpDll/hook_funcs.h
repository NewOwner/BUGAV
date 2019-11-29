#pragma once
namespace winhttp_ns {
#include <winhttp.h>
#include <Winsock2.h>

    BOOL Hook_WinHttpAddRequestHeaders(
        IN HINTERNET hRequest,
        LPCWSTR      lpszHeaders,
        IN DWORD     dwHeadersLength,
        IN DWORD     dwModifiers
    );

    HINTERNET Hook_WinHttpConnect(
        IN HINTERNET     hSession,
        IN LPCWSTR       pswzServerName,
        IN INTERNET_PORT nServerPort,
        IN DWORD         dwReserved
    );

}