#include "pch.h"

#include "RTNewFilesWrap.h"

RTNewFilesWrap::RTNewFilesWrap() : ptr_RTNewFilesCtrl(new RTNewFilesCtrl()) {}

RTNewFilesWrap::~RTNewFilesWrap() {
    delete ptr_RTNewFilesCtrl;
}

bool RTNewFilesWrap::WRAP_ConnectPort() {
    return ptr_RTNewFilesCtrl->ConnectPort();
}

bool RTNewFilesWrap::WRAP_GetFileMessage() {
    return ptr_RTNewFilesCtrl->GetFileMessage();
}
