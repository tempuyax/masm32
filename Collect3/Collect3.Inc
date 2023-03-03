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

ClientID           equ     0002                  
ClientCollectionID equ     0003

;Field ID = FID
AccountFID 	equ 1
NameFID		equ 2
PhoneFID	equ 3

; =================================================================================================
;     Object definitions
; =================================================================================================

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
  DefineVariable    Idx,	     Dword,      NULL   
  DefineVariable    BufPrint,    Pointer,    NULL  
ObjectEnd

;Starts ClientCollection definition, inherided from Collection
Object ClientCollection, ClientCollectionID, Collection
  RedefineMethod    Init
  RedefineMethod    Done
  VirtualMethod     SearchField, dword, Pointer
ObjectEnd


Method Client.Init, uses esi, Account:Pointer, LName:Pointer, Phone:Pointer
	LOCAL Buf:Pointer

    DbgText "Method: Client.Init"
    SetObject esi
    ACall Init,esi
  
    ; Setup Client Object
    m2m  [esi].Account, $invoke(StrNew,Account)
    m2m  [esi].LName, $invoke(StrNew,LName)
    m2m  [esi].Phone, $invoke(StrNew,Phone)
   
    ; Setup Print Buffer
    m2m Buf, $MemAlloc(255, MEM_INIT_ZERO)

    invoke StrCat, Buf, [esi].Account
    invoke StrCat, Buf, $OfsDStr(" ") 
    invoke StrCat, Buf, [esi].LName 
    invoke StrCat, Buf, $OfsDStr(" ") 
    invoke StrCat, Buf, [esi].Phone 

    m2m  [esi].BufPrint, $invoke(StrNew, Buf)

    MemFree Buf
MethodEnd

Method Client.Done, uses esi
    DbgText "Method: Client.Done"
    SetObject esi
    invoke StrDispose, [esi].Account
    invoke StrDispose, [esi].LName
    invoke StrDispose, [esi].Phone
    invoke StrDispose, [esi].BufPrint
    ACall Done
MethodEnd

Method Client.Print, uses esi
	LOCAL Buf:Pointer

    DbgText "Method: Client.Print"
    SetObject esi

    ; Setup Print Buffer
    m2m Buf, $MemAlloc(128, MEM_INIT_ZERO)

    invoke StrCat, Buf, [esi].BufPrint 
    invoke StrCat, Buf, $OfsDStr(" ") 
    invoke StrCat, Buf, $OfsDStr("Index") 
    invoke StrCat, Buf, $OfsDStr(" ") 
    invoke StrCat, Buf, $Reg32Dec([esi].Idx) 

    invoke StrDispose, [esi].BufPrint
    mov  [esi].BufPrint, $invoke(StrNew, Buf)

    MemFree Buf

    ;Print Debug
    DbgStr [esi].BufPrint
    DbgHex [esi].BufPrint
MethodEnd


Method Client.Load, uses esi, pStream:Pointer, pOwner:Pointer
    SetObject esi
    
    ACall esi.Init, pOwner
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

Method ClientCollection.Init, uses esi
    DbgText "Method: ClientCollection.Init"
    SetObject esi
    ACall Init, esi, 10, 5, NULL 
    
	; setup insert static into collection of data record Pointer Client Object 
    ACall Insert,  $New(Client, Init,"91-100", "Anders, Smitty", "(406) 111-2222")
    ACall Insert,  $New(Client, Init,"90-167", "Smith, Zelda", "(800) 555-1212")
    ACall Insert,  $New(Client, Init,"90-177", "Smitty, John", "(406) 987-4321")
    ACall Insert,  $New(Client, Init,"90-160", "Johnson, Agatha", "(302) 139-8913")
    ACall Insert,  $New(Client, Init,"92-120", "Rudy, Mark", "(501) 129-3941")

MethodEnd

; ——————————————————————————————————————————————————————————————————————————————————————————————————
; Method:    ClientCollection.Done
; Purpose:   
; Arguments: None.
; Return:    
; Note:      

Method ClientCollection.Done, uses esi
    SetObject esi
    ACall Done
MethodEnd


; ——————————————————————————————————————————————————————————————————————————————————————————————————
; Method:    ClientCollection.SearchField
; Purpose:   
; Arguments: Arg1: 
;            Arg2: 
; Return:    
; Note:      

Method ClientCollection.SearchField, uses esi, FieldID:dword, StringToFind:Pointer
	LOCAL FoundClient:Pointer

    SetObject esi
    .if FieldID == AccountFID
		mov FoundClient, $ACall(FirstThat, $addr(AccountMatch),StringToFind)
    .elseif FieldID == NameFID
		mov FoundClient, $ACall(FirstThat, $addr(NameMatch),StringToFind)
    .elseif FieldID == PhoneFID
		mov FoundClient, $ACall(FirstThat, $addr(PhoneMatch),StringToFind)
    .endif

	.if FoundClient == NULL
	  	DbgWarning "No client met the search requirement"
	.else
	  	DbgWarning "Found client:"
	  	;Store Current Index to Client Object Variable
	  	mov ecx, FoundClient
     	mov ebx, [ecx].Client.pOwner
	  	mov [ebx].Client.Idx, $ACall(IndexOf, FoundClient)
	  	
	  	;Object Call by Methode Print of Client Object
	  	OCall FoundClient::Client.Print
	.endif
    
MethodEnd


; ——————————————————————————————————————————————————————————————————————————————————————————————————
; Method:    ClientCollection.SetupList
; Purpose:   
; Arguments: None.
; Return:    
; Note:      

;Method ClientCollection.SetupList, uses esi
;    SetObject esi
;    mov [esi].pList, $New(LinkedList)
;	ACall Foreach,
;MethodEnd



; ——————————————————————————————————————————————————————————————————————————————————————————————————

;Penting:
;  Difinisi sebuah Fungsi dalam OA32 tidak lain adalah "Procedure" 
;
;Catatan:
;  Penulisan kode Fungsi OA32 Pada Methode Object
;  1. Cara mengambil nilai Parameter Fungsi
;	  di Lihat dari jumlah parameter Procedure nya
;		dalam kelipatan 4	
;		[esp + 12] adalah berisi nilai parameter 1 (yang pertama)
;		[esp + 16] adalah berisi nilai parameter 2 (yang kedua)
;		[esp + 20] adalah berisi nilai parameter 3 (yang ketiga)
;		dan seterusnya....
;
;  2. Cara fungsi mengembalikan EIP (Instruksi Pointer) ke program induk
;	  di Lihat dari jumlah parameter Procedure nya	
;		dalam kelipatan 4	
;		ret 4  jika tanpa parmeter
;       ret 8  jika 1 parameter
;       ret 12 jika 2 parameter
;		dan seterusnya....

PhoneMatch proc pClient:Pointer, PhoneToFind:Pointer
    invoke GetObjectID, [esi] ;[esi]->pObj eax = ID, ecx -> ID
    .if eax == ClientID
	    mov ecx, pClient
		DbgText "PhoneMatch"
		.if $invoke(StrPos, [ecx].Client.Phone, [esp + 12]) 
			mov eax, TRUE
		.else
			mov eax, FALSE
	    .endif
	.else   
	    mov eax, FALSE
    .endif
	ret 8 
PhoneMatch endp

NameMatch proc pClient:Pointer, NameToFind:Pointer
    invoke GetObjectID, [esi] ;[esi]->pObj eax = ID, ecx -> ID
    .if eax == ClientID
	    mov ecx, pClient
		DbgText "NameMatch"
		.if $invoke(StrPos, [ecx].Client.LName, [esp + 12]) 
			mov eax, TRUE
		.else
			mov eax, FALSE
	    .endif
	.else   
	    mov eax, FALSE
    .endif
	ret 8 
NameMatch endp

AccountMatch proc pClient:Pointer, AccountToFind:Pointer
    invoke GetObjectID, [esi] ;[esi]->pObj eax = ID, ecx -> ID
    .if eax == ClientID
	    mov ecx, pClient
		DbgText "AccountMatch"
		.if $invoke(StrPos, [ecx].Client.Account, [esp + 12]) 
			mov eax, TRUE
		.else
			mov eax, FALSE
	    .endif
	.else   
	    mov eax, FALSE
    .endif
	ret 8 
AccountMatch endp