; ==================================================================================================
; Title:   Fpu1.asm
; Author:  Pahor.m  @ Mei 2020
; Version: 1.0.0
; Purpose: Demonstration program 1 of ObjAsm32.
; ==================================================================================================

;Include & initialize standard modules
%include @Environ(OA32_PATH)\\Code\\Macros\\Model.inc

;Include coprocessor math macros
% include &MacPath&fMath.inc   

;Loads OOP files and OS related objects       
SysSetup OOP_WINDOWS , DEBUG(WND)                          

;Load or build the following objects
;LoadObjects WinApp, SdiApp                                  
;LoadObjects Window
;LoadObjects Button, ColorButton

;Includes Demonstration object (insert .code)
;include skindata.inc                                      
;include skinregion.inc                                      
;include skinpaint.inc 
;include skinTittle.inc 
;include skinMenu.inc 
;                                 
;include Wndx4.inc      
                                
.data

nItem equ 3
real8_array real8 nItem dup (2.0, 3.0, 4.0)
array_items dword nItem 
real8_var	real8 0.0

temp_bcd     dt   ?
szdecimal    db   32 dup(0)

.code
;The application is an object called "WndX"
start:                          ;Program entry point
    SysInit						;Runtime initialization of OOP model (Required)
	
	DbgText "Start"
	DbgLine
	
	lea   edx,real8_array ;use EDX as a pointer to the array
	mov   ecx,array_items ;use ECX as counter for the number of items to process
	fldz                  ;initialize a register to accumulate the squared values
	                      ;-> ST(0)=accumulator=0
@@:
	fld   real8 ptr [edx] ;load the next REAL8 value
	                      ;-> ST(0)=REAL value, ST(1)=accumulator
	fmul  st,st           ;square it
	                      ;-> ST(0)=REAL value squared, ST(1)=accumulator
	faddp st(1),st        ;add to the accumulator and discard the squared value
	                      ;-> ST(0)=accumulator+squared REAL value
	add   edx,8           ;adjust the pointer to the next REAL8 item
	dec   ecx             ;decrement the counter
	jnz   @B              ;continue until all items are processed
	
						  
	fst  real8_var		  ;-> ST(0)=the sum of squares, store to real_var
	
	;real8 = 15 digit
	invoke St0ToStr, addr szdecimal,32-20,1, f_SCI ;f_SCI=Sentific f_NOR=Normal			
	;100 000 000 000 000 000 0 = 19 digit
	DbgDec array_items
	DbgStr szdecimal
	
	DbgLine
	DbgText "End"
    SysDone						;Runtime finalization of the OOP model (Required)
    invoke ExitProcess, 0		;Exits program returning 0 to the OS
end start						;Code end and defines prg entry point
