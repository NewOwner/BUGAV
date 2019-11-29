#include "pch.h"
#include "hook_funcs.h"

extern HANDLE hPipe1;
std::mutex m;

//https://www.win7dll.info/winhttp_dll.html winhttp.dll 
//  DllCanUnloadNow             DllGetClassObject	Private1
//  SvchostPushServiceGlobals	WinHttpAddRequestHeaders	WinHttpAutoProxySvcMain
//  WinHttpCheckPlatform	    WinHttpCloseHandle	WinHttpConnect
//  WinHttpCrackUrl	            WinHttpCreateUrl	WinHttpDetectAutoProxyConfigUrl
//  WinHttpGetDefaultProxyConfiguration	WinHttpGetIEProxyConfigForCurrentUser	WinHttpGetProxyForUrl
//  WinHttpOpen	                WinHttpOpenRequest	WinHttpQueryAuthSchemes
//  WinHttpQueryDataAvailable	WinHttpQueryHeaders	WinHttpQueryOption
//  WinHttpReadData	            WinHttpReceiveResponse	WinHttpSendRequest
//  WinHttpSetCredentials	    WinHttpSetDefaultProxyConfiguration	WinHttpSetOption
//  WinHttpSetStatusCallback	WinHttpSetTimeouts	WinHttpTimeFromSystemTime
//  WinHttpTimeToSystemTime	    WinHttpWriteData

//https://www.win7dll.info/wininet_dll.html wininet.dll 
//  CommitUrlCacheEntryA	CommitUrlCacheEntryW
//  CreateMD5SSOHash	CreateUrlCacheContainerA
//  CreateUrlCacheContainerW	CreateUrlCacheEntryA
//  CreateUrlCacheEntryW	CreateUrlCacheGroup
//  DeleteIE3Cache	DeleteUrlCacheContainerA
//  DeleteUrlCacheContainerW	DeleteUrlCacheEntry
//  DeleteUrlCacheEntryA	DeleteUrlCacheEntryW
//  DeleteUrlCacheGroup	DeleteWpadCacheForNetworks
//  DetectAutoProxyUrl	DispatchAPICall
//  DllInstall	FindCloseUrlCache
//  FindFirstUrlCacheContainerA	FindFirstUrlCacheContainerW
//  FindFirstUrlCacheEntryA	FindFirstUrlCacheEntryExA
//  FindFirstUrlCacheEntryExW	FindFirstUrlCacheEntryW
//  FindFirstUrlCacheGroup	FindNextUrlCacheContainerA
//  FindNextUrlCacheContainerW	FindNextUrlCacheEntryA
//  FindNextUrlCacheEntryExA	FindNextUrlCacheEntryExW
//  FindNextUrlCacheEntryW	FindNextUrlCacheGroup
//  ForceNexusLookup	ForceNexusLookupExW
//  FreeUrlCacheSpaceA	FreeUrlCacheSpaceW
//  FtpCommandA	FtpCommandW
//  FtpCreateDirectoryA	FtpCreateDirectoryW
//  FtpDeleteFileA	FtpDeleteFileW
//  FtpFindFirstFileA	FtpFindFirstFileW
//  FtpGetCurrentDirectoryA	FtpGetCurrentDirectoryW
//  FtpGetFileA	FtpGetFileEx
//  FtpGetFileSize	FtpGetFileW
//  FtpOpenFileA	FtpOpenFileW
//  FtpPutFileA	FtpPutFileEx
//  FtpPutFileW	FtpRemoveDirectoryA
//  FtpRemoveDirectoryW	FtpRenameFileA
//  FtpRenameFileW	FtpSetCurrentDirectoryA
//  FtpSetCurrentDirectoryW	GetUrlCacheConfigInfoA
//  GetUrlCacheConfigInfoW	GetUrlCacheEntryInfoA
//  GetUrlCacheEntryInfoExA	GetUrlCacheEntryInfoExW
//  GetUrlCacheEntryInfoW	GetUrlCacheGroupAttributeA
//  GetUrlCacheGroupAttributeW	GetUrlCacheHeaderData
//  GopherCreateLocatorA	GopherCreateLocatorW
//  GopherFindFirstFileA	GopherFindFirstFileW
//  GopherGetAttributeA	GopherGetAttributeW
//  GopherGetLocatorTypeA	GopherGetLocatorTypeW
//  GopherOpenFileA	GopherOpenFileW
//  HttpAddRequestHeadersA	HttpAddRequestHeadersW
//  HttpCheckDavCompliance	HttpEndRequestA
//  HttpEndRequestW	HttpOpenRequestA
//  HttpOpenRequestW	HttpQueryInfoA
//  HttpQueryInfoW	HttpSendRequestA
//  HttpSendRequestExA	HttpSendRequestExW
//  HttpSendRequestW	IncrementUrlCacheHeaderData
//  InternetAlgIdToStringA	InternetAlgIdToStringW
//  InternetAttemptConnect	InternetAutodial
//  InternetAutodialCallback	InternetAutodialHangup
//  InternetCanonicalizeUrlA	InternetCanonicalizeUrlW
//  InternetCheckConnectionA	InternetCheckConnectionW
//  InternetClearAllPerSiteCookieDecisions	InternetCloseHandle
//  InternetCombineUrlA	InternetCombineUrlW
//  InternetConfirmZoneCrossing	InternetConfirmZoneCrossingA
//  InternetConfirmZoneCrossingW	InternetConnectA
//  InternetConnectW	InternetCrackUrlA
//  InternetCrackUrlW	InternetCreateUrlA
//  InternetCreateUrlW	InternetDial
//  InternetDialA	InternetDialW
//  InternetEnumPerSiteCookieDecisionA	InternetEnumPerSiteCookieDecisionW
//  InternetErrorDlg	InternetFindNextFileA
//  InternetFindNextFileW	InternetFortezzaCommand
//  InternetGetCertByURL	InternetGetCertByURLA
//  InternetGetConnectedState	InternetGetConnectedStateEx
//  InternetGetConnectedStateExA	InternetGetConnectedStateExW
//  InternetGetCookieA	InternetGetCookieExA
//  InternetGetCookieExW	InternetGetCookieW
//  InternetGetLastResponseInfoA	InternetGetLastResponseInfoW
//  InternetGetPerSiteCookieDecisionA	InternetGetPerSiteCookieDecisionW
//  InternetGetSecurityInfoByURL	InternetGetSecurityInfoByURLA
//  InternetGetSecurityInfoByURLW	InternetGoOnline
//  InternetGoOnlineA	InternetGoOnlineW
//  InternetHangUp	InternetInitializeAutoProxyDll
//  InternetLockRequestFile	InternetOpenA
//  InternetOpenUrlA	InternetOpenUrlW
//  InternetOpenW	InternetQueryDataAvailable
//  InternetQueryFortezzaStatus	InternetQueryOptionA
//  InternetQueryOptionW	InternetReadFile
//  InternetReadFileExA	InternetReadFileExW
//  InternetSecurityProtocolToStringA	InternetSecurityProtocolToStringW
//  InternetSetCookieA	InternetSetCookieExA
//  InternetSetCookieExW	InternetSetCookieW
//  InternetSetDialState	InternetSetDialStateA
//  InternetSetDialStateW	InternetSetFilePointer
//  InternetSetOptionA	InternetSetOptionExA
//  InternetSetOptionExW	InternetSetOptionW
//  InternetSetPerSiteCookieDecisionA	InternetSetPerSiteCookieDecisionW
//  InternetSetStatusCallback	InternetSetStatusCallbackA
//  InternetSetStatusCallbackW	InternetShowSecurityInfoByURL
//  InternetShowSecurityInfoByURLA	InternetShowSecurityInfoByURLW
//  InternetTimeFromSystemTime	InternetTimeFromSystemTimeA
//  InternetTimeFromSystemTimeW	InternetTimeToSystemTime
//  InternetTimeToSystemTimeA	InternetTimeToSystemTimeW
//  InternetUnlockRequestFile	InternetWriteFile
//  InternetWriteFileExA	InternetWriteFileExW
//  IsHostInProxyBypassList	IsUrlCacheEntryExpiredA
//  IsUrlCacheEntryExpiredW	LoadUrlCacheContent
//  ParseX509EncodedCertificateForListBoxEntry	PrivacyGetZonePreferenceW
//  PrivacySetZonePreferenceW	ReadUrlCacheEntryStream
//  ReadUrlCacheEntryStreamEx	RegisterUrlCacheNotification
//  ResumeSuspendedDownload	RetrieveUrlCacheEntryFileA
//  RetrieveUrlCacheEntryFileW	RetrieveUrlCacheEntryStreamA
//  RetrieveUrlCacheEntryStreamW	RunOnceUrlCache
//  SetUrlCacheConfigInfoA	SetUrlCacheConfigInfoW
//  SetUrlCacheEntryGroup	SetUrlCacheEntryGroupA
//  SetUrlCacheEntryGroupW	SetUrlCacheEntryInfoA
//  SetUrlCacheEntryInfoW	SetUrlCacheGroupAttributeA
//  SetUrlCacheGroupAttributeW	SetUrlCacheHeaderData
//  ShowCertificate	ShowClientAuthCerts
//  ShowSecurityInfo	ShowX509EncodedCertificate
//  UnlockUrlCacheEntryFile	UnlockUrlCacheEntryFileA
//  UnlockUrlCacheEntryFileW	UnlockUrlCacheEntryStream
//  UpdateUrlCacheContentPath	UrlZonesDetach
//  _GetFileExtensionFromUrl

//https://www.win7dll.info/ws2_32_dll.html  ws2_32.dll
//  FreeAddrInfoEx	FreeAddrInfoExW	FreeAddrInfoW
//  GetAddrInfoExA	GetAddrInfoExW	GetAddrInfoW
//  GetNameInfoW	InetNtopW	InetPtonW
//  SetAddrInfoExA	SetAddrInfoExW	WEP
//  WPUCompleteOverlappedRequest	WSAAccept	WSAAddressToStringA
//  WSAAddressToStringW	WSAAdvertiseProvider	WSAAsyncGetHostByAddr
//  WSAAsyncGetHostByName	WSAAsyncGetProtoByName	WSAAsyncGetProtoByNumber
//  WSAAsyncGetServByName	WSAAsyncGetServByPort	WSAAsyncSelect
//  WSACancelAsyncRequest	WSACancelBlockingCall	WSACleanup
//  WSACloseEvent	WSAConnect	WSAConnectByList
//  WSAConnectByNameA	WSAConnectByNameW	WSACreateEvent
//  WSADuplicateSocketA	WSADuplicateSocketW	WSAEnumNameSpaceProvidersA
//  WSAEnumNameSpaceProvidersExA	WSAEnumNameSpaceProvidersExW	WSAEnumNameSpaceProvidersW
//  WSAEnumNetworkEvents	WSAEnumProtocolsA	WSAEnumProtocolsW
//  WSAEventSelect	WSAGetLastError	WSAGetOverlappedResult
//  WSAGetQOSByName	WSAGetServiceClassInfoA	WSAGetServiceClassInfoW
//  WSAGetServiceClassNameByClassIdA	WSAGetServiceClassNameByClassIdW	WSAHtonl
//  WSAHtons	WSAInstallServiceClassA	WSAInstallServiceClassW
//  WSAIoctl	WSAIsBlocking	WSAJoinLeaf
//  WSALookupServiceBeginA	WSALookupServiceBeginW	WSALookupServiceEnd
//  WSALookupServiceNextA	WSALookupServiceNextW	WSANSPIoctl
//  WSANtohl	WSANtohs	WSAPoll
//  WSAProviderCompleteAsyncCall	WSAProviderConfigChange	WSARecv
//  WSARecvDisconnect	WSARecvFrom	WSARemoveServiceClass
//  WSAResetEvent	WSASend	WSASendDisconnect
//  WSASendMsg	WSASendTo	WSASetBlockingHook
//  WSASetEvent	WSASetLastError	WSASetServiceA
//  WSASetServiceW	WSASocketA	WSASocketW
//  WSAStartup	WSAStringToAddressA	WSAStringToAddressW
//  WSAUnadvertiseProvider	WSAUnhookBlockingHook	WSAWaitForMultipleEvents
//  WSApSetPostRoutine	WSCDeinstallProvider	WSCEnableNSProvider
//  WSCEnumProtocols	WSCGetApplicationCategory	WSCGetProviderInfo
//  WSCGetProviderPath	WSCInstallNameSpace	WSCInstallNameSpaceEx
//  WSCInstallProvider	WSCInstallProviderAndChains	WSCSetApplicationCategory
//  WSCSetProviderInfo	WSCUnInstallNameSpace	WSCUpdateProvider
//  WSCWriteNameSpaceOrder	WSCWriteProviderOrder	WahCloseApcHelper
//  WahCloseHandleHelper	WahCloseNotificationHandleHelper	WahCloseSocketHandle
//  WahCloseThread	WahCompleteRequest	WahCreateHandleContextTable
//  WahCreateNotificationHandle	WahCreateSocketHandle	WahDestroyHandleContextTable
//  WahDisableNonIFSHandleSupport	WahEnableNonIFSHandleSupport	WahEnumerateHandleContexts
//  WahInsertHandleContext	WahNotifyAllProcesses	WahOpenApcHelper
//  WahOpenCurrentThread	WahOpenHandleHelper	WahOpenNotificationHandleHelper
//  WahQueueUserApc	WahReferenceContextByHandle	WahRemoveHandleContext
//  WahWaitForNotification	WahWriteLSPEvent	__WSAFDIsSet
//  accept	bind	closesocket
//  connect	freeaddrinfo	getaddrinfo
//  gethostbyaddr	gethostbyname	gethostname
//  getnameinfo	getpeername	getprotobyname
//  getprotobynumber	getservbyname	getservbyport
//  getsockname	getsockopt	htonl
//  htons	inet_addr	inet_ntoa
//  inet_ntop	inet_pton	ioctlsocket
//  listen	ntohl	ntohs
//  recv	recvfrom	select
//  send	sendto	setsockopt
//  shutdown	socket

//libcurl.dll

BOOL Hook_ReadProcessMemory(HANDLE hProcess, LPCVOID lpBaseAddress, LPVOID lpBuffer, SIZE_T nSize, SIZE_T* lpNumberOfBytesRead) {
    std::cout << "\n Hook_ReadProcessMemory \n\n";
    char buf[500] = "ReadProcessMemory";
    DWORD cbWritten;
    DWORD dwBytesToWrite = (DWORD)strlen(buf);
    WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
    return ReadProcessMemory(hProcess, lpBaseAddress, lpBuffer, nSize, lpNumberOfBytesRead);
}

BOOL Hook_WriteProcessMemory(HANDLE hProcess, LPVOID lpBaseAddress, LPCVOID lpBuffer, SIZE_T nSize, SIZE_T* lpNumberOfBytesWritten) {
    std::cout << "\n Hook_WriteProcessMemory \n\n";
    char buf[500] = "WriteProcessMemory";
    DWORD cbWritten;
    DWORD dwBytesToWrite = (DWORD)strlen(buf);
    WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
    return WriteProcessMemory(hProcess, lpBaseAddress, lpBuffer, nSize, lpNumberOfBytesWritten);
}

LPVOID Hook_VirtualAllocEx(HANDLE hProcess, LPVOID lpAddress, SIZE_T dwSize, DWORD flAllocationType, DWORD flProtect) {
    std::cout << "\n Hook_VirtualAllocEx \n\n";
    return VirtualAllocEx(hProcess, lpAddress, dwSize, flAllocationType, flProtect);
}

BOOL Hook_SetThreadContext(HANDLE hThread, const CONTEXT* lpContext) {
    std::cout << "\n Hook_SetThreadContext \n\n";
    char buf[500] = "SetThreadContext";
    DWORD cbWritten;
    DWORD dwBytesToWrite = (DWORD)strlen(buf);
    WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
    return SetThreadContext(hThread, lpContext);
}

BOOL Hook_SetProcessAffinityMask(HANDLE hProcess, DWORD_PTR dwProcessAffinityMask) {
    std::cout << "\n Hook_SetProcessAffinityMask \n\n";
    char buf[500] = "SetProcessAffinityMask";
    DWORD cbWritten;
    DWORD dwBytesToWrite = (DWORD)strlen(buf);
    WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
    return SetProcessAffinityMask(hProcess, dwProcessAffinityMask);
}

BOOL Hook_TerminateProcess(HANDLE hProcess, UINT uExitCode) {
    std::cout << "\n Hook_TerminateProcess \n\n";
    char buf[500] = "TerminateProcess";
    DWORD cbWritten;
    DWORD dwBytesToWrite = (DWORD)strlen(buf);
    WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
    return TerminateProcess(hProcess, uExitCode);
}

void Hook_ExitProcess(UINT uExitCode) {
    std::cout << "\n Hook_ExitProcess \n\n";
    ExitProcess(uExitCode);
}

HHOOK Hook_SetWindowsHookExA(int idHook, HOOKPROC lpfn, HINSTANCE hmod, DWORD dwThreadId) {
    std::cout << "\n Hook_SetWindowsHookExA \n\n";
    char buf[500] = "SetWindowsHookExA";
    DWORD cbWritten;
    DWORD dwBytesToWrite = (DWORD)strlen(buf);
    WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
    return SetWindowsHookExA(idHook, lpfn, hmod, dwThreadId);
}

LRESULT Hook_CallNextHookEx(HHOOK hhk, int nCode, WPARAM wParam, LPARAM lParam) {
    std::cout << "\n Hook_CallNextHookEx \n\n";
    char buf[500] = "CallNextHookEx";
    DWORD cbWritten;
    DWORD dwBytesToWrite = (DWORD)strlen(buf);
    WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
    return CallNextHookEx(hhk, nCode, wParam, lParam);
}

BOOL Hook_IsDebuggerPresent() {
    std::cout << "\n Hook_IsDebuggerPresent \n\n";
    char buf[500] = "IsDebuggerPresent";
    DWORD cbWritten;
    DWORD dwBytesToWrite = (DWORD)strlen(buf);
    WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
    return IsDebuggerPresent();
}

void Hook_OutputDebugStringA(LPCSTR lpOutputString) {
    std::cout << "\n Hook_OutputDebugStringA \n\n";
    char buf[500] = "OutputDebugStringA";
    DWORD cbWritten;
    DWORD dwBytesToWrite = (DWORD)strlen(buf);
    WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
    OutputDebugStringA(lpOutputString);
}

HANDLE Hook_CreateMutexA(LPSECURITY_ATTRIBUTES lpMutexAttributes, BOOL bInitialOwner, LPCSTR lpName) {
    std::cout << "\n Hook_CreateMutexA \n\n";
    return CreateMutexA(lpMutexAttributes, bInitialOwner, lpName);
}

HANDLE Hook_CreateSemaphoreW(LPSECURITY_ATTRIBUTES lpSemaphoreAttributes, LONG lInitialCount, LONG lMaximumCount, LPCWSTR lpName) {
    std::cout << "\n Hook_CreateSemaphoreW \n\n";
    return CreateSemaphoreW(lpSemaphoreAttributes, lInitialCount, lMaximumCount, lpName);
}

BOOL Hook_DeviceIoControl(HANDLE hDevice, DWORD dwIoControlCode, LPVOID lpInBuffer, DWORD nInBufferSize, LPVOID lpOutBuffer, DWORD nOutBufferSize, LPDWORD lpBytesReturned, LPOVERLAPPED lpOverlapped) {
    std::cout << "\n Hook_DeviceIoControl \n\n";
    char buf[500] = "DeviceIoControl";
    DWORD cbWritten;
    DWORD dwBytesToWrite = (DWORD)strlen(buf);
    WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
    return DeviceIoControl(hDevice, dwIoControlCode, lpInBuffer, nInBufferSize, lpOutBuffer, nOutBufferSize, lpBytesReturned, lpOverlapped);
}

UINT Hook_GetDriveTypeW(LPCWSTR lpRootPathName) {
    std::cout << "\n Hook_GetDriveTypeW \n\n";
    return GetDriveTypeW(lpRootPathName);
}

int WSAAPI Hook_send(SOCKET s, const char* buf, int len, int flags) {
    std::cout << "\n Hook_send \n\n";
    return send(s, buf, len, flags);
}

int Hook_recv(SOCKET s, char* buf, int len, int flags) {
    std::cout << "\n Hook_recv \n\n";
    return recv(s, buf, len, flags);
}

int WSAAPI Hook_WSARecv(SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount, LPDWORD lpNumberOfBytesRecvd, LPDWORD lpFlags, LPWSAOVERLAPPED lpOverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine) {
    std::cout << "\n Hook_WSARecv \n\n";
    return WSARecv(s, lpBuffers, dwBufferCount, lpNumberOfBytesRecvd, lpFlags, lpOverlapped, lpCompletionRoutine);
}

int WSAAPI Hook_connect(SOCKET s, const sockaddr* name, int namelen) {
    std::cout << "\n Hook_connect \n\n";
    return connect(s, name, namelen);
}

SC_HANDLE Hook_CreateServiceA(SC_HANDLE hSCManager, LPCSTR lpServiceName, LPCSTR lpDisplayName, DWORD dwDesiredAccess, DWORD dwServiceType, DWORD dwStartType, DWORD dwErrorControl, LPCSTR lpBinaryPathName, LPCSTR lpLoadOrderGroup, LPDWORD lpdwTagId, LPCSTR lpDependencies, LPCSTR lpServiceStartName, LPCSTR lpPassword) {
    std::cout << "\n Hook_CreateServiceA \n\n";
    char buf[500] = "CreateServiceA";
    DWORD cbWritten;
    DWORD dwBytesToWrite = (DWORD)strlen(buf);
    WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
    return CreateServiceA(hSCManager, lpServiceName, lpDisplayName, dwDesiredAccess, dwServiceType, dwStartType, dwErrorControl, lpBinaryPathName, lpLoadOrderGroup, lpdwTagId, lpDependencies, lpServiceStartName, lpPassword);
}

BOOL Hook_StartServiceA(SC_HANDLE hService, DWORD dwNumServiceArgs, LPCSTR* lpServiceArgVectors) {
    std::cout << "\n Hook_StartServiceA \n\n";
    char buf[500] = "StartServiceA";
    DWORD cbWritten;
    DWORD dwBytesToWrite = (DWORD)strlen(buf);
    WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
    return StartServiceA(hService, dwNumServiceArgs, lpServiceArgVectors);
}

BOOL Hook_ChangeServiceConfigA(SC_HANDLE hService, DWORD dwServiceType, DWORD dwStartType, DWORD dwErrorControl, LPCSTR lpBinaryPathName, LPCSTR lpLoadOrderGroup, LPDWORD lpdwTagId, LPCSTR lpDependencies, LPCSTR lpServiceStartName, LPCSTR lpPassword, LPCSTR lpDisplayName) {
    std::cout << "\n Hook_ChangeServiceConfigA \n\n";
    //char buf[500] = "ChangeServiceConfigA";
    //DWORD cbWritten;
    //DWORD dwBytesToWrite = (DWORD)strlen(buf);
    //WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
    return ChangeServiceConfigA(hService, dwServiceType, dwStartType, dwErrorControl, lpBinaryPathName, lpLoadOrderGroup, lpdwTagId, lpDependencies, lpServiceStartName, lpPassword, lpDisplayName);
}

UINT Hook_GetSystemDirectoryW(LPWSTR lpBuffer, UINT uSize) {
    std::cout << "\n Hook_GetSystemDirectoryW \n\n";
    return GetSystemDirectoryW(lpBuffer, uSize);
}

void Hook_GetSystemTime(LPSYSTEMTIME lpSystemTime) {
    std::cout << "\n Hook_GetSystemTime \n\n";
    GetSystemTime(lpSystemTime);
}

HMODULE Hook_GetModuleHandleA(LPCSTR lpModuleName) {
    std::cout << "\n Hook_GetModuleHandleA \n\n";
    return GetModuleHandleA(lpModuleName);
}

FARPROC Hook_GetProcAddress(HMODULE hModule, LPCSTR lpProcName) {
    std::cout << "\n Hook_GetProcAddress \n\n";
    char buf[500] = "GetProcAddress";
    DWORD cbWritten;
    DWORD dwBytesToWrite = (DWORD)strlen(buf);
    WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
    return GetProcAddress(hModule, lpProcName);
}

DWORD Hook_GetModuleFileNameA(HMODULE hModule, LPSTR lpFilename, DWORD nSize) {
    std::cout << "\n Hook_GetModuleFileNameA \n\n";
    char buf[500] = "GetModuleFileNameA";
    DWORD cbWritten;
    DWORD dwBytesToWrite = (DWORD)strlen(buf);
    WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
    return GetModuleFileNameA(hModule, lpFilename, nSize);
}

HMODULE Hook_LoadLibraryA(LPCSTR lpLibFileName) {
    std::cout << "\n Hook_LoadLibraryA \n\n";
    char buf[500] = "LoadLibraryA";
    DWORD cbWritten;
    DWORD dwBytesToWrite = (DWORD)strlen(buf);
    WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
    return LoadLibraryA(lpLibFileName);
}