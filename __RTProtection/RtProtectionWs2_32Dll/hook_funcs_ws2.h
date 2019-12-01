#pragma once
#include <winsock2.h>
#include <WS2tcpip.h>

SOCKET Hook_WSAAccept(
    SOCKET          s,
    sockaddr* addr,
    LPINT           addrlen,
    LPCONDITIONPROC lpfnCondition,
    DWORD_PTR       dwCallbackData
);

int Hook_WSARecv(
    SOCKET                             s,
    LPWSABUF                           lpBuffers,
    DWORD                              dwBufferCount,
    LPDWORD                            lpNumberOfBytesRecvd,
    LPDWORD                            lpFlags,
    LPWSAOVERLAPPED                    lpOverlapped,
    LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
);

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
);

int Hook_WSASend(
    SOCKET                             s,
    LPWSABUF                           lpBuffers,
    DWORD                              dwBufferCount,
    LPDWORD                            lpNumberOfBytesSent,
    DWORD                              dwFlags,
    LPWSAOVERLAPPED                    lpOverlapped,
    LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
);

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
);
