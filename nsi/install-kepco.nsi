; example1.nsi
;
; This script is perhaps one of the simplest NSIs you can make. All of the
; optional settings are left to their default settings. The installer simply 
; prompts the user asking them where to install, and drops a copy of example1.nsi
; there. 
;
; example2.nsi expands on this by adding a uninstaller and start menu shortcuts.

;--------------------------------

; The name of the installer
Name "Install-kepco"

; The file to write
OutFile "install-kepco.exe"

; Request application privileges for Windows Vista
RequestExecutionLevel user

; Build Unicode installer
Unicode True

; The default installation directory
InstallDir $DESKTOP\install

;--------------------------------

; Pages

Page directory
Page instfiles

;--------------------------------

; The stuff to install
Section "" ;No components page, name is not important

  ; Set output path to the installation directory.
  SetOutPath $INSTDIR
  
  ; Put file there
   File /r "C:\InstallShield 2021 Projects\kepcoMe\Product Configuration 2\Release 1\DiskImages\DISK1\*"

   IfFileExists "$INSTDIR\setup.exe" 0 +2
	Exec "$INSTDIR\setup.exe"
SectionEnd
 