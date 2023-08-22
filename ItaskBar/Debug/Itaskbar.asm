;EasyCodeName=Itaskbar,1
;Contoh paling simpel menulis assambler utk mengunakan activX
;Programmer : Pahor M
;Edit App   : Easy Code

.Const
;Define Macro Implementation COM
ComInvoke Macro pInterface:REQ, Method:REQ, arg
    IFNB <arg>       ;; If not blank
         Push arg    ;; push parameter
    ENDIF
    Mov Eax, pInterface
    Push Eax
    mov eax, [eax]
    Call [Eax].Method
EndM

;ITaskBarList Methods
ITaskBarList Struct
   QueryInterface DWord ?
   AddRef         DWord ?
   Release        DWord ?
   HrInit         DWord ?
   AddTab         DWord ?
   DeleteTab      DWord ?
   ActivateTab    DWord ?
   SetActiveAlt   DWord ?
ITaskBarList EndS

;String Constant CLSID & IID IUnknown
sCLSID_ITaskbarList       TextEqu <{056FDF344H, 0FD6DH, 011D0H, \
                                   {095H, 08AH, 000H, 060H, 097H, 0C9H, 0A0H, 090H}}>
sIID_ITaskbarList         TextEqu <{056FDF342H, 0FD6DH, 011D0H, \
                                   {095H, 08AH, 000H, 060H, 097H, 0C9H, 0A0H, 090H}}>
.Data?

.Data
;Global data
hInst	           HINSTANCE 	NULL
IID_ITaskbarList   GUID         sIID_ITaskbarList
CLSID_ITaskbarList GUID         sCLSID_ITaskbarList
ShellTaskBar       DWord        ?

.Code
start:
	invoke GetModuleHandleA, 0
	Mov hInst, Eax
	Invoke CoInitialize, NULL
	Invoke CoCreateInstance, Offset CLSID_ITaskbarList, NULL, CLSCTX_INPROC_SERVER, Offset IID_ITaskbarList, Offset ShellTaskBar
	Invoke DialogBoxParam, hInst, IDD_DIALOG, 0, Addr DlgProc, 0
	Invoke CoUninitialize
	Invoke ExitProcess, 0

DlgProc Proc Private Uses Ebx Edi Esi hWnd:HWND, uMsg:ULONG, wParam:WPARAM, lParam:LPARAM
	.If uMsg == WM_INITDIALOG
        Return TRUE
	.ElseIf uMsg == WM_COMMAND
        .If wParam == (BN_CLICKED + IDC_EXIT)
        	Invoke SendMessage, hWnd, WM_CLOSE, 0, 0
        .ElseIf wParam == (BN_CLICKED + IDC_SHOW)
        	Invoke DisableControl, hWnd, IDC_SHOW, IDC_HIDE
                ;show =====================
        	ComInvoke ShellTaskBar, ITaskBarList.HrInit
		    ComInvoke ShellTaskBar, ITaskBarList.AddTab, hWnd
            ComInvoke ShellTaskBar, ITaskBarList.ActivateTab, hWnd
        .ElseIf wParam == (BN_CLICKED + IDC_HIDE)
        	Invoke DisableControl, hWnd, IDC_HIDE, IDC_SHOW
                ;hide =====================
                ComInvoke ShellTaskBar, ITaskBarList.HrInit
                ComInvoke ShellTaskBar, ITaskBarList.DeleteTab, hWnd
        .EndIf
        Return TRUE
	.ElseIf uMsg == WM_CLOSE
    	ComInvoke ShellTaskBar, ITaskBarList.Release
    	Invoke	EndDialog, hWnd, 0
        Return TRUE
	.EndIf
    Return FALSE
DlgProc EndP
DisableControl Proc hWnd:HWND, Id1:DWord, Id2:DWord
  	Invoke GetDlgItem, hWnd, Id1
   	Invoke EnableWindow, Eax, FALSE
  	Invoke GetDlgItem, hWnd, Id2
   	Invoke EnableWindow, Eax, TRUE
	Ret
DisableControl EndP
End start
