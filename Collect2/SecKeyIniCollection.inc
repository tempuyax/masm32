CallPrint   proto 
CallDone    proto
SearchNullStr proto :Pointer, :Pointer
NullStrMatch  proto :Pointer, :Pointer

SecKeyIniCollectionID equ     0002     

;===========================================================
Object SecKeyIniCollection, SecKeyIniCollectionID, Collection
  RedefineMethod    Init,          DWord, DWord   ;Limit, Faktor
  VirtualMethod     SearchNullStr, Pointer, Pointer
  VirtualMethod     Print

  DefineVariable    NullStrToFind, Pointer, NULL
ObjectEnd

; ——————————————————————————————————————————————————————————————————————————————————————————————————
; Method:    SecKeyIniCollection.Init
; Purpose:   
; Arguments: Arg1: 
;            Arg2: 
; Return:    

Method SecKeyIniCollection.Init, uses esi, nLimit:DWord, nFaktor:DWord
    DbgText "Method: SecKeyIniCollection.Init"
    SetObject esi
    ACall Init, esi, nLimit, nFaktor, NULL ; Call init Accsesor of Collection
MethodEnd

; ——————————————————————————————————————————————————————————————————————————————————————————————————
; Method:    SecKeyIniCollection.SearchNullStr
; Purpose:   
; Arguments: Arg1: Pointer SecKeyIniCollection
;            Arg2: Pointer string NullStrToFind
; Return:    NONE
Method SecKeyIniCollection.SearchNullStr, uses esi, pCollect:Pointer, NullStrToFind:Pointer
    SetObject esi
    
    m2m [esi].NullStrToFind, $invoke(StrNew, NullStrToFind)
    invoke SearchNullStr, pCollect, [esi].NullStrToFind
    invoke StrDispose, [esi].NullStrToFind
  
MethodEnd

; ——————————————————————————————————————————————————————————————————————————————————————————————————
; Method:    SecKeyIniCollection.Print
; Purpose:   
; Arguments: None.
; Return:    
; Note:      

Method SecKeyIniCollection.Print, uses esi
    SetObject esi
    DbgText "Method: SecKeyIniCollection.Print"
    
MethodEnd


; ——————————————————————————————————————————————————————————————————————————————————————————————————

CallPrint proc 
    LOCAL p:Pointer
    DbgText "Go Print"
    m2m p, [esi]
    invoke GetObjectID, [esi]     ;eax = ID, ecx -> ID
    .if eax == SecKeyIniID
       OCall p::SecKeyIni.Print   
    .elseif eax == SecKeyIniCollectionID
       OCall p::SecKeyIniCollection.Print   
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
SearchNullStr proc pCollect:Pointer, NullStrToFind:Pointer
LOCAL FoundSecKeyIni:Pointer
	OCall pCollect::Collection.ItemAt, 0 ; first index
	m2m FoundSecKeyIni, $OCall(pCollect::Collection.FirstThat, $addr(NullStrMatch),eax,NullStrToFind)
	.if eax == NULL
	  DbgText "No SecKeyIni met the search requirement"
	.else
	  DbgWarning "Found SecKeyIni:"
	  OCall FoundSecKeyIni::SecKeyIni.Print
	.endif
	ret
SearchNullStr endp

; Collection.FirstThat di atas menggunakan ini
;Catatan
;[esp + 12] adalah statis parameter 1 (yang awal)
;[esp + 16] adalah statis parameter 2
;[esp + 20] adalah statis parameter 3 (paling ujung)
;dan seterusnya
;ret 4  tampa parmeter
;ret 8  1 parameter
;ret 12 2 parameter
NullStrMatch proc pSecKeyIni:Pointer, NullStrToFind:Pointer
    invoke GetObjectID, [esi] ;eax = ID, ecx -> ID
    .if eax == SecKeyIniID
	    mov ecx, pSecKeyIni
		DbgText "NullStrMatch"
		;DbgHex ecx 
		.if $invoke(StrPos, [ecx].SecKeyIni.NullStr, [esp + 16]) 
			mov eax, TRUE
		.else
			mov eax, FALSE
	    .endif
	.else   
	    mov eax, FALSE
    .endif
	ret 12 ; two parameters
NullStrMatch endp
