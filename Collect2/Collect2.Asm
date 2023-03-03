; =================================================================================================
; Title:   Demo01D.asm
; Author:  G. Friedrich, June 2005
; Version: 1.0.0
; Purpose: Demonstration Application 01D of ObjAsm32 using object streaming capabilities.
; =================================================================================================


%include @Environ(OA32_PATH)\\Code\\Macros\\Model.inc  ;Include & initialize standard modules
SysSetup OOP_PRIMER, DEBUG(WND)                        ;Loads OOP files and OS related objects

LoadObjects Streamable, Stream, DiskStream
LoadObjects Collection
LoadObjects MemoryStream

include Collect2.inc                                ;Include Shape, Triangle- and RectangleShape
include SecKeyIniCollection.inc

.data                                               ;Define global variables in the Data segment
pDskStm               	Pointer   NULL
pCollection  			Pointer   NULL

.code                                               ;Begin Code segment
start:                                              ;Program entry point
    SysInit                                         ;Runtime initialization of the OOP model

; ——————————————————————————————————————————————————————————————————————————————————————————————————
    DbgText "Start"
;    mov pSecKeyIniFileHeader, $New(SecKeyIniFileHeader, Init,addr szFileTAG, equCodeTAG, equMayVerTAG, equMinVerTAG, addr szDateTAG, addr szOwnerTAG)
 
    mov pCollection, $New(SecKeyIniCollection, Init, 20, 30)
    OCall pCollection::SecKeyIniCollection.Insert, $New(SecKeyIni, Init,"SECTION_1", "KEY_1", "NULL_1", 0)
    OCall pCollection::SecKeyIniCollection.Insert, $New(SecKeyIni, Init,"SECTION_2", "KEY_2", "NULL_2", 1)
    OCall pCollection::SecKeyIniCollection.Insert, $New(SecKeyIni, Init,"SECTION_3", "KEY_3", "NULL_3", 2)
    OCall pCollection::SecKeyIniCollection.Insert, $New(SecKeyIni, Init,"SECTION_4", "KEY_4", "NULL_4", 3)
    OCall pCollection::SecKeyIniCollection.Insert, $New(SecKeyIni, Init,"SECTION_5", "KEY_5", "NULL_5", 4)

    DbgWarning "Cara melihat data object"
    OCall pCollection::SecKeyIniCollection.ItemAt, 3
    mov ebx, [eax].SecKeyIni.pOwner
    DbgStr [ebx].SecKeyIni.Section
    DbgStr [ebx].SecKeyIni.Key
    DbgStr [ebx].SecKeyIni.NullStr
    DbgDec [ebx].SecKeyIni.Idx
    DbgStr [ebx].SecKeyIni.BufPrint

    DbgWarning "Cara memanggil methode"
    OCall pCollection::SecKeyIniCollection.ItemAt, 3
    OCall eax::SecKeyIni.Print ; cara memanggil methode

 
    DbgWarning "Cara mengganti item baru dan menghapus yg lama"
    Destroy $OCall(pCollection::SecKeyIniCollection.PutAt, 3, $New(SecKeyIni, Init,"SECTION_6", "KEY_6", "NULL_6", 3))
    
    DbgWarning "Hasil Item data yang baru"
    OCall pCollection::SecKeyIniCollection.ItemAt, 3
    OCall eax::SecKeyIni.Print

    DbgWarning "Semua Hasil data yang baru"
    OCall pCollection::SecKeyIniCollection.ForEach, $addr(CallPrint)

;    DbgWarning "Cara mennyimpan FILE STM"
;    mov pDskStm, $New(DiskStream, Init, NULL, "Data.stm")
;    OCall pDskStm::DiskStream.Put, $OCall(pCollection::SecKeyIniCollection.ItemAt, 0)
;    OCall pDskStm::DiskStream.Put, $OCall(pCollection::SecKeyIniCollection.ItemAt, 1)
;    OCall pDskStm::DiskStream.Put, $OCall(pCollection::SecKeyIniCollection.ItemAt, 2)
;    OCall pDskStm::DiskStream.Put, $OCall(pCollection::SecKeyIniCollection.ItemAt, 3)
;    OCall pDskStm::DiskStream.Put, $OCall(pCollection::SecKeyIniCollection.ItemAt, 4)

;    ;Destroy is Automatic Done
     OCall pCollection::SecKeyIniCollection.ForEach, $addr(CallDone)
     Destroy pDskStm

 
    DbgText "End"

; ——————————————————————————————————————————————————————————————————————————————————————————————————

    SysDone                                         ;Runtime finalization of the OOP model

    invoke ExitProcess, 0                           ;Exit program returning 0 to Windows OS
; ——————————————————————————————————————————————————————————————————————————————————————————————————

end start   ;End of code and define the program entry point
