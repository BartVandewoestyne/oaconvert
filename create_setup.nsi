; Script generated by the HM NIS Edit Script Wizard.

!include build\nsis\EnvVarUpdate.nsh

; HM NIS Edit Wizard helper defines
!define PRODUCT_NAME "oaconvert"
!define PRODUCT_VERSION "0.1.0"
!define /date MyTIMESTAMP "%Y%m%d%H%M%S"
!define PRODUCT_PUBLISHER "Bart Vandewoestyne"
!define PRODUCT_WEB_SITE "https://github.com/BartVandewoestyne/oaconvert"
!define PRODUCT_UNINST_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}"
!define PRODUCT_UNINST_ROOT_KEY "HKLM"

Name "${PRODUCT_NAME} ${PRODUCT_VERSION}"
OutFile "${PRODUCT_NAME}-${PRODUCT_VERSION}-${MyTIMESTAMP}.exe"
LoadLanguageFile "${NSISDIR}\Contrib\Language files\Dutch.nlf"
LoadLanguageFile "${NSISDIR}\Contrib\Language files\English.nlf"
LoadLanguageFile "${NSISDIR}\Contrib\Language files\French.nlf"
InstallDir "$PROGRAMFILES\${PRODUCT_NAME}"
Icon "${NSISDIR}\Contrib\Graphics\Icons\modern-install.ico"
UninstallIcon "${NSISDIR}\Contrib\Graphics\Icons\modern-uninstall.ico"
DirText "Setup will install $(^Name) in the following folder.$\r$\n$\r$\nTo install in a different folder, click Browse and select another folder."
LicenseText "If you accept all the terms of the agreement, choose I Agree to continue. You must accept the agreement to install $(^Name)."
LicenseData "creative_commons_license.txt"
LicenseForceSelection checkbox
ShowInstDetails show
ShowUnInstDetails show

; With 'user', the files are not copied... probably user has no access to this directory.
;RequestExecutionLevel user
RequestExecutionLevel admin

Page license
Page custom paypal
Page components
Page directory
Page instfiles

!macro writeRegistryEntries Name Fid Id
  WriteRegBin "HKLM" "Software\Garmin\MapSource\Families\${Name}"   "ID"   ${Fid}
  WriteRegStr "HKLM" "Software\Garmin\Mapsource\Families\${Name}"   "IDX"  "$INSTDIR\garmin\${Name}.mdx"
  WriteRegStr "HKLM" "Software\Garmin\Mapsource\Families\${Name}"   "TYP"  "$INSTDIR\garmin\${Id}.typ"
  WriteRegStr "HKLM" "Software\Garmin\Mapsource\Families\${Name}\1" "LOC"  "$INSTDIR\garmin"
  WriteRegStr "HKLM" "Software\Garmin\Mapsource\Families\${Name}\1" "BMAP" "$INSTDIR\garmin\${Name}.img"
  WriteRegStr "HKLM" "Software\Garmin\Mapsource\Families\${Name}\1" "TDB"  "$INSTDIR\garmin\${Name}.tdb"
  WriteRegStr "HKLM" "Software\Garmin\Mapsource\Families\${Name}\1" "MDR"  "$INSTDIR\garmin\${Name}.img"
!macroend

Function paypal
  MessageBox MB_OK "Disclaimer: we provide these maps as a free service.  Although we do our very best to make sure that the maps are accurate, we are aware that some might contain mistakes and we make no guarantee as to their absolute correctness.  These maps are provided �as is� in the hope that they will be useful, but WITHOUT ANY WARRANTY, to the extent permitted by law; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  Please use these maps as a guide and not as definitive information."
FunctionEnd

Function .onInit
#TODO: call UserInfo plugin to make sure user is admin
FunctionEnd

Section "License file" SEC01
  SetOutPath "$INSTDIR"
  SetOverwrite ifnewer
  File "creative_commons_license.txt"
  SectionIn 1 RO
SectionEnd

#TODO: do not hardcode C:\cygwin64\bin\cygwin1.dll here, but maybe add cygwin1.dll to the repo and use a relative path, or search for cygwin1.dll???
Section "oaconvert" SEC02
  SetOutPath "$INSTDIR"
  SetOverwrite ifnewer
  File "src\oaconvert.exe"
  File "C:\cygwin64\bin\cygwin1.dll"
  File "C:\cygwin64\bin\cyggcc_s-seh-1.dll"
  File "C:\cygwin64\bin\cygstdc++-6.dll"
SectionEnd

Section "Garmin maps" SEC03
  SetOutPath "$INSTDIR\garmin"
  SetOverwrite ifnewer
  File /r "build\garmin\*.*"
SectionEnd

Section "GPX files" SEC04
  SetOutPath "$INSTDIR\gpx"
  SetOverwrite ifnewer
  File /r "build\gpx\*.*"
SectionEnd

Section "KML files" SEC05
  SetOutPath "$INSTDIR\kml"
  SetOverwrite ifnewer
  File /r "build\kml\*.*"
SectionEnd

Section "OpenAir files" SEC06
  SetOutPath "$INSTDIR\openair"
  SetOverwrite ifnewer
  File /r "build\openair\*.*"
  File /r "openair\countries\belgium\*.*"
  File /r "openair\countries\france\*.*"
  File /r "openair\countries\germany\*.*"
  File /r "openair\countries\luxembourg\*.*"
SectionEnd

Section "Polish Format files" SEC07
  SetOutPath "$INSTDIR\polish_format"
  SetOverwrite ifnewer
  File /r "build\polish_format\*.*"
SectionEnd

Section -AdditionalIcons
  SetShellVarContext all
  CreateDirectory "$SMPROGRAMS\${PRODUCT_NAME}"
  CreateShortCut "$SMPROGRAMS\${PRODUCT_NAME}\Uninstall.lnk" "$INSTDIR\uninst.exe"
SectionEnd

Section -Post

  SetShellVarContext all
  WriteUninstaller "$INSTDIR\uninst.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayName" "$(^Name)"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "UninstallString" "$INSTDIR\uninst.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayVersion" "${PRODUCT_VERSION}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "URLInfoAbout" "${PRODUCT_WEB_SITE}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "Publisher" "${PRODUCT_PUBLISHER}"

  ${EnvVarUpdate} $0 "PATH" "P" "HKLM" "$INSTDIR"

  !include build\nsis\create_registry_keys.nsi
  
SectionEnd


Function un.onUninstSuccess
  HideWindow
  MessageBox MB_ICONINFORMATION|MB_OK "$(^Name) was successfully removed from your computer."
FunctionEnd

Function un.onInit
  MessageBox MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 "Are you sure you want to completely remove $(^Name) and all of its components?" IDYES +2
  Abort
FunctionEnd

Section Uninstall

  SetShellVarContext all

  Delete "$INSTDIR\uninst.exe"
  
  Delete "$INSTDIR\polish_format\*.*"
  Delete "$INSTDIR\garmin\*.*"
  Delete "$INSTDIR\gpx\*.*"
  Delete "$INSTDIR\kml\*.*"
  Delete "$INSTDIR\openair\*.*"
  Delete "$INSTDIR\oaconvert.exe"
  Delete "$INSTDIR\*.dll"
  Delete "$INSTDIR\creative_commons_license.txt"

  RMDir "$INSTDIR\polish_format"
  RMDir "$INSTDIR\garmin"
  RMDir "$INSTDIR\gpx"
  RMDir "$INSTDIR\kml"
  RMDir "$INSTDIR\openair"
  RMDir "$INSTDIR"

  Delete "$SMPROGRAMS\${PRODUCT_NAME}\Uninstall.lnk"
  RMDir "$SMPROGRAMS\${PRODUCT_NAME}"

  DeleteRegKey ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}"

  ${un.EnvVarUpdate} $0 "PATH" "R" "HKLM" "$INSTDIR"
  
  !include build\nsis\delete_registry_keys.nsi
  
  ;SetAutoClose true
SectionEnd
