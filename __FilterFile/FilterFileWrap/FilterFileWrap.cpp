#include "pch.h"

#include "FilterFileWrap.h"
#pragma comment(lib, "DriverCtrl.lib")
#pragma comment(lib, "FilterFileCtrl.lib")
#pragma comment(lib, "FilterFileCtrl.lib")

#pragma comment(lib, "FltLib.lib")
#pragma comment(lib, "advapi32.lib")
#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "setupapi.lib")

FilterFileWrap::FilterFileWrap() : ptr_FilterFileCtrl(new FilterFileCtrl())
{}

FilterFileWrap::~FilterFileWrap() {
    delete ptr_FilterFileCtrl;
}

// FILE

VOID FilterFileWrap::WRAP_FilterFileDrv_LoadDriver() { ptr_FilterFileCtrl->FilterFileDrv_LoadDriver(); }
VOID FilterFileWrap::WRAP_FilterFileDrv_UnloadDriver() { ptr_FilterFileCtrl->FilterFileDrv_UnloadDriver(); }
VOID FilterFileWrap::WRAP_FilterFileDrv_OpenDevice() { ptr_FilterFileCtrl->FilterFileDrv_OpenDevice(); }

VOID FilterFileWrap::WRAP_FilterFileDrv_UpdateConfig() { ptr_FilterFileCtrl->FilterFileDrv_UpdateConfig(); }
VOID FilterFileWrap::WRAP_FilterFileDrv_ConnectCommunicationPort() { ptr_FilterFileCtrl->FilterFileDrv_ConnectCommunicationPort(); }
VOID FilterFileWrap::WRAP_FilterFileDrv_SendMessage(PCHAR msg) { ptr_FilterFileCtrl->FilterFileDrv_SendMessage(msg); }
