#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <wchar.h>
#include <netcfgx.h>
#include <netcfgn.h>
#include <setupapi.h>
#include <devguid.h>
#include <objbase.h>
#include <strsafe.h>

#define APP_NAME            L"ndisuser"
#define LOCK_TIME_OUT     5000

// INSTALL

VOID InstallSelectedComponentType(_In_opt_ LPWSTR lpszInfFile);

HRESULT InstallSpecifiedComponent(_In_ LPWSTR lpszInfFile,
    _In_ LPWSTR lpszPnpID,
    const GUID* pguidClass);

HRESULT HrInstallNetComponent(IN INetCfg* pnc,
    IN LPCWSTR lpszComponentId,
    IN const GUID* pguidClass,
    IN LPCWSTR lpszInfFullPath);

HRESULT HrInstallComponent(IN INetCfg* pnc,
    IN LPCWSTR szComponentId,
    IN const GUID* pguidClass);     // XXX

// UNINSTALL

VOID UninstallSelectedComponent(_In_ LPWSTR lpszInfId);

HRESULT UninstallComponent(_In_ LPWSTR lpszInfId);

HRESULT HrUninstallNetComponent(IN INetCfg* pnc, 
    IN LPCWSTR szComponentId);      // XXX

// UTIL

HRESULT GetKeyValue(
    HINF hInf,
    _In_ LPCWSTR lpszSection,
    _In_opt_ LPCWSTR lpszKey,
    DWORD  dwIndex,
    _Outptr_ LPWSTR* lppszValue);

HRESULT GetPnpID(_In_ LPWSTR lpszInfFile,
    _Outptr_ LPWSTR* lppszPnpID);


// COM

HRESULT HrGetINetCfg(IN BOOL fGetWriteLock,
    IN LPCWSTR lpszAppName,
    OUT INetCfg** ppnc,
    _Outptr_opt_result_maybenull_ LPWSTR* lpszLockedBy);

HRESULT HrReleaseINetCfg(INetCfg* pnc, BOOL fHasWriteLock);

VOID ReleaseRef(IN IUnknown* punk);