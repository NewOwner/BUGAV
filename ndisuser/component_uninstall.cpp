#include "ndisuser.h"

// Function:  UninstallComponent
//
// Purpose:   Uninstall a network component.
//
// Arguments:
//    lpszInfId  [in]  PnpID of the network component to uninstall.
//
// Returns:   S_OK on success, otherwise an error code.
//
// Notes:
//
HRESULT UninstallComponent(_In_ LPWSTR lpszInfId) {
    INetCfg* pnc;
    INetCfgComponent* pncc;
    INetCfgClass* pncClass;
    INetCfgClassSetup* pncClassSetup;
    LPWSTR               lpszApp;
    GUID                 guidClass;
    OBO_TOKEN            obo;
    HRESULT              hr;

    hr = HrGetINetCfg(TRUE,
        APP_NAME,
        &pnc,
        &lpszApp);

    if (hr == S_OK) {

        //
        // Get a reference to the network component to uninstall.
        //
        pnc->
        hr = pnc->FindComponent(lpszInfId, &pncc);

        if (hr == S_OK) {

            //
            // Get the class GUID.
            //

            hr = pncc->GetClassGuid(&guidClass);

            if (hr == S_OK) {

                //
                // Get a reference to component's class.
                //

                hr = pnc->QueryNetCfgClass(&guidClass,
                    IID_INetCfgClass,
                    (PVOID*)&pncClass);
                if (hr == S_OK) {

                    //
                    // Get the setup interface.
                    //

                    hr = pncClass->QueryInterface(IID_INetCfgClassSetup,
                        (LPVOID*)&pncClassSetup);

                    if (hr == S_OK) {

                        //
                        // Uninstall the component.
                        //

                        ZeroMemory(&obo,
                            sizeof(OBO_TOKEN));

                        obo.Type = OBO_USER;

                        hr = pncClassSetup->DeInstall(pncc,
                            &obo,
                            NULL);
                        if ((hr == S_OK) || (hr == NETCFG_S_REBOOT)) {

                            hr = pnc->Apply();

                            if ((hr != S_OK) && (hr != NETCFG_S_REBOOT)) {
                                wprintf(L"%d; Couldn't apply the changes after uninstalling %s.", hr, lpszInfId);
                            }
                        } else {
                            wprintf(L"%d; Failed to uninstall %s.",hr, lpszInfId);
                        }

                        ReleaseRef(pncClassSetup);
                    } else {
                        wprintf(L"%d; Couldn't get an interface to setup class.",hr);
                    }

                    ReleaseRef(pncClass);
                } else {
                    wprintf(L"%d; Couldn't get a pointer to class interface of %s.",hr,lpszInfId);
                }
            } else {
                wprintf(L"%d; Couldn't get the class guid of %s.",hr, lpszInfId);
            }

            ReleaseRef(pncc);
        } else {
            wprintf(L"%d; Couldn't get an interface pointer to %s.",hr, lpszInfId);
        }

        HrReleaseINetCfg(pnc,
            TRUE);
    } else {
        if ((hr == NETCFG_E_NO_WRITE_LOCK) && lpszApp) {
            wprintf(L"%d; %s currently holds the lock, try later.",hr, lpszApp);

            CoTaskMemFree(lpszApp);
        } else {
            wprintf(L"%d; Couldn't get the notify object interface.",hr);
        }
    }

    return hr;
}

VOID UninstallSelectedComponent(HWND hwndDlg) {
    HRESULT   hr;
    LPARAM    lParam;
    hr = UninstallComponent((LPWSTR)lParam);

    switch (hr) {

    case S_OK:
        wprintf(L"Uninstallation successful.");
        break;

    case NETCFG_S_REBOOT:
        wprintf(L"Uninstallation successful: Reboot required.");
    }
}

// Function:  HrUninstallNetComponent
//
// Purpose:   Uninstall a network component(protocols, clients and services).
//
// Arguments:
//    pnc           [in] Reference to INetCfg.
//    szComponentId [in] PnpID of the network component to uninstall.
//
// Returns:   S_OK on success, otherwise an error code.
//
// Notes:
//

HRESULT HrUninstallNetComponent(IN INetCfg* pnc,
    IN LPCWSTR szComponentId) {
    INetCfgComponent* pncc = NULL;
    INetCfgClass* pncClass = NULL;
    INetCfgClassSetup* pncClassSetup = NULL;
    OBO_TOKEN           OboToken;
    GUID                guidClass;
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
    // Get the component's reference.
    //

    hr = pnc->FindComponent(szComponentId,
        &pncc);

    if (S_OK == hr) {

        //
        // Get the component's class GUID.
        //

        hr = pncc->GetClassGuid(&guidClass);

        if (hr == S_OK) {

            //
            // Get component's class reference.
            //

            hr = pnc->QueryNetCfgClass(&guidClass,
                IID_INetCfgClass,
                (void**)&pncClass);
            if (hr == S_OK) {

                //
                // Get Setup reference.
                //

                hr = pncClass->QueryInterface(IID_INetCfgClassSetup,
                    (void**)&pncClassSetup);
                if (hr == S_OK) {

                    hr = pncClassSetup->DeInstall(pncc,
                        &OboToken,
                        NULL);
                    if (hr == S_OK) {

                        //
                        // Apply the changes
                        //

                        hr = pnc->Apply();
                    }

                    ReleaseRef(pncClassSetup);
                }

                ReleaseRef(pncClass);
            }
        }
        ReleaseRef(pncc);
    }
    return hr;
}