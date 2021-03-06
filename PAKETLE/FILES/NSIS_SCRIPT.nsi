; Script generated by the HM NIS Edit Script Wizard.
;
; HM NIS Edit Wizard helper defines
!define PRODUCT_NAME "${ADAK_PRG_NAME}"
!define PRODUCT_PUBLISHER "Adak Teknoloji Ltd."
!define PRODUCT_WEB_SITE "http://www.adak.com.tr"
!define PRODUCT_DIR_REGKEY "Software\Microsoft\Windows\CurrentVersion\App Paths\${ADAK_PRG_EXE}"
!define PRODUCT_UNINST_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}"
!define PRODUCT_UNINST_ROOT_KEY "HKLM"

SetCompressor lzma

; MUI 1.67 compatible ------
!include "MUI.nsh"

; MUI Settings
!define MUI_ABORTWARNING
!define MUI_ICON "${NSISDIR}\Contrib\Graphics\Icons\modern-install.ico"
!define MUI_UNICON "${NSISDIR}\Contrib\Graphics\Icons\modern-uninstall.ico"

; Welcome page
!insertmacro MUI_PAGE_WELCOME
; License page
!insertmacro MUI_PAGE_LICENSE "lisans.txt"
; Directory page
!insertmacro MUI_PAGE_DIRECTORY
; Instfiles page
!insertmacro MUI_PAGE_INSTFILES
; Finish page
!define MUI_FINISHPAGE_RUN "$INSTDIR\${ADAK_PRG_DIR}\${ADAK_PRG_EXE}"
!insertmacro MUI_PAGE_FINISH


; Uninstaller pages
!insertmacro MUI_UNPAGE_INSTFILES

; Language files
!insertmacro MUI_LANGUAGE "Turkish"

; Reserve files
!insertmacro MUI_RESERVEFILE_INSTALLOPTIONS

; MUI end ------

Name "${PRODUCT_NAME} ${PRODUCT_VERSION}"
OutFile "Setup.exe"
InstallDir "$PROGRAMFILES\ADAK"
InstallDirRegKey HKLM "${PRODUCT_DIR_REGKEY}" ""
ShowInstDetails show
ShowUnInstDetails show
RequestExecutionLevel none
ShowInstDetails       show
Section "MainSection" SEC01
  SetOutPath "$INSTDIR"
  CreateDirectory "$INSTDIR\etc"
  CreateDirectory "$INSTDIR\${ADAK_PRG_DIR}"
  CreateDirectory "$INSTDIR\${ADAK_PRG_DIR}\plugins"
  CreateDirectory "$INSTDIR\${ADAK_PRG_DIR}\plugins\sqldrivers"
  CreateDirectory "$INSTDIR\${ADAK_PRG_DIR}\plugins\imageformats"

  File "/oname=${ADAK_PRG_DIR}\${ADAK_PRG_EXE}"                     "..\..\..\${ADAK_PRG_DIR}\WIN32\${ADAK_PRG_EXE}"
  File "/oname=${ADAK_PRG_DIR}\${ADAK_PRG_ICON}"                    "..\${ADAK_PRG_ICON}"
  File "/oname=${ADAK_PRG_DIR}\hlusb.dll"                            "..\DONGLE_DRIVERS\WIN\hlusb.dll"
  File "/oname=${ADAK_PRG_DIR}\mingwm10.dll"                         "..\Qt\WIN32\mingwm10.dll"
  File "/oname=${ADAK_PRG_DIR}\libgcc_s_dw2-1.dll"                   "..\Qt\WIN32\libgcc_s_dw2-1.dll"

  File "/oname=${ADAK_PRG_DIR}\phonon4.dll"                          "..\Qt\WIN32\phonon4.dll"
  File "/oname=${ADAK_PRG_DIR}\QtCore4.dll"                          "..\Qt\WIN32\QtCore4.dll"
  File "/oname=${ADAK_PRG_DIR}\QtGui4.dll"                           "..\Qt\WIN32\QtGui4.dll"
  File "/oname=${ADAK_PRG_DIR}\QtSvg4.dll"                           "..\Qt\WIN32\QtSvg4.dll"
  File "/oname=${ADAK_PRG_DIR}\QtNetwork4.dll"                       "..\Qt\WIN32\QtNetwork4.dll"
  File "/oname=${ADAK_PRG_DIR}\QtWebkit4.dll"                        "..\Qt\WIN32\QtWebkit4.dll"
  File "/oname=${ADAK_PRG_DIR}\QtSql4.dll"                           "..\Qt\WIN32\QtSql4.dll"
  File "/oname=${ADAK_PRG_DIR}\QtXml4.dll"                           "..\Qt\WIN32\QtXml4.dll"
  File "/oname=${ADAK_PRG_DIR}\QtXmlPatterns4.dll"                   "..\Qt\WIN32\QtXmlPatterns4.dll"

  File "/oname=${ADAK_PRG_DIR}\libmysql.dll"                         "..\Qt\WIN32\MySQL\libmysql.dll"
  File "/oname=${ADAK_PRG_DIR}\libeay32.dll"                         "..\Qt\WIN32\PostgreSQL\libeay32.dll"
  File "/oname=${ADAK_PRG_DIR}\ssleay32.dll"                         "..\Qt\WIN32\PostgreSQL\ssleay32.dll"
  File "/oname=${ADAK_PRG_DIR}\iconv.dll"                            "..\Qt\WIN32\PostgreSQL\iconv.dll"
  File "/oname=${ADAK_PRG_DIR}\libiconv-2.dll"                       "..\Qt\WIN32\PostgreSQL\libiconv-2.dll"
  File "/oname=${ADAK_PRG_DIR}\libintl-8.dll"                        "..\Qt\WIN32\PostgreSQL\libintl-8.dll"
  File "/oname=${ADAK_PRG_DIR}\libpq.dll"                            "..\Qt\WIN32\PostgreSQL\libpq.dll"
  File "/oname=${ADAK_PRG_DIR}\libxml2.dll"                          "..\Qt\WIN32\PostgreSQL\libxml2.dll"
  File "/oname=${ADAK_PRG_DIR}\libxslt.dll"                          "..\Qt\WIN32\PostgreSQL\libxslt.dll"
  File "/oname=${ADAK_PRG_DIR}\zlib1.dll"                            "..\Qt\WIN32\PostgreSQL\zlib1.dll"
  File "/oname=${ADAK_PRG_DIR}\oci.dll"                              "..\Qt\WIN32\Oracle\oci.dll"
  File "/oname=${ADAK_PRG_DIR}\oraociei11.dll"                       "..\Qt\WIN32\Oracle\oraociei11.dll"
  File "/oname=${ADAK_PRG_DIR}\libtdsodbc-0.dll"                     "..\Qt\WIN32\TDS\libtdsodbc-0.dll"
  File "/oname=${ADAK_PRG_DIR}\libsybdb-5.dll"                       "..\Qt\WIN32\TDS\libsybdb-5.dll"
  File "/oname=${ADAK_PRG_DIR}\libct-4.dll"                          "..\Qt\WIN32\TDS\libct-4.dll"



  File "/oname=${ADAK_PRG_DIR}\plugins\sqldrivers\qsqlite4.dll"      "..\Qt\WIN32\plugins\sqldrivers\qsqlite4.dll"
  File "/oname=${ADAK_PRG_DIR}\plugins\sqldrivers\qsqlmysql4.dll"    "..\Qt\WIN32\plugins\sqldrivers\qsqlmysql4.dll"
  File "/oname=${ADAK_PRG_DIR}\plugins\sqldrivers\qsqlpsql4.dll"     "..\Qt\WIN32\plugins\sqldrivers\qsqlpsql4.dll"
  File "/oname=${ADAK_PRG_DIR}\plugins\sqldrivers\qsqlodbc4.dll"     "..\Qt\WIN32\plugins\sqldrivers\qsqlodbc4.dll"
  File "/oname=${ADAK_PRG_DIR}\plugins\sqldrivers\qsqloci4.dll"      "..\Qt\WIN32\plugins\sqldrivers\qsqloci4.dll"
  File "/oname=${ADAK_PRG_DIR}\plugins\sqldrivers\qsqltds4.dll"      "..\Qt\WIN32\plugins\sqldrivers\qsqltds4.dll"

  File "/oname=${ADAK_PRG_DIR}\plugins\imageformats\qgif4.dll"       "..\Qt\WIN32\plugins\imageformats\qgif4.dll"
  File "/oname=${ADAK_PRG_DIR}\plugins\imageformats\qico4.dll"       "..\Qt\WIN32\plugins\imageformats\qico4.dll"
  File "/oname=${ADAK_PRG_DIR}\plugins\imageformats\qjpeg4.dll"      "..\Qt\WIN32\plugins\imageformats\qjpeg4.dll"
  File "/oname=${ADAK_PRG_DIR}\plugins\imageformats\qmng4.dll"       "..\Qt\WIN32\plugins\imageformats\qmng4.dll"
  File "/oname=${ADAK_PRG_DIR}\plugins\imageformats\qsvg4.dll"       "..\Qt\WIN32\plugins\imageformats\qsvg4.dll"
  File "/oname=${ADAK_PRG_DIR}\plugins\imageformats\qtiff4.dll"      "..\Qt\WIN32\plugins\imageformats\qtiff4.dll"

  File "/oname=etc\freetds.conf"                                      "..\Qt\WIN32\etc\freetds.conf"

  CreateDirectory "$SMPROGRAMS\ADAK"
  CreateShortCut "$SMPROGRAMS\ADAK\${ADAK_PRG_NAME}" "$INSTDIR\${ADAK_PRG_DIR}\${ADAK_PRG_EXE}" "" "$INSTDIR\${ADAK_PRG_DIR}\${ADAK_PRG_ICON}"
  CreateShortCut "$DESKTOP\${ADAK_PRG_NAME}.lnk" "$INSTDIR\${ADAK_PRG_DIR}\${ADAK_PRG_EXE}" "" "$INSTDIR\${ADAK_PRG_DIR}\${ADAK_PRG_ICON}"
SectionEnd

Section -Post
  WriteUninstaller "$INSTDIR\${ADAK_PRG_DIR}\uninst.exe"
  WriteRegDWORD HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Policies\System" "EnableLUA" "0"
  WriteRegStr HKLM "${PRODUCT_DIR_REGKEY}" "" "$INSTDIR\${ADAK_PRG_EXE}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayName" "$(^Name)"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "UninstallString" "$INSTDIR\${ADAK_PRG_DIR}\uninst.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayIcon" "$INSTDIR\${ADAK_PRG_DIR}\${ADAK_PRG_ICON}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayVersion" "${PRODUCT_VERSION}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "URLInfoAbout" "${PRODUCT_WEB_SITE}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "Publisher" "${PRODUCT_PUBLISHER}"
SectionEnd


Function un.onUninstSuccess
  HideWindow
  MessageBox MB_ICONINFORMATION|MB_OK "$(^Name) sistemden kaldirildi."
FunctionEnd

Function un.onInit
  MessageBox MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 "$(^Name) sisteminizden kaldirilacak , eminmisiniz ?" IDYES +2
  Abort
FunctionEnd

Section "Uninstall"
  Delete "$INSTDIR\uninst.exe"

  Delete "$INSTDIR\${ADAK_PRG_EXE}"
  Delete "$INSTDIR\${ADAK_PRG_ICON}"
  Delete "$INSTDIR\hlusb.dll"
  Delete "$INSTDIR\mingwm10.dll"
  Delete "$INSTDIR\libgcc_s_dw2-1.dll"
  Delete "$INSTDIR\QtCore4.dll"
  Delete "$INSTDIR\QtGui4.dll"
  Delete "$INSTDIR\QtSvg4.dll"
  Delete "$INSTDIR\QtNetwork4.dll"
  Delete "$INSTDIR\QtWebkit4.dll"
  Delete "$INSTDIR\QtSql4.dll"
  Delete "$INSTDIR\QtXml4.dll"
  Delete "$INSTDIR\QtXmlPatterns4.dll"
  Delete "$INSTDIR\phonon4.dll"
  Delete "$INSTDIR\libmysql.dll"
  Delete "$INSTDIR\iconv.dll"
  Delete "$INSTDIR\libiconv-2.dll"
  Delete "$INSTDIR\libintl-8.dll"
  Delete "$INSTDIR\libpq.dll"
  Delete "$INSTDIR\libxml2.dll"
  Delete "$INSTDIR\libxslt.dll"
  Delete "$INSTDIR\ssleay32.dll"
  Delete "$INSTDIR\libeay32.dll"
  Delete "$INSTDIR\libssl32.dll"
  Delete "$INSTDIR\zlib1.dll"
  Delete "$INSTDIR\oci.dll"
  Delete "$INSTDIR\oraociei11.dll"
  Delete "$INSTDIR\libct-4.dll"
  Delete "$INSTDIR\libsybdb-5.dll"
  Delete "$INSTDIR\libtdsodbc-0.dll"
  Delete "$INSTDIR\plugins\sqldrivers\qsqlite4.dll"
  Delete "$INSTDIR\plugins\sqldrivers\qsqlmysql4.dll"
  Delete "$INSTDIR\plugins\sqldrivers\qsqlpsql4.dll"
  Delete "$INSTDIR\plugins\sqldrivers\qsqlodbc4.dll"
  Delete "$INSTDIR\plugins\sqldrivers\qsqloci4.dll"
  Delete "$INSTDIR\plugins\sqldrivers\qsqltds4.dll"
  Delete "$INSTDIR\plugins\imageformats\qgif4.dll"
  Delete "$INSTDIR\plugins\imageformats\qico4.dll"
  Delete "$INSTDIR\plugins\imageformats\qjpeg4.dll"
  Delete "$INSTDIR\plugins\imageformats\qmng4.dll"
  Delete "$INSTDIR\plugins\imageformats\qsvg4.dll"
  Delete "$INSTDIR\plugins\imageformats\qtiff4.dll"

  RMDir "$INSTDIR\plugins\sqldrivers"
  RMDir "$INSTDIR\plugins\imageformats"
  RMDir "$INSTDIR\plugins"


  Delete "$DESKTOP\${ADAK_PRG_NAME}.lnk"
  Delete "$SMPROGRAMS\ADAK\${ADAK_PRG_NAME}.lnk"

  DeleteRegKey ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}"
  DeleteRegKey HKLM "${PRODUCT_DIR_REGKEY}"

  RMDir "$SMPROGRAMS\ADAK"
  RMDir "$INSTDIR"
  SetAutoClose true
SectionEnd
