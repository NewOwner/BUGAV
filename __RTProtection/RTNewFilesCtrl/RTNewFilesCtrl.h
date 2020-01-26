#pragma once

#include <iostream>
#include <Windows.h>
#include <Fltuser.h>
#include <string>
#include <iomanip>
#include <fstream>

#define NEWFILES_PORT_NAME                   L"\\FilterFilePort"

class RTNewFilesCtrl {

public:
    HANDLE hPort;

    RTNewFilesCtrl();
    ~RTNewFilesCtrl();

    bool ConnectPort();
    bool GetFileMessage();
};

