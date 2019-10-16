#pragma warning(disable:4201)  //nonstandard extension used : nameless struct/union
#include <ndis.h>
#include "common.h"

VOID __cdecl
wmain(
    _In_ ULONG argc,
    _In_reads_(argc) LPCWSTR argv[]
    )
{
    UNREFERENCED_PARAMETER(argc);
    UNREFERENCED_PARAMETER(argv);
}
