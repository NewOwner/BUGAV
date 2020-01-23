#include "pch.h"
#include "hook_funcs_console.h"

extern HANDLE hPipe1;

BOOL Hook_ReadConsoleA(
    _In_     HANDLE  hConsoleInput,
    _Out_    LPVOID  lpBuffer,
    _In_     DWORD   nNumberOfCharsToRead,
    _Out_    LPDWORD lpNumberOfCharsRead,
    _In_opt_ PCONSOLE_READCONSOLE_CONTROL pInputControl
) {
    std::cout << "\n Hook_ReadConsoleA \n\n";
    char buf[500] = "ReadConsoleA";
    DWORD cbWritten;
    DWORD dwBytesToWrite = (DWORD)strlen(buf);
    WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
    return ReadConsoleA(
        hConsoleInput,
        lpBuffer,
        nNumberOfCharsToRead,
        lpNumberOfCharsRead,
        pInputControl
    );
}

BOOL Hook_ReadConsoleW(
    _In_     HANDLE  hConsoleInput,
    _Out_    LPVOID  lpBuffer,
    _In_     DWORD   nNumberOfCharsToRead,
    _Out_    LPDWORD lpNumberOfCharsRead,
    _In_opt_ PCONSOLE_READCONSOLE_CONTROL  pInputControl
) {
    std::cout << "\n Hook_ReadConsoleW \n\n";
    char buf[500] = "ReadConsoleW";
    DWORD cbWritten;
    DWORD dwBytesToWrite = (DWORD)strlen(buf);
    WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
    return ReadConsoleW(
        hConsoleInput,
        lpBuffer,
        nNumberOfCharsToRead,
        lpNumberOfCharsRead,
        pInputControl
    );
}

BOOL Hook_ReadConsoleInputA(
    _In_  HANDLE        hConsoleInput,
    _Out_ PINPUT_RECORD lpBuffer,
    _In_  DWORD         nLength,
    _Out_ LPDWORD       lpNumberOfEventsRead
) {
    std::cout << "\n Hook_ReadConsoleInputA \n\n";
    char buf[500] = "ReadConsoleInputA";
    DWORD cbWritten;
    DWORD dwBytesToWrite = (DWORD)strlen(buf);
    WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
    return ReadConsoleInputA(
        hConsoleInput,
        lpBuffer,
        nLength,
        lpNumberOfEventsRead
    );
}
std::string cur_command = "";

VOID KeyEventProc(KEY_EVENT_RECORD ker) {
    if (ker.bKeyDown) {
        if (ker.uChar.AsciiChar == 0x03) {
            std::cout << "\n CONTROL-C \n\n";
            cur_command = "";
        } else if (ker.uChar.AsciiChar == 0x0D) {
            std::cout << "\n ENTER \n\n";
            char buf[500] = { 0 };
            memcpy(buf, cur_command.c_str(), cur_command.length());
            DWORD cbWritten;
            DWORD dwBytesToWrite = cur_command.length();
            WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
            cur_command = "";
        } else {
            cur_command += ker.uChar.AsciiChar;
        }
    }
}

BOOL Hook_ReadConsoleInputW(
    _In_  HANDLE        hConsoleInput,
    _Out_ PINPUT_RECORD lpBuffer,
    _In_  DWORD         nLength,
    _Out_ LPDWORD       lpNumberOfEventsRead
) {
    BOOL res = ReadConsoleInputW(
        hConsoleInput,
        lpBuffer,
        nLength,
        lpNumberOfEventsRead
    );

    for (int i = 0; i < *lpNumberOfEventsRead; i++) {
        switch (lpBuffer[i].EventType) {
        case KEY_EVENT: // keyboard input 
            KeyEventProc(lpBuffer[i].Event.KeyEvent);
            break;
        }
    }
    return res;
}

BOOL Hook_ReadConsoleOutputA(
    _In_    HANDLE      hConsoleOutput,
    _Out_   PCHAR_INFO  lpBuffer,
    _In_    COORD       dwBufferSize,
    _In_    COORD       dwBufferCoord,
    _Inout_ PSMALL_RECT lpReadRegion
) {
    std::cout << "\n Hook_ReadConsoleOutputA \n\n";
    char buf[500] = "ReadConsoleOutputA";
    DWORD cbWritten;
    DWORD dwBytesToWrite = (DWORD)strlen(buf);
    WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
    return ReadConsoleOutputA(
        hConsoleOutput,
        lpBuffer,
        dwBufferSize,
        dwBufferCoord,
        lpReadRegion
    );
}

BOOL Hook_ReadConsoleOutputW(
    _In_    HANDLE      hConsoleOutput,
    _Out_   PCHAR_INFO  lpBuffer,
    _In_    COORD       dwBufferSize,
    _In_    COORD       dwBufferCoord,
    _Inout_ PSMALL_RECT lpReadRegion
) {
    std::cout << "\n Hook_ReadConsoleOutputW \n\n";
    char buf[500] = "ReadConsoleOutputW";
    DWORD cbWritten;
    DWORD dwBytesToWrite = (DWORD)strlen(buf);
    //WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
    return ReadConsoleOutputW(
        hConsoleOutput,
        lpBuffer,
        dwBufferSize,
        dwBufferCoord,
        lpReadRegion
    );
}

BOOL Hook_ReadConsoleOutputCharacterA(
    _In_  HANDLE  hConsoleOutput,
    _Out_ LPSTR  lpCharacter,
    _In_  DWORD   nLength,
    _In_  COORD   dwReadCoord,
    _Out_ LPDWORD lpNumberOfCharsRead
) {
    std::cout << "\n Hook_ReadConsoleOutputCharacterA \n\n";
    char buf[500] = "ReadConsoleOutputCharacterA";
    DWORD cbWritten;
    DWORD dwBytesToWrite = (DWORD)strlen(buf);
    WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
    return ReadConsoleOutputCharacterA(
        hConsoleOutput,
        lpCharacter,
        nLength,
        dwReadCoord,
        lpNumberOfCharsRead
    );
}

BOOL Hook_ReadConsoleOutputCharacterW(
    _In_  HANDLE  hConsoleOutput,
    _Out_ LPTSTR  lpCharacter,
    _In_  DWORD   nLength,
    _In_  COORD   dwReadCoord,
    _Out_ LPDWORD lpNumberOfCharsRead
) {
    std::cout << "\n Hook_ReadConsoleOutputCharacterW \n\n";
    char buf[500] = "ReadConsoleOutputCharacterW";
    DWORD cbWritten;
    DWORD dwBytesToWrite = (DWORD)strlen(buf);
    WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
    return ReadConsoleOutputCharacterW(
        hConsoleOutput,
        lpCharacter,
        nLength,
        dwReadCoord,
        lpNumberOfCharsRead
    );
}

BOOL Hook_SetConsoleMode(
    _In_ HANDLE hConsoleHandle,
    _In_ DWORD  dwMode
) {
    std::cout << "\n Hook_SetConsoleMode \n\n";
    char buf[500] = "SetConsoleMode";
    DWORD cbWritten;
    DWORD dwBytesToWrite = (DWORD)strlen(buf);
    WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
    return SetConsoleMode(
        hConsoleHandle,
        dwMode
    );
}

BOOL Hook_WriteConsoleOutputCharacterA(
    _In_  HANDLE  hConsoleOutput,
    _In_  LPCSTR lpCharacter,
    _In_  DWORD   nLength,
    _In_  COORD   dwWriteCoord,
    _Out_ LPDWORD lpNumberOfCharsWritten
) {
    std::cout << "\n Hook_WriteConsoleOutputCharacterA \n\n";
    char buf[500] = "WriteConsoleOutputCharacterA";
    DWORD cbWritten;
    DWORD dwBytesToWrite = (DWORD)strlen(buf);
    WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
    return WriteConsoleOutputCharacterA(
        hConsoleOutput,
        lpCharacter,
        nLength,
        dwWriteCoord,
        lpNumberOfCharsWritten
    );
}

BOOL Hook_WriteConsoleOutputCharacterW(
    _In_  HANDLE  hConsoleOutput,
    _In_  LPCTSTR lpCharacter,
    _In_  DWORD   nLength,
    _In_  COORD   dwWriteCoord,
    _Out_ LPDWORD lpNumberOfCharsWritten
) {
    std::cout << "\n Hook_WriteConsoleOutputCharacterW \n\n";
    char buf[500] = "WriteConsoleOutputCharacterW";
    DWORD cbWritten;
    DWORD dwBytesToWrite = (DWORD)strlen(buf);
    WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
    return WriteConsoleOutputCharacterW(
        hConsoleOutput,
        lpCharacter,
        nLength,
        dwWriteCoord,
        lpNumberOfCharsWritten
    );
}