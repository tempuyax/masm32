; =================================================================================================
; Title:   Demo01D.asm
; Author:  G. Friedrich, June 2005
; Version: 1.0.0
; Purpose: Demonstration Application 01D of ObjAsm32 using object streaming capabilities.
; =================================================================================================


%include @Environ(OA32_PATH)\\Code\\Macros\\Model.inc  ;Include & initialize standard modules
SysSetup OOP_PRIMER, DEBUG(WND)                     ;Loads OOP files and OS related objects

LoadObjects Streamable, Stream, DiskStream
LoadObjects Collection
LoadObjects MemoryStream

CallSaveFile proto :Pointer

include Collect1.inc                                 ;Include Shape, Triangle- and RectangleShape
.data                                               ;Define global variables in the Data segment
pClient1          Pointer   NULL                      ;Invokes RectangleShape's Done and disposes it
pClient2          Pointer   NULL                      ;Invokes RectangleShape's Done and disposes it
pClient3          Pointer   NULL                      ;Invokes RectangleShape's Done and disposes it
pClient4          Pointer   NULL                      ;Invokes RectangleShape's Done and disposes it
pClient5          Pointer   NULL                      ;Invokes RectangleShape's Done and disposes it
pClientFileHeader Pointer   NULL
pDskStm           Pointer   NULL
pClientCollection Pointer   NULL
pMem	          Pointer   NULL
.code                                               ;Begin Code segment
start:                                              ;Program entry point
    SysInit                                         ;Runtime initialization of the OOP model

; ——————————————————————————————————————————————————————————————————————————————————————————————————
    DbgText "Start"
;    mov pClientFileHeader, $New(ClientFileHeader, Init,addr szFileTAG, equCodeTAG, equMayVerTAG, equMinVerTAG, addr szDateTAG, addr szOwnerTAG)
;    
    mov pClient1, $New(Client, Init,"91-100", "Anders, Smitty", "(406) 111-2222")
    mov pClient2, $New(Client, Init,"90-167", "Smith, Zelda", "(800) 555-1212")
    mov pClient3, $New(Client, Init,"90-177", "Smitty, John", "(406) 987-4321")
    mov pClient4, $New(Client, Init,"90-160", "Johnson, Agatha", "(302) 139-8913")
    mov pClient5, $New(Client, Init,"92-120", "Rudy, Mark", "(501) 129-3941")
 
;    mov pMem, $New(MemoryStream, Init, pOwner, 20, 30, NULL)
    mov pDskStm, $New(DiskStream, Init, NULL, "Data.stm")
;    OCall pDskStm::DiskStream.Put, pClientFileHeader
    OCall pDskStm::DiskStream.Put, pClient1
    OCall pDskStm::DiskStream.Put, pClient2
    OCall pDskStm::DiskStream.Put, pClient3
    OCall pDskStm::DiskStream.Put, pClient4
    OCall pDskStm::DiskStream.Put, pClient5
; 
;    ;Destroy is Automatic Done
    Destroy pClient1                                ;Invokes RectangleShape's Done and disposes it
    Destroy pClient2                                ;Invokes RectangleShape's Done and disposes it
    Destroy pClient3                                ;Invokes RectangleShape's Done and disposes it
    Destroy pClient4                                ;Invokes RectangleShape's Done and disposes it
    Destroy pClient5                                ;Invokes RectangleShape's Done and disposes it
;    Destroy pClientFileHeader                       ;Invokes RectangleShape's Done and disposes it
    Destroy pDskStm

; ——————————————————————————————————————————————————————————————————————————————————————————————————
    mov pDskStm, $New(DiskStream, Init, NULL, "Data.stm")
    mov pClientCollection, $New(ClientCollection, Init, 10, 5)

    OCall pClientCollection::Collection.Insert, $OCall(pDskStm::DiskStream.Get, 0)   ; idx 0 
    OCall pClientCollection::Collection.Insert, $OCall(pDskStm::DiskStream.Get, 0)   ; idx 1 
    OCall pClientCollection::Collection.Insert, $OCall(pDskStm::DiskStream.Get, 0)   ; idx 2
    OCall pClientCollection::Collection.Insert, $OCall(pDskStm::DiskStream.Get, 0)   ; idx 4
    OCall pClientCollection::Collection.Insert, $OCall(pDskStm::DiskStream.Get, 0)   ; idx 3

    ; New
    ;OCall pClientCollection::Collection.Insert, $New(Client, Init,"91-110", "Mas, Lee", "(501) 123-3340")   ; idx 3

    ;cek data yang terbaca
;    mov ecx, pClientCollection
;    mov ebx, [ecx].Collection.pOwner
;    DbgDec [ebx].Collection.dCount
;    DbgDec [ebx].Collection.dLimit
;    DbgDec [ebx].Collection.dDelta
;    DbgDec [ebx].Collection.dMaxSize

    mov ecx, pClientCollection
    mov ebx, [ecx].Primer.pOwner
    DbgDec [ebx].Collection.dCount
    DbgDec [ebx].Collection.dLimit
    DbgDec [ebx].Collection.dDelta
    DbgDec [ebx].Collection.dMaxSize

    ;memanggil metode object Collection dgn fungsi ForEach, yg menjalankan procedure CallPrint 
    OCall pClientCollection::Collection.ForEach,$addr(CallPrint)

    ;2 cara memanggil
    
    ;1 cara panggil procedure
    ;invoke SearchPhone, pClientCollection, $OfsDStr("(501)") ; call via procedure

    ;2 cara panggil methode sebuah object
    ;OCall pClientCollection::ClientCollection.SearchPhone, pClientCollection, $OfsDStr("555") ; call via Object
    
    ;Destroy is Automatic call Methode Done each objects
    OCall pClientCollection::Collection.ForEach, $addr(CallDone)
    Destroy pDskStm
 	;Destroy pClientCollection ;Collection tidak boleh di Destroy
 
    DbgText "End"

; ——————————————————————————————————————————————————————————————————————————————————————————————————

    SysDone                                         ;Runtime finalization of the OOP model

    invoke ExitProcess, 0                           ;Exit program returning 0 to Windows OS
; ——————————————————————————————————————————————————————————————————————————————————————————————————

; blum fix, msh error
CallSaveFile proc pDisk:Pointer
LOCAL pClient:Pointer, pdsk:Pointer
    DbgText "Go Save"
    m2m pClient, [esi]
    ;DbgHex pClient
    ;DbgHex pDisk
    m2m pdsk, [esp + 12]
    ;DbgHex pdsk
    ;OCall pDisk::DiskStream.Put, pClient  
	
	ret 8

CallSaveFile endp



end start   ;End of code and define the program entry point
