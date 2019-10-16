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

HRESULT HrInstallNetComponent(IN INetCfg* pnc,
    IN LPCWSTR szComponentId,
    IN const GUID* pguildClass,
    IN LPCWSTR lpszInfFullPath);

HRESULT HrInstallComponent(IN INetCfg* pnc,
    IN LPCWSTR szComponentId,
    IN const GUID* pguidClass);

HRESULT HrGetINetCfg(IN BOOL fGetWriteLock,
    IN LPCWSTR lpszAppName,
    OUT INetCfg** ppnc,
    _Outptr_opt_result_maybenull_ LPWSTR* lpszLockedBy);

HRESULT HrReleaseINetCfg(INetCfg* pnc,
    BOOL fHasWriteLock);

VOID ReleaseRef(IUnknown* punk);


HRESULT InstallComponent(HWND hwndDlg,
    const GUID* pguidClass);

HRESULT InstallSpecifiedComponent(_In_ LPWSTR lpszInfFile,
    _In_ LPWSTR lpszPnpID,
    const GUID* pguidClass);

VOID InstallSelectedComponentType(_In_opt_ LPWSTR lpszInfFile);