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

include Collect.inc                                 ;Include Shape, Triangle- and RectangleShape

.data                                               ;Define global variables in the Data segment
pClient1        Pointer   NULL
pClient2        Pointer   NULL
pClient3        Pointer   NULL
pClient4        Pointer   NULL
pDskStm         Pointer   NULL

.code                                               ;Begin Code segment
start:                                              ;Program entry point
    SysInit                                         ;Runtime initialization of the OOP model

; ——————————————————————————————————————————————————————————————————————————————————————————————————
    DbgText "Start"
    
    mov pClient1, $New(Client, Init,"91-100", "Anders, Smitty", "(406) 111-2222")
    mov pClient2, $New(Client, Init,"90-167", "Smith, Zelda", "(800) 555-1212")
    mov pClient3, $New(Client, Init,"90-177", "Smitty, John", "(406) 987-4321")
    mov pClient4, $New(Client, Init,"90-160", "Johnson, Agatha", "(302) 139-8913")
 
    mov pDskStm, $New(DiskStream, Init, NULL, "Data.stm")
    OCall pDskStm::DiskStream.Put, pClient1
    OCall pDskStm::DiskStream.Put, pClient2
    OCall pDskStm::DiskStream.Put, pClient3
    OCall pDskStm::DiskStream.Put, pClient4

    ;Destroy is Automatic Done
    Destroy pClient1                                ;Invokes RectangleShape's Done and disposes it
    Destroy pClient2                                ;Invokes RectangleShape's Done and disposes it
    Destroy pClient3                                ;Invokes RectangleShape's Done and disposes it
    Destroy pClient4                                ;Invokes RectangleShape's Done and disposes it
    Destroy pDskStm

; ——————————————————————————————————————————————————————————————————————————————————————————————————
    mov pDskStm, $New(DiskStream, Init, NULL, "Data.stm")

    mov pClient1, $OCall(pDskStm::DiskStream.Get, NULL)
    mov pClient2, $OCall(pDskStm::DiskStream.Get, NULL)

    OCall pClient1::Client.Print                    ;Invokes GetArea method of TriangleShape
    OCall pClient2::Client.Print                    ;Invokes GetArea method of TriangleShape
 
    ;Destroy is Automatic Done
    Destroy pClient1                                ;Invokes RectangleShape's Done and disposes it
    Destroy pClient2                                ;Invokes TriangleShape's Done and disposes it
    Destroy pDskStm
 
    DbgText "End"

; ——————————————————————————————————————————————————————————————————————————————————————————————————

    SysDone                                         ;Runtime finalization of the OOP model

    invoke ExitProcess, 0                           ;Exit program returning 0 to Windows OS
end start                                           ;End of code and define the program entry point
