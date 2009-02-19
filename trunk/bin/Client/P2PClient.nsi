; �ýű�ʹ�� HM VNISEdit �ű��༭���򵼲���

; ��װ�����ʼ���峣��
!define PRODUCT_NAME "Kan8888_P2PClient"
!define PRODUCT_VERSION "1.02"
!define PRODUCT_PUBLISHER "Kevin, Inc."
!define PRODUCT_WEB_SITE "http://p2p.kan8888.com"
!define PRODUCT_DIR_REGKEY "Software\Microsoft\Windows\CurrentVersion\App Paths\P2PService.exe"
!define PRODUCT_UNINST_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}"
!define PRODUCT_UNINST_ROOT_KEY "HKLM"

SetCompressor lzma

; ------ MUI �ִ����涨�� (1.67 �汾���ϼ���) ------
!include "MUI.nsh"

; MUI Ԥ���峣��
!define MUI_ABORTWARNING
!define MUI_ICON "${NSISDIR}\Contrib\Graphics\Icons\modern-install.ico"
!define MUI_UNICON "${NSISDIR}\Contrib\Graphics\Icons\modern-uninstall.ico"

; ��ӭҳ��
!insertmacro MUI_PAGE_WELCOME
; ���Э��ҳ��
!insertmacro MUI_PAGE_LICENSE "copyright.txt"
; ��װĿ¼ѡ��ҳ��
!insertmacro MUI_PAGE_DIRECTORY
; ��װ����ҳ��
!insertmacro MUI_PAGE_INSTFILES
; ��װ���ҳ��
!define MUI_FINISHPAGE_RUN "$INSTDIR\P2PIEClient.exe"
!insertmacro MUI_PAGE_FINISH

; ��װж�ع���ҳ��
!insertmacro MUI_UNPAGE_INSTFILES

; ��װ�����������������
!insertmacro MUI_LANGUAGE "SimpChinese"

; ��װԤ�ͷ��ļ�
!insertmacro MUI_RESERVEFILE_INSTALLOPTIONS
; ------ MUI �ִ����涨����� ------

Name "${PRODUCT_NAME} ${PRODUCT_VERSION}"
OutFile "P2PClientSetup.exe"
InstallDir "$PROGRAMFILES\Kan8888_P2P�ͻ���"
InstallDirRegKey HKLM "${PRODUCT_UNINST_KEY}" "UninstallString"
ShowInstDetails show
ShowUnInstDetails show

Section "MainSection" SEC01
  SetOutPath "$INSTDIR"
  SetOverwrite ifnewer
  CreateDirectory "$SMPROGRAMS\Kan8888_P2P�ͻ���"
  CreateShortCut "$SMPROGRAMS\Kan8888_P2P�ͻ���\Kan8888_P2P�ͻ���.lnk" "$INSTDIR\P2PIEClient.exe"
  CreateShortCut "$SMPROGRAMS\Kan8888_P2P�ͻ���\ж��.lnk" "$INSTDIR\uninst.exe"
  CreateShortCut "$DESKTOP\Kan8888_P2P�ͻ���.lnk" "$INSTDIR\P2PIEClient.exe"

  KillProcDLL::KillProc "Updater.exe"
  KillProcDLL::KillProc "Iexplore.exe"
  KillProcDLL::KillProc "P2PIEClient.exe"

  ExecWait 'Net Stop K8P2PService'

  File "P2PService.exe"
  File "P2PIEClient.exe"
  File "P2PIEClient.ini"
  File "P2PNetwork.ini"
  File "P2PNetwork.dll"
  File "P2PWebAX.dll"
  File "TcpClient.dll"
  File "Updater.exe"
  File "Updater.ini"
  File "msvcr71.dll"
  File "msvcp71.dll"
  
  RegDll "$INSTDIR\P2PWebAX.dll"

  ExecWait '"$INSTDIR\P2PService.exe" /Service'
  ExecWait 'Net Start K8P2PService'
SectionEnd

Section -Post
  WriteUninstaller "$INSTDIR\uninst.exe"
  WriteRegStr HKLM "${PRODUCT_DIR_REGKEY}" "" "$INSTDIR\P2PService.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayName" "$(^Name)"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "UninstallString" "$INSTDIR\uninst.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayIcon" "$INSTDIR\P2PService.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayVersion" "${PRODUCT_VERSION}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "URLInfoAbout" "${PRODUCT_WEB_SITE}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "Publisher" "${PRODUCT_PUBLISHER}"
SectionEnd

/******************************
 *  �����ǰ�װ�����ж�ز���  *
 ******************************/

Section Uninstall
  ExecWait '"$INSTDIR\P2PService.exe" -UnRegServer'
  KillProcDLL::KillProc "P2PService.exe"
  KillProcDLL::KillProc "Updater.exe"
  KillProcDLL::KillProc "Iexplore.exe"
  KillProcDLL::KillProc "P2PIEClient.exe"
  Delete "$INSTDIR\P2PService.exe"
  Delete "$INSTDIR\P2PIEClient.exe"
  Delete "$INSTDIR\P2PIEClient.ini"
  Delete "$INSTDIR\Updater.exe"
  UnRegDll "$INSTDIR\P2PWebAX.dll"
  Delete "$INSTDIR\uninst.exe"
  Delete "$INSTDIR\msvcp71.dll"
  Delete "$INSTDIR\msvcr71.dll"
  Delete "$INSTDIR\P2PWebAX.dll"
  Delete "$INSTDIR\P2PNetwork.dll"
  Delete "$INSTDIR\TcpClient.dll"
  Delete "$INSTDIR\P2PNetwork.ini"
  Delete "$INSTDIR\Updater.ini"

  Delete "$DESKTOP\Kan8888_P2P�ͻ���.lnk"
  Delete "$SMPROGRAMS\Kan8888_P2P�ͻ���\Kan8888_P2P�ͻ���.lnk"
  Delete "$SMPROGRAMS\Kan8888_P2P�ͻ���\ж��.lnk"
  RMDir "$SMPROGRAMS\Kan8888_P2P�ͻ���"
  
  RMDir /r "$INSTDIR\log"
  RMDir "$INSTDIR"

  DeleteRegKey ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}"
  DeleteRegKey HKLM "${PRODUCT_DIR_REGKEY}"
  SetAutoClose true
SectionEnd

#-- ���� NSIS �ű��༭�������� Function ���α�������� Section ����֮���д���Ա��ⰲװ�������δ��Ԥ֪�����⡣--#

Function un.onInit
  MessageBox MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 "��ȷʵҪ��ȫ�Ƴ� $(^Name) ���������е������" IDYES +2
  Abort
FunctionEnd

Function un.onUninstSuccess
  HideWindow
  MessageBox MB_ICONINFORMATION|MB_OK "$(^Name) �ѳɹ��ش���ļ�����Ƴ���"
FunctionEnd
