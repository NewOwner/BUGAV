#include "pch.h"
#include "hook_funcs_wininet.h"

extern HANDLE hPipe1;

namespace wininet_ns {

    BOOL Hook_FtpCommandA(
        HINTERNET hConnect,
        BOOL      fExpectResponse,
        DWORD     dwFlags,
        LPCSTR    lpszCommand,
        DWORD_PTR dwContext,
        HINTERNET* phFtpCommand
    ) {
        std::cout << "\n Hook_FtpCommandA \n\n";
        char buf[500] = "FtpCommandA";
        DWORD cbWritten;
        DWORD dwBytesToWrite = (DWORD)strlen(buf);
        WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
        return FtpCommandA(
            hConnect,
            fExpectResponse,
            dwFlags,
            lpszCommand,
            dwContext,
            phFtpCommand
        );
    }


    BOOL Hook_FtpCreateDirectoryA(
        HINTERNET hConnect,
        LPCSTR    lpszDirectory
    ) {
        std::cout << "\n Hook_FtpCreateDirectoryA \n\n";
        char buf[500] = "FtpCreateDirectoryA";
        DWORD cbWritten;
        DWORD dwBytesToWrite = (DWORD)strlen(buf);
        WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
        return FtpCreateDirectoryA(
            hConnect,
            lpszDirectory
        );
    }

    BOOL Hook_FtpDeleteFileA(
        HINTERNET hConnect,
        LPCSTR    lpszFileName
    ) {
        std::cout << "\n Hook_FtpDeleteFileA \n\n";
        char buf[500] = "FtpDeleteFileA";
        DWORD cbWritten;
        DWORD dwBytesToWrite = (DWORD)strlen(buf);
        WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
        return FtpDeleteFileA(
            hConnect,
            lpszFileName
        );
    }

    void Hook_FtpFindFirstFileA(
        HINTERNET          hConnect,
        LPCSTR             lpszSearchFile,
        LPWIN32_FIND_DATAA lpFindFileData,
        DWORD              dwFlags,
        DWORD_PTR          dwContext
    ) {
        std::cout << "\n Hook_FtpFindFirstFileA \n\n";
        char buf[500] = "FtpFindFirstFileA";
        DWORD cbWritten;
        DWORD dwBytesToWrite = (DWORD)strlen(buf);
        WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
        FtpFindFirstFileA(
            hConnect,
            lpszSearchFile,
            lpFindFileData,
            dwFlags,
            dwContext
        );
    }

    BOOL Hook_FtpGetCurrentDirectoryA(
        HINTERNET hConnect,
        LPSTR     lpszCurrentDirectory,
        LPDWORD   lpdwCurrentDirectory
    ) {
        std::cout << "\n Hook_FtpGetCurrentDirectoryA \n\n";
        char buf[500] = "FtpGetCurrentDirectoryA";
        DWORD cbWritten;
        DWORD dwBytesToWrite = (DWORD)strlen(buf);
        WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
        return FtpGetCurrentDirectoryA(
            hConnect,
            lpszCurrentDirectory,
            lpdwCurrentDirectory
        );
    }

    BOOL Hook_FtpGetFileA(
        HINTERNET hConnect,
        LPCSTR    lpszRemoteFile,
        LPCSTR    lpszNewFile,
        BOOL      fFailIfExists,
        DWORD     dwFlagsAndAttributes,
        DWORD     dwFlags,
        DWORD_PTR dwContext
    ) {
        std::cout << "\n Hook_FtpGetFileA \n\n";
        char buf[500] = "FtpGetFileA";
        DWORD cbWritten;
        DWORD dwBytesToWrite = (DWORD)strlen(buf);
        WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
        return FtpGetFileA(
            hConnect,
            lpszRemoteFile,
            lpszNewFile,
            fFailIfExists,
            dwFlagsAndAttributes,
            dwFlags,
            dwContext
        );
    }


    BOOL Hook_FtpGetFileEx(
        HINTERNET hFtpSession,
        LPCSTR lpszRemoteFile,
        LPCTSTR lpszNewFile,
        BOOL fFailIfExists,
        DWORD dwFlagsAndAttributes,
        DWORD dwFlags,
        DWORD dwContext
    ) {
        std::cout << "\n Hook_FtpGetFileEx \n\n";
        char buf[500] = "FtpGetFileEx";
        DWORD cbWritten;
        DWORD dwBytesToWrite = (DWORD)strlen(buf);
        WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
        return FtpGetFileEx(
            hFtpSession,
            lpszRemoteFile,
            lpszNewFile,
            fFailIfExists,
            dwFlagsAndAttributes,
            dwFlags,
            dwContext
        );
    }

    BOOL Hook_FtpPutFileA(
        HINTERNET hConnect,
        LPCSTR    lpszLocalFile,
        LPCSTR    lpszNewRemoteFile,
        DWORD     dwFlags,
        DWORD_PTR dwContext
    ) {
        std::cout << "\n Hook_FtpPutFileA \n\n";
        char buf[500] = "FtpPutFileA";
        DWORD cbWritten;
        DWORD dwBytesToWrite = (DWORD)strlen(buf);
        WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
        return FtpPutFileA(
            hConnect,
            lpszLocalFile,
            lpszNewRemoteFile,
            dwFlags,
            dwContext
        );
    }

    BOOL Hook_FtpPutFileEx(
        HINTERNET hFtpSession,
        LPCTSTR lpszLocalFile,
        LPCSTR lpszNewRemoteFile,
        DWORD dwFlags,
        DWORD dwContext
    ) {
        std::cout << "\n Hook_FtpPutFileEx \n\n";
        char buf[500] = "FtpPutFileEx";
        DWORD cbWritten;
        DWORD dwBytesToWrite = (DWORD)strlen(buf);
        WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
        return FtpPutFileEx(
            hFtpSession,
            lpszLocalFile,
            lpszNewRemoteFile,
            dwFlags,
            dwContext
        );
    }

    BOOL Hook_HttpAddRequestHeadersA(
        HINTERNET hRequest,
        LPCSTR    lpszHeaders,
        DWORD     dwHeadersLength,
        DWORD     dwModifiers
    ) {
        std::cout << "\n Hook_HttpAddRequestHeadersA \n\n";
        char buf[500] = "HttpAddRequestHeadersA";
        DWORD cbWritten;
        DWORD dwBytesToWrite = (DWORD)strlen(buf);
        WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
        return HttpAddRequestHeadersA(
            hRequest,
            lpszHeaders,
            dwHeadersLength,
            dwModifiers
        );
    }

    BOOL Hook_HttpQueryInfoA(
        HINTERNET hRequest,
        DWORD     dwInfoLevel,
        LPVOID    lpBuffer,
        LPDWORD   lpdwBufferLength,
        LPDWORD   lpdwIndex
    ) {
        std::cout << "\n Hook_HttpQueryInfoA \n\n";
        char buf[500] = "HttpQueryInfoA";
        DWORD cbWritten;
        DWORD dwBytesToWrite = (DWORD)strlen(buf);
        WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
        return HttpQueryInfoA(
            hRequest,
            dwInfoLevel,
            lpBuffer,
            lpdwBufferLength,
            lpdwIndex
        );
    }

    BOOL Hook_HttpSendRequestA(
        HINTERNET hRequest,
        LPCSTR    lpszHeaders,
        DWORD     dwHeadersLength,
        LPVOID    lpOptional,
        DWORD     dwOptionalLength
    ) {
        std::cout << "\n Hook_HttpSendRequestA \n\n";
        char buf[500] = "HttpSendRequestA";
        DWORD cbWritten;
        DWORD dwBytesToWrite = (DWORD)strlen(buf);
        WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
        return HttpSendRequestA(
            hRequest,
            lpszHeaders,
            dwHeadersLength,
            lpOptional,
            dwOptionalLength
        );
    }

    BOOL Hook_HttpSendRequestExA(
        HINTERNET           hRequest,
        LPINTERNET_BUFFERSA lpBuffersIn,
        LPINTERNET_BUFFERSA lpBuffersOut,
        DWORD               dwFlags,
        DWORD_PTR           dwContext
    ) {
        std::cout << "\n Hook_HttpSendRequestExA \n\n";
        char buf[500] = "HttpSendRequestExA";
        DWORD cbWritten;
        DWORD dwBytesToWrite = (DWORD)strlen(buf);
        WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
        return HttpSendRequestExA(
            hRequest,
            lpBuffersIn,
            lpBuffersOut,
            dwFlags,
            dwContext
        );
    }

    HINTERNET Hook_InternetConnectA(
        HINTERNET     hInternet,
        LPCSTR        lpszServerName,
        INTERNET_PORT nServerPort,
        LPCSTR        lpszUserName,
        LPCSTR        lpszPassword,
        DWORD         dwService,
        DWORD         dwFlags,
        DWORD_PTR     dwContext
    ) {
        std::cout << "\n Hook_InternetConnectA \n\n";
        char buf[500] = "InternetConnectA";
        DWORD cbWritten;
        DWORD dwBytesToWrite = (DWORD)strlen(buf);
        WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
        return InternetConnectA(
            hInternet,
            lpszServerName,
            nServerPort,
            lpszUserName,
            lpszPassword,
            dwService,
            dwFlags,
            dwContext
        );
    }

    BOOL Hook_InternetGetCookieA(
        LPCSTR  lpszUrl,
        LPCSTR  lpszCookieName,
        LPSTR   lpszCookieData,
        LPDWORD lpdwSize
    ) {
        std::cout << "\n Hook_InternetGetCookieA \n\n";
        char buf[500] = "InternetGetCookieA";
        DWORD cbWritten;
        DWORD dwBytesToWrite = (DWORD)strlen(buf);
        WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
        return InternetGetCookieA(
            lpszUrl,
            lpszCookieName,
            lpszCookieData,
            lpdwSize
        );
    }

    BOOL Hook_InternetGetCookieExA(
        LPCSTR  lpszUrl,
        LPCSTR  lpszCookieName,
        LPSTR   lpszCookieData,
        LPDWORD lpdwSize,
        DWORD   dwFlags,
        LPVOID  lpReserved
    ) {
        std::cout << "\n Hook_InternetGetCookieExA \n\n";
        char buf[500] = "InternetGetCookieExA";
        DWORD cbWritten;
        DWORD dwBytesToWrite = (DWORD)strlen(buf);
        WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
        return InternetGetCookieExA(
            lpszUrl,
            lpszCookieName,
            lpszCookieData,
            lpdwSize,
            dwFlags,
            lpReserved
        );
    }

    BOOL Hook_InternetSetCookieA(
        LPCSTR lpszUrl,
        LPCSTR lpszCookieName,
        LPCSTR lpszCookieData
    ) {
        std::cout << "\n Hook_InternetSetCookieA \n\n";
        char buf[500] = "InternetSetCookieA";
        DWORD cbWritten;
        DWORD dwBytesToWrite = (DWORD)strlen(buf);
        WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
        return InternetSetCookieA(
            lpszUrl,
            lpszCookieName,
            lpszCookieData
        );
    }

    DWORD Hook_InternetSetCookieExA(
        LPCSTR    lpszUrl,
        LPCSTR    lpszCookieName,
        LPCSTR    lpszCookieData,
        DWORD     dwFlags,
        DWORD_PTR dwReserved
    ) {
        std::cout << "\n Hook_InternetSetCookieExA \n\n";
        char buf[500] = "InternetSetCookieExA";
        DWORD cbWritten;
        DWORD dwBytesToWrite = (DWORD)strlen(buf);
        WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
        return InternetSetCookieExA(
            lpszUrl,
            lpszCookieName,
            lpszCookieData,
            dwFlags,
            dwReserved
        );
    }


}

