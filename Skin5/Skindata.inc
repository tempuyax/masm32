$GetDec Macro Val:Req
    ;Setup
    dec Val
    ;Done
  EXITM <Val>
ENDM

$GetVal Macro SData:Req, Val:Req
    ;Setup
    mov eax, SData.Val
    ;Done
  EXITM <eax>
ENDM

$DecVal Macro SData:Req, Val:Req
  EXITM <$GetDec($GetVal(SData,Val))>
ENDM

$AddVal Macro SData:Req, nBaseAdd:Req, Args:VarArg
    LOCAL   ArgList
    ArgList TEXTEQU <>
    
    ;Setup
    mov eax, SData.nBaseAdd
    
    ;Subtraction argument        
    IFNB <Args>
        FOR Arg,<Args>
            ArgList CATSTR <Arg>,<,>,ArgList
        ENDM
    ArgList SubStr ArgList, 1, @SizeStr(%ArgList) - 1
    ArgList CATSTR <!<>,ArgList,<!>>

    %FOR parameter,ArgList
        add eax, SData.parameter
    ENDM
    ENDIF
    
    ;Done
    
  EXITM <eax>
ENDM

$SubVal Macro SData:Req, nBaseSub:Req, Args:VarArg
    LOCAL   ArgList
    ArgList TEXTEQU <>
    
    ;Setup
    mov eax, SData.nBaseSub
    
    ;Subtraction argument        
    IFNB <Args>
        FOR Arg,<Args>
            ArgList CATSTR <Arg>,<,>,ArgList
        ENDM
    ArgList SubStr ArgList, 1, @SizeStr(%ArgList) - 1
    ArgList CATSTR <!<>,ArgList,<!>>

    %FOR parameter,ArgList
        sub eax, SData.parameter
    ENDM
    ENDIF
    
    ;Done
    
  EXITM <eax>
ENDM

$DecAddVal Macro SData:Req, nBaseAdd:Req, Args:VarArg
  EXITM <$GetDec($AddVal(SData, nBaseAdd, Args))>
ENDM

;TOP
nTopLftWidth     equ  118	
nTopLftHeight    equ  60
nTopRgtWidth     equ  196
;Bottom
nBotLftWidth     equ  86	
nBotLftHeight    equ  30
nBotRgtWidth     equ  30
;TopFrame
nTopFrameHeight  equ  16
;LR Frame
nLeftFrameWidth  equ  20
nRightFrameWidth equ  20

;===============
;Frame tile mode
nTopFrameWidth     equ  6
nLeftFrameHeight   equ  6
nRightFrameHeight  equ  6
nBottomFrameWidth  equ  6


BASE			struct
 		ObjSize	SIZEL	{} ; static data
		ObjPt	POINT	{} ; static data
		ObjRect	RECT	{} ; static data
BASE			ends

DYNAMICALL		struct		
                BASE    {}
		CurPt	POINT	{} ; dynamic data
		CurSize	SIZEL	{} ; dynamic data
		CurRect	RECT	{} ; dynamic data
DYNAMICALL		ends		

DYNAMICPOINT	struct		
                BASE    {}
		CurPt	POINT	{} ; dynamic data
		CurRect	RECT	{} ; dynamic data
DYNAMICPOINT	ends		

DYNAMICSIZE		struct		
                BASE    {}
		CurSize	SIZEL	{} ; dynamic data
		CurRect	RECT	{} ; dynamic data
DYNAMICSIZE		ends		


SKIN	struct			
		SkinSize	SIZEL			{} ; static data
		WindowRC	RECT			{} ; dynamic data
		Delta		SIZEL			{} ; dynamic data
		TopLft		BASE		    {} ; static data 
		TopRgt		DYNAMICPOINT	{} 
		BotLft		DYNAMICPOINT	{}
		BotRgt		DYNAMICPOINT	{}
		TopFrame	DYNAMICSIZE		{}
		LeftFrame	DYNAMICSIZE		{}
		BottomFrame	DYNAMICALL		{}
		RightFrame	DYNAMICALL		{}
		UserArea	DYNAMICSIZE		{}
		WndCaption	DYNAMICSIZE		{}
SKIN	ends			


Object SkinData, 929292, Primer
	RedefineMethod    Done
	RedefineMethod    Init, 			Pointer, Pointer, Pointer          

    VirtualMethod     InitWindowRC, 	Pointer
    VirtualMethod     InitSkinSize, 	Pointer
    VirtualMethod     InitObjCurrent
    VirtualMethod     HitPoint, 		dword, dword, dword
    VirtualMethod     InitDelta
    VirtualMethod     InitObjSize
    VirtualMethod     InitObjPoint
    VirtualMethod     InitObjRect
    VirtualMethod     InitObjCurSize
    VirtualMethod     InitObjCurPoint
    VirtualMethod     InitObjCurRect
    VirtualMethod     ObjDebug
    VirtualMethod     CurDebug
    VirtualMethod     InitDynamicObj, 	Pointer
    VirtualMethod     InitStaticObj, 	Pointer
    
    DefineVariable	  sSkinData,  SKIN, {}  ;Sumber data
ObjectEnd



; ——————————————————————————————————————————————————————————————————————————————————————————————————
; Method:    SkinData.Init
; Purpose:   
; Arguments: None.
; Return:    
; Note:      

Method SkinData.Init, uses esi, pOwner:Pointer, WndRC:Pointer, ObjBmp:Pointer
    SetObject esi
    ACall Init, pOwner
    
    OCall esi.InitStaticObj, ObjBmp  ;static  1
    OCall esi.InitDynamicObj, WndRC  ;dynamic 2
    
MethodEnd

; ——————————————————————————————————————————————————————————————————————————————————————————————————
; Method:    SkinData.Done
; Purpose:   
; Arguments: None.
; Return:    
; Note:      

Method SkinData.Done, uses esi
    SetObject esi
    ;OCall esi.ObjDebug
    ;OCall esi.CurDebug
    ACall Done
MethodEnd

; ——————————————————————————————————————————————————————————————————————————————————————————————————
; Method:    SkinData.InitDynamicObj
; Purpose:   
; Arguments: None.
; Return:    
; Note:      

Method SkinData.InitDynamicObj, uses esi, WndRC:Pointer
    SetObject esi

    OCall esi.InitWindowRC, WndRC  ;dynamic 1
    OCall esi.InitDelta            ;dynamic 2
    OCall esi.InitObjCurSize       ;dynamic 3 
    OCall esi.InitObjCurPoint      ;dynamic 4
    OCall esi.InitObjCurRect       ;dynamic 5
   
MethodEnd

; ——————————————————————————————————————————————————————————————————————————————————————————————————
; Method:    SkinData.InitStaticObj
; Purpose:   
; Arguments: None.
; Return:    
; Note:      

Method SkinData.InitStaticObj, uses esi, ObjBmp:Pointer
    SetObject esi
    OCall esi.InitSkinSize, ObjBmp ;static  1
    OCall esi.InitObjSize          ;static  2
    OCall esi.InitObjPoint         ;static  3
    OCall esi.InitObjRect          ;static  4
    OCall esi.InitObjCurrent       ;Static  5
MethodEnd


; ——————————————————————————————————————————————————————————————————————————————————————————————————
; Method:    SkinData.InitWindowRC
; Purpose:   
; Arguments: None.
; Return:    
; Note:      

Method SkinData.InitWindowRC, uses esi, WndRC:Pointer
    SetObject esi
    invoke CopyRect,addr [esi].sSkinData.WindowRC, WndRC
    
MethodEnd

; ——————————————————————————————————————————————————————————————————————————————————————————————————
; Method:    SkinData.InitSkinSize
; Purpose:   
; Arguments: Arg1: 
; Return:    
; Note:      

Method SkinData.InitSkinSize, uses esi, ObjBmp:Pointer
    SetObject esi
    mov eax, ObjBmp
    m2m [esi].sSkinData.SkinSize.x, (BITMAP ptr [eax]).bmWidth
    m2m [esi].sSkinData.SkinSize.y, (BITMAP ptr [eax]).bmHeight
    
MethodEnd



; ——————————————————————————————————————————————————————————————————————————————————————————————————
; Method:    SkinData.HitPoint
; Purpose:   
; Arguments: Arg1: 
;            Arg2: 
; Return:    
; Note: 
;         	OCall pSkin::SkinData.HitPoint,HTTOPLEFT,PtX, PtY     

Method SkinData.HitPoint, uses esi, nObj:dword,PtX:dword, PtY:dword
    SetObject esi
    .if nObj == HTTOPLEFT
        invoke PtInRect, addr [esi].sSkinData.TopLft.ObjRect, PtX, PtY
    .elseif nObj == HTTOPRIGHT
        invoke PtInRect, addr [esi].sSkinData.TopRgt.CurRect, PtX, PtY
    .elseif nObj == HTBOTTOMLEFT
        invoke PtInRect, addr [esi].sSkinData.BotLft.CurRect, PtX, PtY
    .elseif nObj == HTBOTTOMRIGHT
        invoke PtInRect, addr [esi].sSkinData.BotRgt.CurRect, PtX, PtY
    .elseif nObj == HTTOP
        invoke PtInRect, addr [esi].sSkinData.TopFrame.CurRect, PtX, PtY
    .elseif nObj == HTLEFT
        invoke PtInRect, addr [esi].sSkinData.LeftFrame.CurRect, PtX, PtY
    .elseif nObj == HTBOTTOM
        invoke PtInRect, addr [esi].sSkinData.BottomFrame.CurRect, PtX, PtY
    .elseif nObj == HTRIGHT
        invoke PtInRect, addr [esi].sSkinData.RightFrame.CurRect, PtX, PtY
    .elseif nObj == HTCAPTION
        invoke PtInRect, addr [esi].sSkinData.WndCaption.CurRect, PtX, PtY
    .endif
MethodEnd eax


; ——————————————————————————————————————————————————————————————————————————————————————————————————
; Method:    SkinData.SetDelta
; Purpose:   
; Arguments: Arg1: 
; Return:    
; Note:      

Method SkinData.InitDelta, uses esi
    SetObject esi

    mov [esi].sSkinData.Delta.x, $SubVal([esi].sSkinData,WindowRC.right,SkinSize.x)
    mov [esi].sSkinData.Delta.y, $SubVal([esi].sSkinData,WindowRC.bottom,SkinSize.y)
    
MethodEnd

; ——————————————————————————————————————————————————————————————————————————————————————————————————
; Method:    SkinData.InitSize
; Purpose:   
; Arguments: None.
; Return:    
; Note:      

Method SkinData.InitObjSize, uses esi
    SetObject esi
    ;SIZE TopLft 
    mov [esi].sSkinData.TopLft.ObjSize.x, nTopLftWidth 
    mov [esi].sSkinData.TopLft.ObjSize.y, nTopLftHeight 
    ;SIZE TopRgt 
    mov [esi].sSkinData.TopRgt.ObjSize.x, nTopRgtWidth 
    mov [esi].sSkinData.TopRgt.ObjSize.y, $GetVal([esi].sSkinData,TopLft.ObjSize.y)
    ;SIZE BotLft 
    mov [esi].sSkinData.BotLft.ObjSize.x, nBotLftWidth 
    mov [esi].sSkinData.BotLft.ObjSize.y, nBotLftHeight 
    ;SIZE BotRgt 
    mov [esi].sSkinData.BotRgt.ObjSize.x, nBotRgtWidth 
    mov [esi].sSkinData.BotRgt.ObjSize.y, $GetVal([esi].sSkinData,BotLft.ObjSize.y)
    ;SIZE TopFrame 
    mov [esi].sSkinData.TopFrame.ObjSize.x, $SubVal([esi].sSkinData,SkinSize.x,TopLft.ObjSize.x,TopRgt.ObjSize.x) 
    mov [esi].sSkinData.TopFrame.ObjSize.y, nTopFrameHeight 
    ;SIZE LeftFrame 
    mov [esi].sSkinData.LeftFrame.ObjSize.x, nLeftFrameWidth 
    mov [esi].sSkinData.LeftFrame.ObjSize.y, $SubVal([esi].sSkinData,SkinSize.y,TopLft.ObjSize.y,BotLft.ObjSize.y) 
    ;SIZE BottomFrame 
    mov [esi].sSkinData.BottomFrame.ObjSize.x, $SubVal([esi].sSkinData,SkinSize.x,BotLft.ObjSize.x,BotRgt.ObjSize.x) 
    mov [esi].sSkinData.BottomFrame.ObjSize.y, $GetVal([esi].sSkinData,BotLft.ObjSize.y) 
    ;SIZE RightFrame 
    mov [esi].sSkinData.RightFrame.ObjSize.x, nRightFrameWidth 
    mov [esi].sSkinData.RightFrame.ObjSize.y, $GetVal([esi].sSkinData,LeftFrame.ObjSize.y)  
    ;SIZE UserArea 
    mov [esi].sSkinData.UserArea.ObjSize.x, $SubVal([esi].sSkinData,SkinSize.x,LeftFrame.ObjSize.x,RightFrame.ObjSize.x) 
    mov [esi].sSkinData.UserArea.ObjSize.y, $GetVal([esi].sSkinData,LeftFrame.ObjSize.y) 
    ;SIZE WndCaption 
    mov [esi].sSkinData.WndCaption.ObjSize.x, $GetVal([esi].sSkinData,TopFrame.ObjSize.x) 
    mov [esi].sSkinData.WndCaption.ObjSize.y, $SubVal([esi].sSkinData,SkinSize.y,TopFrame.ObjSize.y,UserArea.ObjSize.y,BottomFrame.ObjSize.y) 

MethodEnd

; ——————————————————————————————————————————————————————————————————————————————————————————————————
; Method:    SkinData.InitPoint
; Purpose:   
; Arguments: None.
; Return:    
; Note:      

Method SkinData.InitObjPoint, uses esi
    SetObject esi
    ;POINT TopRgt 
    mov [esi].sSkinData.TopRgt.ObjPt.x,$SubVal([esi].sSkinData,SkinSize.x,TopRgt.ObjSize.x)
    ;POINT BotLft 
    mov [esi].sSkinData.BotLft.ObjPt.y,$SubVal([esi].sSkinData,SkinSize.y,BotLft.ObjSize.y)
    ;POINT BotRgt 
    mov [esi].sSkinData.BotRgt.ObjPt.x,$SubVal([esi].sSkinData,SkinSize.x,BotRgt.ObjSize.x)
    mov [esi].sSkinData.BotRgt.ObjPt.y,$GetVal([esi].sSkinData,BotLft.ObjPt.y)
    ;POINT TopFrame 
    mov [esi].sSkinData.TopFrame.ObjPt.x,$GetVal([esi].sSkinData,TopLft.ObjSize.x)
    ;POINT LeftFrame 
    mov [esi].sSkinData.LeftFrame.ObjPt.y,$GetVal([esi].sSkinData,TopLft.ObjSize.y)
    ;POINT BottomFrame 
    mov [esi].sSkinData.BottomFrame.ObjPt.x,$GetVal([esi].sSkinData,BotLft.ObjSize.x)
    mov [esi].sSkinData.BottomFrame.ObjPt.y,$GetVal([esi].sSkinData,BotLft.ObjPt.y)
    ;POINT RightFrame 
    mov [esi].sSkinData.RightFrame.ObjPt.x,$SubVal([esi].sSkinData,SkinSize.x,RightFrame.ObjSize.x)
    mov [esi].sSkinData.RightFrame.ObjPt.y,$GetVal([esi].sSkinData,TopRgt.ObjSize.y)
    ;POINT UserArea 
    mov [esi].sSkinData.UserArea.ObjPt.x,$GetVal([esi].sSkinData,LeftFrame.ObjSize.x)
    mov [esi].sSkinData.UserArea.ObjPt.y,$GetVal([esi].sSkinData,TopLft.ObjSize.y)
    ;POINT WndCaption 
    mov [esi].sSkinData.WndCaption.ObjPt.x,$GetVal([esi].sSkinData,TopLft.ObjSize.x)
    mov [esi].sSkinData.WndCaption.ObjPt.y,$GetVal([esi].sSkinData,TopFrame.ObjSize.y)
    
MethodEnd


; ——————————————————————————————————————————————————————————————————————————————————————————————————
; Method:    SkinData.InitRect
; Purpose:   
; Arguments: None.
; Return:    
; Note:      

Method SkinData.InitObjRect, uses esi
    SetObject esi
    ;RECT TopLft 
    mov [esi].sSkinData.TopLft.ObjRect.right,$DecAddVal([esi].sSkinData,TopLft.ObjPt.x,TopLft.ObjSize.x)
    mov [esi].sSkinData.TopLft.ObjRect.bottom,$DecAddVal([esi].sSkinData,TopLft.ObjPt.y,TopLft.ObjSize.y)
    ;RECT TopRgt 
    mov [esi].sSkinData.TopRgt.ObjRect.left,$GetVal([esi].sSkinData,TopRgt.ObjPt.x)
    mov [esi].sSkinData.TopRgt.ObjRect.right,$DecAddVal([esi].sSkinData,TopRgt.ObjPt.x,TopRgt.ObjSize.x)
    mov [esi].sSkinData.TopRgt.ObjRect.bottom,$DecAddVal([esi].sSkinData,TopRgt.ObjPt.y,TopRgt.ObjSize.y)
    ;RECT BotLft 
    mov [esi].sSkinData.BotLft.ObjRect.top,$GetVal([esi].sSkinData,BotLft.ObjPt.y)
    mov [esi].sSkinData.BotLft.ObjRect.right,$DecAddVal([esi].sSkinData,BotLft.ObjPt.x,BotLft.ObjSize.x)
    mov [esi].sSkinData.BotLft.ObjRect.bottom,$DecAddVal([esi].sSkinData,BotLft.ObjPt.y,BotLft.ObjSize.y)
    ;RECT BotRgt 
    mov [esi].sSkinData.BotRgt.ObjRect.left,$GetVal([esi].sSkinData,BotRgt.ObjPt.x)
    mov [esi].sSkinData.BotRgt.ObjRect.top,$GetVal([esi].sSkinData,BotRgt.ObjPt.y)
    mov [esi].sSkinData.BotRgt.ObjRect.right,$DecAddVal([esi].sSkinData,BotRgt.ObjPt.x,BotRgt.ObjSize.x)
    mov [esi].sSkinData.BotRgt.ObjRect.bottom,$DecAddVal([esi].sSkinData,BotRgt.ObjPt.y,BotRgt.ObjSize.y)
    ;RECT TopFrame 
    mov [esi].sSkinData.TopFrame.ObjRect.left,$GetVal([esi].sSkinData,TopFrame.ObjPt.x)
    mov [esi].sSkinData.TopFrame.ObjRect.right,$DecAddVal([esi].sSkinData,TopFrame.ObjPt.x,TopFrame.ObjSize.x)
    mov [esi].sSkinData.TopFrame.ObjRect.bottom,$DecAddVal([esi].sSkinData,TopFrame.ObjPt.y,TopFrame.ObjSize.y)
    ;RECT LeftFrame 
    mov [esi].sSkinData.LeftFrame.ObjRect.top,$GetVal([esi].sSkinData,LeftFrame.ObjPt.y)
    mov [esi].sSkinData.LeftFrame.ObjRect.right,$DecAddVal([esi].sSkinData,LeftFrame.ObjPt.x,LeftFrame.ObjSize.x)
    mov [esi].sSkinData.LeftFrame.ObjRect.bottom,$DecAddVal([esi].sSkinData,LeftFrame.ObjPt.y,LeftFrame.ObjSize.y)
    ;RECT BottomFrame 
    mov [esi].sSkinData.BottomFrame.ObjRect.left,$GetVal([esi].sSkinData,BottomFrame.ObjPt.x)
    mov [esi].sSkinData.BottomFrame.ObjRect.top,$GetVal([esi].sSkinData,BottomFrame.ObjPt.y)
    mov [esi].sSkinData.BottomFrame.ObjRect.right,$DecAddVal([esi].sSkinData,BottomFrame.ObjPt.x,BottomFrame.ObjSize.x)
    mov [esi].sSkinData.BottomFrame.ObjRect.bottom,$DecAddVal([esi].sSkinData,BottomFrame.ObjPt.y,BottomFrame.ObjSize.y)
    ;RECT RightFrame 
    mov [esi].sSkinData.RightFrame.ObjRect.left,$GetVal([esi].sSkinData,RightFrame.ObjPt.x)
    mov [esi].sSkinData.RightFrame.ObjRect.top,$GetVal([esi].sSkinData,RightFrame.ObjPt.y)
    mov [esi].sSkinData.RightFrame.ObjRect.right,$DecAddVal([esi].sSkinData,RightFrame.ObjPt.x,RightFrame.ObjSize.x)
    mov [esi].sSkinData.RightFrame.ObjRect.bottom,$DecAddVal([esi].sSkinData,RightFrame.ObjPt.y,RightFrame.ObjSize.y)
    ;RECT UserArea 
    mov [esi].sSkinData.UserArea.ObjRect.left,$GetVal([esi].sSkinData,UserArea.ObjPt.x)
    mov [esi].sSkinData.UserArea.ObjRect.top,$GetVal([esi].sSkinData,UserArea.ObjPt.y)
    mov [esi].sSkinData.UserArea.ObjRect.right,$DecAddVal([esi].sSkinData,UserArea.ObjPt.x,UserArea.ObjSize.x)
    mov [esi].sSkinData.UserArea.ObjRect.bottom,$DecAddVal([esi].sSkinData,UserArea.ObjPt.y,UserArea.ObjSize.y)
    ;RECT WndCaption 
    mov [esi].sSkinData.WndCaption.ObjRect.left,$GetVal([esi].sSkinData,WndCaption.ObjPt.x)
    mov [esi].sSkinData.WndCaption.ObjRect.top,$GetVal([esi].sSkinData,WndCaption.ObjPt.y)
    mov [esi].sSkinData.WndCaption.ObjRect.right,$DecAddVal([esi].sSkinData,WndCaption.ObjPt.x,WndCaption.ObjSize.x)
    mov [esi].sSkinData.WndCaption.ObjRect.bottom,$DecAddVal([esi].sSkinData,WndCaption.ObjPt.y,WndCaption.ObjSize.y)
    
MethodEnd
; ——————————————————————————————————————————————————————————————————————————————————————————————————
; Method:    SkinData.InitObjCurrent
; Purpose:   
; Arguments: None.
; Return:    
; Note:      

Method SkinData.InitObjCurrent, uses esi
    SetObject esi
	;COPY SIZE TopFrame
    invoke MemClone,addr [esi].sSkinData.TopFrame.CurSize, addr [esi].sSkinData.TopFrame.ObjSize, sizeof SIZEL 
	;COPY SIZE LeftFrame
    invoke MemClone,addr [esi].sSkinData.LeftFrame.CurSize, addr [esi].sSkinData.LeftFrame.ObjSize, sizeof SIZEL 
	;COPY SIZE BottomFrame
    invoke MemClone,addr [esi].sSkinData.BottomFrame.CurSize, addr [esi].sSkinData.BottomFrame.ObjSize, sizeof SIZEL 
	;COPY SIZE RightFrame
    invoke MemClone,addr [esi].sSkinData.RightFrame.CurSize, addr [esi].sSkinData.RightFrame.ObjSize, sizeof SIZEL 
	;COPY SIZE UserArea
    invoke MemClone,addr [esi].sSkinData.UserArea.CurSize, addr [esi].sSkinData.UserArea.ObjSize, sizeof SIZEL 
	;COPY SIZE WndCaption
    invoke MemClone,addr [esi].sSkinData.WndCaption.CurSize, addr [esi].sSkinData.WndCaption.ObjSize, sizeof SIZEL 

	;COPY POINT TopRgt
    invoke MemClone,addr [esi].sSkinData.TopRgt.CurPt, addr [esi].sSkinData.TopRgt.ObjPt, sizeof POINT 
	;COPY POINT BotLft
    invoke MemClone,addr [esi].sSkinData.BotLft.CurPt, addr [esi].sSkinData.BotLft.ObjPt, sizeof POINT 
	;COPY POINT BotRgt
    invoke MemClone,addr [esi].sSkinData.BotRgt.CurPt, addr [esi].sSkinData.BotRgt.ObjPt, sizeof POINT 
	;COPY POINT BottomFrame
    invoke MemClone,addr [esi].sSkinData.BottomFrame.CurPt, addr [esi].sSkinData.BottomFrame.ObjPt, sizeof POINT 
	;COPY POINT RightFrame
    invoke MemClone,addr [esi].sSkinData.RightFrame.CurPt, addr [esi].sSkinData.RightFrame.ObjPt, sizeof POINT 

	;CURRENT RECT TopRgt
    invoke MemClone,addr [esi].sSkinData.TopRgt.CurRect, addr [esi].sSkinData.TopRgt.ObjRect, sizeof RECT 
	;CURRENT RECT BotLft
    invoke MemClone,addr [esi].sSkinData.BotLft.CurRect, addr [esi].sSkinData.BotLft.ObjRect, sizeof RECT 
	;CURRENT RECT BotRgt
    invoke MemClone,addr [esi].sSkinData.BotRgt.CurRect, addr [esi].sSkinData.BotRgt.ObjRect, sizeof RECT 
	;CURRENT RECT TopFrame
    invoke MemClone,addr [esi].sSkinData.TopFrame.CurRect, addr [esi].sSkinData.TopFrame.ObjRect, sizeof RECT 
	;CURRENT RECT LeftFrame
    invoke MemClone,addr [esi].sSkinData.LeftFrame.CurRect, addr [esi].sSkinData.LeftFrame.ObjRect, sizeof RECT 
	;CURRENT RECT BottomFrame
    invoke MemClone,addr [esi].sSkinData.BottomFrame.CurRect, addr [esi].sSkinData.BottomFrame.ObjRect, sizeof RECT 
	;CURRENT RECT RightFrame
    invoke MemClone,addr [esi].sSkinData.RightFrame.CurRect, addr [esi].sSkinData.RightFrame.ObjRect, sizeof RECT 
	;CURRENT RECT UserArea
    invoke MemClone,addr [esi].sSkinData.UserArea.CurRect, addr [esi].sSkinData.UserArea.ObjRect, sizeof RECT 
	;CURRENT RECT WndCaption
    invoke MemClone,addr [esi].sSkinData.WndCaption.CurRect, addr [esi].sSkinData.WndCaption.ObjRect, sizeof RECT 
    
MethodEnd


; ——————————————————————————————————————————————————————————————————————————————————————————————————
; Method:    SkinData.InitObjCurSize
; Purpose:   
; Arguments: None.
; Return:    
; Note:      

Method SkinData.InitObjCurSize, uses esi
    SetObject esi

    ;CURRENT SIZE TopFrame 
    mov [esi].sSkinData.TopFrame.CurSize.x, $AddVal([esi].sSkinData,TopFrame.ObjSize.x,Delta.x) 
    ;CURRENT SIZE LeftFrame 
    mov [esi].sSkinData.LeftFrame.CurSize.y, $AddVal([esi].sSkinData,LeftFrame.ObjSize.y,Delta.y) 
    ;CURRENT SIZE BottomFrame 
    mov [esi].sSkinData.BottomFrame.CurSize.x, $AddVal([esi].sSkinData,BottomFrame.ObjSize.x,Delta.x) 
    ;CURRENT SIZE RightFrame 
    mov [esi].sSkinData.RightFrame.CurSize.y, $AddVal([esi].sSkinData,RightFrame.ObjSize.y,Delta.y)  
    ;CURRENT SIZE UserArea 
    mov [esi].sSkinData.UserArea.CurSize.x, $AddVal([esi].sSkinData,UserArea.ObjSize.x,Delta.x) 
    mov [esi].sSkinData.UserArea.CurSize.y, $AddVal([esi].sSkinData,UserArea.ObjSize.y,Delta.y) 
    ;CURRENT SIZE WndCaption 
    mov [esi].sSkinData.WndCaption.CurSize.x, $AddVal([esi].sSkinData,WndCaption.ObjSize.x,Delta.x) 
    
MethodEnd

; ——————————————————————————————————————————————————————————————————————————————————————————————————
; Method:    SkinData.InitObjCurPoint
; Purpose:   
; Arguments: None.
; Return:    
; Note:      

Method SkinData.InitObjCurPoint, uses esi
    SetObject esi
	;CURRENT POINT TopRgt
    mov [esi].sSkinData.TopRgt.CurPt.x, $AddVal([esi].sSkinData,TopRgt.ObjPt.x,Delta.x) 
	;CURRENT POINT BotLft
    mov [esi].sSkinData.BotLft.CurPt.y, $AddVal([esi].sSkinData,BotLft.ObjPt.y,Delta.y) 
	;CURRENT POINT BotRgt
    mov [esi].sSkinData.BotRgt.CurPt.x, $AddVal([esi].sSkinData,BotRgt.ObjPt.x,Delta.x) 
    mov [esi].sSkinData.BotRgt.CurPt.y, $AddVal([esi].sSkinData,BotRgt.ObjPt.y,Delta.y) 
	;CURRENT POINT BottomFrame
    mov [esi].sSkinData.BottomFrame.CurPt.y, $AddVal([esi].sSkinData,BottomFrame.ObjPt.y,Delta.y) 
	;CURRENT POINT RightFrame
    mov [esi].sSkinData.RightFrame.CurPt.x, $AddVal([esi].sSkinData,RightFrame.ObjPt.x,Delta.x) 
    
MethodEnd


; ——————————————————————————————————————————————————————————————————————————————————————————————————
; Method:    SkinData.initObjCurRect
; Purpose:   
; Arguments: None.
; Return:    
; Note:      

Method SkinData.InitObjCurRect, uses esi
    SetObject esi
	;CURRENT RECT TopRgt
    mov [esi].sSkinData.TopRgt.CurRect.left,$AddVal([esi].sSkinData,TopRgt.ObjRect.left,Delta.x) 
    mov [esi].sSkinData.TopRgt.CurRect.right,$AddVal([esi].sSkinData,TopRgt.ObjRect.right,Delta.x) 
	;CURRENT RECT BotLft
    mov [esi].sSkinData.BotLft.CurRect.top,$AddVal([esi].sSkinData,BotLft.ObjRect.top,Delta.y) 
    mov [esi].sSkinData.BotLft.CurRect.bottom,$AddVal([esi].sSkinData,BotLft.ObjRect.bottom,Delta.y) 
	;CURRENT RECT BotRgt
    mov [esi].sSkinData.BotRgt.CurRect.left,$AddVal([esi].sSkinData,BotRgt.ObjRect.left,Delta.x) 
    mov [esi].sSkinData.BotRgt.CurRect.top,$AddVal([esi].sSkinData,BotRgt.ObjRect.top,Delta.y) 
    mov [esi].sSkinData.BotRgt.CurRect.right,$AddVal([esi].sSkinData,BotRgt.ObjRect.right,Delta.x) 
    mov [esi].sSkinData.BotRgt.CurRect.bottom,$AddVal([esi].sSkinData,BotRgt.ObjRect.bottom,Delta.y) 
	;CURRENT RECT TopFrame
    mov [esi].sSkinData.TopFrame.CurRect.right,$AddVal([esi].sSkinData,TopFrame.ObjRect.right,Delta.x) 
	;CURRENT RECT LeftFrame
    mov [esi].sSkinData.LeftFrame.CurRect.bottom,$AddVal([esi].sSkinData,LeftFrame.ObjRect.bottom,Delta.y) 
	;CURRENT RECT BottomFrame
    mov [esi].sSkinData.BottomFrame.CurRect.top,$AddVal([esi].sSkinData,BottomFrame.ObjRect.top,Delta.y) 
    mov [esi].sSkinData.BottomFrame.CurRect.right,$AddVal([esi].sSkinData,BottomFrame.ObjRect.right,Delta.x) 
    mov [esi].sSkinData.BottomFrame.CurRect.bottom,$AddVal([esi].sSkinData,BottomFrame.ObjRect.bottom,Delta.y) 
	;CURRENT RECT RightFrame
    mov [esi].sSkinData.RightFrame.CurRect.left,$AddVal([esi].sSkinData,RightFrame.ObjRect.left,Delta.x) 
    mov [esi].sSkinData.RightFrame.CurRect.right,$AddVal([esi].sSkinData,RightFrame.ObjRect.right,Delta.x) 
    mov [esi].sSkinData.RightFrame.CurRect.bottom,$AddVal([esi].sSkinData,RightFrame.ObjRect.bottom,Delta.y) 
	;CURRENT RECT UserArea
    mov [esi].sSkinData.UserArea.CurRect.right,$AddVal([esi].sSkinData,UserArea.ObjRect.right,Delta.x) 
    mov [esi].sSkinData.UserArea.CurRect.bottom,$AddVal([esi].sSkinData,UserArea.ObjRect.bottom,Delta.y) 
	;CURRENT RECT WndCaption
    mov [esi].sSkinData.WndCaption.CurRect.right,$AddVal([esi].sSkinData,WndCaption.ObjRect.right,Delta.x) 
    
MethodEnd

; ——————————————————————————————————————————————————————————————————————————————————————————————————
; Method:    SkinData.ObjDebug
; Purpose:   
; Arguments: None.
; Return:    
; Note:      

Method SkinData.ObjDebug, uses esi
    SetObject esi
    DbgWarning "WindowRC"
    	DbgDec [esi].sSkinData.WindowRC.left
    	DbgDec [esi].sSkinData.WindowRC.top
    	DbgDec [esi].sSkinData.WindowRC.right
    	DbgDec [esi].sSkinData.WindowRC.bottom
    DbgWarning "SkinSize"
    	DbgDec [esi].sSkinData.SkinSize.x
    	DbgDec [esi].sSkinData.SkinSize.y
    DbgWarning "Delta"
    	DbgDec [esi].sSkinData.Delta.x
    	DbgDec [esi].sSkinData.Delta.y
    DbgWarning "TopLft"
	    DbgText "ObjSize"
	    	DbgDec [esi].sSkinData.TopLft.ObjSize.x
	    	DbgDec [esi].sSkinData.TopLft.ObjSize.y
	    DbgText "ObjPt"
	    	DbgDec [esi].sSkinData.TopLft.ObjPt.x
	    	DbgDec [esi].sSkinData.TopLft.ObjPt.y
	    DbgText "ObjRect"
	    	DbgDec [esi].sSkinData.TopLft.ObjRect.left
	    	DbgDec [esi].sSkinData.TopLft.ObjRect.top
	    	DbgDec [esi].sSkinData.TopLft.ObjRect.right
	    	DbgDec [esi].sSkinData.TopLft.ObjRect.bottom
    DbgWarning "TopRgt"
	    DbgText "ObjSize"
	    	DbgDec [esi].sSkinData.TopRgt.ObjSize.x
	    	DbgDec [esi].sSkinData.TopRgt.ObjSize.y
	    DbgText "ObjPt"
	    	DbgDec [esi].sSkinData.TopRgt.ObjPt.x
	    	DbgDec [esi].sSkinData.TopRgt.ObjPt.y
	    DbgText "ObjRect"
	    	DbgDec [esi].sSkinData.TopRgt.ObjRect.left
	    	DbgDec [esi].sSkinData.TopRgt.ObjRect.top
	    	DbgDec [esi].sSkinData.TopRgt.ObjRect.right
	    	DbgDec [esi].sSkinData.TopRgt.ObjRect.bottom
    DbgWarning "BotLft"
	    DbgText "ObjSize"
	    	DbgDec [esi].sSkinData.BotLft.ObjSize.x
	    	DbgDec [esi].sSkinData.BotLft.ObjSize.y
	    DbgText "ObjPt"
	    	DbgDec [esi].sSkinData.BotLft.ObjPt.x
	    	DbgDec [esi].sSkinData.BotLft.ObjPt.y
	    DbgText "ObjRect"
	    	DbgDec [esi].sSkinData.BotLft.ObjRect.left
	    	DbgDec [esi].sSkinData.BotLft.ObjRect.top
	    	DbgDec [esi].sSkinData.BotLft.ObjRect.right
	    	DbgDec [esi].sSkinData.BotLft.ObjRect.bottom
    DbgWarning "BotRgt"
	    DbgText "ObjSize"
	    	DbgDec [esi].sSkinData.BotRgt.ObjSize.x
	    	DbgDec [esi].sSkinData.BotRgt.ObjSize.y
	    DbgText "ObjPt"
	    	DbgDec [esi].sSkinData.BotRgt.ObjPt.x
	    	DbgDec [esi].sSkinData.BotRgt.ObjPt.y
	    DbgText "ObjRect"
	    	DbgDec [esi].sSkinData.BotRgt.ObjRect.left
	    	DbgDec [esi].sSkinData.BotRgt.ObjRect.top
	    	DbgDec [esi].sSkinData.BotRgt.ObjRect.right
	    	DbgDec [esi].sSkinData.BotRgt.ObjRect.bottom
    DbgWarning "TopFrame"
	    DbgText "ObjSize"
	    	DbgDec [esi].sSkinData.TopFrame.ObjSize.x
	    	DbgDec [esi].sSkinData.TopFrame.ObjSize.y
	    DbgText "ObjPt"
	    	DbgDec [esi].sSkinData.TopFrame.ObjPt.x
	    	DbgDec [esi].sSkinData.TopFrame.ObjPt.y
	    DbgText "ObjRect"
	    	DbgDec [esi].sSkinData.TopFrame.ObjRect.left
	    	DbgDec [esi].sSkinData.TopFrame.ObjRect.top
	    	DbgDec [esi].sSkinData.TopFrame.ObjRect.right
	    	DbgDec [esi].sSkinData.TopFrame.ObjRect.bottom
    DbgWarning "LeftFrame"
	    DbgText "ObjSize"
	    	DbgDec [esi].sSkinData.LeftFrame.ObjSize.x
	    	DbgDec [esi].sSkinData.LeftFrame.ObjSize.y
	    DbgText "ObjPt"
	    	DbgDec [esi].sSkinData.LeftFrame.ObjPt.x
	    	DbgDec [esi].sSkinData.LeftFrame.ObjPt.y
	    DbgText "ObjRect"
	    	DbgDec [esi].sSkinData.LeftFrame.ObjRect.left
	    	DbgDec [esi].sSkinData.LeftFrame.ObjRect.top
	    	DbgDec [esi].sSkinData.LeftFrame.ObjRect.right
	    	DbgDec [esi].sSkinData.LeftFrame.ObjRect.bottom
    DbgWarning "BottomFrame"
	    DbgText "ObjSize"
	    	DbgDec [esi].sSkinData.BottomFrame.ObjSize.x
	    	DbgDec [esi].sSkinData.BottomFrame.ObjSize.y
	    DbgText "ObjPt"
	    	DbgDec [esi].sSkinData.BottomFrame.ObjPt.x
	    	DbgDec [esi].sSkinData.BottomFrame.ObjPt.y
	    DbgText "ObjRect"
	    	DbgDec [esi].sSkinData.BottomFrame.ObjRect.left
	    	DbgDec [esi].sSkinData.BottomFrame.ObjRect.top
	    	DbgDec [esi].sSkinData.BottomFrame.ObjRect.right
	    	DbgDec [esi].sSkinData.BottomFrame.ObjRect.bottom
    DbgWarning "RightFrame"
	    DbgText "ObjSize"
	    	DbgDec [esi].sSkinData.RightFrame.ObjSize.x
	    	DbgDec [esi].sSkinData.RightFrame.ObjSize.y
	    DbgText "ObjPt"
	    	DbgDec [esi].sSkinData.RightFrame.ObjPt.x
	    	DbgDec [esi].sSkinData.RightFrame.ObjPt.y
	    DbgText "ObjRect"
	    	DbgDec [esi].sSkinData.RightFrame.ObjRect.left
	    	DbgDec [esi].sSkinData.RightFrame.ObjRect.top
	    	DbgDec [esi].sSkinData.RightFrame.ObjRect.right
	    	DbgDec [esi].sSkinData.RightFrame.ObjRect.bottom
    DbgWarning "WndCaption"
	    DbgText "ObjSize"
	    	DbgDec [esi].sSkinData.WndCaption.ObjSize.x
	    	DbgDec [esi].sSkinData.WndCaption.ObjSize.y
	    DbgText "ObjPt"
	    	DbgDec [esi].sSkinData.WndCaption.ObjPt.x
	    	DbgDec [esi].sSkinData.WndCaption.ObjPt.y
	    DbgText "ObjRect"
	    	DbgDec [esi].sSkinData.WndCaption.ObjRect.left
	    	DbgDec [esi].sSkinData.WndCaption.ObjRect.top
	    	DbgDec [esi].sSkinData.WndCaption.ObjRect.right
	    	DbgDec [esi].sSkinData.WndCaption.ObjRect.bottom
    DbgWarning "UserArea"
	    DbgText "ObjSize"
	    	DbgDec [esi].sSkinData.UserArea.ObjSize.x
	    	DbgDec [esi].sSkinData.UserArea.ObjSize.y
	    DbgText "ObjPt"
	    	DbgDec [esi].sSkinData.UserArea.ObjPt.x
	    	DbgDec [esi].sSkinData.UserArea.ObjPt.y
	    DbgText "ObjRect"
	    	DbgDec [esi].sSkinData.UserArea.ObjRect.left
	    	DbgDec [esi].sSkinData.UserArea.ObjRect.top
	    	DbgDec [esi].sSkinData.UserArea.ObjRect.right
	    	DbgDec [esi].sSkinData.UserArea.ObjRect.bottom
MethodEnd

; ——————————————————————————————————————————————————————————————————————————————————————————————————
; Method:    SkinData.CurDebug
; Purpose:   
; Arguments: None.
; Return:    
; Note:      

Method SkinData.CurDebug, uses esi
    SetObject esi
    DbgWarning "TopLft"
	    DbgText "ObjSize"
	    	DbgDec [esi].sSkinData.TopLft.ObjSize.x
	    	DbgDec [esi].sSkinData.TopLft.ObjSize.y
	    DbgText "ObjPt"
	    	DbgDec [esi].sSkinData.TopLft.ObjPt.x
	    	DbgDec [esi].sSkinData.TopLft.ObjPt.y
	    DbgText "ObjRect"
	    	DbgDec [esi].sSkinData.TopLft.ObjRect.left
	    	DbgDec [esi].sSkinData.TopLft.ObjRect.top
	    	DbgDec [esi].sSkinData.TopLft.ObjRect.right
	    	DbgDec [esi].sSkinData.TopLft.ObjRect.bottom
    DbgWarning "TopRgt"
	    DbgText "CurPt"
	    	DbgDec [esi].sSkinData.TopRgt.CurPt.x
	    	DbgDec [esi].sSkinData.TopRgt.CurPt.y
	    DbgText "CurRect"
	    	DbgDec [esi].sSkinData.TopRgt.CurRect.left
	    	DbgDec [esi].sSkinData.TopRgt.CurRect.top
	    	DbgDec [esi].sSkinData.TopRgt.CurRect.right
	    	DbgDec [esi].sSkinData.TopRgt.CurRect.bottom
    DbgWarning "BotLft"
	    DbgText "CurPt"
	    	DbgDec [esi].sSkinData.BotLft.CurPt.x
	    	DbgDec [esi].sSkinData.BotLft.CurPt.y
	    DbgText "CurRect"
	    	DbgDec [esi].sSkinData.BotLft.CurRect.left
	    	DbgDec [esi].sSkinData.BotLft.CurRect.top
	    	DbgDec [esi].sSkinData.BotLft.CurRect.right
	    	DbgDec [esi].sSkinData.BotLft.CurRect.bottom
    DbgWarning "BotRgt"
	    DbgText "CurPt"
	    	DbgDec [esi].sSkinData.BotRgt.CurPt.x
	    	DbgDec [esi].sSkinData.BotRgt.CurPt.y
	    DbgText "CurRect"
	    	DbgDec [esi].sSkinData.BotRgt.CurRect.left
	    	DbgDec [esi].sSkinData.BotRgt.CurRect.top
	    	DbgDec [esi].sSkinData.BotRgt.CurRect.right
	    	DbgDec [esi].sSkinData.BotRgt.CurRect.bottom
    DbgWarning "TopFrame"
	    DbgText "CurSize"
	    	DbgDec [esi].sSkinData.TopFrame.CurSize.x
	    	DbgDec [esi].sSkinData.TopFrame.CurSize.y
	    DbgText "CurRect"
	    	DbgDec [esi].sSkinData.TopFrame.CurRect.left
	    	DbgDec [esi].sSkinData.TopFrame.CurRect.top
	    	DbgDec [esi].sSkinData.TopFrame.CurRect.right
	    	DbgDec [esi].sSkinData.TopFrame.CurRect.bottom
    DbgWarning "LeftFrame"
	    DbgText "CurSize"
	    	DbgDec [esi].sSkinData.LeftFrame.CurSize.x
	    	DbgDec [esi].sSkinData.LeftFrame.CurSize.y
	    DbgText "CurRect"
	    	DbgDec [esi].sSkinData.LeftFrame.CurRect.left
	    	DbgDec [esi].sSkinData.LeftFrame.CurRect.top
	    	DbgDec [esi].sSkinData.LeftFrame.CurRect.right
	    	DbgDec [esi].sSkinData.LeftFrame.CurRect.bottom
    DbgWarning "BottomFrame"
	    DbgText "CurSize"
	    	DbgDec [esi].sSkinData.BottomFrame.CurSize.x
	    	DbgDec [esi].sSkinData.BottomFrame.CurSize.y
	    DbgText "CurPt"
	    	DbgDec [esi].sSkinData.BottomFrame.CurPt.x
	    	DbgDec [esi].sSkinData.BottomFrame.CurPt.y
	    DbgText "CurRect"
	    	DbgDec [esi].sSkinData.BottomFrame.CurRect.left
	    	DbgDec [esi].sSkinData.BottomFrame.CurRect.top
	    	DbgDec [esi].sSkinData.BottomFrame.CurRect.right
	    	DbgDec [esi].sSkinData.BottomFrame.CurRect.bottom
    DbgWarning "RightFrame"
	    DbgText "CurSize"
	    	DbgDec [esi].sSkinData.RightFrame.CurSize.x
	    	DbgDec [esi].sSkinData.RightFrame.CurSize.y
	    DbgText "CurPt"
	    	DbgDec [esi].sSkinData.RightFrame.CurPt.x
	    	DbgDec [esi].sSkinData.RightFrame.CurPt.y
	    DbgText "CurRect"
	    	DbgDec [esi].sSkinData.RightFrame.CurRect.left
	    	DbgDec [esi].sSkinData.RightFrame.CurRect.top
	    	DbgDec [esi].sSkinData.RightFrame.CurRect.right
	    	DbgDec [esi].sSkinData.RightFrame.CurRect.bottom
    DbgWarning "WndCaption"
	    DbgText "CurSize"
	    	DbgDec [esi].sSkinData.WndCaption.CurSize.x
	    	DbgDec [esi].sSkinData.WndCaption.CurSize.y
	    DbgText "ObjPt"
	    	DbgDec [esi].sSkinData.WndCaption.ObjPt.x
	    	DbgDec [esi].sSkinData.WndCaption.ObjPt.y
	    DbgText "CurRect"
	    	DbgDec [esi].sSkinData.WndCaption.CurRect.left
	    	DbgDec [esi].sSkinData.WndCaption.CurRect.top
	    	DbgDec [esi].sSkinData.WndCaption.CurRect.right
	    	DbgDec [esi].sSkinData.WndCaption.CurRect.bottom
    DbgWarning "UserArea"
	    DbgText "CurSize"
	    	DbgDec [esi].sSkinData.UserArea.CurSize.x
	    	DbgDec [esi].sSkinData.UserArea.CurSize.y
	    DbgText "ObjPt"
	    	DbgDec [esi].sSkinData.UserArea.ObjPt.x
	    	DbgDec [esi].sSkinData.UserArea.ObjPt.y
	    DbgText "CurRect"
	    	DbgDec [esi].sSkinData.UserArea.CurRect.left
	    	DbgDec [esi].sSkinData.UserArea.CurRect.top
	    	DbgDec [esi].sSkinData.UserArea.CurRect.right
	    	DbgDec [esi].sSkinData.UserArea.CurRect.bottom
    
MethodEnd

