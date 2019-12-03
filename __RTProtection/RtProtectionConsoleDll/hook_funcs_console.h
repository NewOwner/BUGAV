#pragma once

BOOL Hook_ReadConsoleA(
    _In_     HANDLE  hConsoleInput,
    _Out_    LPVOID  lpBuffer,
    _In_     DWORD   nNumberOfCharsToRead,
    _Out_    LPDWORD lpNumberOfCharsRead,
    _In_opt_ PCONSOLE_READCONSOLE_CONTROL  pInputControl
);

BOOL Hook_ReadConsoleW(
    _In_     HANDLE  hConsoleInput,
    _Out_    LPVOID  lpBuffer,
    _In_     DWORD   nNumberOfCharsToRead,
    _Out_    LPDWORD lpNumberOfCharsRead,
    _In_opt_ PCONSOLE_READCONSOLE_CONTROL  pInputControl
);

BOOL Hook_ReadConsoleInputA(
    _In_  HANDLE        hConsoleInput,
    _Out_ PINPUT_RECORD lpBuffer,
    _In_  DWORD         nLength,
    _Out_ LPDWORD       lpNumberOfEventsRead
);

BOOL Hook_ReadConsoleInputW(
    _In_  HANDLE        hConsoleInput,
    _Out_ PINPUT_RECORD lpBuffer,
    _In_  DWORD         nLength,
    _Out_ LPDWORD       lpNumberOfEventsRead
);

BOOL Hook_ReadConsoleOutputA(
    _In_    HANDLE      hConsoleOutput,
    _Out_   PCHAR_INFO  lpBuffer,
    _In_    COORD       dwBufferSize,
    _In_    COORD       dwBufferCoord,
    _Inout_ PSMALL_RECT lpReadRegion
);

BOOL Hook_ReadConsoleOutputW(
    _In_    HANDLE      hConsoleOutput,
    _Out_   PCHAR_INFO  lpBuffer,
    _In_    COORD       dwBufferSize,
    _In_    COORD       dwBufferCoord,
    _Inout_ PSMALL_RECT lpReadRegion
);

BOOL Hook_ReadConsoleOutputCharacterA(
    _In_  HANDLE  hConsoleOutput,
    _Out_ LPSTR  lpCharacter,
    _In_  DWORD   nLength,
    _In_  COORD   dwReadCoord,
    _Out_ LPDWORD lpNumberOfCharsRead
);

BOOL Hook_ReadConsoleOutputCharacterW(
    _In_  HANDLE  hConsoleOutput,
    _Out_ LPTSTR  lpCharacter,
    _In_  DWORD   nLength,
    _In_  COORD   dwReadCoord,
    _Out_ LPDWORD lpNumberOfCharsRead
);

BOOL Hook_SetConsoleMode(
    _In_ HANDLE hConsoleHandle,
    _In_ DWORD  dwMode
);

BOOL Hook_WriteConsoleOutputCharacterA(
    _In_  HANDLE  hConsoleOutput,
    _In_  LPCSTR lpCharacter,
    _In_  DWORD   nLength,
    _In_  COORD   dwWriteCoord,
    _Out_ LPDWORD lpNumberOfCharsWritten
);

BOOL Hook_WriteConsoleOutputCharacterW(
    _In_  HANDLE  hConsoleOutput,
    _In_  LPCTSTR lpCharacter,
    _In_  DWORD   nLength,
    _In_  COORD   dwWriteCoord,
    _Out_ LPDWORD lpNumberOfCharsWritten
);