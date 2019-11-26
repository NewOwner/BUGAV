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
std::ofstream TraceFile;
PIN_LOCK pinLock;

// Note that opening a file in a callback is only supported on Linux systems.
// See buffer-win.cpp for how to work around this issue on Windows.
//
// This routine is executed every time a thread is created.
VOID ThreadStart(THREADID threadid, CONTEXT *ctxt, INT32 flags, VOID *v) {
    PIN_GetLock(&pinLock, threadid + 1);
    TraceFile << "thread begin " << threadid << std::endl;
    PIN_ReleaseLock(&pinLock);
}

// This routine is executed every time a thread is destroyed.
VOID ThreadFini(THREADID threadid, const CONTEXT *ctxt, INT32 code, VOID *v) {
    PIN_GetLock(&pinLock, threadid + 1);
    TraceFile << "thread end " << threadid << " code " << code << std::endl;
    PIN_ReleaseLock(&pinLock);
}


//====================================================================
// Instrumentation Routines
//====================================================================

//// This routine is executed for each image.
//VOID ImageLoad(IMG img, VOID *) {
//    fprintf(out, "Loading %s , Image id = %d\n", IMG_Name(img), IMG_Id(img));
//}

// This routine is executed once at the end.
VOID Fini(INT32 code, VOID *v) {
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
    // Initialize the pin lock
    PIN_InitLock(&pinLock);

    // Initialize pin
    if (PIN_Init(argc, argv)) return Usage();
    PIN_InitSymbols();

    TraceFile.open(KnobOutputFile.Value().c_str());

    // Register ImageLoad to be called when each image is loaded.
    //IMG_AddInstrumentFunction(ImageLoad, 0);

    // Register Analysis routines to be called when a thread begins/ends
    PIN_AddThreadStartFunction(ThreadStart, 0);

    PIN_AddThreadFiniFunction(ThreadFini, 0);

    // Register Fini to be called when the application exits
    PIN_AddFiniFunction(Fini, 0);

    // Never returns
    PIN_StartProgram();

    return 0;
}
