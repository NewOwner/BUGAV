/*
XXX malloc, free -> function name

malloctrace
Often one needs the know the value of the argument passed into a function, or the return value.
You can use Pin to find this information. Using the RTN_InsertCall() function, you can specify the arguments of interest.

The example below prints the input argument for malloc() and free(), and the return value from malloc().
 */


#include "pin.H"
#include <iostream>
#include <fstream>
using std::hex;
using std::cerr;
using std::string;
using std::ios;
using std::endl;

/* ===================================================================== */
/* Global Variables */
/* ===================================================================== */

std::ofstream TraceFile;
std::ifstream InFile;
std::string func_tofind;
/* ===================================================================== */
/* Commandline Switches */
/* ===================================================================== */

KNOB<string> KnobOutputFile(KNOB_MODE_WRITEONCE, "pintool",
    "o", "tool_funcargs.txt", "specify file name");

/* ===================================================================== */


/* ===================================================================== */
/* Analysis routines                                                     */
/* ===================================================================== */

VOID Arg1Before(CHAR * name, ADDRINT size) {
    TraceFile << name << "(" << size << ")" << endl;
}

VOID MallocAfter(ADDRINT ret) {
    TraceFile << "  returns " << ret << endl;
}


/* ===================================================================== */
/* Instrumentation routines                                              */
/* ===================================================================== */

VOID Image(IMG img, VOID *v) {
    // Instrument the malloc() and free() functions.  Print the input argument
    // of each malloc() or free(), and the return value of malloc().
    //
    //  Find the malloc() function.
    RTN RtnToFind = RTN_FindByName(img, func_tofind.c_str());
    if (RTN_Valid(RtnToFind)) {
        RTN_Open(RtnToFind);

        // Instrument malloc() to print the input argument value and the return value.
        RTN_InsertCall(RtnToFind, IPOINT_BEFORE, (AFUNPTR)Arg1Before,
            IARG_ADDRINT, func_tofind.c_str(),
            IARG_FUNCARG_ENTRYPOINT_VALUE, 0,
            IARG_END);
        RTN_InsertCall(RtnToFind, IPOINT_AFTER, (AFUNPTR)MallocAfter,
            IARG_FUNCRET_EXITPOINT_VALUE, IARG_END);

        RTN_Close(RtnToFind);
    }
}

/* ===================================================================== */

VOID Fini(INT32 code, VOID *v) {
    TraceFile.close();
}

/* ===================================================================== */
/* Print Help Message                                                    */
/* ===================================================================== */

INT32 Usage() {
    cerr << "This tool produces a trace of calls to malloc." << endl;
    cerr << endl << KNOB_BASE::StringKnobSummary() << endl;
    return -1;
}

/* ===================================================================== */
/* Main                                                                  */
/* ===================================================================== */

int main(int argc, char *argv[]) {

    // Initialize pin & symbol manager
    PIN_InitSymbols();
    if (PIN_Init(argc, argv)) {
        return Usage();
    }

    // Write to a file since cout and cerr maybe closed by the application
    TraceFile.open(KnobOutputFile.Value().c_str());
    TraceFile << hex;
    TraceFile.setf(ios::showbase);

    InFile.open("inf.txt");
    InFile >> func_tofind;
    TraceFile << func_tofind << endl;

    // Register Image to be called to instrument functions.
    IMG_AddInstrumentFunction(Image, 0);
    PIN_AddFiniFunction(Fini, 0);

    // Never returns
    PIN_StartProgram();

    return 0;
}

/* ===================================================================== */
/* eof */
/* ===================================================================== */
