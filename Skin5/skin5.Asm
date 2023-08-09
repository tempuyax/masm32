; ==================================================================================================
; Title:   Skin5.asm
; Author:  Pahor.m  @ September 2019
; Version: 1.0.0
; Purpose: Demonstration program 1 of ObjAsm32.
; ==================================================================================================

;Include & initialize standard modules
%include @Environ(OA32_PATH)\\Code\\Macros\\Model.inc

;Loads OOP files and OS related objects       
SysSetup OOP_WINDOWS ;, DEBUG(WND)                          

;Load or build the following objects
LoadObjects WinApp, SdiApp                                  ;Include SDI framework library

;Includes Demonstration object (insert .code)
include skindata.inc                                      
include skinregion.inc                                      
include skinpaint.inc 
;include skinTittle.inc 
;include skinMenu.inc 

;Include Main App                                
include skin5.inc                                      

;The application is an object called "skin5"
start:                                                      ;Program entry point
    SysInit                                                 ;Runtime initialization of OOP model (Required)

    OCall TPL_skin5::skin5.Init                               ;Initialize the object data
    OCall TPL_skin5::skin5.Run                      
    OCall TPL_skin5::skin5.Done                   

    SysDone                                                 ;Runtime finalization of the OOP model (Required)
    invoke ExitProcess, 0                                   ;Exits program returning 0 to the OS
end start                                                   ;Code end and defines prg entry point
