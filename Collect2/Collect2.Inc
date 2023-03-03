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

SecKeyIniID           equ     0004  

;Starts SecKeyIni definition, inherided from Streamable
Object SecKeyIni, SecKeyIniID, Streamable
  RedefineMethod    Init,        Pointer, Pointer, Pointer, dword    ;Section, Key, NullStr, Imdex
  RedefineMethod    Done
  RedefineMethod    Load,        Pointer, Pointer ;,dword;-> Stream, -> Owner
  RedefineMethod    Store,       Pointer          ;-> Stream
  VirtualMethod     Print

  DefineVariable    Section,     Pointer,    NULL   
  DefineVariable    Key,         Pointer,    NULL   
  DefineVariable    NullStr,     Pointer,    NULL   
  DefineVariable    Idx,         dword,      NULL   
  DefineVariable    BufPrint,    Pointer,    NULL  
ObjectEnd

Method SecKeyIni.Init, uses esi, Section:Pointer, Key:Pointer, NullStr:Pointer, Idx:dword

    DbgText "Method: TSecKeyIni.Init"
    SetObject esi
    ACall Init,esi
    
    m2m  [esi].Section, $invoke(StrNew,Section)
    m2m  [esi].Key, $invoke(StrNew,Key)
    m2m  [esi].NullStr, $invoke(StrNew, NullStr)
    m2m  [esi].Idx, Idx
 
    OCall esi.Print
MethodEnd

Method SecKeyIni.Done, uses esi
    DbgText "Method: TSecKeyIni.Done"
    SetObject esi
    DbgText "Dispose"
    invoke StrDispose, [esi].Section
    invoke StrDispose, [esi].Key
    invoke StrDispose, [esi].NullStr
    invoke StrDispose, [esi].BufPrint
    ACall Done
MethodEnd

Method SecKeyIni.Print, uses esi
 	LOCAL Buf:Pointer
    DbgText "Method: TSecKeyIni.Print"
    SetObject esi

    ; Create Print Buffer
    m2m Buf, $MemAlloc(255, MEM_INIT_ZERO)
    
    invoke MemZero, Buf, 255
    
    invoke StrCat, Buf, $OfsDStr("[") 
    invoke StrCat, Buf, [esi].Section
    invoke StrCat, Buf, $OfsDStr("]") 
    invoke StrCat, Buf, $OfsDStr(" ") 
    invoke StrCat, Buf, [esi].Key 
    invoke StrCat, Buf, $OfsDStr("=") 
    invoke StrCat, Buf, $OfsDStr(" ") 
    invoke StrCat, Buf, [esi].NullStr 
    invoke StrCat, Buf, $OfsDStr(" ") 
    invoke StrCat, Buf, $OfsDStr("index") 
    invoke StrCat, Buf, $OfsDStr(" ") 
    invoke StrCat, Buf, $Reg32Dec([esi].Idx) 
    
    m2m  [esi].BufPrint, $invoke(StrNew, Buf)
    
    MemFree Buf

    DbgStr [esi].BufPrint
    DbgHex [esi].BufPrint
     
MethodEnd

Method SecKeyIni.Load, uses esi, pStream:Pointer, pOwner:Pointer
    SetObject esi
    
    ACall esi.Init, pOwner
    OCall pStream::Stream.StrRead
    m2m  [esi].Section, $invoke(StrNew,eax)
    OCall pStream::Stream.StrRead
    m2m  [esi].Key, $invoke(StrNew,eax)
    OCall pStream::Stream.StrRead
    m2m  [esi].NullStr, $invoke(StrNew,eax)
    
    OCall pStream::Stream.BinRead, addr [esi].Idx, sizeof dword
    
MethodEnd

Method SecKeyIni.Store, uses esi, pStream:Pointer
    SetObject esi
    OCall pStream::Stream.StrWrite, [esi].Section
    OCall pStream::Stream.StrWrite, [esi].Key
    OCall pStream::Stream.StrWrite, [esi].NullStr

    OCall pStream::Stream.BinWrite, addr [esi].Idx, sizeof dword
MethodEnd




