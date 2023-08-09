;Object ID
skin5ID 		equ 1000

;Static ID
IDC_TopLft 		equ 1001
IDC_TopRgt 		equ 1002
IDC_BotLft 		equ 1003
IDC_BotRgt 		equ 1004
IDC_TopFrame 	equ 1005
IDC_LeftFrame 	equ 1006
IDC_BottomFrame equ 1007
IDC_RightFrame 	equ 1008
IDC_WndCaption 	equ 1009

;Resource ID
MaskSkinbmp     equ 100
Skinbmp         equ 101

;Class Name
CStr szskin5,  "szskin5"

Object skin5, skin5ID, SdiApp
  	RedefineMethod    	Done
  	RedefineMethod    	Init           
  	StaticMethod      	Startup

  	VirtualMethod 		DlgSetImage, 		dword, Handle

  	VirtualEvent      	OnCreate,       	WM_CREATE
	VirtualEvent      	OnPaint,     	    WM_PAINT
	VirtualEvent      	OnSize,     	    WM_SIZE
  	VirtualEvent      	OnKeydown,  		WM_KEYDOWN  
	VirtualEvent      	OnGetMinMaxInfo,  	WM_GETMINMAXINFO
	VirtualEvent      	OnNclbuttondblclk,  WM_NCLBUTTONDBLCLK
  	;VirtualEvent      	OnLButtondown,  	WM_LBUTTONDOWN  
	VirtualEvent      	OnNchittest,  		WM_NCHITTEST  

	DefineVariable 		rc,					RECT,		{}
	
	DefineVariable		hBmp, 	 			Handle, 	0
	DefineVariable		hdcBmp,             Handle,     0
	DefineVariable		hOldBmp,            Handle,     0
	DefineVariable		Bmp, 	 			BITMAP, 	{}
	
	DefineVariable		hMaskBmp, 	 		Handle, 	0
	DefineVariable		hdcMaskBmp,         Handle,     0
	DefineVariable		hOldMaskBmp,        Handle,     0

    DefineVariable		pSkinPaint,         Pointer,    0
    
	DefineVariable		hTopLftBmp, 		Handle, 	0
	DefineVariable		hTopRgtBmp,   	    Handle,     0
	DefineVariable		hBotLftBmp, 		Handle, 	0
	DefineVariable		hBotRgtBmp,   	    Handle,     0

	DefineVariable		hTopFrameBmp,  	    Handle,     0
	DefineVariable		hLeftFrameBmp,      Handle,     0
	DefineVariable		hBottomFrameBmp,    Handle,     0
	DefineVariable		hRightFrameBmp,     Handle,     0

	DefineVariable		hWndCaptionBmp,     Handle,     0

ObjectEnd

;.code
; ——————————————————————————————————————————————————————————————————————————————————————————————————
; Method:    skin5.Done
; Purpose:   Finalizes the skin5 object.
; Arguments: None.
; Return:    Nothing.

Method skin5.Done, uses esi
    SetObject esi
	.If [esi].hBmp
		Invoke DeleteObject, $invoke(SelectObject, [esi].hdcBmp, [esi].hOldBmp)
		Invoke DeleteDC, [esi].hdcBmp
	.EndIf
	.If [esi].hMaskBmp
		Invoke DeleteObject, $invoke(SelectObject, [esi].hdcMaskBmp, [esi].hOldMaskBmp)
		Invoke DeleteDC, [esi].hdcMaskBmp
	.EndIf
    
	Invoke DeleteObject, [esi].hTopLftBmp
	Invoke DeleteObject, [esi].hTopRgtBmp
	Invoke DeleteObject, [esi].hBotLftBmp
	Invoke DeleteObject, [esi].hBotRgtBmp

	Invoke DeleteObject, [esi].hTopFrameBmp
	Invoke DeleteObject, [esi].hLeftFrameBmp
	Invoke DeleteObject, [esi].hBottomFrameBmp
	Invoke DeleteObject, [esi].hRightFrameBmp

	Invoke DeleteObject, [esi].hWndCaptionBmp

    Destroy [esi].pSkinPaint
    ACall esi.Done
MethodEnd NONE

; ——————————————————————————————————————————————————————————————————————————————————————————————————
; Method:    skin5.Init
; Purpose:   Initializes the skin5 object.
; Arguments: Arg1: Pointer to an owner.
;            Arg2: Parent window Handle.
;            Arg3: Pointer to a resource name.
;            Arg4: X position
;            Arg5: Y position
;            Arg6: Width
;            Arg7: Height
;            Arg8: Control ID
; Return:    Nothing.

Method skin5.Init, uses esi
    LOCAL hdc:Handle

    SetObject esi                                       ;esi = This Object Instance
    ACall esi.Init
    
    ; ==================
    ; Master Skin Bitmap    
   	Mov [esi].hBmp, $invoke(LoadBitmap, hInstance, Skinbmp)
   	Mov hdc, $invoke(GetDC, 0)
   	Mov [esi].hdcBmp, $invoke(CreateCompatibleDC, hdc)
   	invoke ReleaseDC, 0, hdc
   	Mov [esi].hOldBmp, $invoke(SelectObject, [esi].hdcBmp, [esi].hBmp)
    invoke GetObject,[esi].hBmp,sizeof BITMAP, addr [esi].Bmp
    ; ================
    ; Mask Skin Bitmap    
   	Mov [esi].hMaskBmp, $invoke(LoadBitmap, hInstance, MaskSkinbmp)
   	Mov [esi].hdcMaskBmp, $invoke(CreateCompatibleDC, [esi].hdcBmp)
   	Mov [esi].hOldMaskBmp, $invoke(SelectObject, [esi].hdcMaskBmp, [esi].hMaskBmp)
    ; ================
    ; init size window
	m2m [esi].rc.right, [esi].Bmp.bmWidth
	m2m [esi].rc.bottom, [esi].Bmp.bmHeight
	;Centering Display
	invoke GetSystemMetrics, SM_CXSCREEN
	Invoke TopXY, [esi].rc.right, Eax
	Mov [esi].rc.left, Eax
	invoke GetSystemMetrics, SM_CYSCREEN
	Invoke TopXY, [esi].rc.bottom, Eax
	Mov [esi].rc.top, Eax
    ; ================
    ; init SkinData
    mov [esi].pSkinPaint, $New(SkinPaint, Init, addr [esi].rc, addr [esi].Bmp, [esi].hdcMaskBmp, [esi].hdcBmp)
    ; ================
    ; create main window
	Invoke CreateWindowEx, 0, Addr szskin5, NULL, WS_POPUP, 
	0, 0, 0, 0,
	NULL, NULL, hInstance, esi
MethodEnd NONE

; ——————————————————————————————————————————————————————————————————————————————————————————————————
; Method:    skin5.OnCreate
; Purpose:   Event procedure for WM_CREATE message.
; Arguments: Arg1: First message parameter.
;            Arg2: Second message parameter.
; Return:    Zero to continue creation of the window, else -1.

Method skin5.OnCreate, uses esi, wParam:dword, lParam:dword

    SetObject esi

	;Set Window Size & show window
	Invoke SetWindowPos, [esi].hWnd, HWND_TOP, [esi].rc.left, [esi].rc.top, [esi].rc.right, [esi].rc.bottom, SWP_SHOWWINDOW

    ;createstatic window
    @invoke CreateWindowEx,WS_EX_LEFT,"STATIC",NULL, \
            (WS_CHILD or WS_VISIBLE or SS_BITMAP), \
            0,0,50,50,[esi].hWnd,IDC_TopLft,hInstance,NULL
	OCall [esi].pSkinPaint::SkinPaint.AnyCreateSkinObject, TOPLEFT,  OBJTYPEBITMAP,[esi].hdcBmp, addr [esi].hTopLftBmp 
	OCall esi.DlgSetImage, IDC_TopLft, [esi].hTopLftBmp

    @invoke CreateWindowEx,WS_EX_LEFT,"STATIC",NULL, \
            (WS_CHILD or WS_VISIBLE or SS_BITMAP), \
            0,0,50,50,[esi].hWnd,IDC_TopRgt,hInstance,NULL
    OCall [esi].pSkinPaint::SkinPaint.AnyCreateSkinObject, TOPRIGHT, OBJTYPEBITMAP,[esi].hdcBmp, addr [esi].hTopRgtBmp  
	OCall esi.DlgSetImage, IDC_TopRgt, [esi].hTopRgtBmp

    @invoke CreateWindowEx,WS_EX_LEFT,"STATIC",NULL, \
            (WS_CHILD or WS_VISIBLE or SS_BITMAP), \
            0,0,50,50,[esi].hWnd,IDC_BotLft,hInstance,NULL
	OCall [esi].pSkinPaint::SkinPaint.AnyCreateSkinObject, BOTTOMLEFT,  OBJTYPEBITMAP,[esi].hdcBmp, addr [esi].hBotLftBmp 
	OCall esi.DlgSetImage, IDC_BotLft, [esi].hBotLftBmp

    @invoke CreateWindowEx,WS_EX_LEFT,"STATIC",NULL, \
            (WS_CHILD or WS_VISIBLE or SS_BITMAP), \
            0,0,50,50,[esi].hWnd,IDC_BotRgt,hInstance,NULL
    OCall [esi].pSkinPaint::SkinPaint.AnyCreateSkinObject, BOTTOMRIGHT, OBJTYPEBITMAP,[esi].hdcBmp, addr [esi].hBotRgtBmp  
	OCall esi.DlgSetImage, IDC_BotRgt, [esi].hBotRgtBmp

    @invoke CreateWindowEx,WS_EX_LEFT,"STATIC",NULL, \
            (WS_CHILD or WS_VISIBLE or SS_BITMAP), \
            0,0,1,25,[esi].hWnd,IDC_TopFrame,hInstance,NULL
    OCall [esi].pSkinPaint::SkinPaint.AnyCreateSkinObject, TOPFRAME, OBJTYPEBITMAP,[esi].hdcBmp, addr [esi].hTopFrameBmp  
	OCall esi.DlgSetImage, IDC_TopFrame, [esi].hTopFrameBmp

    @invoke CreateWindowEx,WS_EX_LEFT,"STATIC",NULL, \
            (WS_CHILD or WS_VISIBLE or SS_BITMAP), \
            0,0,1,25,[esi].hWnd,IDC_BottomFrame,hInstance,NULL
    OCall [esi].pSkinPaint::SkinPaint.AnyCreateSkinObject, BOTTOMFRAME, OBJTYPEBITMAP,[esi].hdcBmp, addr [esi].hBottomFrameBmp  
	OCall esi.DlgSetImage, IDC_BottomFrame, [esi].hBottomFrameBmp

    @invoke CreateWindowEx,WS_EX_LEFT,"STATIC",NULL, \
            (WS_CHILD or WS_VISIBLE or SS_BITMAP), \
            0,0,25,1,[esi].hWnd,IDC_LeftFrame,hInstance,NULL
    @invoke CreateWindowEx,WS_EX_LEFT,"STATIC",NULL, \
            (WS_CHILD or WS_VISIBLE or SS_BITMAP), \
            0,0,25,1,[esi].hWnd,IDC_RightFrame,hInstance,NULL
            
    @invoke CreateWindowEx,WS_EX_LEFT,"STATIC",NULL, \
            (WS_CHILD or WS_VISIBLE or SS_BITMAP), \
            0,0,1,25,[esi].hWnd,IDC_WndCaption,hInstance,NULL
    OCall [esi].pSkinPaint::SkinPaint.AnyCreateSkinObject, WNDCAPTION, OBJTYPEBITMAP,[esi].hdcBmp, addr [esi].hWndCaptionBmp  
	OCall esi.DlgSetImage, IDC_WndCaption, [esi].hWndCaptionBmp

MethodEnd eax

; ——————————————————————————————————————————————————————————————————————————————————————————————————
; Method:    skin5.OnSize
; Purpose:   
; Arguments: Arg1: 
;            Arg2: 
;            Arg3: 
;            Arg4: 
; Return:    
; Note:      

Method skin5.OnSize, uses esi, wParam:dword, lParam:dword
    
    SetObject esi
    ;=====================================
	; SetUp Dynamic Rect of structure sSkinData (Point,Rect & Size)
    invoke GetClientRect,[esi].hWnd, addr [esi].rc
    ;OCall [esi].pSkinPaint::SkinPaint.InitDynamicObj, addr [esi].rc ; jika tdk menggunakan regioan
    OCall [esi].pSkinPaint::SkinPaint.DynamicPaintInit, [esi].hWnd, addr [esi].rc , TRUE ;dynamic 

    OCall [esi].pSkinPaint::SkinPaint.AnyCreateSkinObject, LEFTFRAME, OBJTYPEBITMAPCURSIZEFRAME_TILEMODE,[esi].hdcBmp, addr [esi].hLeftFrameBmp  
    OCall [esi].pSkinPaint::SkinPaint.AnyCreateSkinObject, RIGHTFRAME, OBJTYPEBITMAPCURSIZEFRAME_TILEMODE,[esi].hdcBmp, addr [esi].hRightFrameBmp  

	OCall esi.DlgSetImage, IDC_LeftFrame, [esi].hLeftFrameBmp
	OCall esi.DlgSetImage, IDC_RightFrame, [esi].hRightFrameBmp

    ;=======
	; CORNER 
    invoke GetDlgItem, [esi].hWnd, IDC_TopRgt
    mov ecx, [esi].pSkinPaint
    invoke SetWindowPos,eax,HWND_BOTTOM,
    [ecx].SkinPaint.sSkinData.TopRgt.CurPt.x, [ecx].SkinData.sSkinData.TopRgt.CurPt.y,
    NULL,NULL,SWP_NOSIZE

    invoke GetDlgItem, [esi].hWnd, IDC_BotLft
    mov ecx, [esi].pSkinPaint
    invoke SetWindowPos,eax,HWND_BOTTOM,
    [ecx].SkinPaint.sSkinData.BotLft.CurPt.x, [ecx].SkinPaint.sSkinData.BotLft.CurPt.y,
    NULL,NULL,SWP_NOSIZE

    invoke GetDlgItem, [esi].hWnd, IDC_BotRgt
    mov ecx, [esi].pSkinPaint
    invoke SetWindowPos,eax,HWND_BOTTOM,
    [ecx].SkinPaint.sSkinData.BotRgt.CurPt.x, [ecx].SkinPaint.sSkinData.BotRgt.CurPt.y,
    NULL,NULL,SWP_NOSIZE
    
    ;======
	; FRAME 
    invoke GetDlgItem, [esi].hWnd, IDC_TopFrame
    mov ecx, [esi].pSkinPaint
    invoke SetWindowPos,eax,HWND_BOTTOM,
    [ecx].SkinPaint.sSkinData.TopFrame.ObjPt.x, [ecx].SkinPaint.sSkinData.TopFrame.ObjPt.y,
    [ecx].SkinPaint.sSkinData.TopFrame.CurSize.x, [ecx].SkinPaint.sSkinData.TopFrame.CurSize.y,SWP_SHOWWINDOW

    invoke GetDlgItem, [esi].hWnd, IDC_LeftFrame
    mov ecx, [esi].pSkinPaint
    invoke SetWindowPos,eax,HWND_BOTTOM,
    [ecx].SkinPaint.sSkinData.LeftFrame.ObjPt.x, [ecx].SkinPaint.sSkinData.LeftFrame.ObjPt.y,
    [ecx].SkinPaint.sSkinData.LeftFrame.CurSize.x, [ecx].SkinPaint.sSkinData.LeftFrame.CurSize.y,SWP_SHOWWINDOW

    invoke GetDlgItem, [esi].hWnd, IDC_BottomFrame
    mov ecx, [esi].pSkinPaint
    invoke SetWindowPos,eax,HWND_BOTTOM,
    [ecx].SkinPaint.sSkinData.BottomFrame.CurPt.x, [ecx].SkinPaint.sSkinData.BottomFrame.CurPt.y,
    [ecx].SkinPaint.sSkinData.BottomFrame.CurSize.x, [ecx].SkinPaint.sSkinData.BottomFrame.CurSize.y,SWP_SHOWWINDOW

    invoke GetDlgItem, [esi].hWnd, IDC_RightFrame
    mov ecx, [esi].pSkinPaint
    invoke SetWindowPos,eax,HWND_BOTTOM,
    [ecx].SkinPaint.sSkinData.RightFrame.CurPt.x, [ecx].SkinPaint.sSkinData.RightFrame.CurPt.y,
    [ecx].SkinPaint.sSkinData.RightFrame.CurSize.x, [ecx].SkinPaint.sSkinData.RightFrame.CurSize.y,SWP_SHOWWINDOW

    ;===========
	; WNDCAPTION 
    invoke GetDlgItem, [esi].hWnd, IDC_WndCaption
    mov ecx, [esi].pSkinPaint
    invoke SetWindowPos,eax,HWND_BOTTOM,
    [ecx].SkinPaint.sSkinData.WndCaption.ObjPt.x, [ecx].SkinPaint.sSkinData.WndCaption.ObjPt.y,
    [ecx].SkinPaint.sSkinData.WndCaption.CurSize.x, [ecx].SkinPaint.sSkinData.WndCaption.CurSize.y,SWP_SHOWWINDOW

    ;invoke ValidateRgn, [esi].hWnd, NULL
MethodEnd

; ——————————————————————————————————————————————————————————————————————————————————————————————————
; Method:    skin5.OnPaint
; Purpose:   
; Arguments: Arg1: 
;            Arg2: 
; Return:    
; Note:      

Method skin5.OnPaint, uses esi, Arg1:dword, Arg2:dword
    LOCAL ps:PAINTSTRUCT
    SetObject esi
    invoke BeginPaint,[esi].hWnd, addr ps
    invoke EndPaint, [esi].hWnd, addr ps
MethodEnd



; ——————————————————————————————————————————————————————————————————————————————————————————————————
; Method:    skin5.DlgSetImage
; Purpose:   
; Arguments: Arg1: 
;            Arg2: 
; Return:    
; Note:      

Method skin5.DlgSetImage, uses esi, wndID:dword, hbmp:Handle
	LOCAL  hPictureBox:Handle, rc:RECT

    SetObject esi
	Mov hPictureBox, $invoke(GetDlgItem, [esi].hWnd, wndID)
	Invoke GetClientRect, hPictureBox, Addr rc        				; fungsi ini ada jika static dlm keadaan HALLOW BRUSH
	Invoke MapWindowPoints, hPictureBox, [esi].hWnd, Addr rc, 2 	; angka 2 harus di tulis, sebab bukan POINT tetapi RECT
	Invoke InvalidateRect, [esi].hWnd, Addr rc, TRUE 				; fungsi ini ada jika static dlm keadaan HALLOW BRUSH
    Invoke SendMessage, hPictureBox, STM_SETIMAGE, IMAGE_BITMAP, hbmp
MethodEnd


; ——————————————————————————————————————————————————————————————————————————————————————————————————
; Method:    Icz_Demo8.OnCommand
; Purpose:   Event procedure for WM_COMMAND message.
; Arguments: Arg1: First message parameter.
;            Arg2: Second message parameter.
; Return:    Zero if handled.

Method skin5.OnKeydown, uses esi, wParam:dword, lParam:dword
    SetObject esi
	;Exit Window
	.If wParam == VK_ESCAPE
		Invoke DestroyWindow, [esi].hWnd
	.EndIf 
    xor eax, eax
MethodEnd 

; ——————————————————————————————————————————————————————————————————————————————————————————————————
; Method:    Icz_Demo8.OnCommand
; Purpose:   Event procedure for WM_COMMAND message.
; Arguments: Arg1: First message parameter.
;            Arg2: Second message parameter.
; Return:    Zero if handled.

;Method skin5.OnLButtondown, uses esi, wParam:dword, lParam:dword
;    SetObject esi
;    Invoke SendMessage, [esi].hWnd, WM_NCLBUTTONDOWN, HTCAPTION, NULL
;    xor eax, eax
;MethodEnd 

; ——————————————————————————————————————————————————————————————————————————————————————————————————
; Method:    skin5.OnNclbuttondblclk
; Purpose:   
; Arguments: Arg1: 
;            Arg2: 
; Return:    
; Note:      

Method skin5.OnNclbuttondblclk, uses esi, wParam:dword, lParam:dword
    local Pnt:POINT

    SetObject esi

    movzx eax, $LoWord(lParam)
    mov Pnt.x, eax
    movzx eax, $HiWord(lParam)
    mov Pnt.y, eax
    invoke ScreenToClient,[esi].hWnd,ADDR Pnt  ; convert to client coordinates
    
    ;Setup pointer to ebx
    mov ebx, [esi].pSkinPaint
    .if $OCall(ebx::SkinPaint.HitPoint,HTCAPTION,Pnt.x, Pnt.y) 
		.if $invoke(IsZoomed,[esi].hWnd)
			invoke ShowWindow,[esi].hWnd,SW_SHOWNORMAL            ; yes
		.else
			invoke ShowWindow,[esi].hWnd,SW_SHOWMAXIMIZED         ; no
		.endif
   	.endif 
    
MethodEnd

; ——————————————————————————————————————————————————————————————————————————————————————————————————
; Method:    skin5.OnGetMinMaxInfo
; Purpose:   
; Arguments: Arg1: 
;            Arg2: 
; Return:    
; Note:      

Method skin5.OnGetMinMaxInfo, uses esi, wParam:dword, lParam:dword
    SetObject esi
	;using for virtual structure
	Mov Ebx, lParam
	Assume Ebx:Ptr MINMAXINFO
	m2m [Ebx].ptMinTrackSize.x, [esi].Bmp.bmWidth
	m2m [Ebx].ptMinTrackSize.y, [esi].Bmp.bmHeight
	Assume Ebx:nothing
    
MethodEnd

; ——————————————————————————————————————————————————————————————————————————————————————————————————
; Method:    skin5.OnNchittest
; Purpose:   
; Arguments: Arg1: 
;            Arg2: 
; Return:    
; Note:      

Method skin5.OnNchittest, uses esi, wParam:dword, lParam:dword

    local Pnt:POINT, Rct:RECT

    SetObject esi

    movzx eax, $LoWord(lParam)
    mov Pnt.x, eax
    movzx eax, $HiWord(lParam)
    mov Pnt.y, eax
    invoke ScreenToClient,[esi].hWnd,ADDR Pnt  ; convert to client coordinates
    
    ;Setup pointer to ebx
    mov ebx, [esi].pSkinPaint
    
    .if $OCall(ebx::SkinPaint.HitPoint,HTTOPLEFT,Pnt.x, Pnt.y)
        ;DbgWarning "HTTOPLEFT"
		mov eax, HTTOPLEFT
    .else
      .if $OCall(ebx::SkinPaint.HitPoint,HTTOPRIGHT,Pnt.x, Pnt.y) 
          ;DbgWarning "HTTOPRIGHT"
	      mov eax, HTTOPRIGHT
      .else
         .if $OCall(ebx::SkinPaint.HitPoint,HTBOTTOMLEFT,Pnt.x, Pnt.y)
             ;DbgWarning "HTBOTTOMLEFT"
		     mov eax, HTBOTTOMLEFT
         .else
            .if $OCall(ebx::SkinPaint.HitPoint,HTBOTTOMRIGHT,Pnt.x, Pnt.y) 
                ;DbgWarning "HTBOTTOMRIGHT"
		        mov eax, HTBOTTOMRIGHT
            .else
                .if $OCall(ebx::SkinPaint.HitPoint,HTTOP,Pnt.x, Pnt.y) 
                    ;DbgWarning "HTTOP"
                    mov eax, HTTOP
                .else
		            .if $OCall(ebx::SkinPaint.HitPoint,HTLEFT,Pnt.x, Pnt.y)  
		                ;DbgWarning "HTLEFT"
		                mov eax, HTLEFT
		            .else
			            .if $OCall(ebx::SkinPaint.HitPoint,HTRIGHT,Pnt.x, Pnt.y) 
			                ;DbgWarning "HTRIGHT"
			                mov eax, HTRIGHT
			            .else
				            .if $OCall(ebx::SkinPaint.HitPoint,HTBOTTOM,Pnt.x, Pnt.y) 
				                ;DbgWarning "HTBOTTOM"
				                mov eax, HTBOTTOM
				            .else
					            .if $OCall(ebx::SkinPaint.HitPoint,HTCAPTION,Pnt.x, Pnt.y) 
					                ;DbgWarning "HTCAPTION"
					                ;invoke SetForegroundWindow, [esi].hWnd
					                ;invoke SetFocus, [esi].hWnd
					                mov eax, HTCAPTION
				            	.endif 
			            	.endif 
		            	.endif 
	            	.endif 
            	.endif 
            .endif
         .endif
       .endif
    .endif

MethodEnd

; ——————————————————————————————————————————————————————————————————————————————————————————————————
; Method:    skin5.Startup
; Purpose:   Registers the skin5 object with the OS.
; Arguments: None.
; Return:    Nothing.

Method skin5.Startup
    local WC:WNDCLASSEX

    mov WC.cbSize, sizeof WNDCLASSEX
    mov WC.style, 0
    m2m WC.lpfnWndProc, $MethodAddr(skin5.WndProc), edx
    mov WC.cbClsExtra, 0
    mov WC.cbWndExtra, 0
    m2m WC.hInstance, hInstance, edx
    mov WC.hbrBackground, (COLOR_BTNFACE + 1)
    mov WC.lpszMenuName, 0
    mov WC.lpszClassName, offset szskin5
    mov WC.hIcon, 0
    mov WC.hCursor, $invoke(LoadCursor, 0, IDC_ARROW)
    mov WC.hIconSm, NULL

    invoke RegisterClassEx, addr WC
MethodEnd NONE

