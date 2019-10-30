#include "pch.h"

#include "FilterFileWrap.h"

FilterFileWrap::FilterFileWrap() : ptr_FilterFileCtrl(new FilterFileCtrl())
{}

FilterFileWrap::~FilterFileWrap() {
    delete ptr_FilterFileCtrl;
}

// FILE

VOID FilterFileWrap::CLI_Passflt_LoadDriver() { ptr_FilterFileCtrl->FilterFileDrv_LoadDriver(); }
VOID FilterFileWrap::CLI_Passflt_UnloadDriver() { ptr_FilterFileCtrl->FilterFileDrv_UnloadDriver(); }
VOID FilterFileWrap::CLI_Passflt_OpenDevice() { ptr_FilterFileCtrl->FilterFileDrv_OpenDevice(); }

VOID FilterFileWrap::CLI_Passflt_UpdateConfig() { ptr_FilterFileCtrl->FilterFileDrv_UpdateConfig(); }
VOID FilterFileWrap::CLI_Passflt_ConnectCommunicationPort() { ptr_FilterFileCtrl->FilterFileDrv_ConnectCommunicationPort(); }
VOID FilterFileWrap::CLI_Passflt_SendMessage(PCHAR msg) { ptr_FilterFileCtrl->FilterFileDrv_SendMessage(msg); }
