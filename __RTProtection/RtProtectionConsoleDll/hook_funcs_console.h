#pragma once

BOOL Hook_ReadConsoleInputW(
    _In_  HANDLE        hConsoleInput,
    _Out_ PINPUT_RECORD lpBuffer,
    _In_  DWORD         nLength,
    _Out_ LPDWORD       lpNumberOfEventsRead
);

/*

------------------------
COMMAND LINE
------------------------

4H RAT
 shell command: /Microsoft/errorpost<random number>/default.asp?tmp=<encoded hostname>
 Shell response: /MicrosoftUpdate/GetUpdate/KB<random number>/default.asp?tmp=<encoded hostname>

 admin@338
 net user >> %temp%\download net user /domain >> %temp%\download
 dir c:\ >> %temp%\download
 dir "c:\Documents and Settings" >> %temp%\download
 dir "c:\Program Files\" >> %temp%\download
 dir d:\ >> %temp%\download
 ren "%temp%\upload" audiodg.exe
 net localgroup administrator >> %temp%\download
 ver >> %temp%\download systeminfo >> %temp%\download
 ipconfig /all >> %temp%\download
 netstat -ano >> %temp%\download
 net start >> %temp%\download

 ADVSTORESHELL
 msdeltemp.dll
 __tmpdt.tmp
 HKCU\SOFTWARE\Microsoft\Windows\CurrentVersion\Run
 StartUpChekTemp=RUNDLL32.EXE “%path to msdeltemp.dll%”
 RUNDLL32.EXE “%path to msdeltemp.dll%
 cmd /c DEL %path to self%

 APT1
 net localgroup,net user
 net group
 tasklist /v
 ipconfig /all
 net use
 net start

 APT28
 certutil -decode
 wevtutil cl System
 wevtutil cl Security
 rundll32.exe "C:\Windows\twain_64.dll"

 APT3
 C:\Windows\System32\sethc.exe
 "cmd.exe" /C whoami
 -WindowStyle Hidden
 schtasks /create /tn "mysc" /tr C:\Users\Public\test.exe /sc ONLOGON /ru "System"

 APT32
 net localgroup administrators
 net group "Domain Controllers" /domain
 net view
 ping
 netstat -anpo tcp

 APT37
 shutdown /r /t 1

 APT41
 cmd.exe /c
 net share

 Astaroth
 Syswow64\userinit.exe
 System32\userinit.exe

 BabyShark
 tasklist
 reg query
 HKEY_CURRENT_USER\Software\Microsoft\Terminal Server Client\Default
 ver
 ipconfig /all
 whoami

 Bisonal
 HKEY_CURRENT_USER \Software\Microsoft\Windows\CurrentVersion\Run\"vert" = "rundll32.exe c:\windows\temp\pvcu.dll , Qszdez"

 BRONZE BUTLER
 net user /domain
 net time
 
 Carbanak
 HKCU\Software\Microsoft\Windows\CurrentVersion\Internet Settings

 Cardinal RAT
 HKCU\Software\Microsoft\Windows NT\CurrentVersion\Windows\Load

 Chaos
 8338

 Cobalt Group
 cmstp.exe /s /ns C:\Users\ADMINI~W\AppData\Local\Temp\XKNqbpzl.txt
 odbcconf

 Cobalt Strike
 WinRM

 CozyCar
 HKCU\Software\Microsoft\Windows\CurrentVersion\Run\
 HKLM\Software\Microsoft\Windows\CurrentVersion\Policies\Explorer\Run

 DarkComet
 HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Policies\System Enable LUA="0"
 HKEY_CURRENT_USER\Software\DC3_FEXEC

 Empire
 Invoke-RunAs
 Invoke-TokenManipulation
 Invoke-DCOM
 New-GPOImmediateTask
 Invoke-Kerberoast
 Invoke-Obfuscation
 Invoke-PSRemoting
 Install-SSP and Invoke-Mimikatz

 FELIXROOT
 HKCU\Software\Classes\Applications\rundll32.exe\shell\open

 Fysbis
 ls /etc | egrep -e"fedora*|debian*|gentoo*|mandriva*|mandrake*|meego*|redhat*|lsb-*|sun-*|SUSE*|release"

 Gold Dragon
 regkeyenum
 systeminfo

 Gorgon Group
 -W Hidden
 taskkill
 HKCU\Software\Microsoft\Office\

 HARDRAIN
 netsh
 cmd.exe /c netsh firewall add portopening TCP 443 "adp"

 Helminth
 net group Exchange Trusted Subsystem /domain
 net group domain admins /domain

 Honeybee
 from (---).txt

 HOPLIGHT
 SYSTEM\CurrentControlSet\Control\Lsa Name

 HTTPBrowser
 vpdn "%ALLUSERPROFILE%\%APPDATA%\vpdn\VPDN_LU.exe"

 InnaputRAT
 HKU\\Software\Microsoft\Windows\CurrentVersion\Run:%appdata%\NeutralApp\NeutralApp.exe

 Ke3chang
 net group "REDACTED" /domain

 KeyBoy
 reg add "HKLM\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Winlogon"

 KEYMARBLE
 HKEY_CURRENT_USER\SOFTWARE\Microsoft\WABE\DataPath

 Lazarus Group
 HKEY_CURRENT_USER\Software\Bitcoin\Bitcoin-Qt

 LightNeuron
 C:\Windows\ServiceProfiles\NetworkService\appdata\Local\Temp\
 winmail.dat

 menuPass
 certutil -decode

 Mis-Type
 cmd.exe /c net user {{Username}}
 cmd.exe /c ipconfig /all

 Mivast
 HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Run\Micromedia

 Mosquito
 HKCR\CLSID...\InprocServer32
 HKCU\Software\Run auto_update

 OilRig
 reg query "HKEY_CURRENT_USER\Software\Microsoft\Terminal Server Client\Default"

 OopsIE
 SELECT * FROM MSAcpi_ThermalZoneTemperature

 PLAINTEE
 HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\RunOnce

 Pteranodon
 %Temp%\reports\%
 C:\Users\\AppData\Roaming\Microsoft\store

 QUADAGENT
 Office365DCOMCheck.ps1
 SystemDiskClean.ps1

 Rancor
 schtasks /create /sc
 msiexec

 RATANKBA
 netstat -ano
 tasklist /svc

 Remexi
 HKLM\Software\Microsoft\Windows NT\CurrentVersion\Winlogon\Userinit

 Revenge RAT
 Reflection.Assembly
 HKCU\Software\Microsoft\Windows NT\CurrentVersion\Winlogon\Shell

 RobbinHood
 net use * /DELETE /Y

 RogueRobin
 %APPDATA%\OneDrive.bat
 powershell.exe -WindowStyle Hidden -exec bypass -File "%APPDATA%\OneDrive.ps1"

 Sowbug
 CSIDL_APPDATA\microsoft\security

 Turla
 lPH*.dll
 Out-EncryptedScript.ps1
 Invoke-ReflectivePEInjection.ps1
 arp -a
 nbtstat -n
 nbtscan
 profile.ps1

 TYPEFRAME
 HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\ShellCompatibility\Applications\laxhost.dll
 HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\PrintConfigs

 WEBC2
 C:\WINDOWS\ntshrui.dll

 Zebrocy
 wmic process get Capture, ExecutablePath
 netstat -aon

 Zeus Panda
 HKCU\Software\Microsoft\Internet Explorer\ PhishingFilter\

 ZxShell
 HKLM\SYSTEM\CurrentControlSet\Services\SharedAccess\Parameters\FirewallPolicy\StandardProfile
 1985
 1986


------------------------
SCHEDULED TASK
------------------------

Carbon
net time \127.0.0.1

GRIFFON
sctasks

ISMInjector
certutil

JHUHUGIT
HKLM\SYSTEM\CurrentControlSet\Services\Disk\Enum

Machete
netsh wlan show networks mode=bssid
netsh wlan show interfaces

NotPetya
wevtutil
wmic
rundll32

PowerSploit
Invoke-TokenManipulation
Get-ProcessTokenGroup
Get-UnattendedInstallFile
Get-Webconfig
Get-ApplicationHost
Get-SiteListPassword
Get-CachedGPPPassword
Get-RegistryAutoLogon
Get-NetDomainTrust
Get-NetForestTrust
Find-AVSignature
Get-Keystrokes
Get-ProcessTokenPrivilege
New-UserPersistenceOption
Get-TimedScreenshot
Install-SSP
Invoke-WmiCommand

POWERSTATS
"C:\Windows\system32\schtasks.exe" /Create /F /SC DAILY /ST 12:00 /TN MicrosoftEdge /TR "c:\Windows\system32\wscript.exe C:\Windows\temp\Windows.vbe"
8060

SQLRat
%appdata%\Roaming\Microsoft\Templates\

TEMP.Veles
HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Image File Execution Options
4444
8531
50501

yty
SchTasks /Create /SC DAILY /TN BigData /TR " + path_file + "/ST 09:30"


APT19
HKCU\Software\Microsoft\Windows\CurrentVersion\Run\Windows Debug Tools-%LOCALAPPDATA%\

Comnie
route PRINT
net start >> %TEMP%\info.dat

Proxysvc
cmd.exe /c " > %temp%\PM* .tmp 2>&1"











*/