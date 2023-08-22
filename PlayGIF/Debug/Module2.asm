;EasyCodeName=Module2,1
.Const

.Data?

.Data
WideChar CHAR 255 Dup (?)
strGuid  WCHAR 39 Dup (?)
GUIDdat  GUID <?>

.Code
ImageSelectActiveFrame Proc Uses Ebx Edi Esi imagen1:LPSTR, frameIndex:DWord
	Invoke GdipImageSelectActiveFrame, imagen1, Addr GUIDdat, frameIndex
	Ret
ImageSelectActiveFrame EndP
DrawImageWndRect Proc Uses Ebx Edi Esi imagen1:LPSTR, hwnd1:HWND, wndID:DWord, pImageRect:LPSTR
	Local graphics:LPSTR, graphics1:LPSTR, hdc1:HDC
	Local hPictureBox:HWND, PictureBoxRect:RECT
	Invoke GetDlgItem, hwnd1, wndID
	Mov hPictureBox, Eax
	;Invoke SetWindowPos, hPictureBox, HWND_TOP, [Ebx].left, [Ebx].top, [Ebx].right, [Ebx].bottom, SWP_SHOWWINDOW
	;Invoke GetClientRect, hPictureBox, Addr PictureBoxRect
	;Invoke InvalidateRect, hPictureBox, Addr PictureBoxRect, TRUE
	;Invoke GetDC, hPictureBox
	;Mov hdc1, Eax
	Invoke GdipCreateFromHWND, hPictureBox, Addr graphics
	Invoke GdipSetInterpolationMode, graphics, InterpolationModeHighQualityBilinear  ; equ	6
	Invoke GdipGraphicsClear, graphics, 0
;	Invoke GdipCreateFromHDC, hdc1, Addr graphics
	Invoke GdipDrawImageI, graphics, imagen1, 0, 0 ;x:DWord, Y:DWord
;  	Mov Ebx, pImageRect ; ptr to RECT struct
;	Assume Ebx: Ptr RECT
;	Invoke GdipDrawImageRectI, graphics, imagen1, PictureBoxRect.left, PictureBoxRect.top, PictureBoxRect.right, PictureBoxRect.bottom
	;Invoke GdipDrawImageRectI, graphics, imagen1, [Ebx].left, [Ebx].top, [Ebx].right, [Ebx].bottom
	Invoke GdipDeleteGraphics, Addr graphics
	;Invoke ReleaseDC, hPictureBox, hdc1
	Ret
DrawImageWndRect EndP
GetImageRect Proc Uses Ebx Edi Esi imagen1:LPSTR, pImageRect: Ptr
	Local nWidth:DWord, nHeight:DWord
	Invoke GdipGetImageHeight, imagen1, Addr nHeight
	Invoke GdipGetImageWidth, imagen1, Addr nWidth
   	Mov Ebx, pImageRect ; ptr to RECT struct
	Assume Ebx:Ptr RECT
	Mov Eax, nWidth
	Mov [Ebx].right, Eax
	Mov Eax, nHeight
	Mov [Ebx].bottom, Eax
	Ret
GetImageRect EndP
DrawImage Proc hdc:HDC, gImage:DWord, pImageRect: Ptr
    Local graphics:LPSTR
    Invoke GdipCreateFromHDC, hdc, Addr graphics
   	Mov Ebx, pImageRect ; ptr to RECT struct
	Assume Ebx:Ptr RECT
    Invoke GdipDrawImageRectI, graphics, gImage, 0, 0, [Ebx].right, [Ebx].bottom
    Invoke GdipDeleteGraphics, graphics
    ret
DrawImage EndP
GetImage2Bitmap Proc Uses Ebx Edi Esi imagen1:LPSTR, pImageRect: Ptr ;ControlHandle:HWND
	Local _HorRes:DWord
	Local _VerRes:DWord
	Local imagen2:LPVOID
	Local FixelFormat:LPVOID
	Local hBitmap:HBITMAP
	Local Grafhics:LPVOID
	Invoke GdipGetImagePixelFormat, imagen1, Addr FixelFormat
	;Virtual data struktur
   	Mov Ebx, pImageRect ; ptr to RECT struct
	Assume Ebx:Ptr RECT
	Invoke GdipCreateBitmapFromScan0, [Ebx].right, [Ebx].bottom, 0, FixelFormat, 0, Addr imagen2
	Invoke GdipGetImageHorizontalResolution, imagen1, Addr _HorRes
	Invoke GdipGetImageVerticalResolution, imagen1, Addr _VerRes
	Invoke GdipBitmapSetResolution, imagen2, _HorRes, _VerRes
	Invoke GdipGetImageGraphicsContext, imagen2, Addr Grafhics
	Invoke GdipSetInterpolationMode, Grafhics, InterpolationModeHighQualityBilinear  ; equ	6
	Invoke GdipGraphicsClear, Grafhics, 0
	;Virtual data struktur
   	Mov Ebx, pImageRect ; ptr to RECT struct
	Assume Ebx:Ptr RECT
	Invoke GdipDrawImageRectI, Grafhics, imagen1, 0, 0, [Ebx].right, [Ebx].bottom
	Invoke GdipDeleteGraphics, Grafhics
	Invoke GdipCreateHBITMAPFromBitmap, imagen2, Addr hBitmap, 0
	Invoke GdipDisposeImage, imagen2
	Mov Eax, hBitmap
	Ret
GetImage2Bitmap EndP
DelBitmap Proc hbmp:HBITMAP
	Invoke DeleteObject, hbmp
	Ret
DelBitmap EndP
DelImage Proc Imagen1:LPVOID
	Invoke GdipDisposeImage, Imagen1
	Ret
DelImage EndP
GetFile2Image Proc Uses Ebx Edi Esi PathFileName:Ptr LPSTR
	Local _image:LPVOID
	Invoke RtlZeroMemory, Addr WideChar, SizeOf WideChar
	Invoke MultiByteToWideChar, CP_OEMCP, MB_PRECOMPOSED, PathFileName, -1, Addr WideChar, SizeOf WideChar
	Invoke GdipLoadImageFromFile, Addr WideChar, Addr _image
	Mov Eax, _image
	Ret
GetFile2Image EndP
GetFrameSumGIF Proc Uses Ebx Edi Esi imagen:DWord
	Local count:DWord
	Local subcount:DWord
	Local hLocMem1:HANDLE
	Local pCLSID_ImageFormat:LPSTR
	;mengambil jumlah format gambar
	Invoke GdipImageGetFrameDimensionsCount, imagen, Addr count
	;m_pDimensionIDs =new GUID[count];
	;Mov Eax, (SizeOf GUID) * count
    ;Mul count
	Invoke Malloc, SizeOf GUID, Addr hLocMem1
	Mov pCLSID_ImageFormat, Eax
	;mengambil CLSID format gambar
	Invoke GdipImageGetFrameDimensionsList, imagen, pCLSID_ImageFormat, count
	;WCHAR strGuid[39];
	Invoke RtlMoveMemory, Addr GUIDdat, pCLSID_ImageFormat, SizeOf GUID
	;Invoke StringFromGUID2, Addr GUIDdat, Addr strGuid, SizeOf strGuid ;
	Invoke StringFromGUID2, pCLSID_ImageFormat, Addr strGuid, SizeOf strGuid ;
	;Invoke StringFromIID, pCLSID_ImageFormat, Addr strGuid ;
	;m_FrameCount = m_pImage->GetFrameCount(&m_pDimensionIDs[0]);
	;mengambil jumlah frame di CLSID yg pertama saja
	Invoke GdipImageGetFrameCount, imagen, pCLSID_ImageFormat, Addr subcount
	Invoke MemFree, hLocMem1
	Mov Ecx, count    ;jml dimensi
	Mov Eax, subcount ;jml frame
	Ret
GetFrameSumGIF EndP
GetPropertyValue Proc Uses Ebx Esi Edi imagen:DWord, tagPropety:DWord
	Local pItem:LPSTR
	Local propSize:DWord
	Local hLocMem1:HANDLE
	Local ValueRslt:DWord
    ;Mengambil Besar ukuran Data Proprty
	Invoke GdipGetPropertyItemSize, imagen, tagPropety, Addr propSize
	;Pesan Memory
	Invoke Malloc, propSize, Addr hLocMem1
	Mov pItem, Eax
	;Ambil item Property nya
    Invoke GdipGetPropertyItem, imagen, tagPropety, propSize, pItem
	;using for virtual structure
    Mov Ebx, pItem  ; ptr to PropertyItem_ struct
	Assume Ebx:Ptr PropertyItem
	Mov Ebx, [Ebx].value
	Mov ValueRslt, Ebx
    ;bebaskan memory
	Invoke MemFree, hLocMem1
	Mov Eax, ValueRslt ;ambil pointer
	Mov Eax, [Eax] ;ambil nilai
	Ret
GetPropertyValue EndP
DlGSetGUID2String Proc hWnd:HWND, wndID:DWord ;, pCLSID_ImageFormat:Ptr
	Local hLocMem1:HANDLE
	szText szGUID, "CLSID : %s." ;.\n"
	;  WCHAR strGuid[39];
    ;  StringFromGUID2(encoderClsid, strGuid, 39);
    ;  printf ("An ImageCodecInfo object representing the PNG encoder\n") ;
    ;  printf("was found at position %d in the array.\n", result);
    ;  wprintf(L"The CLSID of the PNG encoder is %s.\n", strGuid);
	Invoke RtlZeroMemory, Addr WideChar, SizeOf WideChar
	Invoke WideCharToMultiByte, CP_ACP, 0, Addr strGuid, -1, Addr WideChar, SizeOf WideChar, 0, 0
    ;Invoke SysFreeString, Addr WideChar
	Invoke DlgSetText, hWnd, wndID, Addr szGUID, Addr WideChar
	Ret
DlGSetGUID2String EndP
;The CLSID of the PNG encoder is {557CF406-1A04-11D3-9A73-0000F81EF32E}.
DlgOpenFile Proc hWnd:HWND, hInstance:HINSTANCE, szFileFilter: Ptr, szFileName: Ptr
	Local ofn:OPENFILENAME
	;clear OPENFILENAME Strcture
	Invoke RtlZeroMemory, Addr ofn, SizeOf OPENFILENAME
	;initial  OPENFILENAME Strcture
	Mov ofn.lStructSize, SizeOf OPENFILENAME
	Mov Eax, hWnd
	Mov ofn.hwndOwner, Eax
	Mov Eax, hInstance
	Mov ofn.hInstance, Eax
	Mov Eax, szFileFilter
	Mov ofn.lpstrFilter, Eax
	Mov ofn.nFilterIndex, 1
    Mov Eax, szFileName
	Mov ofn.lpstrFile, Eax
	Mov ofn.nMaxFile, MAX_PATH
	Mov ofn.Flags, (OFN_EXPLORER Or OFN_FILEMUSTEXIST Or OFN_PATHMUSTEXIST Or OFN_HIDEREADONLY)
    Invoke GetOpenFileName, Addr ofn
	Ret
DlgOpenFile EndP
