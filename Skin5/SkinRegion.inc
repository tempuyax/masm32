$GetInc Macro Val:Req
    ;Setup
    inc Val
    ;Done
  EXITM <Val>
ENDM

OBJBITMAP struc
	hObjBmp	   Handle ?
	hOldObjBmp Handle ?
	hdcObjBmp  Handle ?
OBJBITMAP ends

; Object equet
TOPLEFT     	equ 0
TOPRIGHT    	equ 1
BOTTOMLEFT  	equ 2
BOTTOMRIGHT 	equ 3
TOPFRAME    	equ 4
LEFTFRAME   	equ 5
BOTTOMFRAME 	equ 6
RIGHTFRAME  	equ 7
WNDCAPTION  	equ 8

; for static window
OBJTYPEREGION	equ 9
OBJTYPEBITMAP	equ	10
OBJTYPEMASK 	equ	11

; for region dynamic frame
OBJTYPEREGIONMAXSIZEFRAME			equ 12
OBJTYPEREGIONCURSIZEFRAME			equ 13
OBJTYPEREGIONCURSIZEFRAME_TILEMODE 	equ 14

; for bitmap dynamic frame
OBJTYPEBITMAPMAXSIZEFRAME_TILEMODE  equ 15
OBJTYPEMASKMAXSIZEFRAME_TILEMODE  	equ 16
OBJTYPEBITMAPCURSIZEFRAME_TILEMODE  equ 17
OBJTYPEMASKCURSIZEFRAME_TILEMODE  	equ 18

DuplicateBitmap proto :Handle
PartBitmap 		proto :Handle, :dword, :dword, :dword, :dword
PatternBitmap 	proto :Handle, :Handle, :dword, :dword

Object SkinRegion, 939393, SkinData
	RedefineMethod    Done
	RedefineMethod    Init,                 Pointer, Pointer, Pointer, Handle  
	
	VirtualMethod     InitRegionFrame
	VirtualMethod     InitRegionCorner
	VirtualMethod     InitRegionWindow, 	Handle, dword
	VirtualMethod     DynamicInit,          Handle ,Pointer, dword
    VirtualMethod     SetupRegionCorner
    VirtualMethod     SetupRegionFrame

	VirtualMethod     AnyCreateSkinObject,  dword, dword, Handle, Pointer 	
	
	DefineVariable	  hdcMaskBmp,         	Handle,     0  

	DefineVariable	  TopLftRgn,          	Handle,     0  
	DefineVariable	  TopRgtRgn,          	Handle,     0  
	DefineVariable	  BotLftRgn,          	Handle,     0  
	DefineVariable	  BotRgtRgn,          	Handle,     0  

    DefineVariable	  TopRgtCurRgn,    		Handle,     0
    DefineVariable	  BotLftCurRgn,         Handle,     0  
	DefineVariable	  BotRgtCurRgn,        	Handle,     0  

	DefineVariable	  TopFrameRgn,        	Handle,     0       
    DefineVariable	  LeftFrameRgn,       	Handle,     0
    DefineVariable	  BottomFrameRgn,     	Handle,     0
    DefineVariable	  RightFrameRgn,      	Handle,     0

	DefineVariable	  TopFrameRgnBox,      	RECT,       {}       
    DefineVariable	  LeftFrameRgnBox,     	RECT,       {}
    DefineVariable	  BottomFrameRgnBox,   	RECT,       {}
    DefineVariable	  RightFrameRgnBox,    	RECT,       {}

    DefineVariable	  BottomFrameRgnBoxSize,SIZEL,      {}
    DefineVariable	  RightFrameRgnBoxSize,	SIZEL,      {}

	DefineVariable	  TopFrameCurRgn,      	Handle,     0       
    DefineVariable	  LeftFrameCurRgn,     	Handle,     0
    DefineVariable	  BottomFrameCurRgn,   	Handle,     0
    DefineVariable	  RightFrameCurRgn,    	Handle,     0

    DefineVariable	  hWndRgn,            	Handle,     0
    
ObjectEnd


; ——————————————————————————————————————————————————————————————————————————————————————————————————
; Method:    SkinRegion.Init
; Purpose:   
; Arguments: None.
; Return:    
; Note:      

Method SkinRegion.Init, uses esi, pOwner:Pointer, WndRC:Pointer, ObjBmp:Pointer, hdcMaskBmp:Handle
    SetObject esi
    ACall Init, pOwner, WndRC, ObjBmp

    m2m [esi].hdcMaskBmp, hdcMaskBmp

    OCall esi.SetupRegionCorner
    OCall esi.SetupRegionFrame
MethodEnd

; ——————————————————————————————————————————————————————————————————————————————————————————————————
; Method:    SkinRegion.InitRegionCorner
; Purpose:   
; Arguments: None.
; Return:    
; Note:      

Method SkinRegion.SetupRegionCorner, uses esi
    SetObject esi
    ;create region from mask bitmap
	OCall esi.AnyCreateSkinObject, TOPLEFT, OBJTYPEREGION,[esi].hdcMaskBmp, addr [esi].TopLftRgn 
    OCall esi.AnyCreateSkinObject, TOPRIGHT, OBJTYPEREGION,[esi].hdcMaskBmp, addr [esi].TopRgtRgn  
    OCall esi.AnyCreateSkinObject, BOTTOMLEFT, OBJTYPEREGION,[esi].hdcMaskBmp, addr [esi].BotLftRgn  
    OCall esi.AnyCreateSkinObject, BOTTOMRIGHT, OBJTYPEREGION ,[esi].hdcMaskBmp, addr [esi].BotRgtRgn  
    
    mov [esi].TopRgtCurRgn, $invoke(CreateRectRgn, 0, 0, 0, 0)
    mov [esi].BotLftCurRgn, $invoke(CreateRectRgn, 0, 0, 0, 0)
    mov [esi].BotRgtCurRgn, $invoke(CreateRectRgn, 0, 0, 0, 0)
  
MethodEnd

; ——————————————————————————————————————————————————————————————————————————————————————————————————
; Method:    SkinRegion.SetupRegionFrame
; Purpose:   
; Arguments: None.
; Return:    
; Note:      

Method SkinRegion.SetupRegionFrame, uses esi
    SetObject esi
     ;=============================
	;Membuat Region dari mask FRAME
    ;OCall esi.CrtRegionFromMask, TOPFRAME,[esi].hdcMaskBmp, addr [esi].TopFrameRgn 
    ;OCall esi.CrtRegionFromMask, LEFTFRAME, [esi].hdcMaskBmp, addr [esi].LeftFrameRgn
    ;OCall esi.CrtRegionFromMask, BOTTOMFRAME, [esi].hdcMaskBmp, addr [esi].BottomFrameRgn
    ;OCall esi.CrtRegionFromMask, RIGHTFRAME,[esi].hdcMaskBmp, addr [esi].RightFrameRgn

;    OCall esi.AnyCreateSkinObject, TOPFRAME,OBJTYPEREGIONMAXSIZEFRAME,[esi].hdcMaskBmp, addr [esi].TopFrameRgn 
;    OCall esi.AnyCreateSkinObject, LEFTFRAME, OBJTYPEREGIONMAXSIZEFRAME,[esi].hdcMaskBmp, addr [esi].LeftFrameRgn
;    OCall esi.AnyCreateSkinObject, BOTTOMFRAME, OBJTYPEREGIONMAXSIZEFRAME,[esi].hdcMaskBmp, addr [esi].BottomFrameRgn
;    OCall esi.AnyCreateSkinObject, RIGHTFRAME, OBJTYPEREGIONMAXSIZEFRAME,[esi].hdcMaskBmp, addr [esi].RightFrameRgn

;    OCall esi.AnyCreateSkinObject, TOPFRAME,OBJTYPEREGIONCURSIZEFRAME,[esi].hdcMaskBmp, addr [esi].TopFrameRgn 
;    OCall esi.AnyCreateSkinObject, LEFTFRAME, OBJTYPEREGIONCURSIZEFRAME,[esi].hdcMaskBmp, addr [esi].LeftFrameRgn
;    OCall esi.AnyCreateSkinObject, BOTTOMFRAME, OBJTYPEREGIONCURSIZEFRAME,[esi].hdcMaskBmp, addr [esi].BottomFrameRgn
;    OCall esi.AnyCreateSkinObject, RIGHTFRAME, OBJTYPEREGIONCURSIZEFRAME,[esi].hdcMaskBmp, addr [esi].RightFrameRgn

    mov [esi].TopFrameCurRgn, $invoke(CreateRectRgn, 0, 0, 0, 0)
    mov [esi].LeftFrameCurRgn, $invoke(CreateRectRgn, 0, 0, 0, 0)
    mov [esi].BottomFrameCurRgn, $invoke(CreateRectRgn, 0, 0, 0, 0)
    mov [esi].RightFrameCurRgn, $invoke(CreateRectRgn, 0, 0, 0, 0)

;	;posisi TOP FRAME region base x,0
;    invoke OffsetRgn, [esi].TopFrameRgn,
;    [esi].sSkinData.TopFrame.ObjPt.x,
;	[esi].sSkinData.TopFrame.ObjPt.y
;    invoke CombineRgn, [esi].TopFrameCurRgn, [esi].TopFrameRgn, 0, RGN_COPY
;
;	;posisi LEFT FRAME region base 0, y
;    invoke OffsetRgn, [esi].LeftFrameRgn, 
;    [esi].sSkinData.LeftFrame.ObjPt.x,
;	[esi].sSkinData.LeftFrame.ObjPt.y
;    invoke CombineRgn, [esi].LeftFrameCurRgn, [esi].LeftFrameRgn, 0, RGN_COPY
;
;	;posisi BOTTOM FRAME region base x, y
;    invoke OffsetRgn, [esi].BottomFrameRgn,
;    [esi].sSkinData.BottomFrame.CurPt.x,
;	[esi].sSkinData.BottomFrame.CurPt.y
;    invoke CombineRgn, [esi].BottomFrameCurRgn, [esi].BottomFrameRgn, 0, RGN_COPY
;
;	;posisi RIGHT FRAME region base, x,y
;    invoke OffsetRgn, [esi].RightFrameRgn, 
;    [esi].sSkinData.RightFrame.CurPt.x,
;	[esi].sSkinData.RightFrame.CurPt.y
;    invoke CombineRgn, [esi].RightFrameCurRgn, [esi].RightFrameRgn, 0, RGN_COPY
;
;    invoke GetRgnBox, [esi].TopFrameRgn, addr [esi].TopFrameRgnBox     
;    invoke GetRgnBox, [esi].LeftFrameRgn, addr [esi].LeftFrameRgnBox     
;    invoke GetRgnBox, [esi].BottomFrameRgn, addr [esi].BottomFrameRgnBox     
;    invoke GetRgnBox, [esi].RightFrameRgn, addr [esi].RightFrameRgnBox   
;    
;    mov [esi].BottomFrameRgnBoxSize.y,$SubVal([esi],BottomFrameRgnBox.bottom,BottomFrameRgnBox.top)
;    mov [esi].RightFrameRgnBoxSize.x,$SubVal([esi],RightFrameRgnBox.right,RightFrameRgnBox.left)
    
MethodEnd



; ——————————————————————————————————————————————————————————————————————————————————————————————————
; Method:    SkinRegion.Done
; Purpose:   
; Arguments: None.
; Return:    
; Note:      

Method SkinRegion.Done, uses esi
    SetObject esi
    .if [esi].TopLftRgn 
    	invoke DeleteObject, [esi].TopLftRgn
    .else
	    .if [esi].TopRgtRgn 
    		invoke DeleteObject, [esi].TopRgtRgn
    		invoke DeleteObject, [esi].TopRgtCurRgn
	    .else
		    .if [esi].BotLftRgn 
    			invoke DeleteObject, [esi].BotLftRgn
	    		invoke DeleteObject, [esi].TopRgtCurRgn
		    .else
			    .if [esi].BotRgtRgn 
    				invoke DeleteObject, [esi].BotRgtRgn
		    		invoke DeleteObject, [esi].TopRgtCurRgn
			    .else
				    .if [esi].TopFrameRgn 
					    invoke DeleteObject, [esi].TopFrameRgn
					    invoke DeleteObject, [esi].TopFrameCurRgn
			    	.else
			    		.if [esi].LeftFrameRgn 
    						invoke DeleteObject, [esi].LeftFrameRgn
    						invoke DeleteObject, [esi].LeftFrameCurRgn
			    		.else
			    			.if [esi].BottomFrameRgn 
    							invoke DeleteObject, [esi].BottomFrameRgn
    							invoke DeleteObject, [esi].BottomFrameCurRgn
			    			.else
			    				.if [esi].RightFrameRgn 
    								invoke DeleteObject, [esi].RightFrameRgn
    								invoke DeleteObject, [esi].RightFrameCurRgn
			    				.else
    								.if [esi].hWndRgn
								    	invoke DeleteObject, [esi].hWndRgn
    								.endif
   								.endif
							.endif
						.endif
					.endif
				.endif
			.endif
		.endif
	.endif
    ACall Done
MethodEnd

; ——————————————————————————————————————————————————————————————————————————————————————————————————
; Method:    SkinRegion.DynamicInit
; Purpose:   
; Arguments: None.
; Return:    
; Note:      

Method SkinRegion.DynamicInit, uses esi, hWnd:Handle ,WndRC:Pointer, bRegion:dword
    SetObject esi
    OCall esi.InitDynamicObj, WndRC  			;dynamic 1
    OCall esi.InitRegionFrame        			;dynamic 2
    OCall esi.InitRegionCorner       			;dynamic 3
    OCall esi.InitRegionWindow, hWnd, bRegion 	;dynamic 4

MethodEnd
; ——————————————————————————————————————————————————————————————————————————————————————————————————
; Method:    SkinRegion.InitRegionWindow
; Purpose:   
; Arguments: None.
; Return:    
; Note:      

Method SkinRegion.InitRegionWindow, uses esi, hWnd:Handle, bRegion:dword
    SetObject esi
    mov ebx, $invoke(CreateRectRgnIndirect, addr [esi].sSkinData.WindowRC)

    ;Append all created regions and assign it to the window
    .if [esi].hWndRgn
       invoke DeleteObject,[esi].hWndRgn
    .endif
    invoke CombineRgn, ebx, ebx, [esi].TopLftRgn,         RGN_XOR
    invoke CombineRgn, ebx, ebx, [esi].TopRgtCurRgn,      RGN_XOR
    invoke CombineRgn, ebx, ebx, [esi].BotRgtCurRgn,      RGN_XOR
    invoke CombineRgn, ebx, ebx, [esi].BotLftCurRgn,      RGN_XOR
    invoke CombineRgn, ebx, ebx, [esi].TopFrameCurRgn,    RGN_XOR
    invoke CombineRgn, ebx, ebx, [esi].LeftFrameCurRgn,   RGN_XOR
    invoke CombineRgn, ebx, ebx, [esi].BottomFrameCurRgn, RGN_XOR
    invoke CombineRgn, ebx, ebx, [esi].RightFrameCurRgn,  RGN_XOR
    mov [esi].hWndRgn, ebx
    
    .if bRegion == TRUE
    	invoke SetWindowRgn, hWnd, [esi].hWndRgn, TRUE 
    .endif
        
MethodEnd ebx


; ——————————————————————————————————————————————————————————————————————————————————————————————————
; Method:    SkinRegion.InitRegionFrame
; Purpose:   
; Arguments: None.
; Return:    
; Note:      

Method SkinRegion.InitRegionFrame, uses esi

    SetObject esi
     ;=============================
;    invoke SetRectRgn,[esi].TopFrameCurRgn, 
;    [esi].TopFrameRgnBox.left,
;    [esi].TopFrameRgnBox.top, 
;    $GetInc($AddVal([esi],sSkinData.TopFrame.ObjRect.right,sSkinData.Delta.x)), 
;    [esi].TopFrameRgnBox.bottom 
;
;    invoke SetRectRgn,[esi].LeftFrameCurRgn, 
;    [esi].LeftFrameRgnBox.left,
;    [esi].LeftFrameRgnBox.top, 
;    [esi].LeftFrameRgnBox.right, 
;    $GetInc($AddVal([esi],sSkinData.LeftFrame.ObjRect.bottom,sSkinData.Delta.y))
;
;    invoke SetRectRgn,[esi].BottomFrameCurRgn, 
;    [esi].BottomFrameRgnBox.left,
;    $GetInc($SubVal([esi],sSkinData.BottomFrame.CurRect.bottom,BottomFrameRgnBoxSize.y)), 
;    $GetInc([esi].sSkinData.BottomFrame.CurRect.right), 
;    $GetInc([esi].sSkinData.BottomFrame.CurRect.bottom) 
;
;    invoke SetRectRgn,[esi].RightFrameCurRgn, 
;    $GetInc($SubVal([esi],sSkinData.RightFrame.CurRect.right,RightFrameRgnBoxSize.x)), 
;    [esi].RightFrameRgnBox.top, 
;    $GetInc([esi].sSkinData.RightFrame.CurRect.right), 
;    $GetInc([esi].sSkinData.RightFrame.CurRect.bottom) 

    OCall esi.AnyCreateSkinObject, TOPFRAME,OBJTYPEREGIONCURSIZEFRAME,[esi].hdcMaskBmp, addr [esi].TopFrameRgn 
    OCall esi.AnyCreateSkinObject, LEFTFRAME, OBJTYPEREGIONCURSIZEFRAME_TILEMODE,[esi].hdcMaskBmp, addr [esi].LeftFrameRgn
    OCall esi.AnyCreateSkinObject, BOTTOMFRAME, OBJTYPEREGIONCURSIZEFRAME,[esi].hdcMaskBmp, addr [esi].BottomFrameRgn
    OCall esi.AnyCreateSkinObject, RIGHTFRAME, OBJTYPEREGIONCURSIZEFRAME_TILEMODE,[esi].hdcMaskBmp, addr [esi].RightFrameRgn

	;posisi TOP FRAME region base x,0
    invoke OffsetRgn, [esi].TopFrameRgn,
    [esi].sSkinData.TopFrame.ObjPt.x,
	[esi].sSkinData.TopFrame.ObjPt.y
    invoke CombineRgn, [esi].TopFrameCurRgn, [esi].TopFrameRgn, 0, RGN_COPY

	;posisi LEFT FRAME region base 0, y
    invoke OffsetRgn, [esi].LeftFrameRgn, 
    [esi].sSkinData.LeftFrame.ObjPt.x,
	[esi].sSkinData.LeftFrame.ObjPt.y
    invoke CombineRgn, [esi].LeftFrameCurRgn, [esi].LeftFrameRgn, 0, RGN_COPY

	;posisi BOTTOM FRAME region base x, y
    invoke OffsetRgn, [esi].BottomFrameRgn,
    [esi].sSkinData.BottomFrame.CurPt.x,
	[esi].sSkinData.BottomFrame.CurPt.y
    invoke CombineRgn, [esi].BottomFrameCurRgn, [esi].BottomFrameRgn, 0, RGN_COPY

	;posisi RIGHT FRAME region base, x,y
    invoke OffsetRgn, [esi].RightFrameRgn, 
    [esi].sSkinData.RightFrame.CurPt.x,
	[esi].sSkinData.RightFrame.CurPt.y
    invoke CombineRgn, [esi].RightFrameCurRgn, [esi].RightFrameRgn, 0, RGN_COPY
;
;    invoke GetRgnBox, [esi].TopFrameRgn, addr [esi].TopFrameRgnBox     
;    invoke GetRgnBox, [esi].LeftFrameRgn, addr [esi].LeftFrameRgnBox     
;    invoke GetRgnBox, [esi].BottomFrameRgn, addr [esi].BottomFrameRgnBox     
;    invoke GetRgnBox, [esi].RightFrameRgn, addr [esi].RightFrameRgnBox   
;    
;    mov [esi].BottomFrameRgnBoxSize.y,$SubVal([esi],BottomFrameRgnBox.bottom,BottomFrameRgnBox.top)
;    mov [esi].RightFrameRgnBoxSize.x,$SubVal([esi],RightFrameRgnBox.right,RightFrameRgnBox.left)
       
MethodEnd

; ——————————————————————————————————————————————————————————————————————————————————————————————————
; Method:    SkinRegion.InitRegionCorner
; Purpose:   
; Arguments: None.
; Return:    
; Note:      

Method SkinRegion.InitRegionCorner, uses esi
    local hAuxRgn:Handle

    SetObject esi
    mov hAuxRgn, $invoke(CreateRectRgn, 0, 0, 0, 0)

	;TopRgtRgn  
    invoke CombineRgn, hAuxRgn, [esi].TopRgtRgn, 0, RGN_COPY
    invoke OffsetRgn, hAuxRgn,
    [esi].sSkinData.TopRgt.CurPt.x,
	[esi].sSkinData.TopRgt.CurPt.y
    invoke CombineRgn, [esi].TopRgtCurRgn, hAuxRgn, 0, RGN_COPY

	;BotLftRgn  
    invoke CombineRgn, hAuxRgn, [esi].BotLftRgn, 0, RGN_COPY
    invoke OffsetRgn, hAuxRgn,
    [esi].sSkinData.BotLft.CurPt.x,
    [esi].sSkinData.BotLft.CurPt.y
    invoke CombineRgn, [esi].BotLftCurRgn, hAuxRgn, 0, RGN_COPY
	
	;BotRgtRgn  
    invoke CombineRgn, hAuxRgn, [esi].BotRgtRgn, 0, RGN_COPY
    invoke OffsetRgn, hAuxRgn,
    [esi].sSkinData.BotRgt.CurPt.x,
	[esi].sSkinData.BotRgt.CurPt.y
    invoke CombineRgn, [esi].BotRgtCurRgn, hAuxRgn, 0, RGN_COPY

    invoke DeleteObject, hAuxRgn
  
MethodEnd


; ——————————————————————————————————————————————————————————————————————————————————————————————————
; Method:    SkinRegion.AnyCreateSkinObject
; Purpose: 	 Membuat varian object skin 	  
; Arguments: nObj:     target object
;            nObjType: tipe handle yg akan dibuat
;            hdcObj:   handle memori object	
;            AnyObj:   pointer tempat penyimpanan handle 
; Return:    handle region object atau handle bitmap object sesuai pilihan
; Note:      
; 
; Pilihan Object:           
; TOPLEFT:     statik object ujung atas kiri
; TOPRIGHT:    statik object ujung atas kanan
; BOTTOMLEFT:  statik object ujung bawah kiri 
; BOTTOMRIGHT: statik object ujung bawah kiri
; TOPFRAME:    dinamik object binkai atas
; LEFTFRAME    dinamik object binkai kiri
; BOTTOMFRAME: dinamik object binkai bawah
; RIGHTFRAME:  dinamik object binkai kanan
; 
; Pilihan tipe object yg di buat:
; OBJTYPEREGION:	membuat handle region, hrs berpasangan dengan hdcobj yang berisi data bitmap hitam putih
; OBJTYPEBITMAP:	membuat handle bitmap, hrs berpasangan dengan hdcobj yang berisi data bitmap berwarna
; OBJTYPEMASK:   	membuat handle mask bitmap, hrs berpasangan dengan hdcobj yang berisi data bitmap berwarna
;                   bagian warna putih akan menjadi transparan, dan bagian warna selain putih akan menjadi hitam

Method SkinRegion.AnyCreateSkinObject, uses esi, nObj:dword, nObjType:dword, hdcObj:Handle, AnyObj:Pointer 
 	LOCAL hDC:Handle
	LOCAL hdcObjBmp:Handle
	LOCAL hOldObjBmp:Handle
	LOCAL MaxSize:SIZEL   
		
    SetObject esi

    ;========================================================
	;Menghapus Dinamik Object. !Awas Sangat bermasalah
	mov eax, AnyObj
	mov eax,[eax]
	.if eax
		invoke DeleteObject, eax
	.endif

   	mov MaxSize.x, $invoke(GetSystemMetrics, SM_CXSCREEN)
	mov MaxSize.y, $invoke(GetSystemMetrics, SM_CYSCREEN)

	;Menyiapkam memori
    mov hDC, $invoke(GetDC, 0)
    mov hdcObjBmp, $invoke(CreateCompatibleDC, hDC)
    invoke ReleaseDC, 0, hDC

	;TOPLEFT
    .if ((nObj == TOPLEFT) && (nObjType == OBJTYPEREGION)) || ((nObj == TOPLEFT) && (nObjType == OBJTYPEMASK)) 
    	invoke CreateCompatibleBitmap, hdcObjBmp,[esi].sSkinData.TopLft.ObjSize.x, [esi].sSkinData.TopLft.ObjSize.y
    .elseif (nObj == TOPLEFT) && (nObjType == OBJTYPEBITMAP) 
    	invoke CreateCompatibleBitmap, hdcObj,[esi].sSkinData.TopLft.ObjSize.x, [esi].sSkinData.TopLft.ObjSize.y

	;TOPRIGHT
    .elseif ((nObj == TOPRIGHT) && (nObjType == OBJTYPEREGION)) || ((nObj == TOPRIGHT) && (nObjType == OBJTYPEMASK))
    	invoke CreateCompatibleBitmap, hdcObjBmp,[esi].sSkinData.TopRgt.ObjSize.x, [esi].sSkinData.TopRgt.ObjSize.y
    .elseif (nObj == TOPRIGHT) && (nObjType == OBJTYPEBITMAP)
    	invoke CreateCompatibleBitmap, hdcObj,[esi].sSkinData.TopRgt.ObjSize.x, [esi].sSkinData.TopRgt.ObjSize.y

	;BOTTOMLEFT
    .elseif ((nObj == BOTTOMLEFT) && (nObjType == OBJTYPEREGION)) || ((nObj == BOTTOMLEFT) && (nObjType == OBJTYPEMASK))
    	invoke CreateCompatibleBitmap, hdcObjBmp,[esi].sSkinData.BotLft.ObjSize.x, [esi].sSkinData.BotLft.ObjSize.y
    .elseif (nObj == BOTTOMLEFT) && (nObjType == OBJTYPEBITMAP)
    	invoke CreateCompatibleBitmap, hdcObj,[esi].sSkinData.BotLft.ObjSize.x, [esi].sSkinData.BotLft.ObjSize.y

	;BOTTOMRIGHT
    .elseif ((nObj == BOTTOMRIGHT) && (nObjType == OBJTYPEREGION)) || ((nObj == BOTTOMRIGHT) && (nObjType == OBJTYPEMASK))  
    	invoke CreateCompatibleBitmap, hdcObjBmp,[esi].sSkinData.BotRgt.ObjSize.x, [esi].sSkinData.BotRgt.ObjSize.y
    .elseif (nObj == BOTTOMRIGHT) && (nObjType == OBJTYPEBITMAP)
    	invoke CreateCompatibleBitmap, hdcObj,[esi].sSkinData.BotRgt.ObjSize.x, [esi].sSkinData.BotRgt.ObjSize.y
    
    ;=========
	; TOPFRAME
	.elseif ((nObj == TOPFRAME) && (nObjType == OBJTYPEREGIONCURSIZEFRAME)) || \
    		((nObj == TOPFRAME) && (nObjType == OBJTYPEREGIONCURSIZEFRAME_TILEMODE)) || \
    		((nObj == TOPFRAME) && (nObjType == OBJTYPEMASKCURSIZEFRAME_TILEMODE))
	    invoke CreateCompatibleBitmap,hdcObjBmp, [esi].sSkinData.TopFrame.CurSize.x,[esi].sSkinData.TopFrame.CurSize.y
	.elseif ((nObj == TOPFRAME) && (nObjType == OBJTYPEREGIONMAXSIZEFRAME)) || \
    		((nObj == TOPFRAME) && (nObjType == OBJTYPEMASKMAXSIZEFRAME_TILEMODE)) 
	    invoke CreateCompatibleBitmap,hdcObjBmp, MaxSize.x,[esi].sSkinData.TopFrame.CurSize.y

    .elseif (nObj == TOPFRAME) && (nObjType == OBJTYPEBITMAPMAXSIZEFRAME_TILEMODE)
	    invoke CreateCompatibleBitmap,hdcObj,[esi].sSkinData.TopFrame.CurSize.x, MaxSize.y
    .elseif (nObj == TOPFRAME) && (nObjType == OBJTYPEBITMAPCURSIZEFRAME_TILEMODE)
	    invoke CreateCompatibleBitmap,hdcObj,[esi].sSkinData.TopFrame.CurSize.x, [esi].sSkinData.TopFrame.CurSize.y

	.elseif (nObj == TOPFRAME) && (nObjType == OBJTYPEBITMAP)
	    invoke CreateCompatibleBitmap,hdcObj,1,[esi].sSkinData.TopFrame.CurSize.y
	.elseif (nObj == TOPFRAME) && (nObjType == OBJTYPEMASK)
	    invoke CreateCompatibleBitmap,hdcObjBmp,1,[esi].sSkinData.TopFrame.CurSize.y

	; LEFTFRAME
    .elseif ((nObj == LEFTFRAME) && (nObjType == OBJTYPEREGIONCURSIZEFRAME)) || \
    		((nObj == LEFTFRAME) && (nObjType == OBJTYPEREGIONCURSIZEFRAME_TILEMODE)) || \
    		((nObj == LEFTFRAME) && (nObjType == OBJTYPEMASKCURSIZEFRAME_TILEMODE))
	    invoke CreateCompatibleBitmap,hdcObjBmp,[esi].sSkinData.LeftFrame.CurSize.x, [esi].sSkinData.LeftFrame.CurSize.y
    .elseif ((nObj == LEFTFRAME) && (nObjType == OBJTYPEREGIONMAXSIZEFRAME)) || \
    		((nObj == LEFTFRAME) && (nObjType == OBJTYPEMASKMAXSIZEFRAME_TILEMODE)) 
	    invoke CreateCompatibleBitmap,hdcObjBmp,[esi].sSkinData.LeftFrame.CurSize.x, MaxSize.y

    .elseif (nObj == LEFTFRAME) && (nObjType == OBJTYPEBITMAPMAXSIZEFRAME_TILEMODE)
	    invoke CreateCompatibleBitmap,hdcObj,[esi].sSkinData.LeftFrame.CurSize.x, MaxSize.y
    .elseif (nObj == LEFTFRAME) && (nObjType == OBJTYPEBITMAPCURSIZEFRAME_TILEMODE)
	    invoke CreateCompatibleBitmap,hdcObj,[esi].sSkinData.LeftFrame.CurSize.x, [esi].sSkinData.LeftFrame.CurSize.y

    .elseif (nObj == LEFTFRAME) && (nObjType == OBJTYPEBITMAP)
	    invoke CreateCompatibleBitmap,hdcObj,[esi].sSkinData.LeftFrame.CurSize.x,1
    .elseif (nObj == LEFTFRAME) && (nObjType == OBJTYPEMASK)
	    invoke CreateCompatibleBitmap,hdcObjBmp,[esi].sSkinData.LeftFrame.CurSize.x,1

	; BOTTOMFRAME
    .elseif ((nObj == BOTTOMFRAME) && (nObjType == OBJTYPEREGIONCURSIZEFRAME)) || \
    		((nObj == BOTTOMFRAME) && (nObjType == OBJTYPEREGIONCURSIZEFRAME_TILEMODE)) || \
    		((nObj == BOTTOMFRAME) && (nObjType == OBJTYPEMASKCURSIZEFRAME_TILEMODE))
	    invoke CreateCompatibleBitmap,hdcObjBmp, [esi].sSkinData.BottomFrame.CurSize.x, [esi].sSkinData.BottomFrame.CurSize.y
    .elseif ((nObj == BOTTOMFRAME) && (nObjType == OBJTYPEREGIONMAXSIZEFRAME)) || \ 
    		((nObj == BOTTOMFRAME) && (nObjType == OBJTYPEMASKMAXSIZEFRAME_TILEMODE)) 
	    invoke CreateCompatibleBitmap,hdcObjBmp, MaxSize.x, [esi].sSkinData.BottomFrame.CurSize.y

    .elseif (nObj == BOTTOMFRAME) && (nObjType == OBJTYPEBITMAPMAXSIZEFRAME_TILEMODE)
	    invoke CreateCompatibleBitmap,hdcObj,[esi].sSkinData.BottomFrame.CurSize.x, MaxSize.y
    .elseif (nObj == BOTTOMFRAME) && (nObjType == OBJTYPEBITMAPCURSIZEFRAME_TILEMODE)
	    invoke CreateCompatibleBitmap,hdcObj,[esi].sSkinData.BottomFrame.CurSize.x, [esi].sSkinData.BottomFrame.CurSize.y

    .elseif (nObj == BOTTOMFRAME) && (nObjType == OBJTYPEBITMAP)
	    invoke CreateCompatibleBitmap,hdcObj, 1, [esi].sSkinData.BottomFrame.CurSize.y
    .elseif (nObj == BOTTOMFRAME) && (nObjType == OBJTYPEMASK)
	    invoke CreateCompatibleBitmap,hdcObjBmp, 1, [esi].sSkinData.BottomFrame.CurSize.y

	; RIGHTFRAME
    .elseif ((nObj == RIGHTFRAME) && (nObjType == OBJTYPEREGIONCURSIZEFRAME)) || \
    		((nObj == RIGHTFRAME) && (nObjType == OBJTYPEREGIONCURSIZEFRAME_TILEMODE)) || \
    		((nObj == RIGHTFRAME) && (nObjType == OBJTYPEMASKCURSIZEFRAME_TILEMODE))
	    invoke CreateCompatibleBitmap,hdcObjBmp,[esi].sSkinData.RightFrame.CurSize.x, [esi].sSkinData.RightFrame.CurSize.y
    .elseif ((nObj == RIGHTFRAME) && (nObjType == OBJTYPEREGIONMAXSIZEFRAME)) || \
    		((nObj == RIGHTFRAME) && (nObjType == OBJTYPEMASKMAXSIZEFRAME_TILEMODE))
	    invoke CreateCompatibleBitmap,hdcObjBmp,[esi].sSkinData.RightFrame.CurSize.x, MaxSize.y

    .elseif (nObj == RIGHTFRAME) && (nObjType == OBJTYPEBITMAPCURSIZEFRAME_TILEMODE) 
	    invoke CreateCompatibleBitmap,hdcObj,[esi].sSkinData.RightFrame.CurSize.x, [esi].sSkinData.RightFrame.CurSize.y
    .elseif (nObj == RIGHTFRAME) && (nObjType == OBJTYPEBITMAPMAXSIZEFRAME_TILEMODE)
	    invoke CreateCompatibleBitmap,hdcObj,[esi].sSkinData.RightFrame.CurSize.x, MaxSize.y

    .elseif (nObj == RIGHTFRAME) && (nObjType == OBJTYPEBITMAP)
	    invoke CreateCompatibleBitmap,hdcObj,[esi].sSkinData.RightFrame.CurSize.x, 1
    .elseif (nObj == RIGHTFRAME) && (nObjType == OBJTYPEMASK)
	    invoke CreateCompatibleBitmap,hdcObjBmp,[esi].sSkinData.RightFrame.CurSize.x, 1

	; WNDCAPTION
	.elseif (nObj == WNDCAPTION) && (nObjType == OBJTYPEREGIONCURSIZEFRAME)
	    invoke CreateCompatibleBitmap,hdcObjBmp, [esi].sSkinData.WndCaption.CurSize.x,[esi].sSkinData.WndCaption.CurSize.y
	.elseif (nObj == WNDCAPTION) && (nObjType == OBJTYPEREGIONMAXSIZEFRAME)
	    invoke CreateCompatibleBitmap,hdcObjBmp, MaxSize.x,[esi].sSkinData.WndCaption.CurSize.y
	.elseif (nObj == WNDCAPTION) && (nObjType == OBJTYPEBITMAP)
	    invoke CreateCompatibleBitmap,hdcObj,1,[esi].sSkinData.WndCaption.CurSize.y
	.elseif (nObj == WNDCAPTION) && (nObjType == OBJTYPEMASK)
	    invoke CreateCompatibleBitmap,hdcObjBmp,1,[esi].sSkinData.WndCaption.CurSize.y
    .endif

;	;menghubungkan memori ke OBJECT BITMAP
    push eax
    mov hOldObjBmp, $invoke(SelectObject, hdcObjBmp, eax)

;	;Mode Transfer warna antar memori ke OBJECT BITMAP
    .if nObj == TOPLEFT
	    invoke BitBlt, hdcObjBmp, 
	    0, 0, [esi].sSkinData.TopLft.ObjSize.x, [esi].sSkinData.TopLft.ObjSize.y, 
	    hdcObj, 
	    [esi].sSkinData.TopLft.ObjPt.x, [esi].sSkinData.TopLft.ObjPt.y, SRCCOPY
    .elseif nObj == TOPRIGHT
	    invoke BitBlt, hdcObjBmp, 
	    0, 0, [esi].sSkinData.TopRgt.ObjSize.x, [esi].sSkinData.TopRgt.ObjSize.y, 
	    hdcObj, 
	    [esi].sSkinData.TopRgt.ObjPt.x, [esi].sSkinData.TopRgt.ObjPt.y, SRCCOPY
    .elseif nObj == BOTTOMLEFT
	    invoke BitBlt, hdcObjBmp, 
	    0, 0, [esi].sSkinData.BotLft.ObjSize.x, [esi].sSkinData.BotLft.ObjSize.y, 
	    hdcObj, 
	    [esi].sSkinData.BotLft.ObjPt.x, [esi].sSkinData.BotLft.ObjPt.y, SRCCOPY
    .elseif nObj == BOTTOMRIGHT
	    invoke BitBlt, hdcObjBmp, 
	    0, 0, [esi].sSkinData.BotRgt.ObjSize.x, [esi].sSkinData.BotRgt.ObjSize.y, 
	    hdcObj, 
	    [esi].sSkinData.BotRgt.ObjPt.x, [esi].sSkinData.BotRgt.ObjPt.y, SRCCOPY
	
	; TOPFRAME
    .elseif (nObj == TOPFRAME) && (nObjType == OBJTYPEREGIONCURSIZEFRAME_TILEMODE)
        invoke PartBitmap, hdcObj, 
        [esi].sSkinData.TopFrame.ObjPt.x,[esi].sSkinData.TopFrame.ObjPt.y,
        [esi].sSkinData.TopFrame.ObjSize.x, nTopFrameWidth 
		invoke PatternBitmap, eax, 
		hdcObjBmp, 
		[esi].sSkinData.TopFrame.CurSize.x, [esi].sSkinData.TopFrame.CurSize.y

	.elseif (nObj == TOPFRAME) && (nObjType == OBJTYPEREGIONCURSIZEFRAME)
	    invoke StretchBlt, hdcObjBmp,                  \;mengisi warna mask ke memori
	    0, 0, [esi].sSkinData.TopFrame.CurSize.x, [esi].sSkinData.TopFrame.CurSize.y, \;tujuan 0,0 dgn lebar sekarang dan tinggi constant
	    hdcObj, 
	    [esi].sSkinData.TopFrame.ObjPt.x,[esi].sSkinData.TopFrame.ObjPt.y,
	    1,[esi].sSkinData.TopFrame.CurSize.y, SRCCOPY
	.elseif (nObj == TOPFRAME) && (nObjType == OBJTYPEREGIONMAXSIZEFRAME)
	    invoke StretchBlt, hdcObjBmp,                  \;mengisi warna mask ke memori
	    0, 0, MaxSize.x, [esi].sSkinData.TopFrame.CurSize.y, \;tujuan 0,0 dgn lebar sekarang dan tinggi constant
	    hdcObj, 
	    [esi].sSkinData.TopFrame.ObjPt.x,[esi].sSkinData.TopFrame.ObjPt.y,
	    1,[esi].sSkinData.TopFrame.CurSize.y, SRCCOPY

    .elseif ((nObj == TOPFRAME) && (nObjType == OBJTYPEBITMAPCURSIZEFRAME_TILEMODE)) || \
    		((nObj == TOPFRAME) && (nObjType == OBJTYPEMASKCURSIZEFRAME_TILEMODE))
        invoke PartBitmap, hdcObj, 
        [esi].sSkinData.TopFrame.ObjPt.x,[esi].sSkinData.TopFrame.ObjPt.y,
        [esi].sSkinData.TopFrame.ObjSize.x, nTopFrameWidth 
		invoke PatternBitmap, eax, 
		hdcObjBmp, 
		[esi].sSkinData.TopFrame.CurSize.x, [esi].sSkinData.TopFrame.CurSize.y
    .elseif ((nObj == TOPFRAME) && (nObjType == OBJTYPEBITMAPMAXSIZEFRAME_TILEMODE)) || \
    		((nObj == TOPFRAME) && (nObjType == OBJTYPEMASKMAXSIZEFRAME_TILEMODE))
        invoke PartBitmap, hdcObj, 
        [esi].sSkinData.TopFrame.ObjPt.x,[esi].sSkinData.TopFrame.ObjPt.y,
        [esi].sSkinData.TopFrame.ObjSize.x, nTopFrameWidth 
		invoke PatternBitmap, eax, 
		hdcObjBmp, 
		[esi].sSkinData.TopFrame.CurSize.x, MaxSize.y

	.elseif ((nObj == TOPFRAME) && (nObjType == OBJTYPEBITMAP)) || \
			((nObj == TOPFRAME) && (nObjType == OBJTYPEMASK))
	    invoke BitBlt, hdcObjBmp,                  \;mengisi warna mask ke memori
	    0, 0, 1, [esi].sSkinData.TopFrame.CurSize.y, \;tujuan 0,0 dgn lebar sekarang dan tinggi constant
	    hdcObj, 
	    [esi].sSkinData.TopFrame.ObjPt.x,[esi].sSkinData.TopFrame.ObjPt.y, SRCCOPY

	; LEFTFRAME
    .elseif (nObj == LEFTFRAME) && (nObjType == OBJTYPEREGIONCURSIZEFRAME_TILEMODE)
        invoke PartBitmap, hdcObj, 
        [esi].sSkinData.LeftFrame.ObjPt.x,[esi].sSkinData.LeftFrame.ObjPt.y,
        [esi].sSkinData.LeftFrame.ObjSize.x, nLeftFrameHeight 
		invoke PatternBitmap, eax, 
		hdcObjBmp, 
		[esi].sSkinData.LeftFrame.CurSize.x, [esi].sSkinData.LeftFrame.CurSize.y

    .elseif (nObj == LEFTFRAME) && (nObjType == OBJTYPEREGIONCURSIZEFRAME)
	    invoke StretchBlt, hdcObjBmp,                         \;mengisi warna mask ke memori
	    0, 0, [esi].sSkinData.LeftFrame.CurSize.x, [esi].sSkinData.LeftFrame.CurSize.y, \;tujuan 0,0 dgn lebar sekarang dan tinggi constant
	    hdcObj, 
	    [esi].sSkinData.LeftFrame.ObjPt.x,[esi].sSkinData.LeftFrame.ObjPt.y,
	    [esi].sSkinData.LeftFrame.CurSize.x,1, SRCCOPY
    .elseif (nObj == LEFTFRAME) && (nObjType == OBJTYPEREGIONMAXSIZEFRAME)
	    invoke StretchBlt, hdcObjBmp,                         \;mengisi warna mask ke memori
	    0, 0, [esi].sSkinData.LeftFrame.CurSize.x, MaxSize.y, \;tujuan 0,0 dgn lebar sekarang dan tinggi constant
	    hdcObj, 
	    [esi].sSkinData.LeftFrame.ObjPt.x,[esi].sSkinData.LeftFrame.ObjPt.y,
	    [esi].sSkinData.LeftFrame.CurSize.x,1, SRCCOPY

    .elseif ((nObj == LEFTFRAME) && (nObjType == OBJTYPEBITMAPCURSIZEFRAME_TILEMODE)) || \
    		((nObj == LEFTFRAME) && (nObjType == OBJTYPEMASKCURSIZEFRAME_TILEMODE))
        invoke PartBitmap, hdcObj, 
        [esi].sSkinData.LeftFrame.ObjPt.x,[esi].sSkinData.LeftFrame.ObjPt.y,
        [esi].sSkinData.LeftFrame.ObjSize.x, nLeftFrameHeight 
		invoke PatternBitmap, eax, 
		hdcObjBmp, 
		[esi].sSkinData.LeftFrame.CurSize.x, [esi].sSkinData.LeftFrame.CurSize.y
    .elseif ((nObj == LEFTFRAME) && (nObjType == OBJTYPEBITMAPMAXSIZEFRAME_TILEMODE)) || \
    		((nObj == LEFTFRAME) && (nObjType == OBJTYPEMASKMAXSIZEFRAME_TILEMODE))
        invoke PartBitmap, hdcObj, 
        [esi].sSkinData.LeftFrame.ObjPt.x,[esi].sSkinData.LeftFrame.ObjPt.y,
        [esi].sSkinData.LeftFrame.ObjSize.x, nLeftFrameHeight 
		invoke PatternBitmap, eax, 
		hdcObjBmp, 
		[esi].sSkinData.LeftFrame.CurSize.x, MaxSize.y

    .elseif ((nObj == LEFTFRAME) && (nObjType == OBJTYPEBITMAP)) || \
    		((nObj == LEFTFRAME) && (nObjType == OBJTYPEMASK))
	    invoke BitBlt, hdcObjBmp,                     \;mengisi warna mask ke memori
	    0, 0, [esi].sSkinData.LeftFrame.CurSize.x, 1, \;tujuan 0,0 dgn lebar sekarang dan tinggi constant
	    hdcObj, 
	    [esi].sSkinData.LeftFrame.ObjPt.x,[esi].sSkinData.LeftFrame.ObjPt.y, SRCCOPY

	; BOTTOMFRAME
    .elseif (nObj == BOTTOMFRAME) && (nObjType == OBJTYPEREGIONCURSIZEFRAME_TILEMODE)
        invoke PartBitmap, hdcObj, 
        [esi].sSkinData.BottomFrame.ObjPt.x,[esi].sSkinData.BottomFrame.ObjPt.y,
        [esi].sSkinData.BottomFrame.ObjSize.x, nBottomFrameWidth 
		invoke PatternBitmap, eax, 
		hdcObjBmp, 
		[esi].sSkinData.BottomFrame.CurSize.x, [esi].sSkinData.BottomFrame.CurSize.y

    .elseif (nObj == BOTTOMFRAME) && (nObjType == OBJTYPEREGIONCURSIZEFRAME)
	    invoke StretchBlt, hdcObjBmp, 
	    0, 0, [esi].sSkinData.BottomFrame.CurSize.x,[esi].sSkinData.BottomFrame.CurSize.y,
	    hdcObj, 
	    [esi].sSkinData.BottomFrame.ObjPt.x,[esi].sSkinData.BottomFrame.ObjPt.y,
	    1,[esi].sSkinData.BottomFrame.CurSize.y, SRCCOPY
    .elseif (nObj == BOTTOMFRAME) && (nObjType == OBJTYPEREGIONMAXSIZEFRAME)
	    invoke StretchBlt, hdcObjBmp, 
	    0, 0, MaxSize.x,[esi].sSkinData.BottomFrame.CurSize.y,
	    hdcObj, 
	    [esi].sSkinData.BottomFrame.ObjPt.x,[esi].sSkinData.BottomFrame.ObjPt.y,
	    1,[esi].sSkinData.BottomFrame.CurSize.y, SRCCOPY

    .elseif ((nObj == BOTTOMFRAME) && (nObjType == OBJTYPEBITMAPCURSIZEFRAME_TILEMODE)) || \
    		((nObj == BOTTOMFRAME) && (nObjType == OBJTYPEMASKCURSIZEFRAME_TILEMODE))
        invoke PartBitmap, hdcObj, 
        [esi].sSkinData.BottomFrame.ObjPt.x,[esi].sSkinData.BottomFrame.ObjPt.y,
        [esi].sSkinData.BottomFrame.ObjSize.x, nBottomFrameWidth 
		invoke PatternBitmap, eax, 
		hdcObjBmp, 
		[esi].sSkinData.BottomFrame.CurSize.x, [esi].sSkinData.BottomFrame.CurSize.y
    .elseif ((nObj == BOTTOMFRAME) && (nObjType == OBJTYPEBITMAPMAXSIZEFRAME_TILEMODE)) || \
    		((nObj == BOTTOMFRAME) && (nObjType == OBJTYPEMASKMAXSIZEFRAME_TILEMODE))
        invoke PartBitmap, hdcObj, 
        [esi].sSkinData.BottomFrame.ObjPt.x,[esi].sSkinData.BottomFrame.ObjPt.y,
        [esi].sSkinData.BottomFrame.ObjSize.x, nBottomFrameWidth 
		invoke PatternBitmap, eax, 
		hdcObjBmp, 
		[esi].sSkinData.BottomFrame.CurSize.x, MaxSize.y

    .elseif ((nObj == BOTTOMFRAME) && (nObjType == OBJTYPEBITMAP)) || \
    		((nObj == BOTTOMFRAME) && (nObjType == OBJTYPEMASK))
	    invoke BitBlt, hdcObjBmp, 
	    0, 0, 1,[esi].sSkinData.BottomFrame.CurSize.y,
	    hdcObj, 
	    [esi].sSkinData.BottomFrame.ObjPt.x,[esi].sSkinData.BottomFrame.ObjPt.y, SRCCOPY

	; RIGHTFRAME
    .elseif (nObj == RIGHTFRAME) && (nObjType == OBJTYPEREGIONCURSIZEFRAME_TILEMODE)
        invoke PartBitmap, hdcObj, 
        [esi].sSkinData.RightFrame.ObjPt.x,[esi].sSkinData.RightFrame.ObjPt.y,
        [esi].sSkinData.RightFrame.ObjSize.x, nRightFrameHeight 
		invoke PatternBitmap, eax, 
		hdcObjBmp, 
		[esi].sSkinData.RightFrame.CurSize.x, [esi].sSkinData.RightFrame.CurSize.y

    .elseif (nObj == RIGHTFRAME) && (nObjType == OBJTYPEREGIONCURSIZEFRAME)
	    invoke StretchBlt, hdcObjBmp,                  
	    0, 0, [esi].sSkinData.RightFrame.CurSize.x, [esi].sSkinData.RightFrame.CurSize.y, 
	    hdcObj, 
	    [esi].sSkinData.RightFrame.ObjPt.x,[esi].sSkinData.RightFrame.ObjPt.y,
	    [esi].sSkinData.RightFrame.CurSize.x,1, SRCCOPY
    .elseif (nObj == RIGHTFRAME) && (nObjType == OBJTYPEREGIONMAXSIZEFRAME)
	    invoke StretchBlt, hdcObjBmp,                  
	    0, 0, [esi].sSkinData.RightFrame.CurSize.x, MaxSize.y, 
	    hdcObj, 
	    [esi].sSkinData.RightFrame.ObjPt.x,[esi].sSkinData.RightFrame.ObjPt.y,
	    [esi].sSkinData.RightFrame.CurSize.x,1, SRCCOPY

    .elseif ((nObj == RIGHTFRAME) && (nObjType == OBJTYPEBITMAPCURSIZEFRAME_TILEMODE)) || \
    		((nObj == RIGHTFRAME) && (nObjType == OBJTYPEMASKCURSIZEFRAME_TILEMODE))
        invoke PartBitmap, hdcObj, 
        [esi].sSkinData.RightFrame.ObjPt.x,[esi].sSkinData.RightFrame.ObjPt.y,
        [esi].sSkinData.RightFrame.ObjSize.x, nRightFrameHeight 
		invoke PatternBitmap, eax, 
		hdcObjBmp, 
		[esi].sSkinData.RightFrame.CurSize.x, [esi].sSkinData.RightFrame.CurSize.y
    .elseif ((nObj == RIGHTFRAME) && (nObjType == OBJTYPEBITMAPMAXSIZEFRAME_TILEMODE)) || \
    		((nObj == RIGHTFRAME) && (nObjType == OBJTYPEMASKMAXSIZEFRAME_TILEMODE))
        invoke PartBitmap, hdcObj, 
        [esi].sSkinData.RightFrame.ObjPt.x,[esi].sSkinData.RightFrame.ObjPt.y,
        [esi].sSkinData.RightFrame.ObjSize.x, nRightFrameHeight 
		invoke PatternBitmap, eax, 
		hdcObjBmp, 
		[esi].sSkinData.RightFrame.CurSize.x, MaxSize.y

    .elseif ((nObj == RIGHTFRAME) && (nObjType == OBJTYPEBITMAP)) || \
    		((nObj == RIGHTFRAME) && (nObjType == OBJTYPEMASK))
	    invoke BitBlt, hdcObjBmp,                  
	    0, 0, [esi].sSkinData.RightFrame.CurSize.x, 1, 
	    hdcObj, 
	    [esi].sSkinData.RightFrame.ObjPt.x,[esi].sSkinData.RightFrame.ObjPt.y, SRCCOPY 

	; WNDCAPTION
	.elseif (nObj == WNDCAPTION) && (nObjType == OBJTYPEREGIONCURSIZEFRAME)
	    invoke StretchBlt, hdcObjBmp,                  \;mengisi warna mask ke memori
	    0, 0, [esi].sSkinData.WndCaption.CurSize.x, [esi].sSkinData.WndCaption.CurSize.y, \;tujuan 0,0 dgn lebar sekarang dan tinggi constant
	    hdcObj, 
	    [esi].sSkinData.WndCaption.ObjPt.x,[esi].sSkinData.WndCaption.ObjPt.y,
	    1,[esi].sSkinData.WndCaption.CurSize.y, SRCCOPY
	.elseif (nObj == WNDCAPTION) && (nObjType == OBJTYPEREGIONMAXSIZEFRAME)
	    invoke StretchBlt, hdcObjBmp,                  \;mengisi warna mask ke memori
	    0, 0, MaxSize.x, [esi].sSkinData.WndCaption.CurSize.y, \;tujuan 0,0 dgn lebar sekarang dan tinggi constant
	    hdcObj, 
	    [esi].sSkinData.WndCaption.ObjPt.x,[esi].sSkinData.WndCaption.ObjPt.y,
	    1,[esi].sSkinData.WndCaption.CurSize.y, SRCCOPY
	.elseif ((nObj == WNDCAPTION) && (nObjType == OBJTYPEBITMAP)) || ((nObj == WNDCAPTION) && (nObjType == OBJTYPEMASK))
	    invoke BitBlt, hdcObjBmp,                  \;mengisi warna mask ke memori
	    0, 0, 1, [esi].sSkinData.WndCaption.CurSize.y, \;tujuan 0,0 dgn lebar sekarang dan tinggi constant
	    hdcObj, 
	    [esi].sSkinData.WndCaption.ObjPt.x,[esi].sSkinData.WndCaption.ObjPt.y, SRCCOPY
    .endif

	; Restore eax
    pop eax
	; Pilihan type object
	.if (nObjType == OBJTYPEREGION) || \
		(nObjType == OBJTYPEREGIONCURSIZEFRAME) || \
		(nObjType == OBJTYPEREGIONMAXSIZEFRAME) || \
		(nObjType == OBJTYPEREGIONCURSIZEFRAME_TILEMODE)
		;=====================
	    ;proses membuat region
	    invoke Bmp2Rgn, eax, $RGB(0,0,0); warna hitam menjadi region

	    ;simpan hasil region ke pointer AnyObj 
	    mov ecx, AnyObj
	    mov [ecx], eax
	    
	    ;Hapus Object Bitmap	
		Invoke DeleteObject, $invoke(SelectObject, hdcObjBmp, hOldObjBmp)

    .elseif (nObjType == OBJTYPEBITMAP) || \
        	(nObjType == OBJTYPEMASK) || \
        	(nObjType == OBJTYPEBITMAPMAXSIZEFRAME_TILEMODE) || \
        	(nObjType == OBJTYPEMASKMAXSIZEFRAME_TILEMODE)   || \ 
        	(nObjType == OBJTYPEBITMAPCURSIZEFRAME_TILEMODE)  || \
        	(nObjType == OBJTYPEMASKCURSIZEFRAME_TILEMODE)
		;=====================
	    ;simpan hasil bitmap ke pointer AnyObj 
	    mov ecx, AnyObj
	    mov [ecx], eax
	    
	    ;Pengembalian Object Bitmap	
		invoke SelectObject, hdcObjBmp, hOldObjBmp
    .endif
	
	;===============
    ;Bebaskan memori	
	Invoke DeleteDC, hdcObjBmp
    
MethodEnd

DuplicateBitmap proc hbmpSrc:Handle
    local hbmpOldSrc:Handle, hbmpOldDest:Handle, hbmpNew:Handle
    local hdcSrc:Handle, hdcDest:Handle
    local bmp:BITMAP

    mov hdcSrc, $invoke(CreateCompatibleDC, NULL)
    mov hdcDest,$invoke(CreateCompatibleDC, hdcSrc)

    invoke GetObject, hbmpSrc, sizeof BITMAP, addr bmp
    mov hbmpOldSrc,  $invoke(SelectObject,hdcSrc, hbmpSrc)
    
    mov hbmpNew,     $invoke(CreateCompatibleBitmap,hdcSrc, bmp.bmWidth, bmp.bmHeight)
    mov hbmpOldDest, $invoke(SelectObject,hdcDest, hbmpNew)
    invoke BitBlt, hdcDest, 0, 0, bmp.bmWidth, bmp.bmHeight, hdcSrc, 0, 0, SRCCOPY

    invoke SelectObject, hdcDest, hbmpOldDest
    invoke SelectObject, hdcSrc, hbmpOldSrc

    invoke DeleteDC, hdcDest
    invoke DeleteDC, hdcSrc

    mov eax, hbmpNew
	ret

DuplicateBitmap endp

PartBitmap proc hdcSrc:Handle, ptx:dword,pty:dword,bmWidth:dword, bmHeight:dword
    local hbmpOldDest:Handle, hbmpNew:Handle
    local hdcDest:Handle
    
    mov hdcDest,$invoke(CreateCompatibleDC, NULL)
    mov hbmpNew,     $invoke(CreateCompatibleBitmap, hdcSrc, bmWidth, bmHeight)
    mov hbmpOldDest, $invoke(SelectObject,hdcDest, hbmpNew)
    invoke BitBlt, hdcDest, 0, 0, bmWidth, bmHeight, hdcSrc, ptx, pty, SRCCOPY

    invoke SelectObject, hdcDest, hbmpOldDest
    invoke DeleteDC, hdcDest

    mov eax, hbmpNew
	ret
PartBitmap endp

PatternBitmap proc hbmp:Handle, hdcDst:Handle, PatbmWidth:dword, PatbmHeight:dword
	local hbr:Handle, hbrPrevious:Handle

	mov hbr, $invoke(CreatePatternBrush,hbmp)
	invoke UnrealizeObject,hbr
	mov hbrPrevious,$invoke(SelectObject,hdcDst, hbr)
	invoke PatBlt,hdcDst, 0, 0, PatbmWidth, PatbmHeight, PATCOPY
	invoke SelectObject,hdcDst, hbrPrevious
	invoke DeleteObject,hbr
	invoke DeleteObject,hbmp
	ret

PatternBitmap endp


