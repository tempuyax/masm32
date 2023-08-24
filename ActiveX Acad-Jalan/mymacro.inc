ComInvoke Macro pInterface:REQ, Method:REQ, p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12, \
                                            p13,p14,p15,p16,p17,p18,p19,p20,p21,p22
  ;reverse argument
  FOR arg,<p22,p21,p20,p19,p18,p17,p16,p15,p14,p13,\
           p12,p11,p10,p9,p8,p7,p6,p5,p4,p3,p2,p1>
     IFNB <arg>       ;; If not blank
         Push arg    ;; push parameter
     ENDIF
  ENDM
      Mov Eax, pInterface
  .IF Eax
      Push Eax
      mov eax, [eax]
      Call [Eax].Method
  .ENDIF
EndM
;======================================================
StdCallCom Macro pInterface:REQ, nMethod:REQ, p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12, \
                                            p13,p14,p15,p16,p17,p18,p19,p20,p21,p22
  ;reverse argument
  FOR arg,<p22,p21,p20,p19,p18,p17,p16,p15,p14,p13,\
           p12,p11,p10,p9,p8,p7,p6,p5,p4,p3,p2,p1>
     IFNB <arg>       ;; If not blank
         Push arg    ;; push parameter
     ENDIF
  ENDM
      Mov Eax, pInterface
  .IF Eax
      Push Eax
      mov Eax, [Eax]
      call dword ptr [eax+(nMethod-1)*4]
  .ENDIF
EndM
;======================================================
  ; ---------------------------------------------------
  ; Create an Interface a macro
  ; argument list is type Data DWORD  
  ; ---------------------------------------------------
Interface MACRO Iname:REQ,args:VARARG
Iname Struct
      FOR arg, <args>
        IFNB <arg>
          arg dword ?     
        ENDIF
      ENDM
Iname Ends   
     ENDM