#include <iostream>
#include <windows.h>
#include <Fltuser.h>
#include <strsafe.h>

#define SUCCESS              0
#define USAGE_ERROR          1
#define BUFFER_SIZE     4096

#define PASSFLT_PORT_NAME                   L"\\PassFltPort"

VOID DisplayError(_In_ DWORD Code);

#pragma warning(push)
#pragma warning(disable:4706) // assignment within conditional expression

int _cdecl
main(_In_ int argc, _In_reads_(argc) char* argv[]) {
    HANDLE port = INVALID_HANDLE_VALUE;
    HRESULT hResult = S_OK;

    //  Open the port that is used to talk to MiniSpy.
    printf("Connecting to filter's port...\n");

    hResult = FilterConnectCommunicationPort(PASSFLT_PORT_NAME,
        0,
        NULL,
        0,
        NULL,
        &port);

    if (hResult != S_OK) {
        printf("Could not connect to filter: 0x%08x\n", hResult);
        DisplayError(hResult);
        goto Main_Exit;
    }

    {
        printf("send msg\n");
        PCHAR parm = (PCHAR)"updfcfg";
        CHAR out_buffer[10];
        DWORD breturned = 0;
        hResult = FilterSendMessage(port, parm, 10, out_buffer, 10, &breturned); 
    }

Main_Exit:

    if (INVALID_HANDLE_VALUE != port) {
        CloseHandle(port);
    }
    return 0;
}

#pragma warning(pop)

VOID DisplayError(_In_ DWORD Code)
/*++
   This routine will display an error message based off of the Win32 error
   code that is passed in. This allows the user to see an understandable
   error message instead of just the code.
--*/

{
    WCHAR buffer[MAX_PATH] = { 0 };
    DWORD count;
    HMODULE module = NULL;
    HRESULT status;

    count = FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,
        NULL,
        Code,
        0,
        buffer,
        sizeof(buffer) / sizeof(WCHAR),
        NULL);

    if (count == 0) {
        count = GetSystemDirectory(buffer, sizeof(buffer) / sizeof(WCHAR));

        if (count == 0 || count > sizeof(buffer) / sizeof(WCHAR)) {
            //  In practice we expect buffer to be large enough to hold the 
            //  system directory path. 
            printf("    Could not translate error: %d\n", Code);
            return;
        }

        status = StringCchCat(buffer, sizeof(buffer) / sizeof(WCHAR), L"\\fltlib.dll");

        if (status != S_OK) {
            printf("    Could not translate error: %d\n", Code);
            return;
        }

        module = LoadLibraryExW(buffer, NULL, LOAD_LIBRARY_AS_DATAFILE);

        //  Translate the Win32 error code into a useful message.
        count = FormatMessage(FORMAT_MESSAGE_FROM_HMODULE,
            module,
            Code,
            0,
            buffer,
            sizeof(buffer) / sizeof(WCHAR),
            NULL);

        if (module != NULL) { FreeLibrary(module); }

        //  If we still couldn't resolve the message, generate a string
        if (count == 0) {
            printf("    Could not translate error: %d\n", Code);
            return;
        }
    }
    //  Display the translated error.
    printf("    %ws\n", buffer);
}