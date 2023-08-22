;EasyCodeName=ReadIniFile,1
;Latihan Memanggil fitur rutin masm32.lib yg tersedia
;dengan printah Scall
.Const

.Data?

.Data
hInst	           HINSTANCE 	 NULL
szFileName         CHAR "getini.ini", 0
szFileErr          CHAR "error loading getini.ini file", 0
szTitleErr         CHAR "ERROR", 0

hedit1             HANDLE ?
hedit2             HANDLE ?
hedit3             HANDLE ?
;hwnd HANDLE
hfile              HANDLE ?
nfilesize          HANDLE ?
sizeread           HANDLE ?

memhand            HANDLE ?
pmem               HANDLE ?

buffer             CHAR 128 Dup (?)
rPos               HANDLE ?

outTxt             CHAR 128 Dup (?)
formatTxt 		   CHAR "jumlah : %d", 0
totLF 			   HANDLE ?


.Code
start:
	Invoke GetModuleHandle, 0
	Mov hInst, Eax
	Invoke DialogBoxParam, hInst, IDD_DIALOG, 0, Addr DlgProc, 0
	Invoke ExitProcess, 0

DlgProc Proc Private Uses Ebx Edi Esi hwnd:HWND, uMsg:ULONG, wParam:WPARAM, lParam:LPARAM
	Local nmemsize:DWord
	.If uMsg == WM_INITDIALOG
		Invoke GetDlgItem, hwnd, IDC_EDIT1
		Mov hedit1, Eax
		Invoke GetDlgItem, hwnd, IDC_EDIT2
		Mov hedit2, Eax
		Invoke GetDlgItem, hwnd, IDC_EDIT3
		Mov hedit3, Eax
	    Invoke  CreateFile, Addr szFileName, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_ARCHIVE, 0
        .If Eax == INVALID_HANDLE_VALUE
        	Invoke MessageBox, hwnd, Addr szFileErr, Addr szTitleErr, MB_OK
        	Invoke SendMessage, hwnd, WM_CLOSE, 0, 0
            Return FALSE
		.EndIf
	    Mov hfile, Eax
	    Invoke  GetFileSize, hfile, 0
	    Mov nfilesize, Eax
	    Inc Eax
	    Mov nmemsize, Eax
	    Invoke  GlobalAlloc, GMEM_MOVEABLE + GMEM_ZEROINIT, nmemsize ;nfilesize
	    Mov memhand, Eax
	    Invoke  GlobalLock, memhand
	    Mov pmem, Eax
	    Mov Ecx, nfilesize
	    Mov Byte Ptr [Eax + Ecx], NULL ;Clear Byte for EOF
	    Invoke  ReadFile, hfile, pmem, nfilesize, Addr sizeread, NULL

        Scall lfcnt, pmem
        Mov totLF, Eax
        Invoke wsprintf, Addr outTxt, Addr formatTxt, totLF
        Invoke SetDlgItemText, hwnd, IDC_STATIC1, Addr outTxt

	    Scall readline, pmem, Offset buffer, rPos
	    Mov rPos, Eax
	    Invoke SendMessage, hedit1, WM_SETTEXT, 0, Addr buffer

	    Scall readline, pmem, Offset buffer, rPos
	    Mov rPos, Eax
	    Invoke SendMessage, hedit2, WM_SETTEXT, 0, Addr buffer

	    Scall readline, pmem, Offset buffer, rPos
	    Mov rPos, Eax
	    Invoke SendMessage, hedit3, WM_SETTEXT, 0, Addr buffer

	   	Invoke GlobalFree, memhand
	   	Invoke CloseHandle, hfile

	    Return TRUE
	.ElseIf uMsg == WM_COMMAND
        .If wParam == (BN_CLICKED + IDC_EXIT)
        	Invoke SendMessage, hwnd, WM_CLOSE, 0, 0
        .EndIf
        Return TRUE
	.ElseIf uMsg == WM_CLOSE
    	Invoke	EndDialog, hwnd, 0
        Return TRUE
	.EndIf
    Return FALSE
DlgProc EndP

End start
