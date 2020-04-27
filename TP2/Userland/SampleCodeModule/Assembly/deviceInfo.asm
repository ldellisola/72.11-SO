GLOBAL infoReg
GLOBAL __UD2__
GLOBAL __MEM__

GLOBAL __halt__
EXTERN printRegisters

section .text

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


__halt__:
		enter 0,0
		
		hlt

		leave
		ret

__UD2__:

		enter 0,0

		ud2

		leave
		ret



infoReg:

        enter 0,0

		pushState 
        mov rdi,rsp
		

		call printRegisters

		mov rax,0
        
        leave
        ret
