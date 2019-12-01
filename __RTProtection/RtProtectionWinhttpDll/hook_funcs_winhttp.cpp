#include "pch.h"
#include "hook_funcs_winhttp.h"

extern HANDLE hPipe1;

namespace winhttp_ns {

    BOOL Hook_WinHttpAddRequestHeaders(
        IN HINTERNET hRequest,
        LPCWSTR      lpszHeaders,
        IN DWORD     dwHeadersLength,
        IN DWORD     dwModifiers
    ) {
        std::cout << "\n Hook_WinHttpAddRequestHeaders \n\n";
        char buf[500] = "WinHttpAddRequestHeaders";
        DWORD cbWritten;
        DWORD dwBytesToWrite = (DWORD)strlen(buf);
        WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
        return WinHttpAddRequestHeaders(hRequest, lpszHeaders, dwHeadersLength, dwModifiers);
    }

    HINTERNET Hook_WinHttpConnect(
        IN HINTERNET     hSession,
        IN LPCWSTR       pswzServerName,
        IN INTERNET_PORT nServerPort,
        IN DWORD         dwReserved
    ) {
        std::cout << "\n Hook_WinHttpConnect \n\n";
        char buf[500] = "WinHttpConnect";
        DWORD cbWritten;
        DWORD dwBytesToWrite = (DWORD)strlen(buf);
        WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
        return WinHttpConnect(
            hSession, 
            pswzServerName, 
            nServerPort, 
            dwReserved
        );
    }

    BOOL Hook_WinHttpCreateUrl(
        LPURL_COMPONENTS lpUrlComponents,
        DWORD            dwFlags,
        LPWSTR           pwszUrl,
        LPDWORD          pdwUrlLength
    ) {
        std::cout << "\n Hook_WinHttpCreateUrl \n\n";
        char buf[500] = "WinHttpCreateUrl";
        DWORD cbWritten;
        DWORD dwBytesToWrite = (DWORD)strlen(buf);
        WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
        return WinHttpCreateUrl(
            lpUrlComponents,
            dwFlags,
            pwszUrl,
            pdwUrlLength
        );
    }

    HINTERNET Hook_WinHttpOpen(
        LPCWSTR pszAgentW,
        DWORD   dwAccessType,
        LPCWSTR pszProxyW,
        LPCWSTR pszProxyBypassW,
        DWORD   dwFlags
    ) {
        std::cout << "\n Hook_WinHttpOpen \n\n";
        char buf[500] = "WinHttpOpen";
        DWORD cbWritten;
        DWORD dwBytesToWrite = (DWORD)strlen(buf);
        WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
        return WinHttpOpen(
            pszAgentW,
            dwAccessType,
            pszProxyW,
            pszProxyBypassW,
            dwFlags
        );
    }

    HINTERNET Hook_WinHttpOpenRequest(
        IN HINTERNET hConnect,
        IN LPCWSTR   pwszVerb,
        IN LPCWSTR   pwszObjectName,
        IN LPCWSTR   pwszVersion,
        IN LPCWSTR   pwszReferrer,
        IN LPCWSTR* ppwszAcceptTypes,
        IN DWORD     dwFlags
    ) {
        std::cout << "\n Hook_WinHttpOpenRequest \n\n";
        char buf[500] = "WinHttpOpenRequest";
        DWORD cbWritten;
        DWORD dwBytesToWrite = (DWORD)strlen(buf);
        WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
        return WinHttpOpenRequest(
            hConnect,
            pwszVerb,
            pwszObjectName,
            pwszVersion,
            pwszReferrer,
            ppwszAcceptTypes,
            dwFlags
        );
    }

    BOOL Hook_WinHttpQueryDataAvailable(
        IN HINTERNET hRequest,
        LPDWORD      lpdwNumberOfBytesAvailable
    ) {
        std::cout << "\n Hook_WinHttpQueryDataAvailable \n\n";
        char buf[500] = "WinHttpQueryDataAvailable";
        DWORD cbWritten;
        DWORD dwBytesToWrite = (DWORD)strlen(buf);
        WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
        return WinHttpQueryDataAvailable(
            hRequest,
            lpdwNumberOfBytesAvailable
        );
    }

    BOOL Hook_WinHttpQueryHeaders(
        IN HINTERNET   hRequest,
        IN DWORD       dwInfoLevel,
        IN LPCWSTR     pwszName,
        LPVOID         lpBuffer,
        IN OUT LPDWORD lpdwBufferLength,
        IN OUT LPDWORD lpdwIndex
    ) {
        std::cout << "\n Hook_WinHttpQueryHeaders \n\n";
        char buf[500] = "WinHttpQueryHeaders";
        DWORD cbWritten;
        DWORD dwBytesToWrite = (DWORD)strlen(buf);
        WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
        return WinHttpQueryHeaders(
            hRequest,
            dwInfoLevel,
            pwszName,
            lpBuffer,
            lpdwBufferLength,
            lpdwIndex
        );
    }

    BOOL Hook_WinHttpReadData(
        IN HINTERNET hRequest,
        LPVOID       lpBuffer,
        IN DWORD     dwNumberOfBytesToRead,
        OUT LPDWORD  lpdwNumberOfBytesRead
    ) {
        std::cout << "\n Hook_WinHttpReadData \n\n";
        char buf[500] = "WinHttpReadData";
        DWORD cbWritten;
        DWORD dwBytesToWrite = (DWORD)strlen(buf);
        WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
        return WinHttpReadData(
            hRequest,
            lpBuffer,
            dwNumberOfBytesToRead,
            lpdwNumberOfBytesRead
        );
    }

    BOOL Hook_WinHttpReceiveResponse(
        IN HINTERNET hRequest,
        IN LPVOID    lpReserved
    ) {
        std::cout << "\n Hook_WinHttpReceiveResponse \n\n";
        char buf[500] = "WinHttpReceiveResponse";
        DWORD cbWritten;
        DWORD dwBytesToWrite = (DWORD)strlen(buf);
        WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
        return WinHttpReceiveResponse(
            hRequest,
            lpReserved
        );
    }

    BOOL Hook_WinHttpSendRequest(
        IN HINTERNET hRequest,
        LPCWSTR      lpszHeaders,
        IN DWORD     dwHeadersLength,
        LPVOID       lpOptional,
        IN DWORD     dwOptionalLength,
        IN DWORD     dwTotalLength,
        IN DWORD_PTR dwContext
    ) {
        std::cout << "\n Hook_WinHttpSendRequest \n\n";
        char buf[500] = "WinHttpSendRequest";
        DWORD cbWritten;
        DWORD dwBytesToWrite = (DWORD)strlen(buf);
        WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
        return WinHttpSendRequest(
            hRequest,
            lpszHeaders,
            dwHeadersLength,
            lpOptional,
            dwOptionalLength,
            dwTotalLength,
            dwContext
        );
    }

    BOOL Hook_WinHttpSetCredentials(
        IN HINTERNET hRequest,
        IN DWORD     AuthTargets,
        IN DWORD     AuthScheme,
        IN LPCWSTR   pwszUserName,
        IN LPCWSTR   pwszPassword,
        IN LPVOID    pAuthParams
    ) {
        std::cout << "\n Hook_WinHttpSetCredentials \n\n";
        char buf[500] = "WinHttpSetCredentials";
        DWORD cbWritten;
        DWORD dwBytesToWrite = (DWORD)strlen(buf);
        WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
        return WinHttpSetCredentials(
            hRequest,
            AuthTargets,
            AuthScheme,
            pwszUserName,
            pwszPassword,
            pAuthParams
        );
    }

    BOOL Hook_WinHttpWriteData(
        IN HINTERNET hRequest,
        LPCVOID      lpBuffer,
        IN DWORD     dwNumberOfBytesToWrite,
        OUT LPDWORD  lpdwNumberOfBytesWritten
    ) {
        std::cout << "\n Hook_WinHttpWriteData \n\n";
        char buf[500] = "WinHttpWriteData";
        DWORD cbWritten;
        DWORD dwBytesToWrite = (DWORD)strlen(buf);
        WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
        return WinHttpWriteData(
            hRequest,
            lpBuffer,
            dwNumberOfBytesToWrite,
            lpdwNumberOfBytesWritten
        );
    }

}