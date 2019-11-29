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

    BOOL Hook_WinHttpCreateUrl(
        LPURL_COMPONENTS lpUrlComponents,
        DWORD            dwFlags,
        LPWSTR           pwszUrl,
        LPDWORD          pdwUrlLength
    );

    HINTERNET Hook_WinHttpOpen(
        LPCWSTR pszAgentW,
        DWORD   dwAccessType,
        LPCWSTR pszProxyW,
        LPCWSTR pszProxyBypassW,
        DWORD   dwFlags
    );

    HINTERNET Hook_WinHttpOpenRequest(
        IN HINTERNET hConnect,
        IN LPCWSTR   pwszVerb,
        IN LPCWSTR   pwszObjectName,
        IN LPCWSTR   pwszVersion,
        IN LPCWSTR   pwszReferrer,
        IN LPCWSTR* ppwszAcceptTypes,
        IN DWORD     dwFlags
    );

    BOOL Hook_WinHttpQueryDataAvailable(
        IN HINTERNET hRequest,
        LPDWORD      lpdwNumberOfBytesAvailable
    );

    BOOL Hook_WinHttpQueryHeaders(
        IN HINTERNET   hRequest,
        IN DWORD       dwInfoLevel,
        IN LPCWSTR     pwszName,
        LPVOID         lpBuffer,
        IN OUT LPDWORD lpdwBufferLength,
        IN OUT LPDWORD lpdwIndex
    );

    BOOL Hook_WinHttpReadData(
        IN HINTERNET hRequest,
        LPVOID       lpBuffer,
        IN DWORD     dwNumberOfBytesToRead,
        OUT LPDWORD  lpdwNumberOfBytesRead
    );

    BOOL Hook_WinHttpReceiveResponse(
        IN HINTERNET hRequest,
        IN LPVOID    lpReserved
    );

    BOOL Hook_WinHttpSendRequest(
        IN HINTERNET hRequest,
        LPCWSTR      lpszHeaders,
        IN DWORD     dwHeadersLength,
        LPVOID       lpOptional,
        IN DWORD     dwOptionalLength,
        IN DWORD     dwTotalLength,
        IN DWORD_PTR dwContext
    );

    BOOL Hook_WinHttpSetCredentials(
        IN HINTERNET hRequest,
        IN DWORD     AuthTargets,
        IN DWORD     AuthScheme,
        IN LPCWSTR   pwszUserName,
        IN LPCWSTR   pwszPassword,
        IN LPVOID    pAuthParams
    );

    BOOL Hook_WinHttpWriteData(
        IN HINTERNET hRequest,
        LPCVOID      lpBuffer,
        IN DWORD     dwNumberOfBytesToWrite,
        OUT LPDWORD  lpdwNumberOfBytesWritten
    );

}