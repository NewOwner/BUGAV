#include "ndisuser.h"

// Function:  GetKeyValue
//
// Purpose:   Retrieve the value of a key from the inf file.
//
// Arguments:
//    hInf        [in]  Inf file handle.
//    lpszSection [in]  Section name.
//    lpszKey     [in]  Key name.
//    dwIndex     [in]  Key index.
//    lppszValue  [out] Key value.
//
// Returns:   S_OK on success, otherwise and error code.
//
// Notes:
//

HRESULT
GetKeyValue(
    HINF hInf,
    _In_ LPCWSTR lpszSection,
    _In_opt_ LPCWSTR lpszKey,
    DWORD  dwIndex,
    _Outptr_ LPWSTR* lppszValue) {
    INFCONTEXT  infCtx;
    __range(0, 512) DWORD       dwSizeNeeded;
    HRESULT     hr;

    *lppszValue = NULL;

    if (SetupFindFirstLineW(hInf,
        lpszSection,
        lpszKey,
        &infCtx) == FALSE) {
        return HRESULT_FROM_WIN32(GetLastError());
    }

    if (SetupGetStringFieldW(&infCtx,
        dwIndex,
        NULL,
        0,
        &dwSizeNeeded)) {
        *lppszValue = (LPWSTR)CoTaskMemAlloc(sizeof(WCHAR) * dwSizeNeeded);

        if (!*lppszValue) {
            return HRESULT_FROM_WIN32(ERROR_NOT_ENOUGH_MEMORY);
        }

        if (SetupGetStringFieldW(&infCtx,
            dwIndex,
            *lppszValue,
            dwSizeNeeded,
            NULL) == FALSE) {

            hr = HRESULT_FROM_WIN32(GetLastError());

            CoTaskMemFree(*lppszValue);
            *lppszValue = NULL;
        } else {
            hr = S_OK;
        }
    } else {
        DWORD dwErr = GetLastError();
        hr = HRESULT_FROM_WIN32(dwErr);
    }

    return hr;
}

// Function:  GetPnpID
//
// Purpose:   Retrieve PnpID from an inf file.
//
// Arguments:
//    lpszInfFile [in]  Inf file to search.
//    lppszPnpID  [out] PnpID found.
//
// Returns:   TRUE on success.
//
// Notes:
//

HRESULT
GetPnpID(
    _In_ LPWSTR lpszInfFile,
    _Outptr_ LPWSTR* lppszPnpID) {
    HINF    hInf;
    LPWSTR  lpszModelSection;
    HRESULT hr;

    *lppszPnpID = NULL;

    hInf = SetupOpenInfFileW(lpszInfFile,
        NULL,
        INF_STYLE_WIN4,
        NULL);

    if (hInf == INVALID_HANDLE_VALUE) {

        return HRESULT_FROM_WIN32(GetLastError());
    }

    //
    // Read the Model section name from Manufacturer section.
    //

    hr = GetKeyValue(hInf,
        L"Manufacturer",
        NULL,
        1,
        &lpszModelSection);

    if (SUCCEEDED(hr)) {

        //
        // Read PnpID from the Model section.
        //

        hr = GetKeyValue(hInf,
            lpszModelSection,
            NULL,
            2,
            lppszPnpID);

        CoTaskMemFree(lpszModelSection);
    }

    SetupCloseInfFile(hInf);

    return hr;
}

// Function:  InstallSelectedComponentType
//
// Purpose:   Install a network component.
//
// Arguments:
//    hwndDlg     [in]  Handle to Install dialog box.
//    lpszInfFile [in]  Inf file of the network component.
//
// Returns:   None
//
// Notes:
//       If lpszInfFile is NULL, network components are installed from the
//       system directory.
//

VOID
InstallSelectedComponentType(
    _In_opt_ LPWSTR lpszInfFile) {
    HRESULT   hr;
    LPWSTR  lpszPnpID;

    hr = GetPnpID(lpszInfFile, &lpszPnpID);

    if (hr == S_OK) {

        hr = InstallSpecifiedComponent(lpszInfFile,
            lpszPnpID,
            &GUID_DEVCLASS_NETSERVICE);

        CoTaskMemFree(lpszPnpID);
    } else {
        wprintf(L"%d; Error reading the INF file %s.",hr, lpszInfFile);
    }
}

// Function:  InstallSpecifiedComponent
//
// Purpose:   Install a network component from an INF file.
//
// Arguments:
//    lpszInfFile [in]  INF file.
//    lpszPnpID   [in]  PnpID of the network component to install.
//    pguidClass  [in]  Class GUID of the network component.
//
// Returns:   None.
//
// Notes:
//

HRESULT InstallSpecifiedComponent(_In_ LPWSTR lpszInfFile,
    _In_ LPWSTR lpszPnpID,
    const GUID* pguidClass) {
    INetCfg* pnc;
    LPWSTR     lpszApp;
    HRESULT    hr;

    hr = HrGetINetCfg(TRUE,
        APP_NAME,
        &pnc,
        &lpszApp);

    if (hr == S_OK) {

        //
        // Install the network component.
        //

        hr = HrInstallNetComponent(pnc,
            lpszPnpID,
            pguidClass,
            lpszInfFile);
        if ((hr == S_OK) || (hr == NETCFG_S_REBOOT)) {

            hr = pnc->Apply();
        } else {
            if (hr != HRESULT_FROM_WIN32(ERROR_CANCELLED)) {
                wprintf(L"%d; Couldn't install the network component.", hr);
            }
        }

        HrReleaseINetCfg(pnc,
            TRUE);
    } else {
        if ((hr == NETCFG_E_NO_WRITE_LOCK) && lpszApp) {
            wprintf(L"%d; %s currently holds the lock, try later.", hr, lpszApp);

            CoTaskMemFree(lpszApp);
        } else {
            wprintf(L"%d; Couldn't the get notify object interface.",hr);
        }
    }

    return hr;
}

// Function:  HrInstallNetComponent
//
// Purpose:   Install a network component(protocols, clients and services)
//            given its INF file.
//
// Arguments:
//    pnc              [in] Reference to INetCfg.
//    lpszComponentId  [in] PnpID of the network component.
//    pguidClass       [in] Class GUID of the network component.
//    lpszInfFullPath  [in] INF file to install from.
//
// Returns:   S_OK on success, otherwise an error code.

HRESULT HrInstallNetComponent(IN INetCfg* pnc,
    IN LPCWSTR lpszComponentId,
    IN const GUID* pguidClass,
    IN LPCWSTR lpszInfFullPath) {

    DWORD     dwError;
    HRESULT   hr = S_OK;
    WCHAR* Drive = NULL;
    WCHAR* Dir = NULL;
    WCHAR* DirWithDrive = NULL;
    do {
        if (lpszInfFullPath) {

            //
            // Allocate memory to hold the strings
            //
            Drive = (WCHAR*)CoTaskMemAlloc(_MAX_DRIVE * sizeof(WCHAR));
            if (NULL == Drive) {
                hr = E_OUTOFMEMORY;
                break;
            }
            ZeroMemory(Drive, _MAX_DRIVE * sizeof(WCHAR));

            Dir = (WCHAR*)CoTaskMemAlloc(_MAX_DIR * sizeof(WCHAR));
            if (NULL == Dir) {
                hr = E_OUTOFMEMORY;
                break;
            }
            ZeroMemory(Dir, _MAX_DRIVE * sizeof(WCHAR));

            DirWithDrive = (WCHAR*)CoTaskMemAlloc((_MAX_DRIVE + _MAX_DIR) * sizeof(WCHAR));
            if (NULL == DirWithDrive) {
                hr = E_OUTOFMEMORY;
                break;
            }
            ZeroMemory(DirWithDrive, (_MAX_DRIVE + _MAX_DIR) * sizeof(WCHAR));

            //
            // Get the path where the INF file is.
            //

            _wsplitpath_s(lpszInfFullPath,
                Drive,
                _MAX_DRIVE,
                Dir,
                _MAX_DIR,
                NULL,
                0,
                NULL,
                0);

            StringCchCopyW(DirWithDrive,
                _MAX_DRIVE + _MAX_DIR,
                Drive);
            StringCchCatW(DirWithDrive,
                _MAX_DRIVE + _MAX_DIR,
                Dir);

            //
            // Copy the INF file and other files referenced in the INF file.
            //

            if (!SetupCopyOEMInfW(lpszInfFullPath,
                DirWithDrive,  // Other files are in the
                               // same dir. as primary INF
                SPOST_PATH,    // First param is path to INF
                0,             // Default copy style
                NULL,          // Name of the INF after
                               // it's copied to %windir%\inf
                0,             // Max buf. size for the above
                NULL,          // Required size if non-null
                NULL)) {      // Optionally get the filename
                               // part of Inf name after it is copied.
                dwError = GetLastError();

                hr = HRESULT_FROM_WIN32(dwError);
            }
        }
        if (S_OK == hr) {

            // Install the network component.
            hr = HrInstallComponent(pnc,
                lpszComponentId,
                pguidClass);
            if (hr == S_OK) {

                //
                // On success, apply the changes
                //

                hr = pnc->Apply();
            }
        }
    } while (false);

    return hr;
}

// Function:  HrInstallComponent
//
// Purpose:   Install a network component(protocols, clients and services)
//            given its INF file.
// Arguments:
//    pnc              [in] Reference to INetCfg.
//    lpszComponentId  [in] PnpID of the network component.
//    pguidClass       [in] Class GUID of the network component.
//
// Returns:   S_OK on success, otherwise an error code.
//
// Notes:
//

HRESULT HrInstallComponent(IN INetCfg* pnc,
    IN LPCWSTR szComponentId,
    IN const GUID* pguidClass) {
    INetCfgClassSetup* pncClassSetup = NULL;
    INetCfgComponent* pncc = NULL;
    OBO_TOKEN           OboToken;
    HRESULT             hr = S_OK;

    //
    // OBO_TOKEN specifies on whose behalf this
    // component is being installed.
    // Set it to OBO_USER so that szComponentId will be installed
    // on behalf of the user.
    //

    ZeroMemory(&OboToken,
        sizeof(OboToken));
    OboToken.Type = OBO_USER;

    //
    // Get component's setup class reference.
    //

    hr = pnc->QueryNetCfgClass(pguidClass,
        IID_INetCfgClassSetup,
        (void**)&pncClassSetup);
    if (hr == S_OK) {

        hr = pncClassSetup->Install(szComponentId,
            &OboToken,
            0,
            0,       // Upgrade from build number.
            NULL,    // Answerfile name
            NULL,    // Answerfile section name
            &pncc); // Reference after the component
        if (S_OK == hr) {                   // is installed.

            //
            // we don't need to use pncc (INetCfgComponent), release it
            //

            ReleaseRef(pncc);
        }

        ReleaseRef(pncClassSetup);
    }

    return hr;
}

// Function:  ReleaseRef
//
// Purpose:   Release reference.
//
// Arguments:
//    punk     [in]  IUnknown reference to release.
//
// Returns:   Reference count.
//
// Notes:
//

VOID ReleaseRef(IN IUnknown* punk) {
    if (punk) {
        punk->Release();
    }

    return;
}