GLOBAL _read
GLOBAL _write
GLOBAL delete

GLOBAL mem_manager
GLOBAL process_manager

GLOBAL sem
GLOBAL pipes
GLOBAL LoadDummyProcess 


section .text:


%macro pushState 0
	push rax
	push rbx
	push rcx
	push rdx
	push rbp
	push rdi
	push rsi
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15

%endmacro

%macro popState 0
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop rsi
	pop rdi
	pop rbp
	pop rdx
	pop rcx
	pop rbx
	pop rax
%endmacro

_read:
    enter 0,0
    
    pushState
    
    mov r15, rdx    ; guardo el valor

    mov r9, r8      ;cuarto arg
    mov rdx, rcx    ;tercer arg
    mov rcx, r15    ;segundo arg
    mov rbx, rsi    ;primer arg
    mov rax, rdi    ; fd
    int 80h

    popState

    leave
    ret

_write:
    enter 0,0

    pushState

    mov r15, rdx    ; guardo el valor

    mov r9, r8      ;cuarto arg
    mov rdx, rcx    ;tercer arg
    mov rcx, r15    ;segundo arg
    mov rbx, rsi    ;primer arg
    mov rax, rdi    ; fd

    int 81h

    popState

    leave
    ret

 delete:
        enter 0,0

        pushState

        mov r15, rdx    ; guardo el valor

        mov r9, r8      ;cuarto arg
        mov rdx, rcx    ;tercer arg
        mov rcx, r15    ;segundo arg
        mov rbx, rsi    ;primer arg
        mov rax, rdi    ; fd        
        int 82h

        popState

        leave
        ret

mem_manager:
        enter 0,0

        pushState
        mov r15, rdx    ; guardo el valor

        mov rdx, rcx    ;tercer arg
        mov rcx, r15    ;segundo arg
        mov rbx, rsi    ;primer arg
        mov rax, rdi    ; fd        
        int 86h

        popState

        leave
        ret
process_manager:
        enter 0,0

        pushState
        mov r15, rdx    ; guardo el valor

        mov rdx, rcx    ;tercer arg
        mov rcx, r15    ;segundo arg
        mov rbx, rsi    ;primer arg
        mov rax, rdi    ; fd        
        int 87h

        popState

        leave
        ret
sem:
        enter 0,0

        pushState

        mov rcx, rdx    ;segundo arg
        mov rbx, rsi    ;primer arg
        mov rax, rdi    ;fd        
        int 88h

        popState

        leave
        ret

pipes:
    enter 0,0
    
    pushState
    
    mov r15, rdx    ; guardo el valor

    mov rdx, rcx    ;tercer arg
    mov rcx, r15    ;segundo arg
    mov rbx, rsi    ;primer arg
    mov rax, rdi    ; ind
    int 89h

    popState

    leave
    ret

LoadDummyProcess: 
        enter 0,0 
 
        pushState 
         
        mov rax, rdi    ;primer arg      
        int 90h 
 
        popState 
 
        leave 
        ret 