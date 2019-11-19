//
//  Jonathan Salwan - Copyright (C) 2013-08
// 
//  http://shell-storm.org
//  http://twitter.com/JonathanSalwan
//
//  Note: Example 5 - http://shell-storm.org/blog/Taint-analysis-with-Pin/
//        Detect the classical use after free vulnerability 
//

#include "pin.H"
#include <asm/unistd.h>
#include <fstream>
#include <iostream>
#include <list>
#include <stdlib.h>
using std::ofstream;
using std::string;
using std::endl;

#define LOCKED    1
#define UNLOCKED  !LOCKED

#define ALLOCATE  1
#define FREE      !ALLOCATE

static size_t         lastSize;

struct mallocArea
{
  UINT64  base;
  UINT64  size;
  BOOL    status;
};

UINT32 lockTaint = LOCKED;

std::list<UINT64>               addressTainted;
std::list<REG>                  regsTainted;
std::list<struct mallocArea>    mallocAreaList;

KNOB<string> KnobOutputFile(KNOB_MODE_WRITEONCE, "pintool",
    "o", "tool_useafterfree.txt", "specify file name");

ofstream TraceFile;

INT32 Usage()
{
    PIN_ERROR("This tool prints use after free events\n"
        + KNOB_BASE::StringKnobSummary() + "\n");
    return -1;
}

BOOL checkAlreadyRegTainted(REG reg)
{
    std::list<REG>::iterator i;

  for(i = regsTainted.begin(); i != regsTainted.end(); i++){
    if (*i == reg){
      return true;
    }
  }
  return false;
}

VOID removeMemTainted(UINT64 addr)
{
  addressTainted.remove(addr);
  TraceFile << std::hex << "\t\t\t" << addr << " is now freed" << std::endl;
}

VOID addMemTainted(UINT64 addr)
{
  addressTainted.push_back(addr);
  TraceFile << std::hex << "\t\t\t" << addr << " is now tainted" << std::endl;
}

BOOL taintReg(REG reg)
{
  if (checkAlreadyRegTainted(reg) == true){
    TraceFile << "\t\t\t" << REG_StringShort(reg) << " is already tainted" << std::endl;
    return false;
  }

  switch(reg){

    case REG_RAX:  regsTainted.push_front(REG_RAX);
    case REG_EAX:  regsTainted.push_front(REG_EAX); 
    case REG_AX:   regsTainted.push_front(REG_AX); 
    case REG_AH:   regsTainted.push_front(REG_AH); 
    case REG_AL:   regsTainted.push_front(REG_AL); 
         break;

    case REG_RBX:  regsTainted.push_front(REG_RBX);
    case REG_EBX:  regsTainted.push_front(REG_EBX);
    case REG_BX:   regsTainted.push_front(REG_BX);
    case REG_BH:   regsTainted.push_front(REG_BH);
    case REG_BL:   regsTainted.push_front(REG_BL);
         break;

    case REG_RCX:  regsTainted.push_front(REG_RCX); 
    case REG_ECX:  regsTainted.push_front(REG_ECX);
    case REG_CX:   regsTainted.push_front(REG_CX);
    case REG_CH:   regsTainted.push_front(REG_CH);
    case REG_CL:   regsTainted.push_front(REG_CL);
         break;

    case REG_RDX:  regsTainted.push_front(REG_RDX); 
    case REG_EDX:  regsTainted.push_front(REG_EDX); 
    case REG_DX:   regsTainted.push_front(REG_DX); 
    case REG_DH:   regsTainted.push_front(REG_DH); 
    case REG_DL:   regsTainted.push_front(REG_DL); 
         break;

    case REG_RDI:  regsTainted.push_front(REG_RDI); 
    case REG_EDI:  regsTainted.push_front(REG_EDI); 
    case REG_DI:   regsTainted.push_front(REG_DI); 
    case REG_DIL:  regsTainted.push_front(REG_DIL); 
         break;

    case REG_RSI:  regsTainted.push_front(REG_RSI); 
    case REG_ESI:  regsTainted.push_front(REG_ESI); 
    case REG_SI:   regsTainted.push_front(REG_SI); 
    case REG_SIL:  regsTainted.push_front(REG_SIL); 
         break;

    default:
      TraceFile << "\t\t\t" << REG_StringShort(reg) << " can't be tainted" << std::endl;
      return false;
  }
  TraceFile << "\t\t\t" << REG_StringShort(reg) << " is now tainted" << std::endl;
  return true;
}

BOOL removeRegTainted(REG reg)
{
  switch(reg){

    case REG_RAX:  regsTainted.remove(REG_RAX);
    case REG_EAX:  regsTainted.remove(REG_EAX);
    case REG_AX:   regsTainted.remove(REG_AX);
    case REG_AH:   regsTainted.remove(REG_AH);
    case REG_AL:   regsTainted.remove(REG_AL);
         break;

    case REG_RBX:  regsTainted.remove(REG_RBX);
    case REG_EBX:  regsTainted.remove(REG_EBX);
    case REG_BX:   regsTainted.remove(REG_BX);
    case REG_BH:   regsTainted.remove(REG_BH);
    case REG_BL:   regsTainted.remove(REG_BL);
         break;

    case REG_RCX:  regsTainted.remove(REG_RCX); 
    case REG_ECX:  regsTainted.remove(REG_ECX);
    case REG_CX:   regsTainted.remove(REG_CX);
    case REG_CH:   regsTainted.remove(REG_CH);
    case REG_CL:   regsTainted.remove(REG_CL);
         break;

    case REG_RDX:  regsTainted.remove(REG_RDX); 
    case REG_EDX:  regsTainted.remove(REG_EDX); 
    case REG_DX:   regsTainted.remove(REG_DX); 
    case REG_DH:   regsTainted.remove(REG_DH); 
    case REG_DL:   regsTainted.remove(REG_DL); 
         break;

    case REG_RDI:  regsTainted.remove(REG_RDI); 
    case REG_EDI:  regsTainted.remove(REG_EDI); 
    case REG_DI:   regsTainted.remove(REG_DI); 
    case REG_DIL:  regsTainted.remove(REG_DIL); 
         break;

    case REG_RSI:  regsTainted.remove(REG_RSI); 
    case REG_ESI:  regsTainted.remove(REG_ESI); 
    case REG_SI:   regsTainted.remove(REG_SI); 
    case REG_SIL:  regsTainted.remove(REG_SIL); 
         break;

    default:
      return false;
  }
  TraceFile << "\t\t\t" << REG_StringShort(reg) << " is now freed" << std::endl;
  return true;
}

VOID ReadMem(UINT64 insAddr, std::string insDis, UINT32 opCount, REG reg_r, UINT64 memOp, UINT64 sp)
{
  std::list<UINT64>::iterator i;
  std::list<struct mallocArea>::iterator i2;
  UINT64 addr = memOp;
 
  if (opCount != 2)
    return;

  for(i2 = mallocAreaList.begin(); i2 != mallocAreaList.end(); i2++){
    if (addr >= i2->base && addr < (i2->base + i2->size) && i2->status == FREE){
      TraceFile << std::hex << "[UAF in " << addr << "]\t" << insAddr << ": " << insDis << std::endl;
      return;
    }
  }

  for(i = addressTainted.begin(); i != addressTainted.end(); i++){
      if (addr == *i){
        TraceFile << std::hex << "[READ in " << addr << "]\t" << insAddr << ": " << insDis << std::endl;
        taintReg(reg_r);
      
        if (sp > addr && addr > 0x700000000000)
          TraceFile << std::hex << "[UAF in " << addr << "]\t" << insAddr << ": " << insDis << std::endl;

        return;
      }
  }
  if (checkAlreadyRegTainted(reg_r)){
    TraceFile << std::hex << "[READ in " << addr << "]\t" << insAddr << ": " << insDis << std::endl;
    removeRegTainted(reg_r);
  }
}

VOID WriteMem(UINT64 insAddr, std::string insDis, UINT32 opCount, REG reg_r, UINT64 memOp, UINT64 sp)
{
  std::list<UINT64>::iterator i;
  std::list<struct mallocArea>::iterator i2;
  UINT64 addr = memOp;
  
  if (opCount != 2)
    return;
  
  for(i2 = mallocAreaList.begin(); i2 != mallocAreaList.end(); i2++){
    if (addr >= i2->base && addr < (i2->base + i2->size) && i2->status == FREE){
      TraceFile << std::hex << "[UAF in " << addr << "]\t" << insAddr << ": " << insDis << std::endl;
      return;
    }
  }

  for(i = addressTainted.begin(); i != addressTainted.end(); i++){
      if (addr == *i){
        TraceFile << std::hex << "[WRITE in " << addr << "]\t" << insAddr << ": " << insDis << std::endl;
        if (!REG_valid(reg_r) || !checkAlreadyRegTainted(reg_r))
          removeMemTainted(addr);
        
        if (sp > addr && addr > 0x700000000000)
          TraceFile << std::hex << "[UAF in " << addr << "]\t" << insAddr << ": " << insDis << std::endl;

        return ;
      }
  }
  if (checkAlreadyRegTainted(reg_r)){
    TraceFile << std::hex << "[WRITE in " << addr << "]\t" << insAddr << ": " << insDis << std::endl;
    addMemTainted(addr);
  }
}

VOID spreadRegTaint(UINT64 insAddr, std::string insDis, UINT32 opCount, REG reg_r, REG reg_w)
{
  if (opCount != 2)
    return;

  if (REG_valid(reg_w)){
    if (checkAlreadyRegTainted(reg_w) && (!REG_valid(reg_r) || !checkAlreadyRegTainted(reg_r))){
      TraceFile << "[SPREAD]\t\t" << insAddr << ": " << insDis << std::endl;
      TraceFile << "\t\t\toutput: "<< REG_StringShort(reg_w) << " | input: " << (REG_valid(reg_r) ? REG_StringShort(reg_r) : "constant") << std::endl;
      removeRegTainted(reg_w);
    }
    else if (!checkAlreadyRegTainted(reg_w) && checkAlreadyRegTainted(reg_r)){
      TraceFile << "[SPREAD]\t\t" << insAddr << ": " << insDis << std::endl;
      TraceFile << "\t\t\toutput: " << REG_StringShort(reg_w) << " | input: "<< REG_StringShort(reg_r) << std::endl;
      taintReg(reg_w);
    }
  }
}

VOID followData(UINT64 insAddr, std::string insDis, REG reg)
{
  if (!REG_valid(reg))
    return;

  if (checkAlreadyRegTainted(reg)){
      TraceFile << "[FOLLOW]\t\t" << insAddr << ": " << insDis << std::endl;
  }
}

VOID Instruction(INS ins, VOID *v)
{
  if (INS_OperandCount(ins) > 1 && INS_MemoryOperandIsRead(ins, 0) && INS_OperandIsReg(ins, 0)){
    INS_InsertCall(
        ins, IPOINT_BEFORE, (AFUNPTR)ReadMem,
        IARG_ADDRINT, INS_Address(ins),
        IARG_PTR, new std::string(INS_Disassemble(ins)),
        IARG_UINT32, INS_OperandCount(ins),
        IARG_UINT32, INS_OperandReg(ins, 0),
        IARG_MEMORYOP_EA, 0,
        IARG_REG_VALUE, REG_STACK_PTR,
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
        IARG_REG_VALUE, REG_STACK_PTR,
        IARG_END);
  }
  else if (INS_OperandCount(ins) > 1 && INS_OperandIsReg(ins, 0)){
    INS_InsertCall(
        ins, IPOINT_BEFORE, (AFUNPTR)spreadRegTaint,
        IARG_ADDRINT, INS_Address(ins),
        IARG_PTR, new std::string(INS_Disassemble(ins)),
        IARG_UINT32, INS_OperandCount(ins),
        IARG_UINT32, INS_RegR(ins, 0),
        IARG_UINT32, INS_RegW(ins, 0),
        IARG_END);
  }
  
  if (INS_OperandCount(ins) > 1 && INS_OperandIsReg(ins, 0)){
    INS_InsertCall(
        ins, IPOINT_BEFORE, (AFUNPTR)followData,
        IARG_ADDRINT, INS_Address(ins),
        IARG_PTR, new std::string(INS_Disassemble(ins)),
        IARG_UINT32, INS_RegR(ins, 0),
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
  
  TraceFile << "[INFO]\t\tfree(" << std::hex << addr << ")" << std::endl;
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

  TraceFile << "[INFO]\t\tmalloc(" << lastSize << ") = " << std::hex << ret << std::endl;
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

VOID Fini(INT32 code, VOID* v) {
    TraceFile << "=======================================================" << endl;
    TraceFile << "Analysis successfully completed." << endl;
    TraceFile << "Exit code: " << code << endl;
    TraceFile << "=======================================================" << endl;
}

int main(int argc, char *argv[])
{
    PIN_InitSymbols();

    if(PIN_Init(argc, argv)){ return Usage(); }
    
    TraceFile.open(KnobOutputFile.Value().c_str());

    //PIN_SetSyntaxIntel();
    IMG_AddInstrumentFunction(Image, 0);
    INS_AddInstrumentFunction(Instruction, 0);
    PIN_AddFiniFunction(Fini, 0);
    PIN_StartProgram();
    
    return 0;
}

