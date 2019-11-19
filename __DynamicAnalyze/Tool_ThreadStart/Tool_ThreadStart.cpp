/*
malloc_mt

XXX malloc -> function name

The following example demonstrates using the ThreadStart() and ThreadFini() notification callbacks.
Although ThreadStart() and ThreadFini() are executed under the VM and client locks,
they could still contend with resources that are shared by other analysis routines.
Using PIN_GetLock() prevents this.

Note that there is known isolation issue when using Pin on Windows.
On Windows, a deadlock can occur if a tool opens a file in a callback when run on a multi-threaded application.
To work around this problem, open one file in main, and tag the data with the thread ID.
See source/tools/ManualExamples/buffer_windows.cpp as an example. This problem does not exist on Linux.
 */

#include <stdio.h>
#include <fstream>
#include "pin.H"
using std::string;

KNOB<string> KnobOutputFile(KNOB_MODE_WRITEONCE, "pintool",
    "o", "tool_threadstart.txt", "specify output file name");

//==============================================================
//  Analysis Routines
//==============================================================
// Note:  threadid+1 is used as an argument to the PIN_GetLock()
//        routine as a debugging aid.  This is the value that
//        the lock is set to, so it must be non-zero.

// lock serializes access to the output file.
FILE * out;
std::ifstream InFile;
PIN_LOCK pinLock;
std::string func_tofind;

// Note that opening a file in a callback is only supported on Linux systems.
// See buffer-win.cpp for how to work around this issue on Windows.
//
// This routine is executed every time a thread is created.
VOID ThreadStart(THREADID threadid, CONTEXT *ctxt, INT32 flags, VOID *v) {
    PIN_GetLock(&pinLock, threadid + 1);
    fprintf(out, "thread begin %d\n", threadid);
    fflush(out);
    PIN_ReleaseLock(&pinLock);
}

// This routine is executed every time a thread is destroyed.
VOID ThreadFini(THREADID threadid, const CONTEXT *ctxt, INT32 code, VOID *v) {
    PIN_GetLock(&pinLock, threadid + 1);
    fprintf(out, "thread end %d code %d\n", threadid, code);
    fflush(out);
    PIN_ReleaseLock(&pinLock);
}

// This routine is executed each time malloc is called.
VOID BeforeFunc(int size, THREADID threadid) {
    PIN_GetLock(&pinLock, threadid + 1);
    fprintf(out, "thread %d entered malloc(%d)\n", threadid, size);
    fflush(out);
    PIN_ReleaseLock(&pinLock);
}


//====================================================================
// Instrumentation Routines
//====================================================================

// This routine is executed for each image.
VOID ImageLoad(IMG img, VOID *) {
    RTN rtn = RTN_FindByName(img, func_tofind.c_str());

    if (RTN_Valid(rtn)) {
        RTN_Open(rtn);

        RTN_InsertCall(rtn, IPOINT_BEFORE, AFUNPTR(BeforeFunc),
            IARG_FUNCARG_ENTRYPOINT_VALUE, 0,
            IARG_THREAD_ID, IARG_END);

        RTN_Close(rtn);
    }
}

// This routine is executed once at the end.
VOID Fini(INT32 code, VOID *v) {
    fclose(out);
}

/* ===================================================================== */
/* Print Help Message                                                    */
/* ===================================================================== */

INT32 Usage() {
    PIN_ERROR("This Pintool prints a trace of func in arg calls in the guest application\n"
        + KNOB_BASE::StringKnobSummary() + "\n");
    return -1;
}

/* ===================================================================== */
/* Main                                                                  */
/* ===================================================================== */

int main(INT32 argc, CHAR **argv) {
    func_tofind = string(argv[1]);

    // Initialize the pin lock
    PIN_InitLock(&pinLock);

    // Initialize pin
    if (PIN_Init(argc, argv)) return Usage();
    PIN_InitSymbols();

    out = fopen(KnobOutputFile.Value().c_str(), "w");

    InFile.open("inf.txt");
    InFile >> func_tofind;

    // Register ImageLoad to be called when each image is loaded.
    IMG_AddInstrumentFunction(ImageLoad, 0);

    // Register Analysis routines to be called when a thread begins/ends
    PIN_AddThreadStartFunction(ThreadStart, 0);
    PIN_AddThreadFiniFunction(ThreadFini, 0);

    // Register Fini to be called when the application exits
    PIN_AddFiniFunction(Fini, 0);

    // Never returns
    PIN_StartProgram();

    return 0;
}
