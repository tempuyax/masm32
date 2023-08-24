;EasyCodeName=Module2,1
; ==================================================================================================
; Title:   Bmp2Rgn.asm
; Author:  G. Friedrich
; Version: 2.0.0
; Notes:   Version 1.0.0, June 2004
;            - First release.
.Const

.Data?

.Data

.Code
;          Version 2.0.0, April 2006
;            - Completely rewritten to speedup the execution.
; ==================================================================================================
; Diambil dari bawaan OBJASM32, tidak ada perubahan code yg signifikan.
; hanya sedikit penyesuaian dgn Lingkungan EASY CODE - VISUAL ASSEMBLER
; Membuat Handle Region dari sebuah Handle Bitmap sesuai warna transparan yg dimita.
; ttd PAHOR .M Nunukan,19 Jan 2011
; output eax = hregion
;        ecx = total byte yg sudah termasuk struktur header regionnya...
;===============================================================================
Bmp2Rgn Proc Private Uses Ebx Edi Esi hBmp:HBITMAP, dTransparentColor:DWord
    Local Bmp:BITMAP, BmpInfoHdr:BITMAPINFOHEADER, hDC:HDC
    Local pBuffer:LPSTR, pRectBuffer:LPSTR, dRectCount:DWord
    Local dCurrScanLine:DWord, sdIncrement:SDWord

    Invoke GetObject, hBmp, SizeOf Bmp, Addr Bmp
    .If Eax != 0
      Mov Ecx, dTransparentColor            ;Transform the RGB to a BGR color as it is found in mem.
      Rol Ecx, 8                            ;  RR GG BB AA
      Ror Cx, 8                             ;  RR GG AA BB
      Rol Ecx, 16                           ;  AA BB RR GG
      Ror Cx, 8                             ;  AA BB GG RR
      Mov dTransparentColor, Ecx

      Mov Eax, Bmp.bmWidth
      Shl Eax, 2
      Mov BmpInfoHdr.biSizeImage, Eax
      Mov BmpInfoHdr.biSize, SizeOf BmpInfoHdr
      Mov Eax, Bmp.bmWidth
      Mov BmpInfoHdr.biWidth, Eax

      Mov Ecx, Bmp.bmHeight
      Mov BmpInfoHdr.biHeight, Ecx

      .If SDWord Ptr (Ecx) > 0              ;Detect top-down or bottom-up bitmaps
        Mov sdIncrement, -1                 ;Bottom-up bitmap
        Mov dCurrScanLine, Ecx
      .Else
        Mov sdIncrement, 1                  ;Top-down bitmap
        Mov dCurrScanLine, -1
      .EndIf

      Mov BmpInfoHdr.biPlanes, 1
      Mov BmpInfoHdr.biBitCount, 32
      Mov BmpInfoHdr.biCompression, BI_RGB

      Shl Eax, 2                            ;Scanline buffer = Bmp.bmWidth * 4
      Push Eax
      Mul Ecx                               ;Max possible number of rects = width x height / 2
      Shl Eax, 1
      Add Eax, [Esp]
      Add Eax, SizeOf RGNDATAHEADER
      Invoke VirtualAlloc, NULL, Eax, MEM_COMMIT, PAGE_READWRITE
      Pop Ecx
      .If Eax != NULL
        Mov pBuffer, Eax
        Add Eax, Ecx
        Mov pRectBuffer, Eax
        Mov [Eax].RGNDATAHEADER.dwSize, SizeOf RGNDATAHEADER
        Mov [Eax].RGNDATAHEADER.iType, RDH_RECTANGLES
        Mov [Eax].RGNDATAHEADER.nRgnSize, 0
        Add Eax, SizeOf RGNDATAHEADER - SizeOf RECT
        Mov Edi, Eax
        Invoke GetDC, NULL
        Mov hDC, Eax ;$invoke(GetDC, 0)
        Xor Ebx, Ebx
        Mov dRectCount, Ebx

        .While Ebx < Bmp.bmHeight
          Mov Ecx, sdIncrement
          Add dCurrScanLine, Ecx
          Invoke GetDIBits, hDC, hBmp, dCurrScanLine, 1, pBuffer, Addr BmpInfoHdr, DIB_RGB_COLORS

          Mov Esi, pBuffer
          Xor Ecx, Ecx                      ;ecx = 0 => not in region flag
          Xor Edx, Edx                      ;Reset Scanline pixel counter
          .While Edx < Bmp.bmWidth
            Mov Eax, [Esi]
            And Eax, 00FFFFFFH              ;Ignore alpha value
            .If Eax == dTransparentColor
              .If Ecx != 0                  ;Terminate the current Rect
                Mov [Edi].RECT.right, Edx
                Xor Ecx, Ecx                ;Reset flag
              .EndIf
            .ElseIf Ecx == 0                ;Start a new Rect
              Inc dRectCount
              Add Edi, SizeOf RECT          ;Point to next Rect
              Mov Eax, Ebx
              Mov [Edi].RECT.left, Edx
              Inc Eax
              Mov [Edi].RECT.top, Ebx
              Mov [Edi].RECT.bottom, Eax
              Inc Ecx                       ;Set flag
            .EndIf
            Inc Edx
            Add Esi, 4
          .EndW

          .If Ecx != 0                      ;Close last Rect
            Mov [Edi].RECT.right, Edx
          .EndIf

          Inc Ebx
        .EndW

        Mov Eax, pRectBuffer
        Mov Ecx, dRectCount
        Mov [Eax].RGNDATAHEADER.nCount, Ecx
        Shl Ecx, 4
        Add Ecx, SizeOf RGNDATAHEADER
        Invoke ExtCreateRegion, NULL, Ecx, pRectBuffer
        Push Eax
        Invoke ReleaseDC, 0, hDC
        Invoke VirtualFree, pBuffer, 0, MEM_RELEASE
        Pop Eax
      .EndIf
    .EndIf
    Ret
Bmp2Rgn EndP

Rgn2File Proc Private Uses Ebx Edi Esi hRgn:HRGN, FileName:LPSTR, dwCount:DWord
	local hFile:HFILE
	Local lpRgnData:LPVOID
	Local pBytesWritten:LPDWORD
    Invoke CreateFile, FileName, GENERIC_READ, FILE_SHARE_READ, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0
    .If Eax == -1
    	Ret
	.EndIf

   	Mov hFile, Eax
    Invoke VirtualAlloc, NULL, dwCount, MEM_COMMIT, PAGE_READWRITE

    .If Eax != 0
	    Mov lpRgnData, Eax
	   	Invoke GetRegionData, hRgn, dwCount, lpRgnData
   		Invoke WriteFile, hFile, lpRgnData, dwCount, Addr pBytesWritten, 0
	    Invoke VirtualFree, lpRgnData, 0, MEM_RELEASE
    .EndIf

	Invoke CloseHandle, hFile
	Ret
Rgn2File EndP
Cliping Proc Private Uses Ebx Edi Esi hWnd:HRGN, FileName:LPSTR, dwCount:DWord
	 Local rctTmp:RECT
	 Local hdc:HDC
	 Local stockObj:HBRUSH
     Invoke GetDC, hWnd ;
     Mov hdc, Eax
     Invoke    GetClientRect, hWnd, Addr rctTmp ;
     invoke    GetStockObject,WHITE_BRUSH;
     Mov stockObj, Eax
     Invoke    FillRect, hdc, Addr rctTmp, stockObj ;

     ;Use the rect coordinates to define a clipping region. */ 
     Invoke    CreateRectRgn, rctTmp.top, rctTmp.left, rctTmp.bottom, rctTmp.right ;
     Mov hRgn, Eax
     Invoke    SelectClipRgn, hdc, hRgn ;
 
     ;/* Transfer (draw) the bitmap into the clipped rectangle. */ 
     Invoke BitBlt, hdc, 0, 0, bmp.bmWidth, bmp.bmHeight, hdcCompatible, 0, 0, SRCCOPY ;
     Invoke ReleaseDC, hWnd, hdc

	Ret
Cliping EndP
DlgOpenFile Proc hWnd:HWND, hInstance:HINSTANCE, szFileFilter:Ptr, szFileName:Ptr
	Local ofn:OPENFILENAME
	;clear OPENFILENAME Strcture
	Invoke RtlZeroMemory, Addr ofn, SizeOf OPENFILENAME
	;initial  OPENFILENAME Strcture
	Mov ofn.lStructSize, SizeOf OPENFILENAME
	Mov Eax, hWnd
	Mov ofn.hwndOwner, Eax
	Mov Eax, hInstance
	Mov ofn.hInstance, Eax
	Mov ofn.lpstrFilter, szFileFilter
	Mov ofn.nFilterIndex, 1
	Mov ofn.lpstrFile, szFileName
	Mov ofn.nMaxFile, MAX_PATH
	Mov ofn.Flags, (OFN_EXPLORER Or OFN_FILEMUSTEXIST Or OFN_PATHMUSTEXIST Or OFN_HIDEREADONLY)
    Invoke GetOpenFileName, Addr ofn
	Ret
DlgOpenFile EndP
