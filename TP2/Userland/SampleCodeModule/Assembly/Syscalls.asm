GLOBAL read
GLOBAL write
GLOBAL delete
GLOBAL sbrk_asm
GLOBAL brk_asm
GLOBAL memory_state
GLOBAL create_process
GLOBAL kill_process
GLOBAL block_process
GLOBAL nice_process
GLOBAL ps
GLOBAL get_pid

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

 sbrk_asm:
        enter 0,0

        mov r15, rdx    ; guardo el valor

        mov r9, r8      ;cuarto arg
        mov rdx, rcx    ;tercer arg
        mov rcx, r15    ;segundo arg
        mov rbx, rsi    ;primer arg
        mov rax, rdi    ; fd        
        int 86h

        leave
        ret

 brk_asm:
        enter 0,0

        mov r15, rdx    ; guardo el valor

        mov r9, r8      ;cuarto arg
        mov rdx, rcx    ;tercer arg
        mov rcx, r15    ;segundo arg
        mov rbx, rsi    ;primer arg
        mov rax, rdi    ; fd        
        int 87h

        leave
        ret

memory_state:
        enter 0,0

        mov r15, rdx    ; guardo el valor

        mov r9, r8      ;cuarto arg
        mov rdx, rcx    ;tercer arg
        mov rcx, r15    ;segundo arg
        mov rbx, rsi    ;primer arg
        mov rax, rdi    ; fd        
        int 88h

        leave
        ret

create_process:
        enter 0,0

        mov r15, rdx    ; guardo el valor

        mov r9, r8      ;cuarto arg
        mov rdx, rcx    ;tercer arg
        mov rcx, r15    ;segundo arg
        mov rbx, rsi    ;primer arg
        mov rax, rdi    ; fd        
        int 89h

        leave
        ret

kill_process:
        enter 0,0

        mov r15, rdx    ; guardo el valor

        mov r9, r8      ;cuarto arg
        mov rdx, rcx    ;tercer arg
        mov rcx, r15    ;segundo arg
        mov rbx, rsi    ;primer arg
        mov rax, rdi    ; fd        
        int 90h

        leave
        ret
nice_process:
        enter 0,0

        mov r15, rdx    ; guardo el valor

        mov r9, r8      ;cuarto arg
        mov rdx, rcx    ;tercer arg
        mov rcx, r15    ;segundo arg
        mov rbx, rsi    ;primer arg
        mov rax, rdi    ; fd        
        int 91h

        leave
        ret

block_process:
        enter 0,0

        mov r15, rdx    ; guardo el valor

        mov r9, r8      ;cuarto arg
        mov rdx, rcx    ;tercer arg
        mov rcx, r15    ;segundo arg
        mov rbx, rsi    ;primer arg
        mov rax, rdi    ; fd        
        int 92h

        leave
        ret

ps:
        enter 0,0

        mov r15, rdx    ; guardo el valor

        mov r9, r8      ;cuarto arg
        mov rdx, rcx    ;tercer arg
        mov rcx, r15    ;segundo arg
        mov rbx, rsi    ;primer arg
        mov rax, rdi    ; fd        
        int 93h

        leave
        ret        

get_pid:
        enter 0,0

        mov r15, rdx    ; guardo el valor

        mov r9, r8      ;cuarto arg
        mov rdx, rcx    ;tercer arg
        mov rcx, r15    ;segundo arg
        mov rbx, rsi    ;primer arg
        mov rax, rdi    ; fd        
        int 94h

        leave
        ret