GdiplusStartupInput Struct
    GdiplusVersion DWord ?
    DebugEventCallback DWord ?
    SuppressBackgroundThread DWord ?
    SuppressExternalCodecs DWord ?
GdiplusStartupInput EndS

PointF Struct
    x Real4 ?
    y Real4 ?
PointF EndS

RectF Struct
    Left Real4 ?
    Top Real4 ?
    Right Real4 ?
    Bottom Real4 ?
RectF EndS

SizeF Struct
    sx Real4 ?
    sy Real4 ?
SizeF EndS

; TASK #1  TASK #1  TASK #1  TASK #1  TASK #1  TASK #1  TASK #1  TASK #1  TASK #1  TASK #1  TASK #1  TASK #1  TASK #1  TASK #1
; xzazet
;-----------------------------------------------
; GDI+ Constants
;-----------------------------------------------
LF_FACESIZE = 32
; Shift count and bit mask for A, R, G, B components
AlphaShift	Equ	24
RedShift	Equ	16
GreenShift	Equ	8
BlueShift	Equ	0
AlphaMask	Equ	0FF000000H
RedMask	Equ	000FF0000H
GreenMask	Equ	00000FF00H
BlueMask	Equ	0000000FFH

; Access modes used when calling Image::LockBits (GdipBitmapLockBits API)
; phoenix
ImageLockModeRead                   Equ 1
ImageLockModeWrite                  Equ 2
ImageLockModeReadWrite              Equ 3
ImageLockModeUserInputBuf           Equ 4

PixelFormat1bppIndexed              Equ 30101H
PixelFormat4bppIndexed              Equ 30402H
PixelFormat8bppIndexed              Equ 30803H
PixelFormat16bppGreyScale           Equ 101004H
PixelFormat16bppRGB555              Equ 21005H
PixelFormat16bppRGB565              Equ 21006H
PixelFormat16bppARGB1555            Equ 61007H
PixelFormat24bppRGB                 Equ 21808H
PixelFormat32bppRGB                 Equ 22009
PixelFormat32bppARGB                Equ 26200AH
PixelFormat32bppPARGB               Equ 0E200BH
PixelFormat48bppRGB                 Equ 10300CH
PixelFormat64bppARGB                Equ 34400DH
PixelFormat64bppPARGB               Equ 1C400EH
PixelFormatMax                      Equ 0FH

; Image property types
PropertyTagTypeByte			Equ	1
PropertyTagTypeASCII			Equ	2
PropertyTagTypeShort			Equ	3
PropertyTagTypeLong			Equ	4
PropertyTagTypeRational		Equ	5
PropertyTagTypeUndefined		Equ	7
PropertyTagTypeSLONG		Equ	9
PropertyTagTypeSRational		Equ	10

; Image property ID tags
PropertyTagExifIFD			Equ	8769H
PropertyTagGpsIFD			Equ	8825H

PropertyTagNewSubfileType		Equ	0FEH
PropertyTagSubfileType			Equ	0FFH
PropertyTagImageWidth			Equ	100H
PropertyTagImageHeight			Equ	101H
PropertyTagBitsPerSample		Equ	102H
PropertyTagCompression	            Equ	103H
PropertyTagPhotometricInterp		Equ	106H
PropertyTagThreshHolding		Equ	107H
PropertyTagCellWidth			Equ	108H
PropertyTagCellHeight			Equ	109H
PropertyTagFillOrder			Equ	10AH
PropertyTagDocumentName		      Equ	10DH
PropertyTagImageDescription		Equ	10EH
PropertyTagEquipMake			Equ	10FH
PropertyTagEquipModel			Equ	110H
PropertyTagStripOffsets			Equ	111H
PropertyTagOrientation			Equ	112H
PropertyTagSamplesPerPixel		Equ	115H
PropertyTagRowsPerStrip		      Equ	116H
PropertyTagStripBytesCount		Equ	117H
PropertyTagMinSampleValue		Equ	118H
PropertyTagMaxSampleValue		Equ	119H
PropertyTagXResolution			Equ	11AH		; Image resolution in width direction
PropertyTagYResolution			Equ	11BH		; Image resolution in height direction
PropertyTagPlanarConfig	            Equ	11CH		; Image data arrangement
PropertyTagPageName			Equ	11DH
PropertyTagXPosition			Equ	11EH
PropertyTagYPosition			Equ	11FH
PropertyTagFreeOffset			Equ	120H
PropertyTagFreeByteCounts		Equ	121H
PropertyTagGrayResponseUnit         Equ	122H
PropertyTagGrayResponseCurve        Equ	123H
PropertyTagT4Option			Equ	124H
PropertyTagT6Option			Equ	125H
PropertyTagResolutionUnit		Equ	128H		; Unit of X and Y resolution
PropertyTagPageNumber		      Equ	129H
PropertyTagTransferFuncition		Equ	12DH
PropertyTagSoftwareUsed		      Equ	131H
PropertyTagDateTime			Equ	132H
PropertyTagArtist				Equ	13BH
PropertyTagHostComputer		      Equ	13CH
PropertyTagPredictor			Equ	13DH
PropertyTagWhitePoint			Equ	13EH
PropertyTagPrimaryChromaticities	Equ	13FH
PropertyTagColorMap			Equ	140H
PropertyTagHalftoneHints		Equ	141H
PropertyTagTileWidth			Equ	142H
PropertyTagTileLength			Equ	143H
PropertyTagTileOffset			Equ	144H
PropertyTagTileByteCounts		Equ	145H
PropertyTagInkSet				Equ	14CH
PropertyTagInkNames			Equ	14DH
PropertyTagNumberOfInks		      Equ	14EH
PropertyTagDotRange			Equ	150H
PropertyTagTargetPrinter		Equ	151H
PropertyTagExtraSamples		      Equ	152H
PropertyTagSampleFormat             Equ	153H
PropertyTagSMinSampleValue		Equ	154H
PropertyTagSMaxSampleValue          Equ	155H
PropertyTagTransferRange		Equ	156H

PropertyTagJPEGProc			Equ	200H
PropertyTagJPEGInterFormat		Equ	201H
PropertyTagJPEGInterLength		Equ	202H
PropertyTagJPEGRestartInterval	Equ	203H
PropertyTagJPEGLosslessPredictors	Equ	205H
PropertyTagJPEGPointTransforms	Equ	206H
PropertyTagJPEGQTables		Equ	207H
PropertyTagJPEGDCTables		Equ	208H
PropertyTagJPEGACTables		Equ	209H
PropertyTagYCbCrCoefficients		Equ	211H
PropertyTagYCbCrSubsampling	Equ	212H
PropertyTagYCbCrPositioning		Equ	213H
PropertyTagREFBlackWhite		Equ	214H
PropertyTagICCProfile			Equ	8773H	; This TAG is defined by ICC for embedded ICC in TIFF
PropertyTagGamma			Equ	301H
PropertyTagICCProfileDescriptor	Equ	302H
PropertyTagSRGBRenderingIntent	Equ	303H
PropertyTagImageTitle			Equ	320H
PropertyTagCopyright			Equ	8298H

; Extra TAGs (Like Adobe Image Information tags etc.)
PropertyTagResolutionXUnit			Equ	5001H
PropertyTagResolutionYUnit			Equ	5002H
PropertyTagResolutionXLengthUnit		Equ	5003H
PropertyTagResolutionYLengthUnit		Equ	5004H
PropertyTagPrintFlags				Equ	5005H
PropertyTagPrintFlagsVersion			Equ	5006H
PropertyTagPrintFlagsCrop			Equ	5007H
PropertyTagPrintFlagsBleedWidth		Equ	5008H
PropertyTagPrintFlagsBleedWidthScale	Equ	5009H
PropertyTagHalftoneLPI				Equ	500AH
PropertyTagHalftoneLPIUnit			Equ	500BH
PropertyTagHalftoneDegree			Equ	500CH
PropertyTagHalftoneShape			Equ	500DH
PropertyTagHalftoneMisc				Equ	500EH
PropertyTagHalftoneScreen			Equ	500FH
PropertyTagJPEGQuality				Equ	5010H
PropertyTagGridSize				Equ	5011H
PropertyTagThumbnailFormat			Equ	5012H	; 1 = JPEG, 0 = RAW RGB
PropertyTagThumbnailWidth			Equ	5013H
PropertyTagThumbnailHeight			Equ	5014H
PropertyTagThumbnailColorDepth		Equ	5015H
PropertyTagThumbnailPlanes			Equ	5016H
PropertyTagThumbnailRawBytes		Equ	5017H
PropertyTagThumbnailSize			Equ	5018H
PropertyTagThumbnailCompressedSize	Equ	5019H
PropertyTagColorTransferFunction		Equ	501AH
PropertyTagThumbnailData			Equ	501BH	; RAW thumbnail bits in JPEG format or RGB format
										; depends on PropertyTagThumbnailFormat

; Thumbnail related TAGs
PropertyTagThumbnailImageWidth		Equ	5020H	; Thumbnail width
PropertyTagThumbnailImageHeight		Equ	5021H	; Thumbnail height
PropertyTagThumbnailBitsPerSample		Equ	5022H	; Number of bits per component
PropertyTagThumbnailCompression		Equ	5023H	; Compression Scheme
PropertyTagThumbnailPhotometricInterp	Equ	5024H	; Pixel composition
PropertyTagThumbnailImageDescription	Equ	5025H	; Image Tile
PropertyTagThumbnailEquipMake		Equ	5026H	; Manufacturer of Image Input equipment
PropertyTagThumbnailEquipModel		Equ	5027H	; Model of Image input equipment
PropertyTagThumbnailStripOffsets		Equ	5028H	; Image data location
PropertyTagThumbnailOrientation		Equ	5029H	; Orientation of image
PropertyTagThumbnailSamplesPerPixel	Equ	502AH	; Number of components
PropertyTagThumbnailRowsPerStrip		Equ	502BH	; Number of rows per strip
PropertyTagThumbnailStripBytesCount	Equ	502CH	; Bytes per compressed strip
PropertyTagThumbnailResolutionX		Equ	502DH	; Resolution in width direction
PropertyTagThumbnailResolutionY		Equ	502EH	; Resolution in height direction
PropertyTagThumbnailPlanarConfig		Equ	502FH	; Image data arrangement
PropertyTagThumbnailResolutionUnit		Equ	5030H	; Unit of X and Y resolution
PropertyTagThumbnailTransferFunction	Equ	5031H	; Transfer function
PropertyTagThumbnailSoftwareUsed		Equ	5032H	; Software used
PropertyTagThumbnailDateTime		Equ	5033H	; File change date and time
PropertyTagThumbnailArtist			Equ	5034H	; Person who created the  image
PropertyTagThumbnailWhitePoint		Equ	5035H	; White point chromaticity
PropertyTagThumbnailPrimaryChromaticities	Equ	5036H ; Chromaticities of primaries
PropertyTagThumbnailYCbCrCoefficients	Equ	5037H	; Color space transformation coefficients
PropertyTagThumbnailYCbCrSubsampling	Equ	5038H	; Subsampling ratio of Y to C
PropertyTagThumbnailYCbCrPositioning	Equ	5039H	; Y and C position
PropertyTagThumbnailRefBlackWhite		Equ	503AH	; Pair of black and white reference values
PropertyTagThumbnailCopyRight		Equ	503BH	; CopyRight holder
PropertyTagLuminanceTable			Equ	5090H
PropertyTagChrominanceTable		Equ	5091H
PropertyTagFrameDelay				Equ	5100H
PropertyTagLoopCount				Equ	5101H
PropertyTagPixelUnit				Equ	5110H	; Unit specifier for pixel/unit
PropertyTagPixelPerUnitX			Equ	5111H	; Pixels per unit in X
PropertyTagPixelPerUnitY			Equ	5112H	; Pixels per unit in Y
PropertyTagPaletteHistogram			Equ	5113H	; Palette histogram

; EXIF specific tag
PropertyTagExifExposureTime			Equ	829AH
PropertyTagExifFNumber			Equ	829DH
PropertyTagExifExposureProg			Equ	8822H
PropertyTagExifSpectralSense			Equ	8824H
PropertyTagExifISOSpeed			Equ	8827H
PropertyTagExifOECF				Equ	8828H
PropertyTagExifVer				Equ	9000H
PropertyTagExifDTOrig				Equ	9003H	; Date & time of original
PropertyTagExifDTDigitized			Equ	9004H	; Date & time of digital data generation
PropertyTagExifCompConfig			Equ	9101H
PropertyTagExifCompBPP			Equ	9102H
PropertyTagExifShutterSpeed			Equ	9201H
PropertyTagExifAperture				Equ	9202H
PropertyTagExifBrightness			Equ	9203H
PropertyTagExifExposureBias			Equ	9204H
PropertyTagExifMaxAperture			Equ	9205H
PropertyTagExifSubjectDist			Equ	9206H
PropertyTagExifMeteringMode			Equ	9207H
PropertyTagExifLightSource			Equ	9208H
PropertyTagExifFlash				Equ	9209H
PropertyTagExifFocalLength			Equ	920AH
PropertyTagExifMakerNote			Equ	927CH
PropertyTagExifUserComment			Equ	9286H
PropertyTagExifDTSubsec			Equ	9290H	; Date & Time subseconds
PropertyTagExifDTOrigSS			Equ	9291H	; Date & Time original subseconds
PropertyTagExifDTDigSS			Equ	9292H	; Date & TIme digitized subseconds
PropertyTagExifFPXVer				Equ	0A000H
PropertyTagExifColorSpace			Equ	0A001H
PropertyTagExifPixXDim				Equ	0A002H
PropertyTagExifPixYDim				Equ	0A003H
PropertyTagExifRelatedWav			Equ	0A004H	; Related sound file
PropertyTagExifInterop				Equ	0A005H
PropertyTagExifFlashEnergy			Equ	0A20BH
PropertyTagExifSpatialFR			Equ	0A20CH	; Spatial Frequency Response
PropertyTagExifFocalXRes			Equ	0A20EH	; Focal Plane X Resolution
PropertyTagExifFocalYRes			Equ	0A20FH	; Focal Plane Y Resolution
PropertyTagExifFocalResUnit			Equ	0A210H	; Focal Plane Resolution Unit
PropertyTagExifSubjectLoc			Equ	0A214H
PropertyTagExifExposureIndex		Equ	0A215H
PropertyTagExifSensingMethod		Equ	0A217H
PropertyTagExifFileSource			Equ	0A300H
PropertyTagExifSceneType			Equ	0A301H
PropertyTagExifCfaPattern			Equ	0A302H
PropertyTagGpsVer				Equ	0
PropertyTagGpsLatitudeRef			Equ	1
PropertyTagGpsLatitude				Equ	2
PropertyTagGpsLongitudeRef			Equ	3
PropertyTagGpsLongitude			Equ	4
PropertyTagGpsAltitudeRef			Equ	5
PropertyTagGpsAltitude				Equ	6
PropertyTagGpsGpsTime			Equ	7
PropertyTagGpsGpsSatellites			Equ	8
PropertyTagGpsGpsStatus			Equ	9
PropertyTagGpsGpsMeasureMode		Equ	0AH
PropertyTagGpsGpsDop				Equ	0BH		; Measurement precision
PropertyTagGpsSpeedRef			Equ	0CH
PropertyTagGpsSpeed				Equ	0DH
PropertyTagGpsTrackRef			Equ	0EH
PropertyTagGpsTrack				Equ	0FH
PropertyTagGpsImgDirRef			Equ	10H
PropertyTagGpsImgDir				Equ	11H
PropertyTagGpsMapDatum			Equ	12H
PropertyTagGpsDestLatRef			Equ	13H
PropertyTagGpsDestLat				Equ	14H
PropertyTagGpsDestLongRef			Equ	15H
PropertyTagGpsDestLong			Equ	16H
PropertyTagGpsDestBearRef			Equ	17H
PropertyTagGpsDestBear			Equ	18H
PropertyTagGpsDestDistRef			Equ	19H
PropertyTagGpsDestDist				Equ	1AH

;  [CHECKME]
;' TODO: Make a function to get these GUIDs
;' CLSIDs (aka GUIDs) used with the GdipGetImageRawFormat function:
;'DEFINE_GUID(ImageFormatUndefined, 0xb96b3ca9,0x0728,0x11d3,0x9d,0x7b,0x00,0x00,0xf8,0x1e,0xf3,0x2e);
;'DEFINE_GUID(ImageFormatMemoryBMP, 0xb96b3caa,0x0728,0x11d3,0x9d,0x7b,0x00,0x00,0xf8,0x1e,0xf3,0x2e);
;'DEFINE_GUID(ImageFormatBMP, 0xb96b3cab,0x0728,0x11d3,0x9d,0x7b,0x00,0x00,0xf8,0x1e,0xf3,0x2e);
;'DEFINE_GUID(ImageFormatEMF, 0xb96b3cac,0x0728,0x11d3,0x9d,0x7b,0x00,0x00,0xf8,0x1e,0xf3,0x2e);
;'DEFINE_GUID(ImageFormatWMF, 0xb96b3cad,0x0728,0x11d3,0x9d,0x7b,0x00,0x00,0xf8,0x1e,0xf3,0x2e);
;'DEFINE_GUID(ImageFormatJPEG, 0xb96b3cae,0x0728,0x11d3,0x9d,0x7b,0x00,0x00,0xf8,0x1e,0xf3,0x2e);
;'DEFINE_GUID(ImageFormatPNG, 0xb96b3caf,0x0728,0x11d3,0x9d,0x7b,0x00,0x00,0xf8,0x1e,0xf3,0x2e);
;'DEFINE_GUID(ImageFormatGIF, 0xb96b3cb0,0x0728,0x11d3,0x9d,0x7b,0x00,0x00,0xf8,0x1e,0xf3,0x2e);
;'DEFINE_GUID(ImageFormatTIFF, 0xb96b3cb1,0x0728,0x11d3,0x9d,0x7b,0x00,0x00,0xf8,0x1e,0xf3,0x2e);
;'DEFINE_GUID(ImageFormatEXIF, 0xb96b3cb2,0x0728,0x11d3,0x9d,0x7b,0x00,0x00,0xf8,0x1e,0xf3,0x2e);
;'DEFINE_GUID(ImageFormatIcon, 0xb96b3cb5,0x0728,0x11d3,0x9d,0x7b,0x00,0x00,0xf8,0x1e,0xf3,0x2e);



; TASK #2   TASK #2  TASK #2  TASK #2  TASK #2  TASK #2  TASK #2  TASK #2  TASK #2  TASK #2  TASK #2  TASK #2  TASK #2  TASK #2
; *****************************************************************************
; содержит описание структур из task #2.html
; Работал над данным материалом keYMax
; *****************************************************************************

; Примечание
;------------------------------------------------------------------
; Во втором задании имеются описания структур PointF, SizeF, RectF
; а также gdiplusStartupInput
; Здесь они не приведены так как описаны в файле gdiplus_struc_0.inc

; В структурах PropertyItem и CharacterRange название поля length заменено на _length
; так как слово зарезервировано в masm'е

; В структуре MetafileHeader название поля SIZE заменено на mSize
; так как слово зарезервировано в masm'е

; Аббревиатурой "OK" отмечены проверенные по всем документам элементы,
; но не протестированные в работе.

; Здесь перечислены использованные значения для замены типов данных PowerBasic'а
; INT = DWORD, LONG = DWORD, SINGLE = REAL4, BYTE = BYTE, INTEGER = WORD

; В оригинальных заголовочных файлах C++ не найдены:
; --------------------------------------------------
; 1. Структура PWMFRect16 ( есть похожий на него один в один. Называется APMRect16 )
; 2. Структура COLORBYTES
; 3. Структура COLORLONG



; Структруры
;----------------------------

COLORBYTES  Struc ; OK
  BlueByte   BYTE ?    
  GreenByte  Byte ?
  RedByte    BYTE ?   
  AlphaByte  Byte ?
COLORBYTES  EndS

COLORLONG  Struc ; OK
  longval   DWORD ?
COLORLONG  EndS

 ; В заголовочных файлах C++ GUID выглядит следующим образом:
 ; DEFINE_GUID(ImageFormatUndefined, 0xb96b3ca9,0x0728,0x11d3,0x9d,0x7b,0x00,0x00,0xf8,0x1e,0xf3,0x2e)

 ; В нашем случае это будет выглядеть как:
 ; DEFINE_GUID ImageFormatUndefined, <{0b96b3ca9h, 00728h, 011d3h, {09dh,07bh,000h,000h,0f8h,01eh,0f3h,02eh}}>

ImageCodecInfo  Struc
  ClassID            GUID  <>                    ; ??? пока не знаю ( то ли здесь должен быть указатель на ID, то ли сам полный ID )
  FormatID           GUID  <>                    ; ??? пока не знаю ( то ли здесь должен быть указатель на ID, то ли сам полный ID )
  CodecName          DWord ?                     ; Указатель на строку UNICODE
  DllName            DWORD ?                     ; Указатель на строку UNICODE 
  FormatDescription  DWord ?                     ; Указатель на строку UNICODE
  FilenameExtension  DWord ?                     ; Указатель на строку UNICODE
  MimeType           DWord ?                     ; Указатель на строку UNICODE
  flags              DWord ?
  Version            DWORD ?   
  SigCount           DWord ?
  SigSize            DWord ?
  SigPattern         DWord ?                     ; Указатель на байтовую строку
  SigMask            DWORD ?                     ; Указатель на байтовую строку 
ImageCodecInfo  EndS

 ; Описание структуры Encoder Parameter
 ; ------------------------------------

; EncoderParameter  STRUC        ; OK
; pGUID             DWORD ?                       ; GUID параметров
; NumberOfValues    DWORD ?                       ; Число значений параметров ( обычно 1 )
; vType             DWORD ?                       ; EncoderParameterValueType ( тип значения, такой как ValueTypeLONG и т.п. )
; value             DWORD ?                       ; Указатель значений параметров
; EncoderParameter  ENDS
;

EncoderParameter  Struc ; OK
 pGUID             GUID  <>                       ; GUID параметров
 NumberOfValues    DWord ?                       ; Число значений параметров ( обычно 1 )
 vType             DWord ?                       ; EncoderParameterValueType ( тип значения, такой как ValueTypeLONG и т.п. )
 value             DWord ?                       ; Указатель значений параметров
EncoderParameter  EndS

 ; Описание структуры Encoder Parameters
 ; -------------------------------------

EncoderParameters   Struc ; OK
  Count              DWORD ?                     ; Число параметров в структуре ( должно быть 1 )   
  Parameter          EncoderParameter <>         ; Значения параметра ( это может быть массив !!! )
 EncoderParameters   ENDS                        ; ( для работы используй CopyMemory и строковый или байтовый массив )

ColorPalette  Struc ; OK
  flags        DWORD ?                           ; Флаги палитры  
  Count        DWord ?                           ; Число цветовых входов ( цветов )
  Entries      DWord ?                           ; Входы цветов палитры ( это может быть массив !!! )
ColorPalette  EndS                              ; ( для работы используй CopyMemory и строковый или байтовый массив )

ColorMatrix  Struc ; OK
  m11         REAL4 ?    
  m12         Real4 ?                            ; матрица размером 5х5 элементов
  m13         Real4 ?
  m14         Real4 ?
  m15         Real4 ?
  m21         Real4 ?
  m22         Real4 ?
  m23         Real4 ?
  m24         Real4 ?
  m25         Real4 ?
  m31         Real4 ?
  m32         Real4 ?
  m33         Real4 ?
  m34         Real4 ?
  m35         Real4 ?
  m41         Real4 ?
  m42         Real4 ?
  m43         Real4 ?
  m44         Real4 ?
  m45         Real4 ?
  m51         Real4 ?
  m52         Real4 ?
  m53         Real4 ?
  m54         Real4 ?
  m55         Real4 ?
ColorMatrix  EndS

 ; Информация о битмапе
 ; ---------------------

BitmapData    Struc ; OK
  nWidth        DWORD ?   
  nHeight       DWORD ?   
  Stride       DWord ?
  PixelFormat  DWORD ?   
  Scan0        DWord ?
  Reserved     DWORD ?
BitmapData    EndS

PathData      Struc ; OK
  Count        DWORD ?   
  pPoint       DWord ?                           ; Указатель на массив структур POINTF
  types        DWord ?                           ; Указатель на байтовый массив
PathData      EndS

PropertyItem  Struc ; OK
  propId       DWORD ?                           ; ID этого свойства   
  _length      DWord ?                           ; Длина значения свойства в байтах
  nType        Word ?                            ; Тип значения ( один из TAG_TYPE_XXX )
  value        DWord ?                           ; значение свойства
PropertyItem  EndS

LOGFONTA           Struc ; OK
  lfHeight          DWORD ?   
  lfWidth           DWord ?
  lfEscapement      DWORD ?   
  lfOrientation     DWord ?
  lfWeight          DWORD ?   
  lfItalic          Byte  ?
  lfUnderline       BYTE  ?   
  lfStrikeOut       Byte  ?
  lfCharSet         BYTE  ?   
  lfOutPrecision    Byte  ?
  lfClipPrecision   BYTE  ?   
  lfQuality         Byte  ?
  lfPitchAndFamily  BYTE  ?   
  lfFaceName        Byte  LF_FACESIZE Dup(?)
LOGFONTA           EndS

LOGFONTW           Struc ; OK
  lfHeight          DWORD ?   
  lfWidth           DWord ?
  lfEscapement      DWORD ?   
  lfOrientation     DWord ?
  lfWeight          DWORD ?   
  lfItalic          Byte  ?
  lfUnderline       BYTE  ?   
  lfStrikeOut       Byte  ?
  lfCharSet         BYTE  ?   
  lfOutPrecision    Byte  ?
  lfClipPrecision   BYTE  ?
  lfQuality         Byte  ?
  lfPitchAndFamily  Byte  ?
  lfFaceName        WORD  LF_FACESIZE dup(?)     ; TODO: Spruce this up a bit ???
LOGFONTW           EndS

CharacterRange   Struc ; OK
  First           DWORD ?
  _length         DWord ?
CharacterRange   EndS

PWMFRect16   Struc ; OK
  nLEFT       WORD ? 
  nTop        Word ?
  nRIGHT      Word ?
  nBottom     WORD ?
PWMFRect16   EndS

WmfPlaceableFileHeader  Struc ; OK
  Key                    DWORD ?                 ; GDIP_WMF_PLACEABLEKEY   
  Hmf                    Word  ?                 ; Число Метафайл хедеров ( всегда 0 )
  boundingBox            PWMFRect16 <>           ; Координаты в метафайл единицах  
  Inch                   Word  ?                 ; Число метафайл единиц в дюймах
  Reserved               DWORD ?                 ; Зарезервировано ( всегда 0 )   
  Checksum               Word  ?                 ; Check сумма для 10 предыдущих слов ( WORD'ов )
WmfPlaceableFileHeader  EndS

ENHMETAHEADER3   Struc ; OK
  itype           DWORD ?                        ; Запись типа EMR_HEADER   
  nSize           DWord ?                        ; Размер записи в байтах. Может быть больше чем размер ENHMETAHEADER. ( Прим. sizeof(ENHMETAHEADER) )
  rclBounds       RECTL <>                       ; Ограничивающий прямоугольник в единицах устройства
  rclFrame        RECTL <>                       ; Ограничивающая рисунок рамка в .01mm единицах
  dSignature      DWord ?                        ; Сигнатура. Должна быть равна ENHMETA_SIGNATURE.
  nVersion        DWORD ?                        ; Номер версии
  nBytes          DWord ?                        ; Размер метафайла в байтах
  nRecords        DWord ?                        ; Число записей в метафайле
  nHandles        Word  ?                        ; Число хэндлов в таблице хэндлов ( индекс хэндла равный 0 зарезервирован )
  sReserved       Word  ?                        ; Зарезервировано. Должно быть 0.
  nDescription    DWord ?                        ; Число символов в строке формата UNICODE ( 0 говорит об отсутствии описывающей строки )
  offDescription  DWord ?                        ; Смещение описывающей метафал записи ( 0 говорит об отсутствии описывающей строки )
  nPalEntries     DWord ?                        ; Число входов ( цветов ) в палитре метафайла
  szlDevice       SIZEL <>                       ; Размер эталонного устройства в pels   
  szlMillimeters  SIZEL <>                       ; Размер эталонного устройства в миллиметрах
ENHMETAHEADER3   EndS

MetafileHeader      Struc ; OK
  mType              DWORD ?                     ; Тип метафайла
  msize              DWord ?                     ; Размер метафайла в байтах
  Version            DWord ?                     ; EMF+, EMF, или WMF версия
  EmfPlusFlags       DWord ?
  DpiX               REAL4 ?
  DpiY               Real4 ?
  x                  DWORD ?                     ; Ограничение в единицах устройства
  y                  DWord ?
  nWIDTH             DWORD ?   
  Height             DWord ?
  EmfHeader          ENHMETAHEADER3 <>           ; Примечание: Используй CopyMemory для просмотра типа METAHEADER
  EmfPlusHeaderSize  DWord ?                     ; размер EMF+ хэдера в файле
  LogicalDpiX        DWord ?                     ; Логические Dpi эталонного Hdc
  LogicalDpiY        DWORD ?                     ; Обычно валидатное только для EMF+
MetafileHeader      EndS





; TASK #3  TASK #3  TASK #3  TASK #3  TASK #3  TASK #3  TASK #3  TASK #3  TASK #3  TASK #3  TASK #3  TASK #3  TASK #3  TASK #3

; TASK #3
; xzazet
;-----------------------------------------------
; GDI+ Enums
;-----------------------------------------------
UnitWorld		Equ	0	; World coordinate (non-physical unit)
UnitDisplay		Equ	1	; Variable -- for PageTransform only
UnitPixel		Equ	2	; Each unit is one device pixel.
UnitPoint		Equ	3	; Each unit is a printer's point, or 1/72 inch.
UnitInch		Equ	4	; Each unit is 1 inch.
UnitDocument	Equ	5	; Each unit is 1/300 inch.
UnitMillimeter	Equ	6	; Each unit is 1 millimeter.

; Common color constants
;[CHECKME]
; NOTE: Original enum was unnamed
ColorsAliceBlue			Equ	0FFF0F8FFH
ColorsAntiqueWhite		Equ	0FFFAEBD7H
ColorsAqua				Equ	0FF00FFFFH
ColorsAquamarine			Equ	0FF7FFFD4H
ColorsAzure				Equ	0FFF0FFFFH
ColorsBeige				Equ	0FFF5F5DCH
ColorsBisque			Equ	0FFFFE4C4H
ColorsBlack				Equ	0FF000000H
ColorsBlanchedAlmond		Equ	0FFFFEBCDH
ColorsBlue				Equ	0FF0000FFH
ColorsBlueViolet			Equ	0FF8A2BE2H
ColorsBrown			Equ	0FFA52A2AH
ColorsBurlyWood			Equ	0FFDEB887H
ColorsCadetBlue			Equ	0FF5F9EA0H
ColorsChartreuse			Equ	0FF7FFF00H
ColorsChocolate			Equ	0FFD2691EH
ColorsCoral				Equ	0FFFF7F50H
ColorsCornflowerBlue		Equ	0FF6495EDH
ColorsCornsilk			Equ	0FFFFF8DCH
ColorsCrimson			Equ	0FFDC143CH
ColorsCyan				Equ	0FF00FFFFH
ColorsDarkBlue			Equ	0FF00008BH
ColorsDarkCyan			Equ	0FF008B8BH
ColorsDarkGoldenrod		Equ	0FFB8860BH
ColorsDarkGray			Equ	0FFA9A9A9H
ColorsDarkGreen			Equ	0FF006400H
ColorsDarkKhaki			Equ	0FFBDB76BH
ColorsDarkMagenta		Equ	0FF8B008BH
ColorsDarkOliveGreen		Equ	0FF556B2FH
ColorsDarkOrange		Equ	0FFFF8C00H
ColorsDarkOrchid			Equ	0FF9932CCH
ColorsDarkRed			Equ	0FF8B0000H
ColorsDarkSalmon			Equ	0FFE9967AH
ColorsDarkSeaGreen		Equ	0FF8FBC8BH
ColorsDarkSlateBlue		Equ	0FF483D8BH
ColorsDarkSlateGray		Equ	0FF2F4F4FH
ColorsDarkTurquoise		Equ	0FF00CED1H
ColorsDarkViolet			Equ	0FF9400D3H
ColorsDeepPink			Equ	0FFFF1493H
ColorsDeepSkyBlue		Equ	0FF00BFFFH
ColorsDimGray			Equ	0FF696969H
ColorsDodgerBlue			Equ	0FF1E90FFH
ColorsFirebrick			Equ	0FFB22222H
ColorsFloralWhite			Equ	0FFFFFAF0H
ColorsForestGreen		Equ	0FF228B22H
ColorsFuchsia			Equ	0FFFF00FFH
ColorsGainsboro			Equ	0FFDCDCDCH
ColorsGhostWhite			Equ	0FFF8F8FFH
ColorsGold				Equ	0FFFFD700H
ColorsGoldenrod			Equ	0FFDAA520H
ColorsGray				Equ	0FF808080H
ColorsGreen			Equ	0FF008000H
ColorsGreenYellow		Equ	0FFADFF2FH
ColorsHoneydew			Equ	0FFF0FFF0H
ColorsHotPink			Equ	0FFFF69B4H
ColorsIndianRed			Equ	0FFCD5C5CH
ColorsIndigo			Equ	0FF4B0082H
ColorsIvory				Equ	0FFFFFFF0H
ColorsKhaki				Equ	0FFF0E68CH
ColorsLavender			Equ	0FFE6E6FAH
ColorsLavenderBlush		Equ	0FFFFF0F5H
ColorsLawnGreen			Equ	0FF7CFC00H
ColorsLemonChiffon		Equ	0FFFFFACDH
ColorsLightBlue			Equ	0FFADD8E6H
ColorsLightCoral			Equ	0FFF08080H
ColorsLightCyan			Equ	0FFE0FFFFH
ColorsLightGoldenrodYellow	Equ	0FFFAFAD2H
ColorsLightGray			Equ	0FFD3D3D3H
ColorsLightGreen			Equ	0FF90EE90H
ColorsLightPink			Equ	0FFFFB6C1H
ColorsLightSalmon			Equ	0FFFFA07AH
ColorsLightSeaGreen		Equ	0FF20B2AAH
ColorsLightSkyBlue		Equ	0FF87CEFAH
ColorsLightSlateGray		Equ	0FF778899H
ColorsLightSteelBlue		Equ	0FFB0C4DEH
ColorsLightYellow			Equ	0FFFFFFE0H
ColorsLime				Equ	0FF00FF00H
ColorsLimeGreen			Equ	0FF32CD32H
ColorsLinen				Equ	0FFFAF0E6H
ColorsMagenta			Equ	0FFFF00FFH
ColorsMaroon			Equ	0FF800000H
ColorsMediumAquamarine	Equ	0FF66CDAAH
ColorsMediumBlue			Equ	0FF0000CDH
ColorsMediumOrchid		Equ	0FFBA55D3H
ColorsMediumPurple		Equ	0FF9370DBH
ColorsMediumSeaGreen		Equ	0FF3CB371H
ColorsMediumSlateBlue		Equ	0FF7B68EEH
ColorsMediumSpringGreen	Equ	0FF00FA9AH
ColorsMediumTurquoise		Equ	0FF48D1CCH
ColorsMediumVioletRed		Equ	0FFC71585H
ColorsMidnightBlue		Equ	0FF191970H
ColorsMintCream			Equ	0FFF5FFFAH
ColorsMistyRose			Equ	0FFFFE4E1H
ColorsMoccasin			Equ	0FFFFE4B5H
ColorsNavajoWhite		Equ	0FFFFDEADH
ColorsNavy				Equ	0FF000080H
ColorsOldLace			Equ	0FFFDF5E6H
ColorsOlive				Equ	0FF808000H
ColorsOliveDrab			Equ	0FF6B8E23H
ColorsOrange			Equ	0FFFFA500H
ColorsOrangeRed			Equ	0FFFF4500H
ColorsOrchid			Equ	0FFDA70D6H
ColorsPaleGoldenrod		Equ	0FFEEE8AAH
ColorsPaleGreen			Equ	0FF98FB98H
ColorsPaleTurquoise		Equ	0FFAFEEEEH
ColorsPaleVioletRed		Equ	0FFDB7093H
ColorsPapayaWhip		Equ	0FFFFEFD5H
ColorsPeachPuff			Equ	0FFFFDAB9H
ColorsPeru				Equ	0FFCD853FH
ColorsPink				Equ	0FFFFC0CBH
ColorsPlum				Equ	0FFDDA0DDH
ColorsPowderBlue			Equ	0FFB0E0E6H
ColorsPurple			Equ	0FF800080H
ColorsRed				Equ	0FFFF0000H
ColorsRosyBrown			Equ	0FFBC8F8FH
ColorsRoyalBlue			Equ	0FF4169E1H
ColorsSaddleBrown		Equ	0FF8B4513H
ColorsSalmon			Equ	0FFFA8072H
ColorsSandyBrown		Equ	0FFF4A460H
ColorsSeaGreen			Equ	0FF2E8B57H
ColorsSeaShell			Equ	0FFFFF5EEH
ColorsSienna			Equ	0FFA0522DH
ColorsSilver				Equ	0FFC0C0C0H
ColorsSkyBlue			Equ	0FF87CEEBH
ColorsSlateBlue			Equ	0FF6A5ACDH
ColorsSlateGray			Equ	0FF708090H
ColorsSnow				Equ	0FFFFFAFAH
ColorsSpringGreen		Equ	0FF00FF7FH
ColorsSteelBlue			Equ	0FF4682B4H
ColorsTan				Equ	0FFD2B48CH
ColorsTeal				Equ	0FF008080H
ColorsThistle			Equ	0FFD8BFD8H
ColorsTomato			Equ	0FFFF6347H
ColorsTransparent			Equ	0FFFFFFH
ColorsTurquoise			Equ	0FF40E0D0H
ColorsViolet				Equ	0FFEE82EEH
ColorsWheat			Equ	0FFF5DEB3H
ColorsWhite				Equ	0FFFFFFFFH
ColorsWhiteSmoke			Equ	0FFF5F5F5H
ColorsYellow			Equ	0FFFFFF00H
ColorsYellowGreen		Equ	0FF9ACD32H


;' NOTE: Enums evaluate to a Long
GpStatusOk					Equ	0
GpStatusGenericError			Equ	1
GpStatusInvalidParameter		Equ	2
GpStatusOutOfMemory			Equ	3
GpStatusObjectBusy			Equ	4
GpStatusInsufficientBuffer			Equ	5
GpStatusNotImplemented			Equ	6
GpStatusWin32Error			Equ	7
GpStatusWrongState			Equ	8
GpStatusAborted				Equ	9
GpStatusFileNotFound			Equ	10
GpStatusValueOverflow			Equ	11
GpStatusAccessDenied			Equ	12
GpStatusUnknownImageFormat		Equ	13
GpStatusFontFamilyNotFound		Equ	14
GpStatusFontStyleNotFound		Equ	15
GpStatusNotTrueTypeFont		Equ	16
GpStatusUnsupportedGdiplusVersion	Equ	17
GpStatusGdiplusNotInitialized		Equ	18
GpStatusPropertyNotFound		Equ	19
GpStatusPropertyNotSupported		Equ	20

; Quality mode constants
QualityModeInvalid	Equ	- 1
QualityModeDefault	Equ	0
QualityModeLow		Equ	1	; Best performance
QualityModeHigh		Equ	2	; Best rendering quality

; Alpha Compositing mode constants
CompositingModeSourceOver	Equ	0
CompositingModeSourceCopy	Equ	1

; Alpha Compositing quality constants
CompositingQualityInvalid		Equ	QualityModeInvalid
CompositingQualityDefault		Equ	QualityModeDefault
CompositingQualityHighSpeed		Equ	QualityModeLow
CompositingQualityHighQuality		Equ	QualityModeHigh
CompositingQualityGammaCorrected	Equ	3
CompositingQualityAssumeLinear	Equ	4

; Generic font families
GenericFontFamilySerif		Equ	0
GenericFontFamilySansSerif	Equ	1
GenericFontFamilyMonospace	Equ	2

; FontStyle: face types and common styles
FontStyleRegular			Equ	0
FontStyleBold			Equ	1
FontStyleItalic			Equ	2
FontStyleBoldItalic			Equ	3
FontStyleUnderline		Equ	4
FontStyleStrikeout			Equ	8
SmoothingModeInvalid		Equ	QualityModeInvalid
SmoothingModeDefault		Equ	QualityModeDefault
SmoothingModeHighSpeed	Equ	QualityModeLow
SmoothingModeHighQuality	Equ	QualityModeHigh
SmoothingModeNone		Equ	3
SmoothingModeAntiAlias		Equ	4
FillModeAlternate			Equ	0
FillModeWinding			Equ	1
InterpolationModeInvalid		Equ	QualityModeInvalid
InterpolationModeDefault		Equ	QualityModeDefault
InterpolationModeLowQuality	Equ	QualityModeLow
InterpolationModeHighQuality	Equ	QualityModeHigh
InterpolationModeBilinear		Equ	3
InterpolationModeBicubic		Equ	4
InterpolationModeNearestNeighbor	Equ	5
InterpolationModeHighQualityBilinear	Equ	6
InterpolationModeHighQualityBicubic	Equ	7

; Various wrap modes for brushes
WrapModeTile       		Equ	0
WrapModeTileFlipX  		Equ	1
WrapModeTileFlipY  		Equ	2
WrapModeTileFlipXY 		Equ	3
WrapModeClamp      		Equ	4
LinearGradientModeHorizontal  Equ	0
LinearGradientModeVertical      Equ	1
LinearGradientModeForwardDiagonal	Equ	2
LinearGradientModeBackwardDiagonal  	Equ	3
ImageTypeUnknown  		Equ	0
ImageTypeBitmap   		Equ	1
ImageTypeMetafile 		Equ	2




; TASK #4   TASK #4   TASK #4   TASK #4   TASK #4   TASK #4   TASK #4   TASK #4   TASK #4   TASK #4   TASK #4   TASK #4   TASK #4
; *****************************************************************************************
; содержит описание констант из task #4.html
; Работал над данным материалом keYMax
; *****************************************************************************************

; Константы
;----------------------------

; Варианты выводимых стилей

HatchStyleHorizontal                  Equ  0
HatchStyleVertical                    Equ  1
HatchStyleForwardDiagonal             Equ  2
HatchStyleBackwardDiagonal            Equ  3
HatchStyleCross                       Equ  4
HatchStyleDiagonalCross               Equ  5
HatchStyle05Percent                   Equ  6
HatchStyle10Percent                   Equ  7
HatchStyle20Percent                   Equ  8
HatchStyle25Percent                   Equ  9
HatchStyle30Percent                   Equ  10
HatchStyle40Percent                   Equ  11
HatchStyle50Percent                   Equ  12
HatchStyle60Percent                   Equ  13
HatchStyle70Percent                   Equ  14
HatchStyle75Percent                   Equ  15
HatchStyle80Percent                   Equ  16
HatchStyle90Percent                   Equ  17
HatchStyleLightDownwardDiagonal       Equ  18
HatchStyleLightUpwardDiagonal         Equ  19
HatchStyleDarkDownwardDiagonal        Equ  20
HatchStyleDarkUpwardDiagonal          Equ  21
HatchStyleWideDownwardDiagonal        Equ  22
HatchStyleWideUpwardDiagonal          Equ  23
HatchStyleLightVertical               Equ  24
HatchStyleLightHorizontal             Equ  25
HatchStyleNarrowVertical              Equ  26
HatchStyleNarrowHorizontal            Equ  27
HatchStyleDarkVertical                Equ  28
HatchStyleDarkHorizontal              Equ  29
HatchStyleDashedDownwardDiagonal      Equ  30
HatchStyleDashedUpwardDiagonal        Equ  31
HatchStyleDashedHorizontal            Equ  32
HatchStyleDashedVertical              Equ  33
HatchStyleSmallConfetti               Equ  34
HatchStyleLargeConfetti               Equ  35
HatchStyleZigZag                      Equ  36
HatchStyleWave                        Equ  37
HatchStyleDiagonalBrick               Equ  38
HatchStyleHorizontalBrick             Equ  39
HatchStyleWeave                       Equ  40
HatchStylePlaid                       Equ  41
HatchStyleDivot                       Equ  42
 HatchStyleDottedGrid                  EQU  43
HatchStyleDottedDiamond               Equ  44
HatchStyleShingle                     Equ  45
HatchStyleTrellis                     Equ  46
 HatchStyleSphere                      EQU  47
HatchStyleSmallGrid                   Equ  48
HatchStyleSmallCheckerBoard           Equ  49
HatchStyleLargeCheckerBoard           Equ  50
HatchStyleOutlinedDiamond             Equ  51
HatchStyleSolidDiamond                Equ  52
HatchStyleTotal                       Equ  53
HatchStyleLargeGrid                   Equ  HatchStyleCross
HatchStyleMin                         Equ  HatchStyleHorizontal
HatchStyleMax                         Equ  HatchStyleTotal - 1

 ; Matrix константы
 ;------------------

MatrixOrderPrepend                    Equ  0
MatrixOrderAppend                     Equ  1

 ; Color константы
 ; -----------------

ColorAdjustTypeDefault                Equ  0
ColorAdjustTypeBitmap                 Equ  1
ColorAdjustTypeBrush                  Equ  2
ColorAdjustTypePen                    Equ  3
ColorAdjustTypeText                   Equ  4
ColorAdjustTypeCount                  Equ  5
ColorAdjustTypeAny                    Equ  6  ; Reserved

ColorChannelFlagsC                    Equ  0
 ColorChannelFlagsM                    EQU  1 
ColorChannelFlagsY                    Equ  2
ColorChannelFlagsK                    Equ  3
ColorChannelFlagsLast                 Equ  4

ColorMatrixFlagsDefault               Equ  0
ColorMatrixFlagsSkipGrays             Equ  1
ColorMatrixFlagsAltGray               Equ  2

 ; Pen константы
 ; --------------

PenAlignmentCenter                    Equ  0
PenAlignmentInset                     Equ  1

 ; Brush константы
 ; ----------------

BrushTypeSolidColor                   Equ  0
BrushTypeHatchFill                    Equ  1
BrushTypeTextureFill                  Equ  2
BrushTypePathGradient                 Equ  3
BrushTypeLinearGradient               Equ  4

 ; Dash константы
 ; --------------

DashStyleSolid                        Equ  0
DashStyleDash                         Equ  1
DashStyleDot                          Equ  2
DashStyleDashDot                      Equ  3
DashStyleDashDotDot                   Equ  4
DashStyleCustom                       Equ  5
 
 ; Dash cap constants
 ;--------------------
 ; Line cap константы ( используются только нижние 8 битов ).

DashCapFlat                           Equ  0
DashCapRound                          Equ  2
DashCapTriangle                       Equ  3

LineCapFlat                           Equ  0
LineCapSquare                         Equ  1
LineCapRound                          Equ  2
LineCapTriangle                       Equ  3
LineCapNoAnchor                       Equ  010H     ; corresponds to flat cap
LineCapSquareAnchor                   Equ  011H     ; corresponds to square cap
LineCapRoundAnchor                    Equ  012H     ; corresponds to round cap
LineCapDiamondAnchor                  Equ  013H     ; corresponds to triangle cap
LineCapArrowAnchor                    Equ  014H     ; no correspondence
LineCapCustom                         Equ  0FFH     ; custom cap
LineCapAnchorMask                     Equ  0F0H     ; mask to check for anchor or not.

 ; Custom Line cap type константы
 ;--------------------------------

CustomLineCapTypeDefault              Equ  0
CustomLineCapTypeAdjustableArrow      Equ  1

 ; Line join константы
 ; --------------------

LineJoinMiter                         Equ  0
LineJoinBevel                         Equ  1
LineJoinRound                         Equ  2
LineJoinMiterClipped                  Equ  3

 ; Pen's Fill типы
 ; --------------------

PenTypeSolidColor                     Equ  BrushTypeSolidColor
PenTypeHatchFill                      Equ  BrushTypeHatchFill
PenTypeTextureFill                    Equ  BrushTypeTextureFill
PenTypePathGradient                   Equ  BrushTypePathGradient
PenTypeLinearGradient                 Equ  BrushTypeLinearGradient
PenTypeUnknown                        Equ  - 1

 ; Warp Mode
 ; -----------

WarpModePerspective                   Equ  0
WarpModeBilinear                      Equ  1

 ; Region комбинированные режимы
 ; -----------------------------

CombineModeReplace                    Equ  0
CombineModeIntersect                  Equ  1
CombineModeUnion                      Equ  2
CombineModeXor                        Equ  3
CombineModeExclude                    Equ  4
CombineModeComplement                 Equ  5     ; ( исключение из )

RotateNoneFlipNone                    Equ  0
Rotate90FlipNone                      Equ  1
Rotate180FlipNone                     Equ  2
Rotate270FlipNone                     Equ  3
RotateNoneFlipX                       Equ  4
Rotate90FlipX                         Equ  5
Rotate180FlipX                        Equ  6
Rotate270FlipX                        Equ  7
RotateNoneFlipY                       Equ  Rotate180FlipX
Rotate90FlipY                         Equ  Rotate270FlipX
Rotate180FlipY                        Equ  RotateNoneFlipX
Rotate270FlipY                        Equ  Rotate90FlipX
RotateNoneFlipXY                      Equ  Rotate180FlipNone
Rotate90FlipXY                        Equ  Rotate270FlipNone
Rotate180FlipXY                       Equ  RotateNoneFlipNone
Rotate270FlipXY                       Equ  Rotate90FlipNone


; TASK #5  TASK #5   TASK #5   TASK #5   TASK #5   TASK #5   TASK #5   TASK #5   TASK #5   TASK #5   TASK #5   TASK #5   TASK #5
; ******************************************************************************
; содержит описание констант из task #5.html
; Работал над данным материалом keYMax
; ******************************************************************************

; Пояснения переведены из task'а ( пока только то, что смог перевести )
; ------------------------

; Флаги форматирования строки
; ----------------------------

; DirectionRightToLeft - Для горизонтального текста, направление чтения справа налево.
;                        Это значение вызывается
;                        the base embedding level by the Unicode
;                        bidirectional engine.
;                        Для вертикального текста, направление чтения в столбик справа налево.

; По умолчанию, горизонтальный или вертикальный текст читается слева направо.

; DirectionVertical    - Вертикальное направление текста.
;                        В каждой линии символы располагаются сверху вниз.
;                        По умолчанию линии текста располагаются горизонтально,
;                        каждая новая линия ниже предыдущей.

; NoFitBlackBox        - Allows parts of glyphs to overhang the
;                        bounding rectangle.
;                        By default glyphs are first aligned
;                        inside the margines, then any glyphs which
;                        still overhang the bounding box are
;                        repositioned to avoid any overhang.
;                        For example when an italic
;                        lower case letter f in a font such as
;                        Garamond is aligned at the far left of a
;                        rectangle, the lower part of the f will
;                        reach slightly further left than the left
;                        edge of the rectangle. Setting this flag
;                        will ensure the character aligns visually
;                        with the lines above and below, but may
;                        cause some pixels outside the formatting
;                        rectangle to be clipped or painted.
;
; DisplayFormatControl - Causes control characters such as the
;                        left-to-right mark to be shown in the
;                        output with a representative glyph.
;
; NoFontFallback       - Disables fallback to alternate fonts for
;                        characters not supported in the requested
;                        font. Any missing characters will be
;                        be displayed with the fonts missing glyph,
;                        usually an open square.
;
; NoWrap               - Disables wrapping of text between lines
;                        when formatting within a rectangle.
;                        NoWrap is implied when a point is passed
;                        instead of a rectangle, or when the
;                        specified rectangle has a zero line length.
;
; NoClip               - By default text is clipped to the
;                        formatting rectangle. Setting NoClip
;                        allows overhanging pixels to affect the
;                        device outside the formatting rectangle.
;                        Pixels at the end of the line may be
;                        affected if the glyphs overhang their
;                        cells, and either the NoFitBlackBox flag
;                        has been set, or the glyph extends to far
;                        to be fitted.
;                        Пиксели выше/до первой линии или ниже/после
;                        последней линии могут быть потеряны
;                        if the glyphs extend beyond their cell
;                        ascent / descent. This can occur rarely
;                        with unusual diacritic mark combinations.

StringFormatFlagsDirectionRightToLeft   Equ  01H
StringFormatFlagsDirectionVertical      Equ  02H
StringFormatFlagsNoFitBlackBox          Equ  04H
StringFormatFlagsDisplayFormatControl   Equ  020H
StringFormatFlagsNoFontFallback         Equ  0400H
StringFormatFlagsMeasureTrailingSpaces  Equ  0800H
StringFormatFlagsNoWrap                 Equ  01000H
StringFormatFlagsLineLimit              Equ  02000H

StringFormatFlagsNoClip                 Equ  04000H

StringTrimmingNone                      Equ  0
StringTrimmingCharacter                 Equ  1
StringTrimmingWord                      Equ  2
StringTrimmingEllipsisCharacter         Equ  3
StringTrimmingEllipsisWord              Equ  4
StringTrimmingEllipsisPath              Equ  5

 ; National language digit substitution
 ; -------------------------------------

StringDigitSubstituteUser               Equ  0   ; Как установливается NLS
 StringDigitSubstituteNone               EQU  1
StringDigitSubstituteNational           Equ  2
StringDigitSubstituteTraditional        Equ  3

 ; Hotkey prefix interpretation
 ; ------------------------------

HotkeyPrefixNone                        Equ  0
HotkeyPrefixShow                        Equ  1
HotkeyPrefixHide                        Equ  2

 ; Left edge for left-to-right text,
 ; right for right-to-left text,
 ; and top for vertical

StringAlignmentNear                     Equ  0
StringAlignmentCenter                   Equ  1
StringAlignmentFar                      Equ  2

FlushIntentionFlush                     Equ  0     ; Flush all batched rendering operations
FlushIntentionSync                      Equ  1     ; Flush all batched rendering operations
                                                    ; and wait for them to complete
                                                    ; Image encoder parameter related types

EncoderParameterValueTypeByte           Equ  1     ; 8-bit беззнаковый int
EncoderParameterValueTypeASCII          Equ  2     ; 8-bit byte содержит один 7-bit ASCII
                                                    ; код. оканчивается NULL .

EncoderParameterValueTypeShort          Equ  3     ; 16-bit беззнаковый int
EncoderParameterValueTypeLong           Equ  4     ; 32-bit беззнаковый int
EncoderParameterValueTypeRational       Equ  5     ; Два Long'а. Первый - нумератор
                                                    ; Второй определяет деноминатор

EncoderParameterValueTypeLongRange      Equ  6     ; Два long'а определяют диапазон целых значений.
                                                    ; Первый - определяет нижнюю границу
                                                    ; Второй - верхнюю
                                                    ; Все значения находятся в этих границах

EncoderParameterValueTypeUndefined      Equ  7     ; 8-bit byte that can take any value
                                                    ; depending on field definition

EncoderParameterValueTypeRationalRange  Equ  8     ; Two Rationals. The first Rational
                                                    ; specifies the lower end and the second
                                                    ; specifies the higher end. All values
                                                    ; are inclusive at both ends
 ; Image encoder value types
 ; ----------------------------

EncoderValueColorTypeCMYK               Equ  0
EncoderValueColorTypeYCCK               Equ  1
EncoderValueCompressionLZW              Equ  2
EncoderValueCompressionCCITT3           Equ  3
EncoderValueCompressionCCITT4           Equ  4
EncoderValueCompressionRle              Equ  5
EncoderValueCompressionNone             Equ  6
EncoderValueScanMethodInterlaced        Equ  7
EncoderValueScanMethodNonInterlaced     Equ  8
EncoderValueVersionGif87                Equ  9
EncoderValueVersionGif89                Equ  10
EncoderValueRenderProgressive           Equ  11
EncoderValueRenderNonProgressive        Equ  12
EncoderValueTransformRotate90           Equ  13
EncoderValueTransformRotate180          Equ  14
EncoderValueTransformRotate270          Equ  15
EncoderValueTransformFlipHorizontal     Equ  16
EncoderValueTransformFlipVertical       Equ  17
EncoderValueMultiFrame                  Equ  18
EncoderValueLastFrame                   Equ  19
EncoderValueFlush                       Equ  20
EncoderValueFrameDimensionTime          Equ  21
EncoderValueFrameDimensionResolution    Equ  22
EncoderValueFrameDimensionPage          Equ  23

 ; CLSIDs (aka GUIDs) используются в структуре EncoderParameter:
 ; ПРИМЕЧАНИЕ: Ты можешь найти эти константы в GDI+ доках.
 ; Эта часть была создана в связи с проблемой констант GUID.

EncoderCompression                      Equ  0
EncoderColorDepth                       Equ  1
EncoderScanMethod                       Equ  2
EncoderVersion                          Equ  3
EncoderRenderMethod                     Equ  4
EncoderQuality                          Equ  5
EncoderTransformation                   Equ  6
EncoderLuminanceTable                   Equ  7
EncoderChrominanceTable                 Equ  8
EncoderSaveFlag                         Equ  9

PixelOffsetModeInvalid                  Equ  QualityModeInvalid
PixelOffsetModeDefault                  Equ  QualityModeDefault
PixelOffsetModeHighSpeed                Equ  QualityModeLow
PixelOffsetModeHighQuality              Equ  QualityModeHigh
PixelOffsetModeNone                     Equ  3        ; Нет смещения пикселей
PixelOffsetModeHalf                     Equ  4        ; Смещение -0.5 -0.5 для быстрого антиалиасинга

TextRenderingHintSystemDefault             Equ  0     ; Glyph with system default rendering hint
TextRenderingHintSingleBitPerPixelGridFit  Equ  1     ; Glyph bitmap with hinting
TextRenderingHintSingleBitPerPixel         Equ  2     ; Glyph bitmap without hinting
TextRenderingHintAntiAliasGridFit          Equ  3     ; Glyph anti-alias bitmap with hinting
TextRenderingHintAntiAlias                 Equ  4     ; Glyph anti-alias bitmap without hinting
TextRenderingHintClearTypeGridFit          Equ  5     ; Glyph CT bitmap with hinting

MetafileTypeInvalid                        Equ  0     ; Неправильный метафайл
MetafileTypeWmf                            Equ  1     ; стандартный WMF
MetafileTypeWmfPlaceable                   Equ  2     ; Placeable WMF
MetafileTypeEmf                            Equ  3     ; EMF (не EMF+)
MetafileTypeEmfPlusOnly                    Equ  4     ; EMF+ без двойных down-level записей
MetafileTypeEmfPlusDual                    Equ  5     ; EMF+ с двойными down-level записями

 ; Specifies the type of EMF to record
 ; -------------------------------------

EmfTypeEmfOnly                             Equ  MetafileTypeEmf          ; не EMF+ только EMF
EmfTypeEmfPlusOnly                         Equ  MetafileTypeEmfPlusOnly  ; не EMF только EMF+
EmfTypeEmfPlusDual                         Equ  MetafileTypeEmfPlusDual  ; оба EMF+ и EMF

 ; EMF+ Persistent object types
 ; --------------------------------------

ObjectTypeInvalid                          Equ  0
ObjectTypeBrush                            Equ  1
ObjectTypePen                              Equ  2
ObjectTypePath                             Equ  3
ObjectTypeRegion                           Equ  4
ObjectTypeImage                            Equ  5
ObjectTypeFont                             Equ  6
ObjectTypeStringFormat                     Equ  7
ObjectTypeImageAttributes                  Equ  8
ObjectTypeCustomLineCap                    Equ  9

ObjectTypeMax                              Equ  ObjectTypeCustomLineCap
ObjectTypeMin                              Equ  ObjectTypeBrush

 ; frameRect для создания метафайла может быть определен в любой из этих единиц.
 ; There is an extra frame unit value (MetafileFrameUnitGdi) so
 ; that units can be supplied in the same units that GDI expects for
 ; frame rects -- these units are in .01 (1/100ths) millimeter units
 ; as defined by GDI.

MetafileFrameUnitPixel                     Equ  UnitPixel
MetafileFrameUnitPoint                     Equ  UnitPoint
MetafileFrameUnitInch                      Equ  UnitInch
MetafileFrameUnitDocument                  Equ  UnitDocument
MetafileFrameUnitMillimeter                Equ  UnitMillimeter
MetafileFrameUnitGdi                       Equ  7               ; GDI совместимые .01 MM единицы

 ; Coordinate space identifiers
 ; -----------------------------

CoordinateSpaceWorld                       Equ  0
CoordinateSpacePage                        Equ  1
CoordinateSpaceDevice                      Equ  2

