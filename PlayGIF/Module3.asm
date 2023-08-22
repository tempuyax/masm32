;EasyCodeName=Module3,1
.Const

.Data?

.Data

.Code
TopXY Proc wDim:DWord, sDim:DWord
    Shr sDim, 1      ; divide screen dimension by 2
    shr wDim, 1      ; divide window dimension by 2
    mov eax, wDim    ; copy window dimension into eax
    sub sDim, eax    ; sub half win dimension from half screen dimension
    Return sDim
TopXY EndP
Malloc Proc Uses Ebx Edi Esi MemSize:DWord, phMem:Ptr
	Invoke LocalAlloc, LHND, MemSize
	Mov Ebx, phMem
	Mov [Ebx], Eax ;Simpan data eax ke alamat didalam ebx
	Invoke LocalLock, Eax
	Ret
Malloc EndP
MemFree Proc Uses Ebx Edi Esi hMem:DWord
	Invoke LocalUnlock, hMem
	Invoke LocalFree, hMem
	Ret
MemFree EndP
DlgSetText Proc hWnd:HWND, winID:DWord, Charformat: Ptr, Data:DWord
	Local CekOutPut[255]:CHAR, htes:HWND
	Local CharOutPut[255]:CHAR
	Local hControl:HWND, rc:RECT, hdc:HDC, rcTmp:RECT, hBackground:HANDLE, hRgn:HRGN, hBrs:HBRUSH
	Invoke RtlZeroMemory, Addr CharOutPut, SizeOf CharOutPut
	Invoke wsprintf, Addr CharOutPut, Charformat, Data
	Invoke GetDlgItem, hWnd, winID
	Mov hControl, Eax

	; GetClientRect, MapWindowPoints, InvalidateRect
	; tiga fungsi yg sangat menentukan overlaping windows
	; NOTE: fungsi InvalidateRect adalah "Meng-update semua overlapping windows"
	;		Urusan WM_PAINT NYA sudah di atur oleh system sepenuhnya.
	;		Jika dalam window terjadi overlapping, maka fungsi ini otomatis
	;		meng - update semua window yang ada dalam daerah RECT yg sdh detentukan sendiri
	;       - buatlah window sesuai urutan, karna InvalidateRect mengurut sesuai lapisan windownya.

	Invoke GetClientRect, hControl, Addr rc        ; fungsi ini ada jika static dlm keadaan HALLOW BRUSH
	Invoke MapWindowPoints, hControl, hWnd, Addr rc, 2
	Invoke InvalidateRect, hWnd, Addr rc, TRUE ; fungsi ini ada jika static dlm keadaan HALLOW BRUSH
	Invoke SendMessage, hControl, WM_SETTEXT, 0, Addr CharOutPut
	Ret
DlgSetText EndP
;WM_DRAWITEM membuat control mandiri
DlgSetImage Proc Uses Ebx Edi Esi hwnd:HWND, wndID:DWord, hbmp:HBITMAP
	Local hPictureBox:HWND, rc:RECT, hdc:HDC
	Invoke GetDlgItem, hwnd, wndID
	Mov hPictureBox, Eax

	; GetClientRect, MapWindowPoints, InvalidateRect
	; kombinasi tiga fungsi yg sangat menentukan overlaping windows
	; NOTE: fungsi InvalidateRect adalah "Meng-update semua overlapping windows"
	;		Urusan WM_PAINT NYA sudah di atur oleh system sepenuhnya.
	;		Jika dalam window terjadi overlapping, maka fungsi ini otomatis
	;		meng - update semua window yang ada dalam daerah RECT yg sdh detentukan sendiri
	;       - buatlah window sesuai urutan, karna InvalidateRect mengurut sesuai lapisan windownya.

    ;WM_PAINT
	;hdc = (HDC) wParam; // the device context to draw in
    ;Invoke GetDC, hPictureBox
    ;Mov hdc, Eax

	Invoke GetClientRect, hPictureBox, Addr rc        ; fungsi ini ada jika static dlm keadaan HALLOW BRUSH
	Invoke MapWindowPoints, hPictureBox, hwnd, Addr rc, 2 ; angka 2 harus di tulis, sebab bukan POINT tetapi RECT
	Invoke InvalidateRect, hwnd, Addr rc, TRUE ; fungsi ini ada jika static dlm keadaan HALLOW BRUSH
    Invoke SendMessage, hPictureBox, STM_SETIMAGE, IMAGE_BITMAP, hbmp
	Ret
DlgSetImage EndP
DlgGetClientRect Proc Uses Ebx Edi Esi hwnd:HWND, wndID:DWord, ImageRect: Ptr
	Local hPictureBox:HWND
	Invoke GetDlgItem, hwnd, wndID
	Mov hPictureBox, Eax
	Invoke GetClientRect, hPictureBox, ImageRect
	Ret
DlgGetClientRect EndP
