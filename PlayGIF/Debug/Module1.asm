.Const

.Data?

.Data
hInst			HINSTANCE	NULL
gdipInput 		GdiplusStartupInput <?> ;
gdipToken 		LPVOID ? ;
image 			LPVOID ?
ptWnd			POINT <>
WndRect			RECT <>
StaticClass 	CHAR "Static", 0
hbitmap 		HBITMAP ?
FormatFrame		CHAR ": %d", 0
FormatDimensi	CHAR ": %d", 0
FormatTime		CHAR ": %d", 0
FormatHRes		CHAR ": %d", 0
FormatVRes		CHAR ": %d", 0
JmlFormatGbr	DWord ?
JmlFrame		DWord ?
FrameDelay		DWord ?
HorRes			Real4 ?
VerRes			Real4 ?
AHorRes 		CHAR 20 Dup (?)
AVerRes 		CHAR 20 Dup (?)
nFrame			DWord 0
CurrentFrame	CHAR "Frame = %d", 0
gif_filter 		DB 'Gif files', 0, '*.gif', 0
		 		DB 'Png files', 0, '*.png', 0
		 		DB 'jpg files', 0, '*.jpg', 0
	      		DB 0
BuffFileName	TCHAR MAX_PATH Dup (?) ;for OPENFILENAME

AngkaFormat		DB "N=%d", 0
Angka			DWord ?
AngkaMAX		Equ 20
;IsEqualGUID Proto StdCall :DWord, :DWord
hStaticCtl			  DWord ?
hMeStaticProc         DWord ?
hOriginStaticProc     DWord ?
tes				      DWord ?

.Code

start:
	Invoke GetModuleHandle, NULL
	Mov hInst, Eax
	Mov gdipInput.GdiplusVersion, 1
   	Invoke GdiplusStartup, Addr gdipToken, Addr gdipInput, NULL
	Invoke DialogBoxParam, hInst, IDD_DIALOG1, 0, Addr DlgProc, 0
	Invoke GdiplusShutdown, gdipToken ;
	Invoke ExitProcess, Eax

DlgProc Proc Private Uses Ebx Edi Esi hWnd:HWND, uMsg:ULONG, wParam:WPARAM, lParam:LPARAM
	Local ImageRect:RECT
	Local hStatic4:HANDLE, hCtl:HWND
	Local wc:WNDCLASSEX
	;===================WM_INITDIALOG======================
	.If uMsg == WM_INITDIALOG
		;CONTROL "", IDC_IMAGE1, "STATIC", SS_BITMAP | Not WS_TABSTOP, 10, 26, 100, 87, WS_EX_CLIENTEDGE
		Text szClassName, "STATIC"
;		Mov wc.cbSize, SizeOf WNDCLASSEX
;		Mov wc.style, 0 ;CS_DBLCLKS
;		Mov wc.lpfnWndProc, Offset MeProc
;		Mov wc.cbClsExtra, 0
;		Mov wc.cbWndExtra, 0
;		m2m wc.hInstance, hInst
;		Mov wc.hIcon, NULL
;		Invoke LoadImage, NULL, OCR_NORMAL, IMAGE_CURSOR, 0, 0, (LR_DEFAULTSIZE Or LR_LOADMAP3DCOLORS Or LR_SHARED)
;		Mov wc.hCursor, Eax
;		Mov wc.hbrBackground, (COLOR_BTNFACE + 1)
;		Mov wc.lpszMenuName, NULL
;		Mov wc.lpszClassName, Offset szClassName
;		Mov wc.hIconSm, NULL
;		Invoke RegisterClassEx, Addr wc

		Invoke CreateWindowEx, 0, Addr szClassName, Addr szClassName, (WS_POPUP Or WS_VISIBLE), 0, 0, 100, 100, hWnd, 2000, hInst, NULL
		;Invoke SetWindowPos, Eax, NULL, 50, 50, 100, 100, SWP_SHOWWINDOW
		Invoke ShowWindow, Eax, SW_SHOWNORMAL

  		Invoke GetDlgItem, hWnd, IDC_Next
		Invoke EnableWindow, Eax, FALSE
  		Invoke GetDlgItem, hWnd, IDC_Prev
		Invoke EnableWindow, Eax, FALSE

		Invoke GetWindowRect, hWnd, Addr WndRect
		Invoke GetSystemMetrics, SM_CXSCREEN
  		Invoke TopXY, WndRect.right, Eax
   		Mov ptWnd.x, Eax
		Invoke GetSystemMetrics, SM_CYSCREEN
   		Invoke TopXY, WndRect.bottom, Eax
   		Mov ptWnd.y, Eax
		Invoke SetWindowPos, hWnd, NULL, ptWnd.x, ptWnd.y, WndRect.right, WndRect.bottom, TRUE

		; Tes Mengambil alih Procedure STATIC CLASS
        ;Invoke StaticControl, hWnd
        ;Invoke ShowWindow, hWnd, SW_HIDE
		;Invoke SendDlgItemMessage, hWnd, eee, msg, lParam.wpara
		; Tes Update Brush Color Static Dialog
		Invoke GetDlgItem, hWnd, IDC_STATIC4
		Mov hStatic4, Eax

		Xor Eax, Eax
		Ret

	;==================Merubah Warna Background Dialog==========================
    .ElseIf uMsg == WM_CTLCOLORDLG
            Invoke GetStockObject, BLACK_BRUSH
            Ret
	;==================Merubah seluruh Static Region Window==========================
    .ElseIf uMsg == WM_CTLCOLORSTATIC
   			Invoke SetBkMode, wParam, TRANSPARENT
			RGB 0, 34, 255
			Invoke SetTextColor, wParam, Eax
			; Perintah ini tdk boleh di rubah posisinya
			; harus paling bawah. kerna menentukan HOLLOW_BRUSH
           	Invoke GetStockObject, HOLLOW_BRUSH
          	Ret
;	.ElseIf uMsg == WM_LBUTTONDOWN
;			Invoke GetDlgItem, hWnd, IDC_IMAGE1
;			Mov hCtl, Eax
;	    	Invoke SetActiveWindow, hCtl
;    	    Invoke SendMessage, hCtl, WM_NCLBUTTONDOWN, HTCAPTION, NULL
;	        Xor Eax, Eax
;        	Ret
	;==================WM_COMMAND==========================
	.ElseIf uMsg == WM_COMMAND
        .If wParam == (BN_CLICKED + IDC_Next)
       	;Next Frame==========================
       		Inc nFrame
       		Mov Eax, JmlFrame
       		Dec Eax
       		.If nFrame > Eax
       			Mov nFrame, 0
       		.EndIf
			Invoke DlgSetText, hWnd, IDC_nFrame, Addr CurrentFrame, nFrame
			Invoke ImageSelectActiveFrame, image, nFrame
			.If hbitmap
				Invoke DelBitmap, hbitmap
				Invoke GetImageRect, image, Addr ImageRect
				Invoke GetImage2Bitmap, image, Addr ImageRect
				Mov hbitmap, Eax
				Invoke DlgSetImage, hWnd, IDC_IMAGE1, hbitmap
			.EndIf
        .ElseIf wParam == (BN_CLICKED + IDC_Prev)
            ;Prev Frame===========================
       		Dec nFrame
       		Mov Eax, JmlFrame
       		Dec Eax
       		.If nFrame > Eax
       			Mov nFrame, Eax
       		.EndIf
			Invoke DlgSetText, hWnd, IDC_nFrame, Addr CurrentFrame, nFrame
			Invoke ImageSelectActiveFrame, image, nFrame
			.If hbitmap
				Invoke DelBitmap, hbitmap
				Invoke GetImageRect, image, Addr ImageRect
				Invoke GetImage2Bitmap, image, Addr ImageRect
				Mov hbitmap, Eax
				Invoke DlgSetImage, hWnd, IDC_IMAGE1, hbitmap
			.EndIf
        .ElseIf wParam == (BN_CLICKED + IDC_PLUS)
        	Invoke Plus, hWnd
        .ElseIf wParam == (BN_CLICKED + IDC_MINUS)
        	Invoke Minus, hWnd
        .ElseIf wParam == (BN_CLICKED + IDC_OPEN)
        	Invoke DlgOpenFile, hWnd, hInst, Addr gif_filter, Addr BuffFileName
        	.If Eax
        		; init variable bitmap dan image
				.If hbitmap
					Invoke DelBitmap, hbitmap
				.EndIf
				.If image
					Invoke DelImage, image
			  		Invoke GetDlgItem, hWnd, IDC_Next
					Invoke EnableWindow, Eax, FALSE
			  		Invoke GetDlgItem, hWnd, IDC_Prev
					Invoke EnableWindow, Eax, FALSE
					Mov nFrame, NULL
					Mov FrameDelay, NULL
					Mov JmlFormatGbr, NULL
					Mov JmlFrame, NULL
					Invoke DlgSetText, hWnd, IDC_nFrame, Addr CurrentFrame, nFrame
					Invoke DlgSetText, hWnd, IDC_Delay, Addr FormatTime, FrameDelay
					Invoke DlgSetText, hWnd, IDC_Dimensi, Addr FormatDimensi, JmlFormatGbr
					Invoke DlgSetText, hWnd, IDC_Frame, Addr FormatFrame, JmlFrame
				.EndIf

				Invoke GetFile2Image, Addr BuffFileName
				Mov image, Eax

				Invoke GetFrameSumGIF, image
				Mov JmlFrame, Eax

                .If Eax > 1 ; lebih dari 1 memiliki animasi
					Mov JmlFormatGbr, Ecx
					Invoke GetPropertyValue, image, PropertyTagFrameDelay
					Mov FrameDelay, Eax

	   				Invoke GetDlgItem, hWnd, IDC_Next
					Invoke EnableWindow, Eax, TRUE
  					Invoke GetDlgItem, hWnd, IDC_Prev
					Invoke EnableWindow, Eax, TRUE

					Invoke ImageSelectActiveFrame, image, nFrame
					Invoke DlgSetText, hWnd, IDC_nFrame, Addr CurrentFrame, nFrame
					Invoke DlgSetText, hWnd, IDC_Delay, Addr FormatTime, FrameDelay
					Invoke DlgSetText, hWnd, IDC_Dimensi, Addr FormatDimensi, JmlFormatGbr
					Invoke DlgSetText, hWnd, IDC_Frame, Addr FormatFrame, JmlFrame
				.EndIf

				Invoke GetImageRect, image, Addr ImageRect
				Invoke DlgSetText, hWnd, IDC_Lebar, Addr FormatHRes, ImageRect.right
				Invoke DlgSetText, hWnd, IDC_Tinggi, Addr FormatVRes, ImageRect.bottom

				Invoke GetImage2Bitmap, image, Addr ImageRect
				Mov hbitmap, Eax
				Invoke DlgSetImage, hWnd, IDC_IMAGE1, hbitmap

				Invoke DlGSetGUID2String, hWnd, IDC_GUID
        	.EndIf
        .EndIf
		Xor Eax, Eax
		Ret
	;==================WM_CLOSE============================
	.ElseIf uMsg == WM_CLOSE
		.If hbitmap
			Invoke DelBitmap, hbitmap
		.EndIf
		.If image
			Invoke DelImage, image
		.EndIf
    	Invoke EndDialog, hWnd, 0
		Xor Eax, Eax
		Ret
	.EndIf
	Xor Eax, Eax
	Ret
DlgProc EndP
;StaticControl Proc hWnd:HWND
;		Invoke GetDlgItem, hWnd, IDC_IMAGE1
;		Mov hStaticCtl, Eax
;    	Invoke SetWindowLong, hStaticCtl, DWL_DLGPROC, Addr hMeStaticProc
;    	Mov hOriginStaticProc, Eax
;		Ret
;StaticControl EndP

;hMeStaticProc Proc hCtl:DWord, uMsg:DWord, wParam:DWord, lParam:DWord
;	.If uMsg == WM_LBUTTONDOWN
;    	    Invoke SendMessage, hCtl, WM_NCLBUTTONDOWN, HTCAPTION, NULL
;    .ElseIf uMsg == WM_RBUTTONDOWN
;		   	Invoke MessageBeep, -1
;    .EndIf
;    Invoke CallWindowProc, hOriginStaticProc, hCtl, uMsg, wParam, lParam
;	Ret
;hMeStaticProc EndP

Plus Proc hWnd:HWND
	Inc Angka
	Mov Eax, AngkaMAX
	Dec Eax
	.If Angka > Eax
		Mov Angka, 0
	.EndIf
	Invoke DlgSetText, hWnd, IDC_ANGKA, Addr AngkaFormat, Angka
	Ret
Plus EndP
Minus Proc hWnd:HWND
    Dec Angka
    Mov Eax, AngkaMAX
    Dec Eax
    .If Angka > Eax
    	Mov Angka, Eax
    .EndIf
	Invoke DlgSetText, hWnd, IDC_ANGKA, Addr AngkaFormat, Angka
	Ret
Minus EndP

End start

;WM_CREATE 			Loads the graphic object And sizes the window to the object 's size, for graphic static controls. Takes no action for other static controls.
;WM_DESTROY			Frees and destroys any graphic object, for graphic static  controls. Takes no action for other static controls.
;WM_ENABLE			Repaints visible static controls.
;WM_ERASEBKGND		Returns TRUE, indicating the control erases the background.
;WM_GETDLGCODE		Returns DLGC_STATIC.
;WM_GETFONT			Returns the handle of the font for text static controls.
;WM_GETTEXTLENGTH	Returns the length, in characters, of the text for a text static control.
;WM_LBUTTONDBLCLK	Sends the parent window an STN_DBLCLK notification message if the control style is SS_NOTIFY.
;WM_LBUTTONDOWN		Sends the parent window an STN_CLICKED notification message if the control style is SS_NOTIFY.
;WM_NCLBUTTONDBLCLK	Sends the parent window an STN_DBLCLK notification message if the control style is SS_NOTIFY.
;WM_NCLBUTTONDOWN	Sends the parent window an STN_CLICKED notification message if the control style is SS_NOTIFY.
;WM_NCHITTEST		Returns HTCLIENT if the control style is SS_NOTIFY; otherwise, returns HTTRANSPARENT.
;WM_PAINT			Repaints the control.
;WM_SETFONT			Sets the font and repaints for text static controls.
;WM_SETTEXT	

;DM_GETDEFID
;DM_REPOSITION
;DM_SETDEFID
;WM_CTLCOLORDLG
;WM_CTLCOLORMSGBOX
;WM_ENTERIDLE
;WM_GETDLGCODE
;WM_INITDIALOG
;WM_NEXTDLGCTL

;hWnd CreateWindowEx(
;    DWORD dwExStyle,	// extended window style
;    LPCTSTR lpClassName,	// pointer to registered class name
;    LPCTSTR lpWindowName,	// pointer to window name
;    DWORD dwStyle,	// window style
;    int x,	// horizontal position of window
;    int y,	// vertical position of window
;    int nWidth,	// window width
;    int nHeight,	// window height
;    HWND hWndParent,	// handle to parent or owner window
;    HMENU hMenu,	// handle to menu, or child-window identifier
;    HINSTANCE hInstance,	// handle to application instance
;    LPVOID lpParam 	// pointer to window-creation data
;   );
