//
//  Jonathan Salwan - Copyright (C) 2013-09
// 
//  http://shell-storm.org
//  http://twitter.com/JonathanSalwan
//
//

#include "pin.H"
#include <asm/unistd.h>
#include <fstream>
#include <iostream>
#include <list>
using std::ofstream;
using std::string;
using std::endl;


KNOB<string> KnobOutputFile(KNOB_MODE_WRITEONCE, "pintool",
    "o", "tool_overflowdetect.txt", "specify file name");

ofstream TraceFile;

#define LOCKED    1
#define UNLOCKED  !LOCKED

#define ALLOCATE  1
#define FREE      !ALLOCATE

#define DEBUG 

#define NextIT(_x) ((++_x)--)

static size_t         lastSize;
static size_t         timerJiffies;

static UINT16       _tabAddr[0x10000];
static std::string  _tabStr[0x10000];

struct mallocArea
{
  UINT64  base;
  UINT64  size;
  BOOL    status;
};

struct loopList_s
{
  UINT32 idLoop;
  std::list<UINT64> addrs;
};

static UINT64 stID = 0;

struct stackFrameVar_s
{
  UINT64 addrVar;
  UINT64 sizeVar;
  UINT64 rsp;
};

struct VSA
{
  std::list<struct stackFrameVar_s> stackFrameVar;
};

struct VSA VSAL[64];

UINT32 lockTaint = LOCKED;

std::list<UINT64>               addressTainted;
std::list<REG>                  regsTainted;
std::list<struct mallocArea>    mallocAreaList;

INT32 Usage()
{
    TraceFile << "Stack/Heap overflow detection" << std::endl;
    return -1;
}

VOID WriteMem(UINT64 insAddr, std::string insDis, UINT32 opCount, REG reg_r, UINT64 memOp)
{
  std::list<struct mallocArea>::iterator i;
  UINT64 addr = memOp;
  PIN_LockClient();
  IMG img = IMG_FindByAddress(addr);
  PIN_UnlockClient();
  SEC sec;
  
  if (opCount != 2){
    return;
  }

  /* Check if the address is in a section */
  for(sec = IMG_SecHead(img); SEC_Valid(sec); sec = SEC_Next(sec)){
      if (addr >= SEC_Address(sec) && addr < (SEC_Address(sec) + SEC_Size(sec))) {
          return;
      }
  }

  /* Check if the address is mapped */
  for(i = mallocAreaList.begin(); i != mallocAreaList.end(); i++){
    if (i->status == ALLOCATE && addr >= i->base && addr < (i->base + i->size))
      return;
    if (i->status == FREE && addr >= i->base && addr < (i->base + i->size)){
      TraceFile << std::hex << insAddr << ": " << insDis << " -- Use after free in " << addr << std::endl;
      return;
    }
  }
 
  /* check if the address is in a stack area */
  if (addr > 0x700000000000)
    return;
 
  TraceFile << std::hex << insAddr << ": " << insDis << " -- Heap overflow in " << addr << std::endl;
}

VOID PrologueAnalysis(UINT64 insAddr, UINT64 nextInsAddr, std::string insDis)
{
  UINT64  i = 0;
  std::list<struct stackFrameVar_s>::iterator it;

  if (nextInsAddr >= 0x4004a0){
    #ifdef DEBUG
      //TraceFile << "Function opened " << hex << nextInsAddr << std::endl;
    #endif

    if (VSAL[stID].stackFrameVar.size() == 0){
      stID++;
      return;
    }

    /* premiere passe */
    for(it = VSAL[stID].stackFrameVar.begin(); it != VSAL[stID].stackFrameVar.end(); it++){
      if (i++ != 0){
        it->sizeVar = it->addrVar - (--it)->addrVar;
        it++;
      }
    }

    /* deuxieme passe */
    for(it = VSAL[stID].stackFrameVar.begin(); it != VSAL[stID].stackFrameVar.end(); it++){
      if (it->sizeVar == 0 && it->rsp < it->addrVar){
        it->sizeVar = it->addrVar - it->rsp;
      }
    }

    stID++;
  }
}

VOID EpilogueAnalysis(UINT64 insAddr, UINT64 nextInsAddr, std::string insDis)
{
  if (nextInsAddr >= 0x4004a0){
    #ifdef DEBUG
      //TraceFile << "Function closed" << std::endl;
    #endif
  }
}

VOID ValueSetAnalysis(UINT64 insAddr, std::string insDis, ADDRINT rsp, ADDRINT rbp, UINT64 memOp)
{
  UINT64 addrRBP = memOp;
  struct stackFrameVar_s elem;
  std::list<struct stackFrameVar_s>::iterator i;

  #ifdef DEBUG
    TraceFile << insAddr << ": " << insDis << " (rsp: " << std::hex << rsp << ") (rbp: " << rbp << ") (dest: " << addrRBP << ") (stack frame ID: " << std::dec << stID << ")" << std::endl;
  #endif

  /* Ajout des variables de la stack frame dans une VSAL */
  /* stID est unique pour chaque stack frame */
  elem.addrVar = addrRBP;
  elem.sizeVar = 0;
  elem.rsp     = rsp;
  /* boucle pour eviter les doublons et eviter d'avoir plusieur */
  /* variables pour une meme initialisation */
  for(i = VSAL[stID].stackFrameVar.begin(); i != VSAL[stID].stackFrameVar.end(); i++){
    if (i->addrVar == addrRBP)
      return;
  }

  if (VSAL[stID].stackFrameVar.size() == 0){
    VSAL[stID].stackFrameVar.push_back(elem);
    return;
  }

  for(i = VSAL[stID].stackFrameVar.begin(); i != VSAL[stID].stackFrameVar.end(); i++){
    if (i->addrVar > addrRBP){
      VSAL[stID].stackFrameVar.push_front(elem);
      return;
    }
  }
  VSAL[stID].stackFrameVar.push_back(elem);
}

VOID timerHandler(UINT64 prevAddr, UINT64 insAddr, UINT64 nextAddr, std::string insDis)
{
  timerJiffies++;


  if (insAddr > 0x700000000000)
    return;
 
  if (_tabAddr[insAddr ^ 0x400000] == 0xffff)
    return;
 
  _tabAddr[insAddr ^ 0x400000] += 1;
  _tabStr[insAddr ^ 0x400000] = insDis;
}

static UINT64 oldAddrWritten = 0;
static UINT64 counterWrite = 0;
static UINT64 oldRIP = 0;    

VOID WriteMemAnalysis(UINT64 insAddr, std::string insDis, UINT64 memOp)
{
  std::list<struct stackFrameVar_s>::iterator it;
  std::list<struct stackFrameVar_s>::iterator itNext;
  UINT64 addr = memOp;
  

//  if (_tabAddr[insAddr ^ 0x400000] < 2)
//    return;

  for(it = VSAL[stID].stackFrameVar.begin(); it != VSAL[stID].stackFrameVar.end(); it++){
    //TraceFile << "addr     = " << std::hex << addr << std::endl;
    //TraceFile << "addrVar  = " << std::hex << it->addrVar << std::endl;
    //TraceFile << "addrSize = " << std::hex << it->sizeVar << std::endl;

    itNext = NextIT(it);
    if (addr >= it->addrVar && addr < itNext->addrVar){
      #ifdef DEBUG
        TraceFile << "[Write Mem B] " << std::hex << insAddr << ": " << insDis << std::endl;
      #endif

    if (oldAddrWritten == 0)
      oldAddrWritten = addr;
    

    if (((addr - oldAddrWritten) != 1 && oldAddrWritten != addr) || insAddr != oldRIP){
      counterWrite = 0;
      oldAddrWritten = addr;
    }

    counterWrite++;
    oldRIP = insAddr;

    if (counterWrite > 4){
      TraceFile << std::hex << insAddr << ": " << insDis << " -- Stack overflow in " << addr << std::endl;
      counterWrite = 0;
      oldAddrWritten = addr;
    }

    #ifdef DEBUG
      TraceFile << "counterWrite: " << std::dec << counterWrite << std::endl;
    #endif
    oldAddrWritten = addr;
    break;
    }
    //  TraceFile << "itNext: " << std::hex << itNext->addrVar << std::endl;
  } 
}

VOID Instruction(INS ins, VOID *v)
{
  PIN_LockClient();
  IMG img = IMG_FindByAddress(INS_Address(ins));
  PIN_UnlockClient();
  
  if (IMG_Valid(img) && IMG_IsMainExecutable(img)){
    if (INS_IsCall(ins)){
      INS_InsertCall(
          ins, IPOINT_BEFORE, (AFUNPTR)PrologueAnalysis,
          IARG_ADDRINT, INS_Address(ins),
          IARG_ADDRINT, INS_NextAddress(ins),
          IARG_PTR, new std::string(INS_Disassemble(ins)),
          IARG_END);
    }
    else if (INS_IsRet(ins)){
      INS_InsertCall(
          ins, IPOINT_BEFORE, (AFUNPTR)EpilogueAnalysis,
          IARG_ADDRINT, INS_Address(ins),
          IARG_ADDRINT, INS_NextAddress(ins),
          IARG_PTR, new std::string(INS_Disassemble(ins)),
          IARG_END);
    }
    else if (INS_OperandCount(ins) > 1 && INS_MemoryOperandIsWritten(ins, 0)){
      INS_InsertCall(
          ins, IPOINT_BEFORE, (AFUNPTR)WriteMem,
          IARG_ADDRINT, INS_Address(ins),
          IARG_PTR, new std::string(INS_Disassemble(ins)),
          IARG_UINT32, INS_OperandCount(ins),
          IARG_UINT32, INS_OperandReg(ins, 1),
          IARG_MEMORYOP_EA, 0,
          IARG_END);
    }

    /* Value Set Analysis */
    if (INS_Opcode(ins) == XED_ICLASS_MOV &&
        INS_RegR(ins, 0) == REG_RBP && 
        INS_RegR(ins, 1) == REG_INVALID() && 
        INS_IsMemoryWrite(ins)){
      INS_InsertCall(
          ins, IPOINT_BEFORE, (AFUNPTR)ValueSetAnalysis,
          IARG_ADDRINT, INS_Address(ins),
          IARG_PTR, new std::string(INS_Disassemble(ins)),
          IARG_REG_VALUE, REG_RSP,
          IARG_REG_VALUE, REG_RBP,
          IARG_MEMORYOP_EA, 0,
          IARG_END);
    }

    /* Analyzes stack overflow */
    if (INS_MemoryOperandIsWritten(ins, 0)){
        INS_InsertCall(
            ins, IPOINT_BEFORE, (AFUNPTR)WriteMemAnalysis,
            IARG_ADDRINT, INS_Address(ins),
            IARG_PTR, new std::string(INS_Disassemble(ins)),
            IARG_MEMORYOP_EA, 0,
            IARG_END);
      }

    /* Timer Handler - And instruction counter */
    INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)timerHandler, 
      IARG_ADDRINT, INS_Address(INS_Prev(ins)),
      IARG_ADDRINT, INS_Address(ins),
      IARG_ADDRINT, INS_Address(INS_Next(ins)),
      IARG_PTR, new std::string(INS_Disassemble(ins)),
      IARG_END);

  }
}

VOID callbackBeforeMalloc(ADDRINT size)
{
  lastSize = size;
}

VOID callbackBeforeFree(ADDRINT addr)
{ 
    std::list<struct mallocArea>::iterator i;
  
  #ifdef DEBUG
    TraceFile << "[INFO] free(" << std::hex << addr << ")" << std::endl;
  #endif
  for(i = mallocAreaList.begin(); i != mallocAreaList.end(); i++){
    if (addr == i->base){
      i->status = FREE;
      break;
    }
  }
}

VOID callbackAfterMalloc(ADDRINT ret)
{
    std::list<struct mallocArea>::iterator i;
  struct mallocArea elem;

  #ifdef DEBUG
    TraceFile << "[INFO] malloc(" << std::dec << lastSize << ") = " << std::hex << ret << std::endl;
  #endif
  if (ret){

    for(i = mallocAreaList.begin(); i != mallocAreaList.end(); i++){
      if (ret == i->base){
        i->status = ALLOCATE;
        i->size = lastSize;
        return;
      }
    }
    elem.base = ret;
    elem.size = lastSize;
    elem.status = ALLOCATE;
    mallocAreaList.push_front(elem);
  }
}

VOID Image(IMG img, VOID *v)
{
  RTN mallocRtn = RTN_FindByName(img, "malloc");
  RTN freeRtn = RTN_FindByName(img, "free");

  if (RTN_Valid(mallocRtn)){
    RTN_Open(mallocRtn);

    RTN_InsertCall(
        mallocRtn, 
        IPOINT_BEFORE, (AFUNPTR)callbackBeforeMalloc,
        IARG_FUNCARG_ENTRYPOINT_VALUE, 0,
        IARG_END);

    RTN_InsertCall(
        mallocRtn, 
        IPOINT_AFTER, (AFUNPTR)callbackAfterMalloc,
        IARG_FUNCRET_EXITPOINT_VALUE, 
        IARG_END);

    RTN_Close(mallocRtn);
  }

  if (RTN_Valid(freeRtn)){
    RTN_Open(freeRtn);
    RTN_InsertCall(
        freeRtn, 
        IPOINT_BEFORE, (AFUNPTR)callbackBeforeFree,
        IARG_FUNCARG_ENTRYPOINT_VALUE, 0,
        IARG_END);
    RTN_Close(freeRtn);
  }
}

#ifdef DEBUG
VOID Fini(INT32 code, VOID *v)
{
  UINT32 i;
  std::list<struct stackFrameVar_s>::iterator it;
  
  for (i = 0; i < 32; i++){
    if (VSAL[i].stackFrameVar.size()){
      TraceFile << "id stack frame: " << std::dec << i << "\t Num var: " << VSAL[i].stackFrameVar.size() << " ( ";

      for(it = VSAL[i].stackFrameVar.begin(); it != VSAL[i].stackFrameVar.end(); it++){
        TraceFile << std::hex << it->addrVar << ":" << std::dec << it->sizeVar << " ";
      }
      TraceFile << ")" << std::endl;
    }
  }

  TraceFile << "------------------" << std::endl;
  TraceFile << "Addr\tNumber\tDisass" << std::endl;
  for (i = 0; i < 0x10000; i++){
    if (_tabAddr[i])
      TraceFile << std::hex << (0x400000 + i) << "\t" << std::dec << _tabAddr[i] << "\t" << _tabStr[i] << std::endl;
  }
}
#endif

int main(int argc, char *argv[])
{
    PIN_InitSymbols();
    if(PIN_Init(argc, argv)){
        return Usage();
    }
    
    TraceFile.open(KnobOutputFile.Value().c_str());

    PIN_SetSyntaxIntel();
    IMG_AddInstrumentFunction(Image, 0);
    INS_AddInstrumentFunction(Instruction, 0);
    #ifdef DEBUG
      PIN_AddFiniFunction(Fini, 0);
    #endif
    PIN_StartProgram();
    
    return 0;
}

