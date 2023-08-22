; ------------------------------------------------------------------
; macro for making COM procedure and API struct.
; ------------------------------------------------------------------
Interface Macro IHandle, name:REQ, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, p21, p22
IHandle Struct
       ;ICommon IUnknown <?>
    ;; ---------------------------------------
    ;; loop through arguments upwards, create dword
    ;; NON blank ones Eof the data structure.
    ;; ---------------------------------------
      For arg, <p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, p21, p22>
        IFNB <arg>       ;; If not blank
          arg DWord ?    ;; push parameter
        ENDIF
      EndM
IHandle EndS
    EndM