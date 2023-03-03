; =================================================================================================
; Title:   Collect.inc
; Author:  Pahor.m  @ April 2020
; Version: 1.0.0
; Purpose: Demonstration program imulation Pascal Collect of ObjAsm32.
; =================================================================================================

; modification by me.  
$Reg32Dec MACRO DDvalue
  LOCAL rvstring
  .data
    rvstring db 20 dup (0)
    align 4
  .code
  invoke dword2dec,ADDR rvstring, DDvalue
  EXITM <ADDR rvstring>
ENDM

$Reg32Hex MACRO DDvalue
  LOCAL rvstring
  .data
    rvstring db 20 dup (0)
    align 4
  .code
  invoke dword2hex,ADDR rvstring, DDvalue
  EXITM <ADDR rvstring>
ENDM

CallPrint   proto 
CallDone    proto
SearchPhone proto :Pointer, :Pointer
PhoneMatch  proto :Pointer, :Pointer

CStr szFileTAG,  "STM" 
equCodeTAG       equ 0BBCCAA55h
equMayVerTAG     equ 0
equMinVerTAG     equ 1
CStr szDateTAG,  "05-05-2020" 
CStr szOwnerTAG, "AnaliX.org, Pahor Mustaly, North Borneo (by ObjASM32)" 

; Dummy Structure
sClientFileHeader struct
  FileTAG     byte  size szFileTAG  dup (?) ;string   
  CodeTAG     dword ?   ; bin
  MayVerTAG   dWord ?   ; bin
  MinVerTAG   dWord ?   ; bin
  DateTAG     byte  size szDateTAG  dup (?) ;string
  OwnerTAG    byte  size szOwnerTAG dup (?) ;string
sClientFileHeader ends


ClientID           equ     0002                  ;Shape object ID
ClientCollectionID equ     0003
ClientFileHeaderID equ     0004     

; =================================================================================================
;     Object definitions
; =================================================================================================
Object ClientFileHeader, ClientFileHeaderID, Streamable
  RedefineMethod    Init,         Pointer, dword, dword, dword, Pointer, Pointer    ;Account, Name, Phone
  RedefineMethod    Done
  RedefineMethod    Load,         Pointer, Pointer ;-> Stream, -> Owner
  RedefineMethod    Store,        Pointer          ;-> Stream
  VirtualMethod     Print

  DefineVariable    FileTAG,      Pointer,  NULL   
  DefineVariable    CodeTAG,      dword,    NULL   
  DefineVariable    MayVerTAG,    dword,    NULL
  DefineVariable    MinVerTAG,    dword,    NULL
  DefineVariable    DateTAG,      Pointer,  NULL
  DefineVariable    OwnerTAG,     Pointer,  NULL
   
  DefineVariable    BufPrint,     Pointer,  NULL  
ObjectEnd

;Starts Client definition, inherided from Streamable
Object Client, ClientID, Streamable
  RedefineMethod    Init,        Pointer, Pointer, Pointer    ;Account, Name, Phone
  RedefineMethod    Done
  RedefineMethod    Load,        Pointer, Pointer ;,dword;-> Stream, -> Owner
  RedefineMethod    Store,       Pointer          ;-> Stream
  VirtualMethod     Print

  DefineVariable    Account,     Pointer,    NULL   
  DefineVariable    LName,       Pointer,    NULL   
  DefineVariable    Phone,       Pointer,    NULL   
  DefineVariable    BufPrint,    Pointer,    NULL  
ObjectEnd

;Starts ClientCollection definition, inherided from Collection
Object ClientCollection, ClientCollectionID, Collection
  RedefineMethod    Init,        DWord, DWord   ;Limit, Faktor
  RedefineMethod    Done
  VirtualMethod     SearchPhone, Pointer, Pointer

  DefineVariable    PhoneToFind, Pointer, NULL
ObjectEnd

; ——————————————————————————————————————————————————————————————————————————————————————————————————
; Method:    ClientFileHeader.Init
; Purpose:   
; Arguments: Arg1: 
;            Arg2: 
;            Arg3: 
;            Arg4: 
;            Arg5: 
;            Arg6: 
; Return:    
; Note:      

Method ClientFileHeader.Init, uses esi, FileTAG:Pointer, CodeTAG:dword, MayVerTAG:dword, MinVerTAG:dword, DateTAG:Pointer, OwnerTAG:Pointer
    SetObject esi
    ACall Init,esi
    
    DbgText "Method: ClientFileHeader.Init"

    m2m  [esi].FileTAG,   $invoke(StrNew,FileTAG)
    m2m  [esi].CodeTAG,   CodeTAG
    m2m  [esi].MayVerTAG, MayVerTAG
    m2m  [esi].MinVerTAG, MinVerTAG
    m2m  [esi].DateTAG,   $invoke(StrNew,DateTAG)
    m2m  [esi].OwnerTAG,  $invoke(StrNew,OwnerTAG)

;    DbgStr [esi].FileTAG
;    DbgHex [esi].CodeTAG
;    DbgDec [esi].MayVerTAG
;    DbgDec [esi].MinVerTAG
;    DbgStr [esi].DateTAG
;    DbgStr [esi].OwnerTAG
   
    OCall esi.Print
    DbgLine
MethodEnd


; ——————————————————————————————————————————————————————————————————————————————————————————————————
; Method:    ClientFileHeader.Done
; Purpose:   
; Arguments: None.
; Return:    
; Note:      

Method ClientFileHeader.Done, uses esi
    SetObject esi
    DbgText "Method: ClientFileHeader.Done"
    invoke StrDispose,   [esi].FileTAG
    mov [esi].CodeTAG,   NULL
    mov [esi].MayVerTAG, NULL
    mov [esi].MinVerTAG, NULL
    invoke StrDispose,   [esi].DateTAG
    invoke StrDispose,   [esi].OwnerTAG
    
    invoke StrDispose,   [esi].BufPrint

    ACall Done
MethodEnd

; ——————————————————————————————————————————————————————————————————————————————————————————————————
; Method:    ClientFileHeader.Print
; Purpose:   
; Arguments: None.
; Return:    
; Note:      

Method ClientFileHeader.Print, uses esi
LOCAL Buf:Pointer
    SetObject esi

    DbgText "Method: ClientFileHeader.Print"

    ; Create Print Buffer
    m2m Buf, $MemAlloc(255, MEM_INIT_ZERO)
    
    invoke MemZero, Buf, 255
    
    invoke StrCat, Buf, [esi].FileTAG
    invoke StrCat, Buf, $OfsDStr(" ") 
    invoke StrCat, Buf, $Reg32Hex([esi].CodeTAG) 
    invoke StrCat, Buf, $OfsDStr(" ") 
    invoke StrCat, Buf, $Reg32Dec([esi].MayVerTAG)
    invoke StrCat, Buf, $OfsDStr(".") 
    invoke StrCat, Buf, $Reg32Dec([esi].MinVerTAG) 
    invoke StrCat, Buf, $OfsDStr(" ") 
    invoke StrCat, Buf, [esi].DateTAG 
    invoke StrCat, Buf, $OfsDStr(" ") 
    invoke StrCat, Buf, [esi].OwnerTAG 
    
    m2m  [esi].BufPrint, $invoke(StrNew, Buf)
    
    MemFree Buf

    DbgStr [esi].BufPrint
    DbgHex [esi].BufPrint
    
MethodEnd

; ——————————————————————————————————————————————————————————————————————————————————————————————————
; Method:    ClientFileHeader.Load
; Purpose:   
; Arguments: Arg1: 
;            Arg2: 
; Return:    
; Note:      

Method ClientFileHeader.Load, uses esi, pStream:Pointer, pOwner:Pointer
    SetObject esi
    ACall esi.Init, pOwner         ; Jangan di hapus sebab dijalankan obj stream
    
    OCall pStream::Stream.StrRead
    m2m  [esi].FileTAG, $invoke(StrNew,eax)
    
    OCall pStream::Stream.BinRead, addr [esi].CodeTAG, sizeof dword
    OCall pStream::Stream.BinRead, addr [esi].MayVerTAG, sizeof dword
    OCall pStream::Stream.BinRead, addr [esi].MinVerTAG, sizeof dword
    
    OCall pStream::Stream.StrRead
    m2m  [esi].DateTAG, $invoke(StrNew,eax)
    OCall pStream::Stream.StrRead
    m2m  [esi].OwnerTAG, $invoke(StrNew,eax)
    
MethodEnd


; ——————————————————————————————————————————————————————————————————————————————————————————————————
; Method:    ClientFileHeader.Store
; Purpose:   
; Arguments: Arg1: 
; Return:    
; Note:      

Method ClientFileHeader.Store, uses esi, pStream:Pointer
    SetObject esi
    OCall pStream::Stream.StrWrite, [esi].FileTAG
    
    OCall pStream::Stream.BinWrite, addr [esi].CodeTAG, sizeof dword
    OCall pStream::Stream.BinWrite, addr [esi].MayVerTAG, sizeof dword
    OCall pStream::Stream.BinWrite, addr [esi].MinVerTAG, sizeof dword
    
    OCall pStream::Stream.StrWrite, [esi].DateTAG
    OCall pStream::Stream.StrWrite, [esi].OwnerTAG
   
MethodEnd




Method Client.Init, uses esi, Account:Pointer, LName:Pointer, Phone:Pointer

    DbgText "Method: TClient.Init"
    SetObject esi
    ACall Init,esi
  
    m2m  [esi].Account, $invoke(StrNew,Account)
    m2m  [esi].LName, $invoke(StrNew,LName)
    m2m  [esi].Phone, $invoke(StrNew,Phone)
   
    OCall esi.Print
MethodEnd

Method Client.Done, uses esi
    DbgText "Method: TClient.Done"
    SetObject esi
    DbgText "Dispose"
    invoke StrDispose, [esi].Account
    invoke StrDispose, [esi].LName
    invoke StrDispose, [esi].Phone
    invoke StrDispose, [esi].BufPrint
    ACall Done
MethodEnd

Method Client.Print, uses esi
	LOCAL Buf:Pointer
    DbgText "Method: TClient.Print"
    SetObject esi

    ; Create Print Buffer
    m2m Buf, $MemAlloc(255, MEM_INIT_ZERO)
    
    invoke MemZero, Buf, 255
    
    invoke StrCat, Buf, [esi].Account
    invoke StrCat, Buf, $OfsDStr(" ") 
    invoke StrCat, Buf, [esi].LName 
    invoke StrCat, Buf, $OfsDStr(" ") 
    invoke StrCat, Buf, [esi].Phone 
    
    m2m  [esi].BufPrint, $invoke(StrNew, Buf)
    
    MemFree Buf

    DbgStr [esi].BufPrint
    DbgHex [esi].BufPrint
     
MethodEnd


Method Client.Load, uses esi, pStream:Pointer, pOwner:Pointer;, VarClien:dword
    SetObject esi
    
    ACall esi.Init, pOwner
        ; Jangan di hapus sebab dijalankan obj stream
    OCall pStream::Stream.StrRead
    m2m  [esi].Account, $invoke(StrNew,eax)
    OCall pStream::Stream.StrRead
    m2m  [esi].LName, $invoke(StrNew,eax)
    OCall pStream::Stream.StrRead
    m2m  [esi].Phone, $invoke(StrNew,eax)
    
MethodEnd

Method Client.Store, uses esi, pStream:Pointer
    SetObject esi
    OCall pStream::Stream.StrWrite, [esi].Account
    OCall pStream::Stream.StrWrite, [esi].LName
    OCall pStream::Stream.StrWrite, [esi].Phone
MethodEnd
; ——————————————————————————————————————————————————————————————————————————————————————————————————
; Method:    ClientCollection.Init
; Purpose:   
; Arguments: Arg1: 
;            Arg2: 
; Return:    

Method ClientCollection.Init, uses esi, nLimit:DWord, nFaktor:DWord
    DbgText "Method: ClientCollection.Init"
    SetObject esi
    ACall Init, esi, nLimit, nFaktor, NULL ; Call init Accsesor of Collection
MethodEnd

; ——————————————————————————————————————————————————————————————————————————————————————————————————
; Method:    ClientFileHeader.Done
; Purpose:   
; Arguments: None.
; Return:    
; Note:      

Method ClientFileHeader.Done, uses esi
    SetObject esi
    ACall Done
MethodEnd


; ——————————————————————————————————————————————————————————————————————————————————————————————————
; Method:    ClientCollection.SearchPhone
; Purpose:   
; Arguments: Arg1: Pointer ClientCollection
;            Arg2: Pointer string PhoneToFind
; Return:    NONE
Method ClientCollection.SearchPhone, uses esi, pCollect:Pointer, PhoneToFind:Pointer
	LOCAL FoundClient:Pointer
    
    SetObject esi
    
    ;m2m [esi].PhoneToFind, $invoke(StrNew, PhoneToFind)
    ;invoke SearchPhone, pCollect, [esi].PhoneToFind
	OCall pCollect::Collection.ItemAt, 0 ; first index
	m2m FoundClient, $OCall(pCollect::Collection.FirstThat, $addr(PhoneMatch),eax,PhoneToFind)
	.if eax == NULL
	  DbgText "No client met the search requirement"
	.else
	  DbgWarning "Found client:"
	  OCall FoundClient::Client.Print
	.endif
    ;invoke StrDispose, [esi].PhoneToFind
  
MethodEnd
; ——————————————————————————————————————————————————————————————————————————————————————————————————

CallPrint proc 
    LOCAL p:Pointer
    DbgText "Go Print"
    m2m p, [esi]
    invoke GetObjectID, [esi]     ;eax = ID, ecx -> ID
    .if eax == ClientID
       OCall p::Client.Print   
    .elseif eax == ClientFileHeaderID
       OCall p::ClientFileHeader.Print   
    .endif
	ret 4 ; NONE parameters
CallPrint endp

CallDone proc 
    LOCAL p:Pointer
    DbgText "Go Destroy"
    m2m p, [esi]
    Destroy p
	ret 4 ; NONE parameters
CallDone endp

; methode memanggil procedure ini. utk mencari string
SearchPhone proc pCollect:Pointer, PhoneToFind:Pointer
LOCAL FoundClient:Pointer
	OCall pCollect::Collection.ItemAt, 0 ; first index
	m2m FoundClient, $OCall(pCollect::Collection.FirstThat, $addr(PhoneMatch),eax,PhoneToFind)
	.if eax == NULL
	  DbgText "No client met the search requirement"
	.else
	  DbgWarning "Found client:"
	  OCall FoundClient::Client.Print
	.endif
	ret
SearchPhone endp

; Collection.FirstThat di atas menggunakan ini
;Catatan
;[esp + 12] adalah statis parameter 1 (yang awal)
;[esp + 16] adalah statis parameter 2
;[esp + 20] adalah statis parameter 3 (paling ujung)
;dan seterusnya
;ret 4  tampa parmeter
;ret 8  1 parameter
;ret 12 2 parameter
PhoneMatch proc pClient:Pointer, PhoneToFind:Pointer
    invoke GetObjectID, [esi] ;eax = ID, ecx -> ID
    .if eax == ClientID
	    mov ecx, pClient
		DbgText "PhoneMatch"
		;DbgHex ecx 
		.if $invoke(StrPos, [ecx].Client.Phone, [esp + 16]) 
			mov eax, TRUE
		.else
			mov eax, FALSE
	    .endif
	.else   
	    mov eax, FALSE
    .endif
	ret 12 ; two parameters
PhoneMatch endp



