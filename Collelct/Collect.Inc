; =================================================================================================
; Title:   Collect.inc
; Author:  Pahor.m  @ April 2020
; Version: 1.0.0
; Purpose: Demonstration program imulation Pascal Collect of ObjAsm32.
; =================================================================================================

ClientID           equ     0002                  ;Shape object ID
ClientCollectionID equ     0003

; =================================================================================================
;     Object definitions
; =================================================================================================

;Starts Client definition, inherided from Streamable
Object Client, ClientID, Streamable
  RedefineMethod    Init,    Pointer, Pointer, Pointer    ;Account, Name, Phone
  RedefineMethod    Done
  RedefineMethod    Load,    Pointer, Pointer ;-> Stream, -> Owner
  RedefineMethod    Store,   Pointer          ;-> Stream
  VirtualMethod     Print

  DefineVariable    Account, Pointer,    NULL   ;Sets dBase to 0
  DefineVariable    LName,   Pointer,    NULL   ;Sets dHeight to 0
  DefineVariable    Phone,   Pointer,    NULL   ;Sets dHeight to 0
  DefineVariable    ct,      byte,       255 dup (0)
  
ObjectEnd

;Starts ClientCollection definition, inherided from Collection
Object ClientCollection, ClientCollectionID, Collection
  RedefineMethod    Init,    DWord, DWord   ;Limit, Faktor
  RedefineMethod    Done
  RedefineMethod    Insert,  Pointer
ObjectEnd

;NewStr   PROTO :Pointer
;DelStr   PROTO :Pointer

Method Client.Init, uses esi, Account:Pointer, LName:Pointer, Phone:Pointer
    DbgText "Method: TClient.Init"
    SetObject esi
    ACall Init,esi
    
    DbgText "New"
    
    m2m  [esi].Account, $invoke(StrNew,Account)
    m2m  [esi].LName, $invoke(StrNew,LName)
    m2m  [esi].Phone, $invoke(StrNew,Phone)
    
    DbgStr [esi].Account
    DbgStr [esi].LName
    DbgStr [esi].Phone
    
    ;invoke StrLength, [esi].Account
    ;add eax, 1
    ;DbgDec eax 
    
    ;OCall esi.Print
    DbgLine
MethodEnd

Method Client.Done, uses esi
    DbgText "Method: TClient.Done"
    SetObject esi
    DbgText "Dispose"
    invoke StrDispose, [esi].Account
    invoke StrDispose, [esi].LName
    invoke StrDispose, [esi].Phone
    ;OCall [esi].pCollection::Collection.Done          ; if Embed must be OCall Done
    ;Destroy [esi].pCollection
    ACall Done
MethodEnd

Method Client.Print, uses esi
    DbgText "Method: TClient.Print"
    SetObject esi
    
    invoke StrCat, $addr([esi].ct), [esi].Account
    invoke StrCat, $addr([esi].ct), $OfsDStr(" ") 
    invoke StrCat, $addr([esi].ct), [esi].LName 
    invoke StrCat, $addr([esi].ct), $OfsDStr(" ") 
    invoke StrCat, $addr([esi].ct), [esi].Phone 

    DbgStr $addr([esi].ct)
MethodEnd

Method Client.Load, uses esi, pStream:Pointer, pOwner:Pointer
    SetObject esi
    ACall esi.Init, pOwner         ; Jangan di hapus sebab dijalankan obj stream
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
;===========================================================================

Method ClientCollection.Init, uses esi, nLimit:DWord, nFaktor:DWord
    DbgText "Method: ClientCollection.Init"
    SetObject esi
    ACall Init, esi, nLimit, nFaktor, NULL
MethodEnd

Method ClientCollection.Done, uses esi
    DbgText "Method: ClientCollection.Done"
    SetObject esi
    ACall Done
MethodEnd

Method ClientCollection.Insert, uses esi, pClient:Pointer
    DbgText "Method: ClientCollection.Insert"
    SetObject esi
    OCall [esi]::Collection.Insert, pClient
MethodEnd
