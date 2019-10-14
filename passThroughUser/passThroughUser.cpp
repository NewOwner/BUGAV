#include <iostream>
#include <windows.h>
#include <Fltuser.h>
#include <strsafe.h>

#define SUCCESS              0
#define USAGE_ERROR          1
#define BUFFER_SIZE     4096

#define PASSFLT_PORT_NAME                   L"\\PassFltPort"

VOID DisplayError( _In_ DWORD Code);
DWORD InterpretCommand();

#pragma warning(push)
#pragma warning(disable:4706) // assignment within conditional expression

int _cdecl
main( _In_ int argc, _In_reads_(argc) char* argv[])
{
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

    if (IS_ERROR(hResult)) {
        printf("Could not connect to filter: 0x%08x\n", hResult);
        DisplayError(hResult);
        goto Main_Exit;
    }

    InterpretCommand();

Main_Exit:

    if (INVALID_HANDLE_VALUE != port) {
        CloseHandle(port);
    }
    return 0;
}

#pragma warning(pop)

DWORD InterpretCommand(){
    LONG parmIndex;
    PCHAR parm;
    HRESULT hResult;
    DWORD returnValue = SUCCESS;
    CHAR buffer[BUFFER_SIZE];
    DWORD bufferLength;
    PWCHAR instanceString;
    WCHAR instanceName[INSTANCE_NAME_MAX_CHARS + 1];
    
    parm = (PCHAR)"AAABBBCCC";

    printf("    Attaching to %s... ", parm);

    bufferLength = MultiByteToWideChar(CP_ACP,
        MB_ERR_INVALID_CHARS,
        parm,
        -1,
        (LPWSTR)buffer,
        BUFFER_SIZE / sizeof(WCHAR));

    if (bufferLength == 0) {

        //
        //  We do not expect the user to provide a parm that
        //  causes buffer to overflow. 
        //

        goto InterpretCommand_Usage;
    }
                hResult = FilterAttach(PASSFLT_PORT_NAME,
                    (PWSTR)buffer,
                    NULL, // instance name
                    sizeof(instanceName),
                    instanceName);

                if (SUCCEEDED(hResult)) {
                    printf("    Instance name: %S\n", instanceName);
                } else {
                    printf("\n    Could not attach to device: 0x%08x\n", hResult);
                    DisplayError(hResult);
                    returnValue = SUCCESS;
                }

                //hResult = FilterDetach(MINISPY_NAME,
                //    (PWSTR)buffer,
                //    instanceString);

                //if (IS_ERROR(hResult)) {
                //
                //    printf("    Could not detach from device: 0x%08x\n", hResult);
                //    DisplayError(hResult);
                //    returnValue = SUCCESS;
                //}

InterpretCommand_Exit:
    return returnValue;

InterpretCommand_Usage:
    printf("Valid switches: [/a <drive>] [/d <drive>] [/l] [/s] [/f [<file name>]]\n"
        "    [/a <drive>] starts monitoring <drive>\n"
        "    [/d <drive> [<instance id>]] detaches filter <instance id> from <drive>\n"
        "    [/l] lists all the drives the monitor is currently attached to\n"
        "    [/s] turns on and off showing logging output on the screen\n"
        "    [/f [<file name>]] turns on and off logging to the specified file\n"
        "  If you are in command mode:\n"
        "    [enter] will enter command mode\n"
        "    [go|g] will exit command mode\n"
        "    [exit] will terminate this program\n"
    );
    returnValue = USAGE_ERROR;
    goto InterpretCommand_Exit;
}

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