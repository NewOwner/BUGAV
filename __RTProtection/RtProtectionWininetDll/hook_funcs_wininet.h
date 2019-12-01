#pragma once
namespace wininet_ns {
#include <WinInet.h>

    BOOL Hook_FtpCommandA(
        HINTERNET hConnect,
        BOOL      fExpectResponse,
        DWORD     dwFlags,
        LPCSTR    lpszCommand,
        DWORD_PTR dwContext,
        HINTERNET* phFtpCommand
    );

    BOOL Hook_FtpCreateDirectoryA(
        HINTERNET hConnect,
        LPCSTR    lpszDirectory
    );

    BOOL Hook_FtpDeleteFileA(
        HINTERNET hConnect,
        LPCSTR    lpszFileName
    );

    void Hook_FtpFindFirstFileA(
        HINTERNET          hConnect,
        LPCSTR             lpszSearchFile,
        LPWIN32_FIND_DATAA lpFindFileData,
        DWORD              dwFlags,
        DWORD_PTR          dwContext
    );

    BOOL Hook_FtpGetCurrentDirectoryA(
        HINTERNET hConnect,
        LPSTR     lpszCurrentDirectory,
        LPDWORD   lpdwCurrentDirectory
    );

    BOOL Hook_FtpGetFileA(
        HINTERNET hConnect,
        LPCSTR    lpszRemoteFile,
        LPCSTR    lpszNewFile,
        BOOL      fFailIfExists,
        DWORD     dwFlagsAndAttributes,
        DWORD     dwFlags,
        DWORD_PTR dwContext
    );

    BOOL Hook_FtpGetFileEx(
        HINTERNET hFtpSession,
        LPCSTR lpszRemoteFile,
        LPCTSTR lpszNewFile,
        BOOL fFailIfExists,
        DWORD dwFlagsAndAttributes,
        DWORD dwFlags,
        DWORD dwContext
    );

    BOOL Hook_FtpPutFileA(
        HINTERNET hConnect,
        LPCSTR    lpszLocalFile,
        LPCSTR    lpszNewRemoteFile,
        DWORD     dwFlags,
        DWORD_PTR dwContext
    );

    BOOL Hook_FtpPutFileEx(
        HINTERNET hFtpSession,
        LPCTSTR lpszLocalFile,
        LPCSTR lpszNewRemoteFile,
        DWORD dwFlags,
        DWORD dwContext
    );

    BOOL Hook_HttpAddRequestHeadersA(
        HINTERNET hRequest,
        LPCSTR    lpszHeaders,
        DWORD     dwHeadersLength,
        DWORD     dwModifiers
    );

    BOOL Hook_HttpQueryInfoA(
        HINTERNET hRequest,
        DWORD     dwInfoLevel,
        LPVOID    lpBuffer,
        LPDWORD   lpdwBufferLength,
        LPDWORD   lpdwIndex
    );

    BOOL Hook_HttpSendRequestA(
        HINTERNET hRequest,
        LPCSTR    lpszHeaders,
        DWORD     dwHeadersLength,
        LPVOID    lpOptional,
        DWORD     dwOptionalLength
    );

    BOOL Hook_HttpSendRequestExA(
        HINTERNET           hRequest,
        LPINTERNET_BUFFERSA lpBuffersIn,
        LPINTERNET_BUFFERSA lpBuffersOut,
        DWORD               dwFlags,
        DWORD_PTR           dwContext
    );

    HINTERNET Hook_InternetConnectA(
        HINTERNET     hInternet,
        LPCSTR        lpszServerName,
        INTERNET_PORT nServerPort,
        LPCSTR        lpszUserName,
        LPCSTR        lpszPassword,
        DWORD         dwService,
        DWORD         dwFlags,
        DWORD_PTR     dwContext
    );

    BOOL Hook_InternetGetCookieA(
        LPCSTR  lpszUrl,
        LPCSTR  lpszCookieName,
        LPSTR   lpszCookieData,
        LPDWORD lpdwSize
    );

    BOOL Hook_InternetGetCookieExA(
        LPCSTR  lpszUrl,
        LPCSTR  lpszCookieName,
        LPSTR   lpszCookieData,
        LPDWORD lpdwSize,
        DWORD   dwFlags,
        LPVOID  lpReserved
    );

    BOOL Hook_InternetSetCookieA(
        LPCSTR lpszUrl,
        LPCSTR lpszCookieName,
        LPCSTR lpszCookieData
    );

    DWORD Hook_InternetSetCookieExA(
        LPCSTR    lpszUrl,
        LPCSTR    lpszCookieName,
        LPCSTR    lpszCookieData,
        DWORD     dwFlags,
        DWORD_PTR dwReserved
    );


}