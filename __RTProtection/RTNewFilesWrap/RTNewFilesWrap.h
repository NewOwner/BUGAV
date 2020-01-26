#pragma once

#include "../RTNewFilesCtrl/RTNewFilesCtrl.h"


using namespace System;

public ref class RTNewFilesWrap {
    RTNewFilesCtrl* ptr_RTNewFilesCtrl;

public:
    RTNewFilesWrap();
    ~RTNewFilesWrap();

    bool WRAP_ConnectPort();
    bool WRAP_GetFileMessage();
};
