#include "ndisuser.h"

// Purpose:   Retrieve the value of a key from the inf file.
//
// Arguments:
//    hInf        [in]  Inf file handle.
//    lpszSection [in]  Section name.
//    lpszKey     [in]  Key name.
//    dwIndex     [in]  Key index.
//    lppszValue  [out] Key value.
//
HRESULT GetKeyValue(
    HINF hInf,
    _In_ LPCWSTR lpszSection,
    _In_opt_ LPCWSTR lpszKey,
    DWORD  dwIndex,
    _Outptr_ LPWSTR* lppszValue) {

    INFCONTEXT  infCtx;
    __range(0, 512) DWORD       dwSizeNeeded;
    HRESULT     hr;

    *lppszValue = NULL;

    if (SetupFindFirstLineW(hInf, lpszSection, lpszKey, &infCtx) == FALSE) {
        return HRESULT_FROM_WIN32(GetLastError());
    }
    if (SetupGetStringFieldW(&infCtx, dwIndex, NULL, 0, &dwSizeNeeded)) {
        *lppszValue = (LPWSTR)CoTaskMemAlloc(sizeof(WCHAR) * dwSizeNeeded);

        if (!*lppszValue) { return HRESULT_FROM_WIN32(ERROR_NOT_ENOUGH_MEMORY); }

        if (SetupGetStringFieldW(&infCtx, dwIndex, *lppszValue, dwSizeNeeded, NULL) == FALSE) {

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

// Purpose:   Retrieve PnpID from an inf file.
//
// Arguments:
//    lpszInfFile [in]  Inf file to search.
//    lppszPnpID  [out] PnpID found.
//
HRESULT GetPnpID(_In_ LPWSTR lpszInfFile,
    _Outptr_ LPWSTR* lppszPnpID) {

    HINF    hInf;
    LPWSTR  lpszModelSection;
    HRESULT hr;

    *lppszPnpID = NULL;

    hInf = SetupOpenInfFileW(lpszInfFile, NULL, INF_STYLE_WIN4, NULL);

    if (hInf == INVALID_HANDLE_VALUE) { return HRESULT_FROM_WIN32(GetLastError()); }

    // Read the Model section name from Manufacturer section.
    hr = GetKeyValue(hInf, L"Manufacturer", NULL, 1, &lpszModelSection);

    if (SUCCEEDED(hr)) {

        // Read PnpID from the Model section.
        hr = GetKeyValue(hInf, lpszModelSection, NULL, 2, lppszPnpID);

        CoTaskMemFree(lpszModelSection);
    }
    SetupCloseInfFile(hInf);
    return hr;
}

// Purpose:   Release reference.
//
// Arguments:
//    punk     [in]  IUnknown reference to release.
//
VOID ReleaseRef(IN IUnknown* punk) {
    if (punk) { punk->Release(); }
    return;
}

// Purpose:   Get a reference to INetCfg.
//
// Arguments:
//    fGetWriteLock  [in]  If TRUE, Write lock.requested.
//    lpszAppName    [in]  Application name requesting the reference.
//    ppnc           [out] Reference to INetCfg.
//    lpszLockedBy   [in]  Optional. Application who holds the write lock.
//
HRESULT HrGetINetCfg(IN BOOL fGetWriteLock,
    IN LPCWSTR lpszAppName,
    OUT INetCfg** ppnc,
    _Outptr_opt_result_maybenull_ LPWSTR* lpszLockedBy) {
    INetCfg* pnc = NULL;
    INetCfgLock* pncLock = NULL;
    HRESULT      hr = S_OK;

    // Initialize the output parameters.
    *ppnc = NULL;

    if (lpszLockedBy) { *lpszLockedBy = NULL; }

    // Initialize COM
    hr = CoInitialize(NULL);

    if (hr == S_OK) {

        // Create the object implementing INetCfg.
        hr = CoCreateInstance(CLSID_CNetCfg, NULL, CLSCTX_INPROC_SERVER, IID_INetCfg, (void**)&pnc);
        if (hr == S_OK) {

            if (fGetWriteLock) {

                // Get the locking reference
                hr = pnc->QueryInterface(IID_INetCfgLock, (LPVOID*)&pncLock);
                if (hr == S_OK) {

                    // Attempt to lock the INetCfg for read/write
                    hr = pncLock->AcquireWriteLock(LOCK_TIME_OUT, lpszAppName, lpszLockedBy);
                    if (hr == S_FALSE) {
                        hr = NETCFG_E_NO_WRITE_LOCK;
                    }
                }
            }

            if (hr == S_OK) {

                // Initialize the INetCfg object.
                hr = pnc->Initialize(NULL);

                if (hr == S_OK) {
                    *ppnc = pnc;
                    pnc->AddRef();
                } else {

                    //
                    // Initialize failed, if obtained lock, release it
                    //

                    if (pncLock) {
                        pncLock->ReleaseWriteLock();
                    }
                }
            }

            ReleaseRef(pncLock);
            ReleaseRef(pnc);
        }

        // In case of error, uninitialize COM.
        //

        if (hr != S_OK) { CoUninitialize();  }
    }
    return hr;
}

// Function:  HrReleaseINetCfg
//
// Purpose:   Get a reference to INetCfg.
//
// Arguments:
//    pnc           [in] Reference to INetCfg to release.
//    fHasWriteLock [in] If TRUE, reference was held with write lock.
//
HRESULT HrReleaseINetCfg(IN INetCfg* pnc,
    IN BOOL fHasWriteLock) {
   
    INetCfgLock* pncLock = NULL;
    HRESULT        hr = S_OK;

    // Uninitialize INetCfg
    hr = pnc->Uninitialize();

    // If write lock is present, unlock it
    if (hr == S_OK && fHasWriteLock) {

        // Get the locking reference
        hr = pnc->QueryInterface(IID_INetCfgLock, (LPVOID*)&pncLock);
        if (hr == S_OK) {
            hr = pncLock->ReleaseWriteLock();
            ReleaseRef(pncLock);
        }
    }

    ReleaseRef(pnc);

    // Uninitialize COM.
    CoUninitialize();
    return hr;
}