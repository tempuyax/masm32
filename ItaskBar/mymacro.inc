ComInvoke Macro pInterface:REQ, Method:REQ, arg
    IFNB <arg>       ;; If not blank
         Push arg    ;; push parameter
    ENDIF
    Mov Eax, pInterface
    Push Eax
    mov eax, [eax]
    Call [Eax].Method
EndM
