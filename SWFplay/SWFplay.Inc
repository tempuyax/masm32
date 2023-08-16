include windows.inc
include user32.inc
include kernel32.inc
include comdlg32.inc
include Comctl32.inc
include shell32.inc
include advapi32.inc
include gdi32.inc
include shlwapi.inc

includelib user32.lib
includelib kernel32.lib
includelib comdlg32.lib
includelib Comctl32.lib
includelib shell32.lib
includelib advapi32.lib
includelib gdi32.lib
includelib shlwapi.lib
     
DlgProc			 PROTO	:HWND,:UINT,:WPARAM,:LPARAM
PlayerWin        PROTO	:HWND
WriteHtml        PROTO	:HWND

.const
IDD_DIALOG		equ 1000
IDC_BROWSE      equ 1002
IDC_PATH        equ 1003
;#########################################################################
.data
szDLL			db	"atl.dll",0
szAtlAxWinInit  db	"AtlAxWinInit",0
szAtlAxWin      db  "AtlAxWin",0
szPlayer        db  "biohome2.htm",0
szBksl          db "\",0
szHeader        db '<style type="text/css">',13,10
                db 'body {',13,10
	            db 'margin:0px;',13,10
	            db '}',13,10	
	            db 'td {',13,10
	            db 'font:11px arial;',13,10
	            db 'color:#99CCFF;',13,10
	            db '}',13,10
	            db '</style>',13,10
	            db '<body bgcolor="#14285f">',13,10
	            db '<object class="video" width="435" height="299" type="application/x-shockwave-flash" data="flvplayer.fla">',13,10,0
szFlvFile	    db '<param name="flashvars" value="file=%s" />',0
szFooter	    db '<param name="movie" value="flvplayer.fla" />',13,10
	            db '<embed src="flvplayer.fla" width="435" height="299" bgcolor="#FFFFFF" type="application/x-shockwave-flash" />',13,10
	            db '</object>',0
szReturnLine    db 0Dh,0Ah
FilterString    db "Target (*.swf)",0,"*.swf",0,0
ErrorMsgTitle   db "Error",0
OpenError       db "Cannot open flv-file!",0
ofn             OPENFILENAME <>
OfnTitle        db "Select the flv file",0

include flvplayer.inc
szflvplayer     db "flvplayer.fla",0
.data?

hInstance	    dd ?
hPlayWin        dd ?
hEdit           dd ?
hLib			dd ?
hCurDir         db 512 dup(?)
FileBuffer      db 512 dup (?)
hFile           dd ?
lBytesWriten    dd ?
lpOut           dd ?
;#########################################################################
