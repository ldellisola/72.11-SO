GLOBAL read
GLOBAL write
GLOBAL delete

section .text:

read:
    enter 0,0

    
    mov r15, rdx    ; guardo el valor

    mov r9, r8      ;cuarto arg
    mov rdx, rcx    ;tercer arg
    mov rcx, r15    ;segundo arg
    mov rbx, rsi    ;primer arg
    mov rax, rdi    ; fd
    int 80h

    leave
    ret

write:
    enter 0,0

    mov r15, rdx    ; guardo el valor

    mov r9, r8      ;cuarto arg
    mov rdx, rcx    ;tercer arg
    mov rcx, r15    ;segundo arg
    mov rbx, rsi    ;primer arg
    mov rax, rdi    ; fd
    int 81h

    leave
    ret

 delete:
        enter 0,0

        mov r15, rdx    ; guardo el valor

        mov r9, r8      ;cuarto arg
        mov rdx, rcx    ;tercer arg
        mov rcx, r15    ;segundo arg
        mov rbx, rsi    ;primer arg
        mov rax, rdi    ; fd        int 82h
        int 82h

        leave
        ret
