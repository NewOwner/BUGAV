#include "pch.h"
#include "hook_funcs_ws2.h"
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <sstream>

extern HANDLE hPipe1;

std::string hexStr(BYTE* data, int len) {
    std::stringstream ss;
    ss << std::hex;
    for (int i(0); i < len; ++i) {
        ss << std::setw(2) << std::setfill('0') << (int)data[i];
    }
    return ss.str();
}

SOCKET Hook_WSAAccept(
    SOCKET          s,
    sockaddr* addr,
    LPINT           addrlen,
    LPCONDITIONPROC lpfnCondition,
    DWORD_PTR       dwCallbackData
) {
    std::cout << "\n Hook_WSAAccept \n\n";
    char buf[500] = "WSAAccept";
    DWORD cbWritten;
    DWORD dwBytesToWrite = (DWORD)strlen(buf);
    WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
    return WSAAccept(
        s,
        addr,
        addrlen,
        lpfnCondition,
        dwCallbackData
    );
}

int Hook_WSARecv(
    SOCKET                             s,
    LPWSABUF                           lpBuffers,
    DWORD                              dwBufferCount,
    LPDWORD                            lpNumberOfBytesRecvd,
    LPDWORD                            lpFlags,
    LPWSAOVERLAPPED                    lpOverlapped,
    LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
) {
    std::cout << "\n Hook_WSARecv \n\n";
    char buf[500] = "WSARecv";
    DWORD cbWritten;
    DWORD dwBytesToWrite = (DWORD)strlen(buf);
    WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
    return WSARecv(
        s,
        lpBuffers,
        dwBufferCount,
        lpNumberOfBytesRecvd,
        lpFlags,
        lpOverlapped,
        lpCompletionRoutine
    );
}

int Hook_WSARecvFrom(
    SOCKET                             s,
    LPWSABUF                           lpBuffers,
    DWORD                              dwBufferCount,
    LPDWORD                            lpNumberOfBytesRecvd,
    LPDWORD                            lpFlags,
    sockaddr* lpFrom,
    LPINT                              lpFromlen,
    LPWSAOVERLAPPED                    lpOverlapped,
    LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
) {
    std::cout << "\n Hook_WSARecvFrom \n\n";
    char buf[500] = "WSARecvFrom";
    DWORD cbWritten;
    DWORD dwBytesToWrite = (DWORD)strlen(buf);
    for (int i = 0; i < dwBufferCount; i++) {
        int minlen = min(500, lpBuffers[i].len);
        std::string hex_str = hexStr((BYTE*)lpBuffers[i].buf, minlen);
        memcpy(buf, hex_str.c_str(), minlen);
        WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
    }

    WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
    return WSARecvFrom(
        s,
        lpBuffers,
        dwBufferCount,
        lpNumberOfBytesRecvd,
        lpFlags,
        lpFrom,
        lpFromlen,
        lpOverlapped,
        lpCompletionRoutine
    );
}




int Hook_WSASend(
    SOCKET                             s,
    LPWSABUF                           lpBuffers,
    DWORD                              dwBufferCount,
    LPDWORD                            lpNumberOfBytesSent,
    DWORD                              dwFlags,
    LPWSAOVERLAPPED                    lpOverlapped,
    LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
) {
    std::cout << "\n Hook_WSASend \n\n";
    char buf[500] = "WSASend";
    DWORD cbWritten;
    DWORD dwBytesToWrite = (DWORD)strlen(buf);

    for (int i = 0; i < dwBufferCount; i++) {
        int minlen = min(500, lpBuffers[i].len);
        std::string hex_str = hexStr((BYTE*)lpBuffers[i].buf, minlen);
        memcpy(buf, hex_str.c_str(), minlen);
        WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
    }

    WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
    return WSASend(
        s,
        lpBuffers,
        dwBufferCount,
        lpNumberOfBytesSent,
        dwFlags,
        lpOverlapped,
        lpCompletionRoutine
    );
}

int Hook_WSASendTo(
    SOCKET                             s,
    LPWSABUF                           lpBuffers,
    DWORD                              dwBufferCount,
    LPDWORD                            lpNumberOfBytesSent,
    DWORD                              dwFlags,
    const sockaddr* lpTo,
    int                                iTolen,
    LPWSAOVERLAPPED                    lpOverlapped,
    LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
) {
    std::cout << "\n Hook_WSASendTo \n\n";
    char buf[500] = "WSASendTo";
    DWORD cbWritten;
    DWORD dwBytesToWrite = (DWORD)strlen(buf);

    for (int i = 0; i < dwBufferCount; i++) {
        int minlen = min(500, lpBuffers[i].len);
        std::string hex_str = hexStr((BYTE*)lpBuffers[i].buf, minlen);
        memcpy(buf, hex_str.c_str(), minlen);
        WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
    }

    WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);

    return WSASendTo(
        s,
        lpBuffers,
        dwBufferCount,
        lpNumberOfBytesSent,
        dwFlags,
        lpTo,
        iTolen,
        lpOverlapped,
        lpCompletionRoutine
    );
}