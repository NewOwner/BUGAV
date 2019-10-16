#include "ndisuser.h"

// Function:  HrGetINetCfg
//
// Purpose:   Get a reference to INetCfg.
//
// Arguments:
//    fGetWriteLock  [in]  If TRUE, Write lock.requested.
//    lpszAppName    [in]  Application name requesting the reference.
//    ppnc           [out] Reference to INetCfg.
//    lpszLockedBy   [in]  Optional. Application who holds the write lock.
//
// Returns:   S_OK on success, otherwise an error code.
//
// Notes:
//

HRESULT HrGetINetCfg(IN BOOL fGetWriteLock,
    IN LPCWSTR lpszAppName,
    OUT INetCfg** ppnc,
    _Outptr_opt_result_maybenull_ LPWSTR* lpszLockedBy) {
    INetCfg* pnc = NULL;
    INetCfgLock* pncLock = NULL;
    HRESULT      hr = S_OK;

    //
    // Initialize the output parameters.
    //

    *ppnc = NULL;

    if (lpszLockedBy) {
        *lpszLockedBy = NULL;
    }
    //
    // Initialize COM
    //

    hr = CoInitialize(NULL);

    if (hr == S_OK) {

        //
        // Create the object implementing INetCfg.
        //

        hr = CoCreateInstance(CLSID_CNetCfg,
            NULL, CLSCTX_INPROC_SERVER,
            IID_INetCfg,
            (void**)&pnc);
        if (hr == S_OK) {

            if (fGetWriteLock) {

                //
                // Get the locking reference
                //

                hr = pnc->QueryInterface(IID_INetCfgLock,
                    (LPVOID*)&pncLock);
                if (hr == S_OK) {

                    //
                    // Attempt to lock the INetCfg for read/write
                    //

                    hr = pncLock->AcquireWriteLock(LOCK_TIME_OUT,
                        lpszAppName,
                        lpszLockedBy);
                    if (hr == S_FALSE) {
                        hr = NETCFG_E_NO_WRITE_LOCK;
                    }
                }
            }

            if (hr == S_OK) {

                //
                // Initialize the INetCfg object.
                //

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

        //
        // In case of error, uninitialize COM.
        //

        if (hr != S_OK) {
            CoUninitialize();
        }
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
// Returns:   S_OK on success, otherwise an error code.
//
// Notes:
//

HRESULT HrReleaseINetCfg(IN INetCfg* pnc,
    IN BOOL fHasWriteLock) {
    INetCfgLock* pncLock = NULL;
    HRESULT        hr = S_OK;

    //
    // Uninitialize INetCfg
    //

    hr = pnc->Uninitialize();

    //
    // If write lock is present, unlock it
    //

    if (hr == S_OK && fHasWriteLock) {

        //
        // Get the locking reference
        //

        hr = pnc->QueryInterface(IID_INetCfgLock,
            (LPVOID*)&pncLock);
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