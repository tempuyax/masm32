;CStr szCaption,  "CAPTION"
TopXY  proto :dword, :dword

Object SkinPaint, 949494, SkinRegion
	RedefineMethod    Done
	RedefineMethod    Init,                 Pointer, Pointer, Handle, Handle 
	VirtualMethod     DynamicPaintInit, 	Handle , Pointer, dword
    VirtualMethod	  Paint, 				Handle,  dword	
    VirtualMethod	  SetWindow, 			Handle	
	
	DefineVariable	  hdcBmp,	         	Handle,     0  
    DefineVariable	  hWnd,					Handle,     0
ObjectEnd


; ——————————————————————————————————————————————————————————————————————————————————————————————————
; Method:    SkinPaint.Init
; Purpose:   
; Arguments: None.
; Return:    
; Note:      

Method SkinPaint.Init, uses esi, WndRC:Pointer, ObjBmp:Pointer, hdcMaskBmp:Handle, hdcBmp:Handle
    SetObject esi
    ACall Init, esi, WndRC, ObjBmp, hdcMaskBmp
    m2m [esi].hdcBmp, hdcBmp
MethodEnd

; ——————————————————————————————————————————————————————————————————————————————————————————————————
; Method:    SkinPaint.SetWindow
; Purpose:   
; Arguments: Arg1: 
; Return:    
; Note:      

Method SkinPaint.SetWindow, uses esi, hWnd:Handle
    SetObject esi
    m2m [esi].hWnd, hWnd
    
MethodEnd


; ——————————————————————————————————————————————————————————————————————————————————————————————————
; Method:    SkinPaint.Done
; Purpose:   
; Arguments: None.
; Return:    
; Note:      

Method SkinPaint.Done, uses esi
    SetObject esi
    ACall Done
MethodEnd

; ——————————————————————————————————————————————————————————————————————————————————————————————————
; Method:    SkinPaint.Paint
; Purpose:   
; Arguments: None.
; Return:    
; Note:      

Method SkinPaint.Paint, uses esi, hdcPaint:Handle, fSkinPaint:dword
	LOCAL LenTxt:dword,TxtCaption[128]:byte,SizeTxt:SIZEL,PosTxt:POINT

    SetObject esi
	.if fSkinPaint ==  TRUE
		;Paint Top Left corner to client
	    invoke BitBlt, hdcPaint, 
	    0, 0, [esi].sSkinData.TopLft.ObjSize.x, [esi].sSkinData.TopLft.ObjSize.y, 
	    [esi].hdcBmp, 
	    [esi].sSkinData.TopLft.ObjPt.x, [esi].sSkinData.TopLft.ObjPt.y, SRCCOPY
	 
		;Paint Top Right corner to client
	    invoke BitBlt, hdcPaint,
	    [esi].sSkinData.TopRgt.CurPt.x, [esi].sSkinData.TopRgt.CurPt.y, [esi].sSkinData.TopRgt.ObjSize.x, [esi].sSkinData.TopRgt.ObjSize.y, 
	    [esi].hdcBmp, 
	    [esi].sSkinData.TopRgt.ObjPt.x, [esi].sSkinData.TopRgt.ObjPt.y, SRCCOPY
	
		;Paint Bottom Left corner to client
	    invoke BitBlt, hdcPaint,
	    [esi].sSkinData.BotLft.CurPt.x, [esi].sSkinData.BotLft.CurPt.y, [esi].sSkinData.BotLft.ObjSize.x, [esi].sSkinData.BotLft.ObjSize.y, 
	    [esi].hdcBmp, 
	    [esi].sSkinData.BotLft.ObjPt.x, [esi].sSkinData.BotLft.ObjPt.y, SRCCOPY
	
		;Paint Bottom Right corner to client
	    invoke BitBlt, hdcPaint,
	    [esi].sSkinData.BotRgt.CurPt.x, [esi].sSkinData.BotRgt.CurPt.y, [esi].sSkinData.BotRgt.ObjSize.x, [esi].sSkinData.BotRgt.ObjSize.y, 
	    [esi].hdcBmp, 
	    [esi].sSkinData.BotRgt.ObjPt.x, [esi].sSkinData.BotRgt.ObjPt.y, SRCCOPY
	    
	    ;===============
		;Paint TOP FRAME
	    invoke StretchBlt, hdcPaint,
	    [esi].sSkinData.TopFrame.ObjPt.x, [esi].sSkinData.TopFrame.ObjPt.y, [esi].sSkinData.TopFrame.CurSize.x, [esi].sSkinData.TopFrame.CurSize.y, 
	    [esi].hdcBmp, 
	    [esi].sSkinData.TopFrame.ObjPt.x, [esi].sSkinData.TopFrame.ObjPt.y,1,[esi].sSkinData.TopFrame.ObjSize.y, SRCCOPY
	
		;Paint LEFT FRAME
	    invoke StretchBlt, hdcPaint,
	    [esi].sSkinData.LeftFrame.ObjPt.x, [esi].sSkinData.LeftFrame.ObjPt.y, [esi].sSkinData.LeftFrame.CurSize.x, [esi].sSkinData.LeftFrame.CurSize.y, 
	    [esi].hdcBmp, 
	    [esi].sSkinData.LeftFrame.ObjPt.x, [esi].sSkinData.LeftFrame.ObjPt.y,[esi].sSkinData.LeftFrame.ObjSize.x,1, SRCCOPY
	
		;Paint BOTTOM FRAME
	    invoke StretchBlt, hdcPaint,
	    [esi].sSkinData.BottomFrame.CurPt.x, [esi].sSkinData.BottomFrame.CurPt.y, [esi].sSkinData.BottomFrame.CurSize.x, [esi].sSkinData.BottomFrame.CurSize.y, 
	    [esi].hdcBmp, 
	    [esi].sSkinData.BottomFrame.ObjPt.x, [esi].sSkinData.BottomFrame.ObjPt.y,1,[esi].sSkinData.BottomFrame.ObjSize.y, SRCCOPY
	
		;Paint RIGHT FRAME
	    invoke StretchBlt, hdcPaint,
	    [esi].sSkinData.RightFrame.CurPt.x, [esi].sSkinData.RightFrame.CurPt.y, [esi].sSkinData.RightFrame.CurSize.x, [esi].sSkinData.RightFrame.CurSize.y, 
	    [esi].hdcBmp, 
	    [esi].sSkinData.RightFrame.ObjPt.x, [esi].sSkinData.RightFrame.ObjPt.y, [esi].sSkinData.RightFrame.ObjSize.x, 1,SRCCOPY

	    ;===============
		;Paint UserArea
;	    invoke StretchBlt, hdcPaint,
;	    [esi].sSkinData.UserArea.ObjPt.x, [esi].sSkinData.UserArea.ObjPt.y, [esi].sSkinData.UserArea.CurSize.x, [esi].sSkinData.UserArea.CurSize.y, 
;	    [esi].hdcBmp, 
;	    [esi].sSkinData.UserArea.ObjPt.x, [esi].sSkinData.UserArea.ObjPt.y,1,[esi].sSkinData.UserArea.ObjSize.y, SRCCOPY

	    ;===============
		;Paint WndCaption
;	    invoke StretchBlt, hdcPaint,
;	    [esi].sSkinData.WndCaption.ObjPt.x, [esi].sSkinData.WndCaption.ObjPt.y, [esi].sSkinData.WndCaption.CurSize.x, [esi].sSkinData.WndCaption.CurSize.y, 
;	    [esi].hdcBmp, 
;	    [esi].sSkinData.WndCaption.ObjPt.x, [esi].sSkinData.WndCaption.ObjPt.y,1,[esi].sSkinData.WndCaption.ObjSize.y, SRCCOPY

	    ;===============
		;Text WndCaption
;		mov LenTxt, $invoke(GetWindowText,[esi].hWnd,addr TxtCaption,128)
;		invoke GetTextExtentPoint32, hdcPaint, addr TxtCaption, LenTxt, Addr SizeTxt
;		invoke TopXY, SizeTxt.x, [esi].sSkinData.WndCaption.CurSize.x
;		add eax, [esi].sSkinData.WndCaption.ObjPt.x
;        mov PosTxt.x, eax
;		invoke TopXY, SizeTxt.y, [esi].sSkinData.WndCaption.CurSize.y
;		add eax, [esi].sSkinData.WndCaption.ObjPt.y
;        mov PosTxt.y, eax
;		invoke SetTextColor, hdcPaint, $RGB(255,255,255)
;		invoke SetBkMode, hdcPaint, TRANSPARENT
;		invoke TextOut, hdcPaint, PosTxt.x, PosTxt.y, addr TxtCaption, LenTxt
    .endif
MethodEnd

; ——————————————————————————————————————————————————————————————————————————————————————————————————
; Method:    SkinPaint.DynamicInit
; Purpose:   
; Arguments: Arg1: 
;            Arg2: 
; Return:    
; Note:      

Method SkinPaint.DynamicPaintInit, uses esi, hWnd:Handle ,WndRC:Pointer, bRegion:dword
    SetObject esi
    OCall esi.DynamicInit, hWnd, WndRC, bRegion  ;dynamic 
    invoke RedrawWindow, hWnd, NULL, NULL, RDW_INVALIDATE ;draw bitmap again
MethodEnd


TopXY Proc wDim:DWord, sDim:DWord
    Shr sDim, 1      ; divide screen dimension by 2
    shr wDim, 1      ; divide window dimension by 2
    mov eax, wDim    ; copy window dimension into eax
    sub sDim, eax    ; sub half win dimension from half screen dimension
    mov eax, sDim
    ret
TopXY EndP

