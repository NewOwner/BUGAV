#include "pch.h"
#include "framework.h"
#include "RTNewFilesCtrl.h"

// TODO: This is an example of a library function

RTNewFilesCtrl::RTNewFilesCtrl() : hPort (NULL) {}

RTNewFilesCtrl::~RTNewFilesCtrl() {}

bool RTNewFilesCtrl::ConnectPort() {
    if (hPort) { return true; }
    HRESULT hResult = S_OK;
    hResult = FilterConnectCommunicationPort(NEWFILES_PORT_NAME,
        0,
        NULL,
        0,
        NULL,
        &hPort);
    
    if (hResult == S_OK) {
        std::cout << "newfiles filter connect" << std::endl;
        return true;
    } else {
        return false;
    }
}

void findAndReplaceAll(std::string& data, std::string toSearch, std::string replaceStr) {
    size_t pos = data.find(toSearch);

    while (pos != std::string::npos) {
        data.replace(pos, toSearch.size(), replaceStr);
        pos = data.find(toSearch, pos + replaceStr.size());
    }
}

bool RTNewFilesCtrl::GetFileMessage() {
    CHAR inMsg[512] = { 0 };
    HRESULT hResult = S_OK;
    
    hResult = FilterGetMessage(
        hPort,
        (PFILTER_MESSAGE_HEADER)inMsg,
        512,
        NULL);
    if (hResult == S_OK) {
        std::string strMsg(inMsg + 16);
        std::string strMsg2 = strMsg;

        /*
        \Device\HarddiskVolume3\DRAFTS\FilterNetworkWrap.dll
        \\?\HarddiskVolume3\DRAFTS\FilterNetworkWrap.dll
        */
        findAndReplaceAll(strMsg2, "\\Device", "\\\\?");

        HANDLE hFile = CreateFileA(strMsg2.c_str(), GENERIC_READ,
            FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, NULL, OPEN_EXISTING,
            FILE_FLAG_BACKUP_SEMANTICS, NULL);
        if (hFile == INVALID_HANDLE_VALUE) {
            std::cout << "CreateFile: "<< GetLastError()<<std::endl;
        }
        char lpszFilePath[512];
        DWORD dw = GetFinalPathNameByHandleA(hFile,
            lpszFilePath, _countof(lpszFilePath) - 1, VOLUME_NAME_DOS);

        if (dw == 0) {
            std::cout << "GetFPNBYH: " << GetLastError() << std::endl;
        }

        std::string convmsg(lpszFilePath);
        findAndReplaceAll(convmsg, "\\\\?\\", "");
        std::cout << "convmsg: " << convmsg << std::endl;
        std::ofstream newFile("new_files.txt");
        std::cout << "writing" << std::endl;
        newFile << convmsg;
        newFile.close();
        return true;
    } else {
        return false;
    }
}
