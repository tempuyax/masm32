;Editor:      Pahor Mustaly
;Date:        (C) Sep 2019
;Description: Menjalankan Flash Melalui Sript MS HTML
; ——————————————————————————————————————————————————————————————————————————————————————————————————

.386
.model flat, stdcall  ;32 bit memory model
option casemap :none  ;case sensitive

include windows.inc
include user32.inc
include kernel32.inc
include comdlg32.inc
include Comctl32.inc
include shell32.inc
include advapi32.inc
include gdi32.inc
include shlwapi.inc
include D:\masm32\m32lib\masm32.inc

includelib user32.lib
includelib kernel32.lib
includelib comdlg32.lib
includelib Comctl32.lib
includelib shell32.lib
includelib advapi32.lib
includelib gdi32.lib
includelib shlwapi.lib
includelib D:\masm32\m32lib\masm32.lib
     
DlgProc			PROTO	:HWND,:UINT,:WPARAM,:LPARAM
PlayerWin       PROTO	:HWND
GMalloc 		PROTO 	:DWord, :DWORD
GMemFree 		PROTO 	:DWord
Malloc 			PROTO 	:DWord, :DWORD
MemFree 		PROTO 	:DWord

.const
IDD_DIALOG		equ 1000
IDC_BROWSE      equ 1002
IDC_PATH        equ 1003
;#########################################################################
.data
szDLL			db	"atl.dll",0
szAtlAxWinInit  db	"AtlAxWinInit",0
szAtlAxWin      db  "AtlAxWin",0
szName	        db  "biohome2.swf",0
szBksl          db 	"\",0
szSWF			db	"ShockwaveFlash",0
szIID_SWF		db 	"{D27CDB6E-AE6D-11CF-96B8-444553540000}",0

szHTML 			Label Byte
    			DB "MSHTML:", 13, 10 ; Keyword HTM by microsoft Atl.dll
				DB "<html>", 13, 10
  				DB "<head>", 13, 10
    			DB "    <Title> Pahor. M (C) Sep 2019 </Title>", 13, 10
  				DB "</head>", 13, 10
    			DB "<body BGCOLOR=",22H,"#FFFFFF",22H,"LINK=",22H,"#0000EE",22H,"VLINK=",22H,"#551A8B",22H,"ALINK=",22H,"#FF0000",22H,">", 13, 10
    			DB "<center>", 13, 10
    			DB "   <OBJECT", 13, 10 
    			DB "      id=",22H,"biohome2",22H, 13, 10 
    			DB "      classid=",22H,"clsid:D27CDB6E-AE6D-11cf-96B8-444553540000",22H, 13, 10 
    			DB "      width=100% ", 13, 10 
    			DB "      height=100%", 13, 10 
    			DB "    >", 13, 10 
    			DB NULL ; end of Header
szTxt1			DB "       <param NAME=",22H,"Movie",22H,"VALUE=",22H,"%s",22H,">", 13, 10
				DB NULL ; end of text 1 
szFoot1    		DB "       <param NAME=",22H,"Quality",22H,"VALUE=",22H,"best",22H,">", 13, 10 
    			DB "       <param NAME=",22H,"SAlign",22H,"VALUE=",22H,"Top",22H,">", 13, 10
    			DB "       <param NAME=",22H,"Menu",22H,"VALUE=",22H,"FALSE",22H,">", 13, 10
    			DB NULL ; end of footer 1 
szTxt2 			DB "      <embed SRC=",22H,"%s",22H,"width=150 height=200 salign=top quality=best>", 13, 10
				DB NULL ; end of text 2 
szFoot2    		DB "    </OBJECT>", 13, 10 
    			DB "  </center>", 13, 10 
    			DB "</body>", 13, 10 
				DB "</html>", 13, 10 
				DB NULL ; end of footer2

.data?
hInstance	    dd ?
hPlayWin        dd ?
hLib			dd ?
Buffer          dd 512 dup (?)
hCurDir         db 512 dup(?)
TotBy           dd 0 

; ——————————————————————————————————————————————————————————————————————————————————————————————————

.code
start:

	invoke GetModuleHandle,NULL
	mov		hInstance,eax

    invoke InitCommonControls
       invoke LoadLibrary,offset szDLL
	       mov hLib,eax
	       invoke GetProcAddress,hLib,addr szAtlAxWinInit
	       call eax   
	invoke DialogBoxParam,hInstance,IDD_DIALOG,NULL,addr DlgProc,NULL
	Invoke FreeLibrary,hLib
	invoke ExitProcess,0


; ——————————————————————————————————————————————————————————————————————————————————————————————————


DlgProc proc hWnd:HWND,uMsg:UINT,wParam:WPARAM,lParam:LPARAM

	.if uMsg==WM_INITDIALOG
		invoke PlayerWin, hWnd
     
	.elseif uMsg==WM_CLOSE
		invoke EndDialog, hWnd, 0

	.else
		mov		eax,FALSE
		ret

	.endif
	mov		eax,TRUE
	ret
DlgProc endp

; ——————————————————————————————————————————————————————————————————————————————————————————————————


PlayerWin PROC hWnd:DWORD
    LOCAL hLocMem:DWORD, pStartMem:DWORD, pMem:DWORD 
    LOCAL nPos:DWORD
    
    ; Init Directory
	invoke GetCurrentDirectory,sizeof hCurDir,addr hCurDir
	invoke lstrcat,addr hCurDir,addr szBksl
	invoke lstrcat,addr hCurDir,addr szName ; nama file tggl rubah
 
	; Init Memory
	Invoke Malloc, 1024, Addr hLocMem
	mov pStartMem, eax	; static pointer
	mov pMem, eax		; dynamic pointer
	
    ; #Header manipulation
    invoke lstrlen, addr szHTML
    add TotBy, eax  ; Total Summary
    mov nPos, eax   ; Current Pos
	Invoke RtlMoveMemory, pMem, addr szHTML, eax
	mov eax, pMem   ; Base addres
	add eax, nPos   ; offset addres
	mov pMem, eax   ; Set Base Addres

    ; #text 1 manipulation
	invoke wsprintf, addr Buffer, addr szTxt1, addr hCurDir ; konversi format
    invoke lstrlen, addr Buffer
    add TotBy, eax  ; Total Summary
    mov nPos, eax   ; Current Pos
	Invoke RtlMoveMemory, pMem, addr Buffer, eax
	mov eax, pMem   ; Base addres
	add eax, nPos   ; offset addres
	mov pMem, eax   ; Set Base Addres
	;>> Footer 1
    invoke lstrlen, addr szFoot1
    add TotBy, eax  ; Total Summary
    mov nPos, eax   ; Current Pos
	Invoke RtlMoveMemory, pMem, addr szFoot1, eax
	mov eax, pMem   ; Base addres
	add eax, nPos   ; offset addres
	mov pMem, eax   ; Set Base Addres

    ; #text 2 manipulation
	invoke wsprintf, addr Buffer, addr szTxt2, addr hCurDir ; konversi format
    invoke lstrlen, addr Buffer
    add TotBy, eax  ; Total Summary
    mov nPos, eax   ; Current Pos
	Invoke RtlMoveMemory, pMem, addr Buffer, eax
	mov eax, pMem   ; Base addres
	add eax, nPos   ; offset addres
	mov pMem, eax   ; Set Base Addres
	;>> Footer 2
    invoke lstrlen, addr szFoot2
    add TotBy, eax  ; Total Summary
    mov nPos, eax   ; Current Pos
	Invoke RtlMoveMemory, pMem, addr szFoot2, eax
	mov eax, pMem   ; Base addres
	add eax, nPos   ; offset addres
	mov pMem, eax   ; Set Base Addres
	
	; set NULL byte for END OF data
	inc eax					 ; +1
    Mov Byte Ptr [Eax], NULL ; Clear Byte for EOF
    
    ; View Flahsh Object
	invoke CreateWindowEx,0,addr szAtlAxWin, pStartMem, WS_CHILD or WS_VISIBLE,
	                            0,0,435,299,hWnd,NULL,hInstance,NULL
	mov hPlayWin,eax
	
    ; Memory clear
	Invoke MemFree, hLocMem
    
	ret
PlayerWin endp

; ——————————————————————————————————————————————————————————————————————————————————————————————————


GMalloc Proc Uses Ebx Edi Esi MemSize:DWord, phMem:DWORD
	Invoke GlobalAlloc, GHND, MemSize
	Mov Ebx, phMem
	Mov [Ebx], Eax 			;Simpan data eax ke alamat didalam ebx (Mengisi phMem)
	Invoke GlobalLock, Eax
	Ret
GMalloc EndP

GMemFree Proc Uses Ebx Edi Esi hMem:DWord
	Invoke GlobalUnlock, hMem
	Invoke GlobalFree, hMem
	Ret
GMemFree EndP

; ——————————————————————————————————————————————————————————————————————————————————————————————————


Malloc Proc Uses Ebx Edi Esi MemSize:DWord, phMem:DWORD
	Invoke LocalAlloc, LHND, MemSize
	Mov Ebx, phMem
	Mov [Ebx], Eax 			;Simpan data eax ke alamat didalam ebx (Mengisi phMem)
	Invoke LocalLock, Eax
	Ret
Malloc EndP

; ——————————————————————————————————————————————————————————————————————————————————————————————————


MemFree Proc Uses Ebx Edi Esi hMem:DWord
	Invoke LocalUnlock, hMem
	Invoke LocalFree, hMem
	Ret
MemFree EndP


end start
