;EasyCodeName=Module1,1
MakeARGB Macro Alpha, cRed, cGreen, cBlue
        Xor Eax, Eax
        Mov Ah, Alpha ; blue
        Mov Al, cRed  ; red
        Rol Eax, 16
        Mov Ah, cGreen ; green
        Mov Al, cBlue  ; blue
EndM

.Const
UnitWorld		Equ	0	; World coordinate (non-physical unit)
InterpolationModeHighQualityBilinear	Equ	6
;        Gray                 = 0xFF808080,
;        Green                = 0xFF008000,

GdiplusStartupInput Struct
    GdiplusVersion 				DWord ?
    DebugEventCallback 			DWord ?
    SuppressBackgroundThread 	DWord ?
    SuppressExternalCodecs 		DWord ?
GdiplusStartupInput EndS

.Data?

.Data
hInst 			HANDLE ?
clr   			DWord  ?
WidthX 	  		Real4  1.9
gdipInput 		GdiplusStartupInput <?> ;
gdipToken 		LPVOID ? ;

;curve points
;Pts POINT <10>
CurvePts POINT <0, 100>, <50, 80>, <100, 20>, <150, 80>, <200, 100>
DrawTxt CHAR "Testing", 0
CloseCurvePts POINT <60, 60>, <150, 80>, <200, 40> , <180, 120> , <120, 100> , <80, 160>

.Code

start:
	Invoke GetModuleHandle, NULL
	Mov hInst, Eax
	Invoke GetCommandLine
	Invoke WinMain, hInst, NULL, Eax, SW_SHOWDEFAULT
	Invoke ExitProcess, Eax

WinMain Proc Private hInstance:HINSTANCE, hPrevInst:HINSTANCE, lpCmdLine:LPSTR, nCmdShow:DWord
   	Local hwnd:HWND
   	Local msg:MSG                 ;
   	Local wc:WNDCLASSEX  ;

	Mov gdipInput.GdiplusVersion, 1
   	Invoke GdiplusStartup, Addr gdipToken, Addr gdipInput, NULL

	szText szClassName, "GettingStarted"
	Mov wc.cbSize, SizeOf WNDCLASSEX
	Mov wc.style, (CS_HREDRAW Or CS_VREDRAW)
	Mov wc.lpfnWndProc, Offset WindowProcedure
	Mov wc.cbClsExtra, NULL
	Mov wc.cbWndExtra, NULL
	m2m wc.hInstance, hInstance
	Mov wc.hbrBackground, COLOR_BTNFACE + 1
	Mov wc.lpszMenuName, NULL
	Mov wc.lpszClassName, Offset szClassName
	Invoke LoadIcon, NULL, IDI_APPLICATION
	Mov wc.hIcon, Eax
	Mov wc.hIconSm, Eax
	Invoke LoadCursor, NULL, IDC_ARROW
	Mov wc.hCursor, Eax
	Invoke RegisterClassEx, Addr wc

	szText szAppName, "Getting Started"
	Invoke CreateWindowEx, NULL, Addr szClassName, Addr szAppName,
		   (WS_OVERLAPPEDWINDOW Or WS_CLIPCHILDREN), CW_USEDEFAULT,
		   CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		   NULL, NULL, hInst, NULL
	Mov hwnd, Eax

	Push Eax
	Invoke ShowWindow, Eax, nCmdShow
	Pop Eax
	Invoke UpdateWindow, Eax

@@:	Invoke GetMessage, Addr msg, NULL, 0, 0
	.If Eax
		Invoke TranslateMessage, Addr msg
		Invoke DispatchMessage, Addr msg
		Jmp Short @B
	.EndIf

	Invoke GdiplusShutdown, gdipToken ;

	Mov Eax, msg.wParam
	Ret
WinMain EndP

WindowProcedure Proc Private Uses Ebx Edi Esi hWnd:HWND, uMsg:ULONG, wParam:WPARAM, lParam:LPARAM
    Local ps:PAINTSTRUCT
    Local hdc:HDC
    Local rc:RECT
	.If uMsg == WM_CREATE
		Xor Eax, Eax
		Ret
	.ElseIf uMsg == WM_PAINT
		Invoke BeginPaint, hWnd, Addr ps
		Mov hdc, Eax
        Invoke GetClientRect, hWnd, Addr rc
		Invoke DrawText, hdc, Addr DrawTxt, -1, Addr rc, NULL
		Invoke DrawCloseCurve, hdc, Addr CloseCurvePts, 6
		;Invoke DrawCurve, hdc, Addr CurvePts, 5
		;Invoke DrawLine, hdc
		;Invoke DrawRectangle, hdc
		Invoke EndPaint, hWnd, Addr ps
		Xor Eax, Eax
		Ret
	.ElseIf uMsg == WM_DESTROY
		Invoke PostQuitMessage, 0
		Xor Eax, Eax
		Ret
	.EndIf
	Invoke DefWindowProc, hWnd, uMsg, wParam, lParam
	Ret
WindowProcedure EndP
DrawLine Proc Private Uses Ebx Edi Esi hdc:HDC
		Local nativeGraphics:LPVOID
		Local nativePen:LPVOID

		Invoke GdipCreateFromHDC, hdc, Addr nativeGraphics
		MakeARGB 255, 255, 0, 0
		Mov clr, Eax
		Invoke GdipCreatePen1, clr, WidthX, UnitWorld, Addr nativePen
		Invoke GdipDrawLineI, nativeGraphics, nativePen, 0, 0, 200, 100
		Invoke GdipDrawRectangleI, nativeGraphics, nativePen, 200, 100, 100, 100
		Invoke GdipDeletePen, nativePen
		Invoke GdipDeleteGraphics, nativeGraphics
		Ret
DrawLine EndP
DrawRectangle Proc Private Uses Ebx Edi Esi hdc:HDC
		Local nativeGraphics:LPVOID
		Local nativePen:LPVOID

		Invoke GdipCreateFromHDC, hdc, Addr nativeGraphics
		MakeARGB 255, 255, 0, 0
		Mov clr, Eax
		Invoke GdipCreatePen1, clr, WidthX, UnitWorld, Addr nativePen
		Invoke GdipDrawRectangleI, nativeGraphics, nativePen, 200, 100, 100, 100
		Invoke GdipDeletePen, nativePen
		Invoke GdipDeleteGraphics, nativeGraphics
		Ret
DrawRectangle EndP
;Point points[] = {Point (0, 100),
;                  Point(50, 80),
;                  Point(100, 20),
;                  Point(150, 80),
;                  Point(200, 100)};

;Pen pen(Color(255, 0, 0, 255));
;graphics.DrawCurve(&pen, points, 5);
DrawCurve Proc Uses Ebx Edi Esi hdc:HDC, pPoints: Ptr, PointCount:DWord
		Local nativeGraphics:LPVOID
		Local nativePen:LPVOID

		Invoke GdipCreateFromHDC, hdc, Addr nativeGraphics
		MakeARGB 255, 255, 0, 0
		Mov clr, Eax
		Invoke GdipCreatePen1, clr, WidthX, UnitWorld, Addr nativePen
	 	Invoke GdipDrawCurveI, nativeGraphics, nativePen, pPoints, PointCount
		Invoke GdipDeletePen, nativePen
		Invoke GdipDeleteGraphics, nativeGraphics
		Ret
DrawCurve EndP
;Point points[] = {Point (60, 60),
;   Point(150, 80),
;   Point(200, 40),
;   Point(180, 120),
;   Point(120, 100),
;   Point(80, 160)};
;Pen pen(Color(255, 0, 0, 255));
;graphics.DrawClosedCurve(&pen, points, 6);
DrawCloseCurve Proc Uses Ebx Edi Esi hdc:HDC, pPoints: Ptr POINT, PointCount:DWord
	Local nativeGraphics:LPVOID
	Local nativePen:LPVOID

	Invoke GdipCreateFromHDC, hdc, Addr nativeGraphics
	MakeARGB 255, 255, 0, 0
	Mov clr, Eax
	Invoke GdipCreatePen1, clr, WidthX, UnitWorld, Addr nativePen
	;Invoke GdipDrawRectanglesI, nativeGraphics, nativePen, pRects, PointCount
 	Invoke GdipDrawClosedCurveI, nativeGraphics, nativePen, pPoints, PointCount
	Invoke GdipDeletePen, nativePen
	Invoke GdipDeleteGraphics, nativeGraphics
	Ret
DrawCloseCurve EndP
End start

