#pragma once
#pragma region HEADER

//#include <stdio.h>
//#include <stdlib.h>
//#include <windows.h>
//#include <wchar.h>
//#include <netcfgx.h>
//#include <netcfgn.h>
//#include <setupapi.h>
//#include <devguid.h>
//#include <objbase.h>
//#include <strsafe.h>
//#include <comdef.h>
//
//#define APP_NAME            L"ndisuser"
//#define LOCK_TIME_OUT     5000
//
//// INSTALL
//
//VOID InstallSelectedComponentType(_In_opt_ LPWSTR lpszInfFile);
//
//HRESULT InstallSpecifiedComponent(_In_ LPWSTR lpszInfFile,
//    _In_ LPWSTR lpszPnpID,
//    const GUID* pguidClass);
//
//HRESULT HrInstallNetComponent(IN INetCfg* pnc,
//    IN LPCWSTR lpszComponentId,
//    IN const GUID* pguidClass,
//    IN LPCWSTR lpszInfFullPath);
//
//HRESULT HrInstallComponent(IN INetCfg* pnc,
//    IN LPCWSTR szComponentId,
//    IN const GUID* pguidClass);     // XXX
//
//// UNINSTALL
//
//VOID UninstallSelectedComponent(_In_ LPWSTR lpszInfId);
//
//HRESULT UninstallComponent(_In_ LPWSTR lpszInfId);
//
//HRESULT HrUninstallNetComponent(IN INetCfg* pnc,
//    IN LPCWSTR szComponentId);      // XXX
//
//// UTIL
//
//HRESULT GetKeyValue(
//    HINF hInf,
//    _In_ LPCWSTR lpszSection,
//    _In_opt_ LPCWSTR lpszKey,
//    DWORD  dwIndex,
//    _Outptr_ LPWSTR* lppszValue);
//
//HRESULT GetPnpID(_In_ LPWSTR lpszInfFile,
//    _Outptr_ LPWSTR* lppszPnpID);
//
//
//// COM
//
//HRESULT HrGetINetCfg(IN BOOL fGetWriteLock,
//    IN LPCWSTR lpszAppName,
//    OUT INetCfg** ppnc,
//    _Outptr_opt_result_maybenull_ LPWSTR* lpszLockedBy);
//
//HRESULT HrReleaseINetCfg(INetCfg* pnc, BOOL fHasWriteLock);
//
//VOID ReleaseRef(IN IUnknown* punk);
//
//DWORD GetLastErrorAsString();

#pragma endregion

#pragma region USAGE

////LPWSTR infpath = L"E:\\ndislwf\\netlwf.inf";
//LPWSTR infpath = L"F:\\UNIVER\\9_sem\\TISUIB\\2\\BUGAV\\ndisfilter\\x64\\Debug\\netlwf.inf";
////LPWSTR infpath = L"netlwf.inf";
//    // Callback function
//UINT CopyMsgHandler(UINT Context, UINT Notification, UINT_PTR Param1, UINT_PTR Param2) {
//    UNREFERENCED_PARAMETER(Context);
//    UNREFERENCED_PARAMETER(Notification);
//    UNREFERENCED_PARAMETER(Param1);
//    UNREFERENCED_PARAMETER(Param2);
//    UINT rtnValue = NO_ERROR;
//    return rtnValue;
//}
//
// method 1
//HINF HInf;
//UINT ErrorLine;
//BOOL bRes = FALSE;
//BOOL FileWasInUse = FALSE;
//L"E:\\ndislwf\\netlwf.inf";
////PCWSTR szSourceFileName = L"F:\\UNIVER\\9_sem\\TISUIB\\2\\BUGAV\\ndisfilter\\x64\\Debug\\netlwf.inf";
////PCWSTR szSourceFileName = L"netlwf.inf";
//PCWSTR szSourceFileName = L"E:\\ndislwf\\netlwf.inf";
//PVOID Context = NULL;
//
//HInf = SetupOpenInfFile(szSourceFileName, NULL, INF_STYLE_WIN4, &ErrorLine);
//
//PCWSTR  SourceFile = L"ndislwf.sys";
//PCWSTR SourcePathRoot = L"E:\\ndislwf";
//PCWSTR DestinationName = L"E:\\ndislwf\\ndislwf.sys";
//
//bRes = SetupInstallFileEx(HInf, NULL, SourceFile, SourcePathRoot, DestinationName, SP_COPY_FORCE_IN_USE,
//    (PSP_FILE_CALLBACK)CopyMsgHandler, Context, &FileWasInUse);
//
//GetLastErrorAsString();
//
//SetupCloseInfFile(HInf);
//
// method 2
//InstallSelectedComponentType(infpath);
//
// method 3
//InstallHinfSection(NULL, NULL, TEXT("Install 132 F:\\UNIVER\\9_sem\\TISUIB\\2\\BUGAV\\ndisfilter\\x64\\Debug\\netlwf.inf"), 0);

#pragma endregion

#pragma region COMPONENT
//#include "ndisuser.h"
//
//// Purpose:   Retrieve the value of a key from the inf file.
////
//// Arguments:
////    hInf        [in]  Inf file handle.
////    lpszSection [in]  Section name.
////    lpszKey     [in]  Key name.
////    dwIndex     [in]  Key index.
////    lppszValue  [out] Key value.
////
//HRESULT GetKeyValue(
//    HINF hInf,
//    _In_ LPCWSTR lpszSection,
//    _In_opt_ LPCWSTR lpszKey,
//    DWORD  dwIndex,
//    _Outptr_ LPWSTR* lppszValue) {
//
//    INFCONTEXT  infCtx;
//    __range(0, 512) DWORD       dwSizeNeeded;
//    HRESULT     hr;
//
//    *lppszValue = NULL;
//
//    if (SetupFindFirstLineW(hInf, lpszSection, lpszKey, &infCtx) == FALSE) {
//        return HRESULT_FROM_WIN32(GetLastError());
//    }
//    if (SetupGetStringFieldW(&infCtx, dwIndex, NULL, 0, &dwSizeNeeded)) {
//        *lppszValue = (LPWSTR)CoTaskMemAlloc(sizeof(WCHAR) * dwSizeNeeded);
//
//        if (!*lppszValue) { return HRESULT_FROM_WIN32(ERROR_NOT_ENOUGH_MEMORY); }
//
//        if (SetupGetStringFieldW(&infCtx, dwIndex, *lppszValue, dwSizeNeeded, NULL) == FALSE) {
//
//            hr = HRESULT_FROM_WIN32(GetLastError());
//
//            CoTaskMemFree(*lppszValue);
//            *lppszValue = NULL;
//        } else {
//            hr = S_OK;
//        }
//    } else {
//        DWORD dwErr = GetLastError();
//        hr = HRESULT_FROM_WIN32(dwErr);
//    }
//    return hr;
//}
//
//// Purpose:   Retrieve PnpID from an inf file.
////
//// Arguments:
////    lpszInfFile [in]  Inf file to search.
////    lppszPnpID  [out] PnpID found.
////
//HRESULT GetPnpID(_In_ LPWSTR lpszInfFile,
//    _Outptr_ LPWSTR* lppszPnpID) {
//
//    HINF    hInf;
//    LPWSTR  lpszModelSection;
//    HRESULT hr;
//
//    *lppszPnpID = NULL;
//
//    hInf = SetupOpenInfFileW(lpszInfFile, NULL, INF_STYLE_WIN4, NULL);
//
//    if (hInf == INVALID_HANDLE_VALUE) {
//        DWORD errval = GetLastErrorAsString();
//        return HRESULT_FROM_WIN32(errval);
//    }
//
//    // Read the Model section name from Manufacturer section.
//    hr = GetKeyValue(hInf, L"Manufacturer", NULL, 1, &lpszModelSection);
//
//    if (SUCCEEDED(hr)) {
//
//        // Read PnpID from the Model section.
//        hr = GetKeyValue(hInf, lpszModelSection, NULL, 2, lppszPnpID);
//        CoTaskMemFree(lpszModelSection);
//    }
//    SetupCloseInfFile(hInf);
//    return hr;
//}
//
//// Purpose:   Release reference.
////
//// Arguments:
////    punk     [in]  IUnknown reference to release.
////
//VOID ReleaseRef(IN IUnknown* punk) {
//    if (punk) { punk->Release(); }
//    return;
//}
//
//// Purpose:   Get a reference to INetCfg.
////
//// Arguments:
////    fGetWriteLock  [in]  If TRUE, Write lock.requested.
////    lpszAppName    [in]  Application name requesting the reference.
////    ppnc           [out] Reference to INetCfg.
////    lpszLockedBy   [in]  Optional. Application who holds the write lock.
////
//HRESULT HrGetINetCfg(IN BOOL fGetWriteLock,
//    IN LPCWSTR lpszAppName,
//    OUT INetCfg** ppnc,
//    _Outptr_opt_result_maybenull_ LPWSTR* lpszLockedBy) {
//    INetCfg* pnc = NULL;
//    INetCfgLock* pncLock = NULL;
//    HRESULT      hr = S_OK;
//
//    // Initialize the output parameters.
//    *ppnc = NULL;
//
//    if (lpszLockedBy) { *lpszLockedBy = NULL; }
//
//    // Initialize COM
//    hr = CoInitialize(NULL);
//
//    if (hr == S_OK) {
//
//        // Create the object implementing INetCfg.
//        hr = CoCreateInstance(CLSID_CNetCfg, NULL, CLSCTX_INPROC_SERVER, IID_INetCfg, (void**)&pnc);
//        if (hr == S_OK) {
//
//            if (fGetWriteLock) {
//
//                // Get the locking reference
//                hr = pnc->QueryInterface(IID_INetCfgLock, (LPVOID*)&pncLock);
//                if (hr == S_OK) {
//
//                    // Attempt to lock the INetCfg for read/write
//                    hr = pncLock->AcquireWriteLock(LOCK_TIME_OUT, lpszAppName, lpszLockedBy);
//                    if (hr == S_FALSE) {
//                        hr = NETCFG_E_NO_WRITE_LOCK;
//                    }
//                }
//            }
//
//            if (hr == S_OK) {
//
//                // Initialize the INetCfg object.
//                hr = pnc->Initialize(NULL);
//
//                if (hr == S_OK) {
//                    *ppnc = pnc;
//                    pnc->AddRef();
//                } else {
//
//                    //
//                    // Initialize failed, if obtained lock, release it
//                    //
//
//                    if (pncLock) {
//                        pncLock->ReleaseWriteLock();
//                    }
//                }
//            }
//
//            ReleaseRef(pncLock);
//            ReleaseRef(pnc);
//        }
//
//        // In case of error, uninitialize COM.
//        //
//
//        if (hr != S_OK) { CoUninitialize(); }
//    }
//    return hr;
//}
//
//// Function:  HrReleaseINetCfg
////
//// Purpose:   Get a reference to INetCfg.
////
//// Arguments:
////    pnc           [in] Reference to INetCfg to release.
////    fHasWriteLock [in] If TRUE, reference was held with write lock.
////
//HRESULT HrReleaseINetCfg(IN INetCfg* pnc,
//    IN BOOL fHasWriteLock) {
//
//    INetCfgLock* pncLock = NULL;
//    HRESULT        hr = S_OK;
//
//    // Uninitialize INetCfg
//    hr = pnc->Uninitialize();
//
//    // If write lock is present, unlock it
//    if (hr == S_OK && fHasWriteLock) {
//
//        // Get the locking reference
//        hr = pnc->QueryInterface(IID_INetCfgLock, (LPVOID*)&pncLock);
//        if (hr == S_OK) {
//            hr = pncLock->ReleaseWriteLock();
//            ReleaseRef(pncLock);
//        }
//    }
//
//    ReleaseRef(pnc);
//
//    // Uninitialize COM.
//    CoUninitialize();
//    return hr;
//}
//
//
//
////Returns the last Win32 error, in string format. Returns an empty string if there is no error.
//DWORD GetLastErrorAsString() {
//    //Get the error message, if any.
//    DWORD errorMessageID = ::GetLastError();
//    if (errorMessageID == 0)
//        return NULL; //No error message has been recorded
//
//    LPSTR messageBuffer = nullptr;
//    FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
//        NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);
//
//    printf("GetLastErrorAsString");
//    printf(messageBuffer);
//    return errorMessageID;
//}
//
//
#pragma endregion

#pragma region COMPONENT_INSTALL

//#include "ndisuser.h"
//
//// Purpose:   Install a network component.
////
//// Arguments:
////    hwndDlg     [in]  Handle to Install dialog box.
////    lpszInfFile [in]  Inf file of the network component.
////
//VOID InstallSelectedComponentType(_In_opt_ LPWSTR lpszInfFile) {
//
//    HRESULT   hr;
//    LPWSTR  lpszPnpID;
//
//    hr = GetPnpID(lpszInfFile, &lpszPnpID);
//
//    if (hr == S_OK) {
//        hr = InstallSpecifiedComponent(lpszInfFile, lpszPnpID, &GUID_DEVCLASS_NETSERVICE);
//        CoTaskMemFree(lpszPnpID);
//    } else {
//        _com_error err(hr);
//        LPCTSTR errMsg = err.ErrorMessage();
//        wprintf(L"%s; Error reading the INF file %s.", errMsg, lpszInfFile);
//    }
//}
//
//// Purpose:   Install a network component from an INF file.
////
//// Arguments:
////    lpszInfFile [in]  INF file.
////    lpszPnpID   [in]  PnpID of the network component to install.
////    pguidClass  [in]  Class GUID of the network component.
////
//HRESULT InstallSpecifiedComponent(_In_ LPWSTR lpszInfFile,
//    _In_ LPWSTR lpszPnpID,
//    const GUID* pguidClass) {
//
//    INetCfg* pnc;
//    LPWSTR     lpszApp;
//    HRESULT    hr;
//
//    hr = HrGetINetCfg(TRUE, APP_NAME, &pnc, &lpszApp);
//
//    if (hr == S_OK) {
//
//        // Install the network component.
//        hr = HrInstallNetComponent(pnc, lpszPnpID, pguidClass, lpszInfFile);
//
//        if ((hr == S_OK) || (hr == NETCFG_S_REBOOT)) {
//            hr = pnc->Apply();
//        } else {
//            if (hr != HRESULT_FROM_WIN32(ERROR_CANCELLED)) { wprintf(L"%d; Couldn't install the network component.", hr); }
//        }
//        HrReleaseINetCfg(pnc, TRUE);
//
//    } else {
//        if ((hr == NETCFG_E_NO_WRITE_LOCK) && lpszApp) {
//            wprintf(L"%d; %s currently holds the lock, try later.", hr, lpszApp);
//            CoTaskMemFree(lpszApp);
//
//        } else { wprintf(L"%d; Couldn't the get notify object interface.", hr); }
//    }
//    return hr;
//}
//
//// Purpose:   Install a network component(protocols, clients and services)
////            given its INF file.
////
//// Arguments:
////    pnc              [in] Reference to INetCfg.
////    lpszComponentId  [in] PnpID of the network component.
////    pguidClass       [in] Class GUID of the network component.
////    lpszInfFullPath  [in] INF file to install from.
////
//HRESULT HrInstallNetComponent(IN INetCfg* pnc,
//    IN LPCWSTR lpszComponentId,
//    IN const GUID* pguidClass,
//    IN LPCWSTR lpszInfFullPath) {
//
//    bool isCopied;
//    DWORD     dwError;
//    HRESULT   hr = S_OK;
//    do {
//        if (lpszInfFullPath) {
//            PCWSTR pathToInf = L"F:\\UNIVER\\9_sem\\TISUIB\\2\\BUGAV\\ndisfilter\\x64\\Debug\\ndislwf\\netlwf.inf";
//            PCWSTR pathToBin = L"F:\\UNIVER\\9_sem\\TISUIB\\2\\BUGAV\\ndisfilter\\x64\\Debug\\ndislwf\\";
//            PWSTR DestinationInfFileName = L"netlwf.inf";
//            // Copy the INF file and other files referenced in the INF file.
//            isCopied = SetupCopyOEMInfW(pathToInf,
//                pathToBin,  // Other files are in the
//                               // same dir. as primary INF
//                SPOST_PATH,    // First param is path to INF
//                SP_COPY_REPLACEONLY,             // Default copy style
//                DestinationInfFileName,          // Name of the INF after
//                               // it's copied to %windir%\inf
//                256,             // Max buf. size for the above
//                NULL,          // Required size if non-null
//                NULL);     // Optionally get the filename
//                               // part of Inf name after it is copied.
//            dwError = GetLastErrorAsString();
//            //hr = HRESULT_FROM_WIN32(dwError);
//        }
//        if (S_OK == hr) {
//
//            // Install the network component.
//            hr = HrInstallComponent(pnc,
//                lpszComponentId,
//                pguidClass);
//            if (hr == S_OK) {
//
//                // On success, apply the changes
//                hr = pnc->Apply();
//            }
//        }
//    } while (false);
//    return hr;
//}
//
//// XXX
////
//// Purpose:   Install a network component(protocols, clients and services)
////            given its INF file.
//// Arguments:
////    pnc              [in] Reference to INetCfg.
////    lpszComponentId  [in] PnpID of the network component.
////    pguidClass       [in] Class GUID of the network component.
////
//HRESULT HrInstallComponent(IN INetCfg* pnc,
//    IN LPCWSTR szComponentId,
//    IN const GUID* pguidClass) {
//
//    INetCfgClassSetup* pncClassSetup = NULL;
//    INetCfgComponent* pncc = NULL;
//    OBO_TOKEN           OboToken;
//    HRESULT             hr = S_OK;
//
//    // OBO_TOKEN specifies on whose behalf this
//    // component is being installed.
//    // Set it to OBO_USER so that szComponentId will be installed
//    // on behalf of the user.
//    ZeroMemory(&OboToken, sizeof(OboToken));
//    OboToken.Type = OBO_USER;
//
//    // Get component's setup class reference.
//    hr = pnc->QueryNetCfgClass(pguidClass, IID_INetCfgClassSetup, (void**)&pncClassSetup);
//    if (hr == S_OK) {
//
//        //bool isCopied;
//        //PCSTR pathToInf = "F:\\UNIVER\\9_sem\\TISUIB\\2\\BUGAV\\ndisfilter\\x64\\Debug\\ndislwf\\ndislwf.inf";
//        //PCSTR pathToBin = "F:\\UNIVER\\9_sem\\TISUIB\\2\\BUGAV\\ndisfilter\\x64\\Debug\\ndislwf\\";
//        //PSTR DestinationInfFileName = "ndislwf.inf";
//        //
//        //isCopied = SetupCopyOEMInfA(pathToInf,
//        //    // path to inf file
//        //    pathToBin,
//        //    // dir containing driver binary
//        //    SPOST_PATH,
//        //    0,
//        //    DestinationInfFileName,
//        //    256,
//        //    NULL,
//        //    NULL);
//
//        hr = CoCreateInstance(CLSID_CNetCfg,
//            NULL, CLSCTX_INPROC_SERVER,
//            IID_INetCfg,
//            (void**)&pnc);
//
//        hr = pncClassSetup->Install(szComponentId,
//            &OboToken,
//            NSF_POSTSYSINSTALL,
//            0,       // Upgrade from build number.
//            NULL,    // Answerfile name
//            NULL,    // Answerfile section name
//            &pncc); // Reference after the component
//        if (S_OK == hr) {                   // is installed.
//            // we don't need to use pncc (INetCfgComponent), release it
//            ReleaseRef(pncc);
//        }
//        ReleaseRef(pncClassSetup);
//    }
//    return hr;
//}
//
//

#pragma endregion

#pragma region COMPONENT_UNINSTALL

//#include "ndisuser.h"
//
//// Function:  UninstallSelectedComponent
////
//// Purpose:   Uninstall the selected network component.
////
//// Arguments:
////    hwndDlg     [in]  Window handle of the uninstall dialog box.
////
//VOID UninstallSelectedComponent(_In_ LPWSTR lpszInfId) {
//
//    HRESULT   hr;
//
//    hr = UninstallComponent(lpszInfId);
//
//    switch (hr) {
//
//    case S_OK:
//        wprintf(L"Uninstallation successful.");
//        break;
//
//    case NETCFG_S_REBOOT:
//        wprintf(L"Uninstallation successful: Reboot required.");
//    }
//}
//
//// Purpose:   Uninstall a network component.
////
//// Arguments:
////    lpszInfId  [in]  PnpID of the network component to uninstall.
////
//HRESULT UninstallComponent(_In_ LPWSTR lpszInfId) {
//
//    INetCfg* pnc;
//    INetCfgComponent* pncc;
//    INetCfgClass* pncClass;
//    INetCfgClassSetup* pncClassSetup;
//    LPWSTR               lpszApp;
//    GUID                 guidClass;
//    OBO_TOKEN            obo;
//    HRESULT              hr;
//
//    hr = HrGetINetCfg(TRUE, APP_NAME, &pnc, &lpszApp);
//
//    if (hr == S_OK) {
//
//        // Get a reference to the network component to uninstall.
//        hr = pnc->FindComponent(lpszInfId, &pncc);
//        if (hr == S_OK) {
//
//            // Get the class GUID.
//            hr = pncc->GetClassGuid(&guidClass);
//            if (hr == S_OK) {
//
//                // Get a reference to component's class.
//                hr = pnc->QueryNetCfgClass(&guidClass, IID_INetCfgClass, (PVOID*)&pncClass);
//                if (hr == S_OK) {
//
//                    // Get the setup interface.
//                    hr = pncClass->QueryInterface(IID_INetCfgClassSetup, (LPVOID*)&pncClassSetup);
//                    if (hr == S_OK) {
//
//                        // Uninstall the component.
//                        ZeroMemory(&obo, sizeof(OBO_TOKEN));
//                        obo.Type = OBO_USER;
//                        hr = pncClassSetup->DeInstall(pncc, &obo, NULL);
//                        if ((hr == S_OK) || (hr == NETCFG_S_REBOOT)) {
//
//                            hr = pnc->Apply();
//
//                            if ((hr != S_OK) && (hr != NETCFG_S_REBOOT)) { wprintf(L"%d; Couldn't apply the changes after uninstalling %s.", hr, lpszInfId); }
//                        } else {
//                            wprintf(L"%d; Failed to uninstall %s.", hr, lpszInfId);
//                        }
//                        ReleaseRef(pncClassSetup);
//                    } else {
//                        wprintf(L"%d; Couldn't get an interface to setup class.", hr);
//                    }
//                    ReleaseRef(pncClass);
//                } else {
//                    wprintf(L"%d; Couldn't get a pointer to class interface of %s.", hr, lpszInfId);
//                }
//            } else {
//                wprintf(L"%d; Couldn't get the class guid of %s.", hr, lpszInfId);
//            }
//            ReleaseRef(pncc);
//        } else {
//            wprintf(L"%d; Couldn't get an interface pointer to %s.", hr, lpszInfId);
//        }
//        HrReleaseINetCfg(pnc,
//            TRUE);
//    } else {
//        if ((hr == NETCFG_E_NO_WRITE_LOCK) && lpszApp) {
//            wprintf(L"%d; %s currently holds the lock, try later.", hr, lpszApp);
//            CoTaskMemFree(lpszApp);
//        } else {
//            wprintf(L"%d; Couldn't get the notify object interface.", hr);
//        }
//    }
//    return hr;
//}
//
//// XXX
////
//// Purpose:   Uninstall a network component(protocols, clients and services).
////
//// Arguments:
////    pnc           [in] Reference to INetCfg.
////    szComponentId [in] PnpID of the network component to uninstall.
////
//HRESULT HrUninstallNetComponent(IN INetCfg* pnc, IN LPCWSTR szComponentId) {
//
//    INetCfgComponent* pncc = NULL;
//    INetCfgClass* pncClass = NULL;
//    INetCfgClassSetup* pncClassSetup = NULL;
//    OBO_TOKEN           OboToken;
//    GUID                guidClass;
//    HRESULT             hr = S_OK;
//
//    // OBO_TOKEN specifies on whose behalf this
//    // component is being installed.
//    // Set it to OBO_USER so that szComponentId will be installed
//    // on behalf of the user.
//    ZeroMemory(&OboToken, sizeof(OboToken));
//    OboToken.Type = OBO_USER;
//
//    // Get the component's reference.
//    hr = pnc->FindComponent(szComponentId, &pncc);
//    if (S_OK == hr) {
//
//        // Get the component's class GUID.
//        hr = pncc->GetClassGuid(&guidClass);
//        if (hr == S_OK) {
//
//            // Get component's class reference.
//            hr = pnc->QueryNetCfgClass(&guidClass, IID_INetCfgClass, (void**)&pncClass);
//            if (hr == S_OK) {
//
//                // Get Setup reference.
//                hr = pncClass->QueryInterface(IID_INetCfgClassSetup, (void**)&pncClassSetup);
//                if (hr == S_OK) {
//
//                    hr = pncClassSetup->DeInstall(pncc, &OboToken, NULL);
//                    if (hr == S_OK) {
//
//                        // Apply the changes
//                        hr = pnc->Apply();
//                    }
//                    ReleaseRef(pncClassSetup);
//                }
//                ReleaseRef(pncClass);
//            }
//        }
//        ReleaseRef(pncc);
//    }
//    return hr;
//}

#pragma endregion