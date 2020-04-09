
GLOBAL __GetTime__

section .bss

    TEMP resb 8

section .text:


__GetTime__:
    enter 0,0

    mov [TEMP],rdi

    xor ax,ax
    mov al,[TEMP]
    
    out 70h, al
    in al,71h

    leave
    ret    


