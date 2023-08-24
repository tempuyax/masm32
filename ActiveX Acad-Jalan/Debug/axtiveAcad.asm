Include	mymacro.inc
.Const
;Include	mymacro.inc
;IAcadApplication Interface
put_Visible Equ 9
_Quit       Equ 34
_Release    Equ 3
.Data?

.Data

hInst	      			HINSTANCE	NULL
szOfficeApp   	    	DB "AutoCAD.Application", 0
IID_IAcadApplication 	GUID {093BC4E71H, 0AFE7H, 04AA7H, {0BCH, 007H, 0F8H, 00AH, 0CDH, 0B6H, 072H, 0D5H}}
pApplication  		    DD ?

szInfo DB "*START*", 0DH, 0AH
       DB "Under Conection ActiveX control by Autocad Application", 0DH, 0AH
       DB 0DH, 0AH
       DB "*SHOW*", 0DH, 0AH
       DB "Show Autocad Application in desktop", 0DH, 0AH
       DB 0DH, 0AH
       DB "*HIDE*", 0DH, 0AH
       DB "Hidden Autocad Application", 0DH, 0AH
       DB 0DH, 0AH
       DB "*END*", 0DH, 0AH
       DB "Unconection ActiveX control with Autocad Application", 0DH, 0AH
       DB 0DH, 0AH
       DB "*EXIT*", 0DH, 0AH
       DB "Exit me"
       DB 0

szCopyright DB "Assambler.Lab.", 0DH, 0AH
            DB "(C)Pahor .M, Nunukan 2019", 0DH, 0AH
            DB 0


.Code

start:
	invoke InitCommonControls
	Invoke CoInitializeEx, 0, 0 ;COINIT_MULTITHREADED
	Invoke DialogBoxParam, hInst, IDD_DIALOG1, NULL, Addr DlgProc, NULL
	Invoke CoUninitialize
	Invoke ExitProcess, 0

DlgProc Proc Private Uses Ebx Edi Esi hWnd:HWND, uMsg:ULONG, wParam:WPARAM, lParam:LPARAM
	Local clsidApp:GUID
	Local lpWideCharStr[128]:Byte
	Local hEdit:HWND
	Local hCopyright:HWND

	.If uMsg == WM_INITDIALOG
  		Invoke GetDlgItem, hWnd, IDC_INFO
  		Mov hEdit, Eax
  		Invoke SetTextAlign, hEdit, TA_LEFT
		Invoke SetWindowText, hEdit, Addr szInfo
  		Invoke GetDlgItem, hWnd, IDC_COPYRIGHT
  		Mov hCopyright, Eax
  		Invoke SetTextAlign, hCopyright, TA_LEFT
		Invoke SetWindowText, hCopyright, Addr szCopyright
  		Invoke GetDlgItem, hWnd, IDC_START
		Invoke EnableWindow, Eax, TRUE
  		Invoke GetDlgItem, hWnd, IDC_SHOW
		Invoke EnableWindow, Eax, FALSE
    	Invoke GetDlgItem, hWnd, IDC_HIDE
	    Invoke EnableWindow, Eax, FALSE
  		Invoke GetDlgItem, hWnd, IDC_END
		Invoke EnableWindow, Eax, FALSE
  		Invoke GetDlgItem, hWnd, IDC_EXIT
		Invoke EnableWindow, Eax, TRUE
		Return TRUE
	.ElseIf uMsg == WM_COMMAND
		.If wParam == (BN_CLICKED Shl 16 Or IDC_START)
			Invoke MultiByteToWideChar, CP_ACP, 0, Addr szOfficeApp, -1, Addr lpWideCharStr, SizeOf lpWideCharStr
			Invoke CLSIDFromProgID, Addr lpWideCharStr, Addr clsidApp
			Invoke CoCreateInstance, Addr clsidApp, 0, CLSCTX_SERVER, Addr IID_IAcadApplication, Addr pApplication
    		Invoke GetDlgItem, hWnd, IDC_START
    		Invoke EnableWindow, Eax, FALSE
    		Invoke GetDlgItem, hWnd, IDC_SHOW
    		Invoke EnableWindow, Eax, TRUE
  		    Invoke GetDlgItem, hWnd, IDC_END
		    Invoke EnableWindow, Eax, TRUE
    		Invoke GetDlgItem, hWnd, IDC_EXIT
    		Invoke EnableWindow, Eax, FALSE
		.ElseIf wParam == (BN_CLICKED Shl 16 Or IDC_EXIT)
        	Invoke SendMessage, hWnd, WM_CLOSE, 0, 0
		.ElseIf wParam == (BN_CLICKED Shl 16 Or IDC_SHOW)
			StdCallCom pApplication, put_Visible, VARIANT_TRUE
			.If Eax == S_OK
	  	    	Invoke GetDlgItem, hWnd, IDC_SHOW
			    Invoke EnableWindow, Eax, FALSE
	  	    	Invoke GetDlgItem, hWnd, IDC_HIDE
			    Invoke EnableWindow, Eax, TRUE
		    .EndIf
		.ElseIf wParam == (BN_CLICKED Shl 16 Or IDC_HIDE)
			StdCallCom pApplication, put_Visible, VARIANT_FALSE
			.If Eax == S_OK
	  	    	Invoke GetDlgItem, hWnd, IDC_SHOW
			    Invoke EnableWindow, Eax, TRUE
	  	    	Invoke GetDlgItem, hWnd, IDC_HIDE
			    Invoke EnableWindow, Eax, FALSE
		    .EndIf
		.ElseIf wParam == (BN_CLICKED Shl 16 Or IDC_END)
			StdCallCom pApplication, _Quit
			StdCallCom pApplication, _Release
			.If Eax == S_OK
		  		Invoke GetDlgItem, hWnd, IDC_START
				Invoke EnableWindow, Eax, TRUE
		  		Invoke GetDlgItem, hWnd, IDC_SHOW
				Invoke EnableWindow, Eax, FALSE
		    	Invoke GetDlgItem, hWnd, IDC_HIDE
			    Invoke EnableWindow, Eax, FALSE
		  		Invoke GetDlgItem, hWnd, IDC_END
				Invoke EnableWindow, Eax, FALSE
		  		Invoke GetDlgItem, hWnd, IDC_EXIT
				Invoke EnableWindow, Eax, TRUE
		    .EndIf
		.EndIf
		Return TRUE
	.ElseIf uMsg == WM_CLOSE
		Invoke EndDialog, hWnd, 0
		Return TRUE
	.EndIf
	Return FALSE
DlgProc EndP

End start
