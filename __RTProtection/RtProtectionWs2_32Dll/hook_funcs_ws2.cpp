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
    DWORD cbWritten;
    char buf[500] = { 0 };
    

    int rescode = WSARecvFrom(
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

    std::string hex_str = "WSARecvFrom ";
    
    for (int i = 0; i < dwBufferCount; i++) {
        hex_str += hexStr((BYTE*)lpBuffers[i].buf, lpBuffers[i].len);
    }
    int minlen = min(500, hex_str.length());
    memcpy(buf, hex_str.c_str(), minlen);
    DWORD dwBytesToWrite = minlen;

    WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);

    return rescode;
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
    char buf[500] = { 0 };
    DWORD cbWritten;

    std::string hex_str = "WSASend ";
    
    for (int i = 0; i < dwBufferCount; i++) {
        hex_str += hexStr((BYTE*)lpBuffers[i].buf, lpBuffers[i].len);
    }
    int minlen = min(500, hex_str.length());
    memcpy(buf, hex_str.c_str(), minlen);

    DWORD dwBytesToWrite = minlen;

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
    char buf[500] = { 0 };
    DWORD cbWritten;

    std::string hex_str = "WSASendTo ";
    
    for (int i = 0; i < dwBufferCount; i++) {
        hex_str += hexStr((BYTE*)lpBuffers[i].buf, lpBuffers[i].len);
    }
    int minlen = min(500, hex_str.length());
    memcpy(buf, hex_str.c_str(), minlen);
    
    DWORD dwBytesToWrite = minlen;

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

int WSAAPI Hook_send(
    SOCKET     s,
    const char* buf,
    int        len,
    int        flags
) {
    std::cout << "\n Hook_send \n\n";
    char sendbuf[500] = "send ";
    DWORD cbWritten;
    int namelen = strlen(sendbuf);
    int minlen = min(500, len+namelen);
    DWORD dwBytesToWrite = minlen;
    memcpy(sendbuf + namelen, buf, minlen);

    WriteFile(hPipe1, sendbuf, dwBytesToWrite, &cbWritten, NULL);

    return send(
        s,
        buf,
        len,
        flags
    );
}

int Hook_sendto(
    SOCKET         s,
    const char* buf,
    int            len,
    int            flags,
    const sockaddr* to,
    int            tolen
) {
    std::cout << "\n Hook_sendto \n\n";
    char sendbuf[500] = "sendto ";
    DWORD cbWritten;
    int namelen = strlen(sendbuf);
    int minlen = min(500, len + namelen);
    memcpy(sendbuf + namelen, buf, minlen);
    
    DWORD dwBytesToWrite = minlen;

    WriteFile(hPipe1, sendbuf, dwBytesToWrite, &cbWritten, NULL);

    return sendto(
        s,
        buf,
        len,
        flags,
        to,
        tolen
    );
}

int Hook_recv(
    SOCKET s,
    char* buf,
    int    len,
    int    flags
) {
    std::cout << "\n Hook_recv \n\n";
    char sendbuf[500] = "recv ";
    DWORD cbWritten;

    int rescode = recv(
        s,
        buf,
        len,
        flags
    );
    int namelen = strlen(sendbuf);
    int minlen = min(500, len + namelen);
    memcpy(sendbuf + namelen, buf, minlen);

    DWORD dwBytesToWrite = minlen;

    WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);

    return rescode;
}


int Hook_recvfrom(
    SOCKET   s,
    char* buf,
    int      len,
    int      flags,
    sockaddr* from,
    int* fromlen
) {
    std::cout << "\n Hook_recvfrom \n\n";
    char sendbuf[500] = "recvfrom ";
    DWORD cbWritten;

    int rescode = recvfrom(
        s,
        buf,
        len,
        flags,
        from,
        fromlen
    );

    int namelen = strlen(sendbuf);
    int minlen = min(500, len + namelen);
    memcpy(sendbuf + namelen, buf, minlen);

    DWORD dwBytesToWrite = minlen;

    WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);

    return rescode;
}
