;EasyCodeName=Module1,1
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
hStaticCtl			DWord ?
hMeStaticProc       DWord ?
hOriginStaticProc   DWord ?
tes				    DWord ?
hStaticImg			HWND ?
hStaticGroup		HWND ?
hStatic3 			HWND ?
RegionModel			DWord ?
sNULLREGION			DB "NULLREGION", 0
sSIMPLEREGION   	DB "SIMPLEREGION", 0
sCOMPLEXREGION		DB "COMPLEXREGION", 0
sERROR				DB "ERROR", 0
hRgnGroup			HRGN ?
rcCliping			RECT <>
hRgnGroupX			HRGN ?

;-------------
StcFont 			DWord ?
StcTxtBkColor 		DWord ?
StcTextColor		DWord ?
StcBrush			DWord ?

IDT_TIME1 Equ 1000

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
	Local hStatic4:HANDLE, hCtl:HWND, hStaticGUID:HWND, hBtnANIMTEXT:HWND
	Local rc:RECT, hRgn:HRGN, hWndRgn:HRGN
	Local wFrame:HWND, hFrameRgn:HRGN, wFrameRc:RECT
	;===================WM_INITDIALOG======================
	.If uMsg == WM_INITDIALOG
        ;Setup STATIC CONTROL-------------------
		Invoke	CreateFont, 16, 0, 0, 0, 0, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_RASTER_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, (FIXED_PITCH Or FF_DONTCARE), NULL
		Mov StcFont, Eax
		Mov StcTxtBkColor, TRANSPARENT
		RGB 255, 255, 255
		Mov StcTextColor, Eax
        Mov StcBrush, HOLLOW_BRUSH
		;Setup Enableling DIALOG---------------
  		Invoke GetDlgItem, hWnd, IDC_Next
		Invoke EnableWindow, Eax, FALSE
  		Invoke GetDlgItem, hWnd, IDC_Prev
		Invoke EnableWindow, Eax, FALSE
  		Invoke GetDlgItem, hWnd, IDC_PLUS
		Invoke EnableWindow, Eax, FALSE
  		Invoke GetDlgItem, hWnd, IDC_MINUS
		Invoke EnableWindow, Eax, FALSE

		Invoke GetWindowRect, hWnd, Addr WndRect
		Invoke GetSystemMetrics, SM_CXSCREEN
  		Invoke TopXY, WndRect.right, Eax
   		Mov ptWnd.x, Eax
		Invoke GetSystemMetrics, SM_CYSCREEN
   		Invoke TopXY, WndRect.bottom, Eax
   		Mov ptWnd.y, Eax

 		Invoke CreateRoundRectRgn, WndRect.left, WndRect.top, WndRect.right, WndRect.bottom, 30, 30
 		Mov hWndRgn, Eax
		Invoke SetWindowRgn, hWnd, hWndRgn, TRUE

		Invoke SetWindowPos, hWnd, NULL, ptWnd.x, ptWnd.y, WndRect.right, WndRect.bottom, TRUE

    	Invoke DeleteObject, hWndRgn

		; Tes Mengambil alih Procedure STATIC CLASS
		Invoke GetDlgItem, hWnd, IDC_IMAGE1
		Mov hStaticImg, Eax

		; Tes Update Brush Color Static Dialog
		Invoke GetDlgItem, hWnd, IDC_STATIC4
		Mov hStatic4, Eax

		Xor Eax, Eax
		Ret
    ; -----------------------------------
    ; create a font and return its handle
    ; -----------------------------------
    ;  GetFontHandle MACRO fnam:REQ,fsiz:REQ,fwgt:REQ
    ;    Invoke RetFontHandle, reparg(fnam), fsiz, fwgt
    ;    EXITM <eax>
    ;  ENDM
;WM_CTLCOLORBTN
;transparent
	;==================Merubah Warna Background Dialog==========================WM_FONTCHANGE
;    .ElseIf uMsg == WM_CTLCOLORBTN
;    	    RGB 255, 0, 0
;    		Invoke CreateSolidBrush, Eax
;    		Push Eax
;    		Invoke SelectObject,
;       		;Invoke GetStockObject, Eax
;       		Pop Eax
;       		Invoke DeleteObject, Eax
;            Ret
    .ElseIf uMsg == WM_CTLCOLORDLG
            Invoke GetStockObject, BLACK_BRUSH
            Ret
	;==================Merubah seluruh Static Region Window==========================
	;WM_CTLCOLORSTATIC
	;hdcStatic = (HDC) wParam;   // handle of display context 
	;hwndStatic = (HWND) lParam; // handle of static control
	;Or Eax == IDC_GUID Or Eax == IDC_STATIC4 Or Eax == IDC_STATIC5 Or Eax == IDC_STATIC6 Or Eax == IDC_STATIC7 Or Eax == IDC_STATIC8)
    .ElseIf uMsg == WM_CTLCOLORSTATIC
    	    Invoke GetDlgCtrlID, lParam
            .If Eax == IDC_GUID
;				Invoke SelectObject, wParam, StcFont
;  				Invoke SetBkMode, wParam, StcTxtBkColor
;				Invoke SetTextColor, wParam, StcTextColor
;           		Invoke GetStockObject, StcBrush
            .ElseIf Eax == IDC_GROUP1 ; IDC_STATIC4 5 6 7 8 IDC_GROUP1
           		Invoke GetStockObject, StcBrush
            .ElseIf Eax == IDC_STATIC3 ; IDC_STATIC4 5 6 7 8 IDC_GROUP1
				Invoke SelectObject, wParam, StcFont
  				Invoke SetBkMode, wParam, StcTxtBkColor
				Invoke SetTextColor, wParam, StcTextColor
           		Invoke GetStockObject, StcBrush
            .ElseIf Eax == IDC_STATIC4 ; IDC_STATIC4 5 6 7 8
				Invoke SelectObject, wParam, StcFont
  				Invoke SetBkMode, wParam, StcTxtBkColor
				Invoke SetTextColor, wParam, StcTextColor
           		Invoke GetStockObject, StcBrush
            .ElseIf Eax == IDC_STATIC5 ; 5 6 7 8
				Invoke SelectObject, wParam, StcFont
  				Invoke SetBkMode, wParam, StcTxtBkColor
				Invoke SetTextColor, wParam, StcTextColor
           		Invoke GetStockObject, StcBrush
            .ElseIf Eax == IDC_STATIC6 ; 5 6 7 8
				Invoke SelectObject, wParam, StcFont
  				Invoke SetBkMode, wParam, StcTxtBkColor
				Invoke SetTextColor, wParam, StcTextColor
           		Invoke GetStockObject, StcBrush
            .ElseIf Eax == IDC_STATIC7 ; 5 6 7 8
				Invoke SelectObject, wParam, StcFont
  				Invoke SetBkMode, wParam, StcTxtBkColor
				Invoke SetTextColor, wParam, StcTextColor
           		Invoke GetStockObject, StcBrush
            .ElseIf Eax == IDC_STATIC8 ; 5 6 7 8
				Invoke SelectObject, wParam, StcFont
  				Invoke SetBkMode, wParam, StcTxtBkColor
				Invoke SetTextColor, wParam, StcTextColor
           		Invoke GetStockObject, StcBrush
           	.EndIf
          	Ret
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
        .ElseIf wParam == (BN_CLICKED + IDC_ANIMTEXT)
			;Init Timer Tick ===============
	  		Invoke GetDlgItem, hWnd, IDC_OPEN
			Invoke EnableWindow, Eax, FALSE
	  		Invoke GetDlgItem, hWnd, IDC_ANIMTEXT
			Invoke EnableWindow, Eax, FALSE
	  		Invoke GetDlgItem, hWnd, IDC_ANIMTEXTOFF
			Invoke EnableWindow, Eax, TRUE
	  		Invoke GetDlgItem, hWnd, IDC_Next
			Invoke EnableWindow, Eax, FALSE
	  		Invoke GetDlgItem, hWnd, IDC_Prev
			Invoke EnableWindow, Eax, FALSE

	  		Invoke GetDlgItem, hWnd, IDC_GUID
			Invoke RunText, Eax, FALSE

;		    Invoke GetClientRect, hWnd, Addr rc
;			Invoke CreateRoundRectRgn, 0, 0, rc.right, 20, 10, 10
;    		Mov hRgn, Eax
;			Invoke GetDC, hWnd
;			Push Eax
;            Invoke PaintRgn, Eax, hRgn
;            Pop Eax
;            Invoke ReleaseDC, hWnd, Eax
;    		Invoke DeleteObject, hRgn

			;Mov Eax, FrameDelay
			;Mul Eax, 10
   	    	;Invoke SetTimer, hWnd, IDT_TIME1, 100, NULL
        .ElseIf wParam == (BN_CLICKED + IDC_ANIMTEXTOFF)
	  		Invoke GetDlgItem, hWnd, IDC_OPEN
			Invoke EnableWindow, Eax, TRUE
	  		Invoke GetDlgItem, hWnd, IDC_ANIMTEXTOFF
			Invoke EnableWindow, Eax, FALSE
	  		Invoke GetDlgItem, hWnd, IDC_ANIMTEXT
			Invoke EnableWindow, Eax, TRUE
	  		Invoke GetDlgItem, hWnd, IDC_Next
			Invoke EnableWindow, Eax, TRUE
	  		Invoke GetDlgItem, hWnd, IDC_Prev
			Invoke EnableWindow, Eax, TRUE
   	    	;Invoke KillTimer, hWnd, IDT_TIME1
        .ElseIf wParam == (BN_CLICKED + IDC_PLUS)
        	Invoke Plus, hWnd
        .ElseIf wParam == (BN_CLICKED + IDC_MINUS)
        	Invoke Minus, hWnd
        .ElseIf wParam == (BN_CLICKED + IDC_EXIT)
        	Invoke DestroyWindow, hWnd
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
			  		Invoke GetDlgItem, hWnd, IDC_PLUS
					Invoke EnableWindow, Eax, FALSE
			  		Invoke GetDlgItem, hWnd, IDC_MINUS
					Invoke EnableWindow, Eax, FALSE
			  		Invoke GetDlgItem, hWnd, IDC_ANIMTEXT
					Invoke EnableWindow, Eax, TRUE
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
			  		Invoke GetDlgItem, hWnd, IDC_ANIMTEXT
					Invoke EnableWindow, Eax, TRUE

					Invoke ImageSelectActiveFrame, image, nFrame
					Invoke DlgSetText, hWnd, IDC_nFrame, Addr CurrentFrame, nFrame
					Invoke DlgSetText, hWnd, IDC_Delay, Addr FormatTime, FrameDelay
					Invoke DlgSetText, hWnd, IDC_Dimensi, Addr FormatDimensi, JmlFormatGbr
					Invoke DlgSetText, hWnd, IDC_Frame, Addr FormatFrame, JmlFrame
				.EndIf

		  		Invoke GetDlgItem, hWnd, IDC_PLUS
				Invoke EnableWindow, Eax, TRUE
		  		Invoke GetDlgItem, hWnd, IDC_MINUS
				Invoke EnableWindow, Eax, TRUE

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
	;==================WM_TIMER============================
	.ElseIf uMsg == WM_TIMER
		;WM_TIMER
		;wTimerID = wParam ;            // timer identifier
		;tmprc = (TIMERPROC *) lParam ; // address of timer callback
		.If wParam == IDT_TIME1
			Invoke SendMessage, hWnd, WM_COMMAND, (BN_CLICKED + IDC_Next), NULL
	    .EndIf
		Xor Eax, Eax
		Ret
	;==================WM_LBUTTONDOWN======================
 	.ElseIf uMsg == WM_LBUTTONDOWN
        Invoke SendMessage, hWnd, WM_NCLBUTTONDOWN, HTCAPTION, NULL
		Xor Eax, Eax
		Ret
	;==================WM_CLOSE============================
	.ElseIf uMsg == WM_CLOSE
    	Invoke KillTimer, hWnd, IDT_TIME1
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
;    	Invoke SetWindowLong, hStaticCtl, GWL_WNDPROC, Addr hMeStaticProc
;    	Mov hOriginStaticProc, Eax
;		Ret
;StaticControl EndP

;hMeStaticProc Proc Private Uses Ebx Edi Esi hCtl:HWND, uMsg:ULONG, wParam:WPARAM, lParam:LPARAM
;	.If uMsg == WM_LBUTTONDOWN
;    	    Invoke SendMessage, hCtl, WM_NCLBUTTONDOWN, HTCAPTION, NULL
;    .ElseIf uMsg == WM_RBUTTONDOWN
;		   	Invoke MessageBeep, -1
;    .EndIf
;    Invoke CallWindowProc, hOriginStaticProc, hCtl, uMsg, wParam, lParam
;	Ret
;hMeStaticProc EndP

Plus Proc hWnd:HWND
	Local rc:RECT
	Inc Angka
	Mov Eax, AngkaMAX
	Dec Eax
	.If Angka > Eax
		Mov Angka, 0
	.EndIf
	Invoke DlgSetText, hWnd, IDC_ANGKA, Addr AngkaFormat, Angka
	Invoke GetClientRect, hStaticImg, Addr rc
	Mov Eax, Angka
	Add Eax, 10
	Invoke SetWindowPos, hStaticImg, NULL, HWND_BOTTOM, Eax, rc.right, rc.bottom, SWP_SHOWWINDOW
	Invoke DlgSetImage, hWnd, IDC_IMAGE1, hbitmap
	Ret
Plus EndP
Minus Proc hWnd:HWND
	Local rc:RECT
    Dec Angka
    Mov Eax, AngkaMAX
    Dec Eax
    .If Angka > Eax
    	Mov Angka, Eax
    .EndIf
	Invoke DlgSetText, hWnd, IDC_ANGKA, Addr AngkaFormat, Angka
	Invoke GetClientRect, hStaticImg, Addr rc
	Mov Eax, Angka
	Sub Eax, 10
	Invoke SetWindowPos, hStaticImg, NULL, HWND_BOTTOM, Eax, rc.right, rc.bottom, SWP_SHOWWINDOW
	Invoke DlgSetImage, hWnd, IDC_IMAGE1, hbitmap
	Ret
Minus EndP
RunText Proc hWin:DWord, movit:DWord
    Local hOld:DWord, rc:RECT, hDC:DWord
    Local memDC:DWord, hBmp:HBITMAP, hBmpOld:HBITMAP, bmp:BITMAP, hRgn:HRGN, hRgnOld:HRGN
    Local var1:DWord
    Local var2:DWord
    Local var3:DWord
    Local bmScreen:BITMAP, hdcScreen:HDC, hdcCompatible:HDC, hbmScreen:HBITMAP, hbmScreenOld:HBITMAP

    Invoke GetClientRect, hWin, Addr rc
	Invoke GetDC, hWin
	Mov hDC, Eax
    Invoke CreateCompatibleDC, hDC
    Mov memDC, Eax
    Invoke CreateCompatibleBitmap, hDC, rc.right, rc.bottom
    Mov hBmp, Eax
    Invoke SelectObject, memDC, hBmp
    Mov hBmpOld, Eax
    Invoke GetObject, hBmp, SizeOf bmp, Addr bmp
  	Invoke BitBlt, memDC, 0, 0, bmp.bmWidth, bmp.bmHeight, hDC, 0, 0, SRCCOPY

    ; Bitmap bayangan utk membuat duplikat BMP di belakangnya ===============
	Invoke GetDC, NULL
	Mov hdcScreen, Eax
	Invoke CreateCompatibleDC, hdcScreen
	Mov hdcCompatible, Eax
    Mov Eax, bmp.bmWidth
    Shl Eax, 1
	Invoke CreateCompatibleBitmap, hdcScreen, Eax, bmp.bmHeight
	Mov hbmScreen, Eax
	Invoke SelectObject, hdcCompatible, hbmScreen
	Mov hbmScreenOld, Eax
    Invoke GetObject, hbmScreen, SizeOf bmScreen, Addr bmScreen
	;data bitmap I target
  	Invoke BitBlt, hdcCompatible, 0, 0, bmp.bmWidth, bmp.bmHeight, memDC, 0, 0, SRCCOPY
	;data bitmap II isi sama dgn yg Bitmap I
    Mov Eax, bmp.bmWidth
    Sub Eax, 1
  	Invoke BitBlt, hdcCompatible, Eax, 0, bmp.bmWidth, bmp.bmHeight, memDC, 0, 0, SRCCOPY
	; Device tidak digunakan lagi
    Invoke ReleaseDC, NULL, hdcScreen

    .If movit == FALSE
    	;Invoke CreateRectRgn, 0, 0, bmp.bmWidth, bmp.bmHeight
 		Invoke CreateRoundRectRgn, rc.left, rc.top, rc.right, rc.bottom, 5, 5
 		;Invoke CreateRoundRectRgn, 0, 0, rc.right, 20, 5, 5
    	Mov hRgn, Eax
		Invoke SetWindowRgn, hWin, hRgn, TRUE
    	;Invoke PaintRgn, hDC, hRgn
    	;Invoke SelectObject, hDC, hRgn
    	;Mov hRgnOld, Eax
    	;Invoke BitBlt, hDC, 10, 10, bmp.bmWidth, bmp.bmHeight, hdcCompatible, 0, 0, SRCCOPY
    	;Invoke SelectObject, hDC, hRgnOld
    	Invoke DeleteObject, hRgn
    .Else
    	Mov var3, 0
	    .While var3 < 1     ;<< set the number of times image is looped
      		Mov var1, 0
			Mov Ecx, bmp.bmWidth
    	  	.While var1 < Ecx ;<<  Bitmap width
    	  		Push Ecx
        		Invoke BitBlt, hDC, 0, 0, bmp.bmWidth, bmp.bmHeight, hdcCompatible, var1, 0, SRCCOPY
        		Invoke GetTickCount
        		Mov var2, Eax
        		Add var2, 10    ; nominal milliseconds delay
        		.While Eax < var2
	   					Invoke GetTickCount
        		.EndW
        		Pop Ecx
       			Inc var1
      		.EndW
	    	Inc var3
    	.EndW
    .EndIf
    Invoke SelectObject, hdcCompatible, hbmScreenOld
    Invoke DeleteObject, hbmScreen
    Invoke DeleteDC, hdcCompatible
    Invoke SelectObject, memDC, hBmpOld
    Invoke DeleteObject, hBmp
    Invoke DeleteDC, memDC
    Invoke ReleaseDC, hWin, hDC
    Ret
RunText EndP

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

;WM_CTLCOLORBTN
;hdcButton = (HDC) wParam;   // handle of button display context
;hwndButton = (HWND) lParam; // handle of button
;Value Element colored
;COLOR_BTNFACE	Button faces.
;COLOR_BTNHIGHLIGHT	Highlight area (the top and left edges) of a button.
;COLOR_BTNSHADOW	Shadow area (the bottom and right edges) of a button.
;COLOR_BTNTEXT	Regular (nongrayed) text in buttons.
;COLOR_GRAYTEXT	Disabled (gray) text in buttons. This color is set to 0 if the current display driver does not support a solid gray color.
;COLOR_WINDOW	Window backgrounds.
;COLOR_WINDOWFRAME	Window frames.
;COLOR_WINDOWTEXT	Text in windows.
;LRESULT APIENTRY OwnDrawProc (hDlg, message, wParam, lParam)
;HWND hDlg;      // window handle of dialog box 
;UINT message;   // type of message 
;UINT wParam;    // message-specific information 
;LONG lParam; 
;{ 
;    HDC hdcMem; 
;    LPDRAWITEMSTRUCT lpdis; 
;    switch (message) { 
;        case WM_INITDIALOG:
;            // hinst, hbm1 and hbm2 are defined globally. 
;            hbm1 = LoadBitmap((HANDLE) hinst, "OwnBit1");
;            hbm2 = LoadBitmap((HANDLE) hinst, "OwnBit2"); 
;            return TRUE; 
;        case WM_DRAWITEM: 
;            lpdis = (LPDRAWITEMSTRUCT) lParam;
;            hdcMem = CreateCompatibleDC(lpdis->hDC); 
;            if (lpdis->itemState & ODS_SELECTED)  // if selected 
;                SelectObject(hdcMem, hbm2);
;            else 
;                SelectObject(hdcMem, hbm1); 
;            // Destination 
;            StretchBlt(
;                lpdis->hDC,         // destination DC 
;                lpdis->rcItem.left, // x upper left 
;                lpdis->rcItem.top,  // y upper left 
;                // The next two lines specify the width and 
;                // height.
;                lpdis->rcItem.right - lpdis->rcItem.left, 
;                lpdis->rcItem.bottom - lpdis->rcItem.top, 
;                hdcMem,    // source device context 
;                0, 0,      // x and y upper left 
;                32,        // source bitmap width 
;                32,        // source bitmap height 
;                SRCCOPY);  // raster operation 
;            DeleteDC(hdcMem);
;            return TRUE;
;        case WM_COMMAND: 
;            if (wParam == IDOK
;                || wParam == IDCANCEL) { 
;                EndDialog(hDlg, TRUE); 
;                return TRUE; 
;            } 
;            if (HIWORD(wParam) == BN_CLICKED) { 
;                switch (LOWORD(wParam)) { 
;                    case IDB_OWNERDRAW: 
;                    . 
;                    . // application-defined processing

;                    . 
; 
;                    break; 
;                } 
;            } 
;            break; 
; 
;        case WM_DESTROY: 
;            DeleteObject(hbm1);  // delete bitmaps 
;            DeleteObject(hbm2); 
; 
;            break; 
; 
;    } 
;    return FALSE; 
;        UNREFERENCED_PARAMETER(lParam); 
;} 


;ELSE IF (message == WM_DRAWITEM) {
;    LPDRAWITEMSTRUCT pDIS;
;    pDIS = (LPDRAWITEMSTRUCT)lParam;
;    RECT rc;

;    SetTextColor(pDIS->hDC, RGB(200,10,60));
;    SelectObject(pDIS->hDC, (HPEN)GetStockObject(NULL_PEN));
;    SelectObject(pDIS->hDC, (HBRUSH)GetStockObject(NULL_BRUSH));
;    SetBkMode(pDIS->hDC, TRANSPARENT);
;    // Start Drawing
;    Rectangle(pDIS->hDC, 0, 0, pDIS->rcItem.right+1, pDIS->rcItem.bottom+1);
;    DrawText(pDIS->hDC, "teststring", 10, &pDIS->rcItem, 0); 

;    return 0;
;}
