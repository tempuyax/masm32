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

include Collect3.inc    

.data 
pDskStm Pointer   NULL
pCollect Pointer   NULL

.code  
start:   
    SysInit  
    DbgText "Start"
    DbgLine
    
    mov pCollect, $New(ClientCollection,Init)
    
    ;Field
    ;call via Object
    OCall pCollect::ClientCollection.SearchField, AccountFID, $OfsDStr("90-160")
    OCall pCollect::ClientCollection.SearchField, NameFID, $OfsDStr("John")
    OCall pCollect::ClientCollection.SearchField, PhoneFID, $OfsDStr("555")
    
    ;mov pDskStm, $New(DiskStream, Init, NULL, "Data.stm")
   	;OCall pDskStm::DiskStream.Put, pCollect
   	;Destroy pDskStm
    
;    mov pDskStm, $New(MemoryStream, Init, NULL, 20, 5, 1024*2)
;   	OCall pDskStm::MemoryStream.Put, pCollect
;   	OCall pDskStm::MemoryStream.FileSave, "TES.DTA"
;   	Destroy pDskStm

    Destroy pCollect
    
    DbgLine
    DbgText "Done"
    SysDone       
    invoke ExitProcess, 0

end start  
