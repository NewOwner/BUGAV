#pragma once

#include <iostream>
#include <Windows.h>
#include <Fltuser.h>
#include <string>
#include <iomanip>
#include <fstream>

#define NEWFILES_PORT_NAME                   L"\\NewFilePort"

class RTNewFilesCtrl {

public:
    HANDLE hPort;

    RTNewFilesCtrl();
    ~RTNewFilesCtrl();

    bool ConnectPort();
    bool GetFileMessage();
};

