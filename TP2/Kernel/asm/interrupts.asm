
GLOBAL _cli
GLOBAL _sti
GLOBAL picMasterMask
GLOBAL picSlaveMask
GLOBAL haltcpu
GLOBAL _hlt

GLOBAL _irq00Handler
GLOBAL _irq01Handler
GLOBAL _irq02Handler
GLOBAL _irq03Handler
GLOBAL _irq04Handler
GLOBAL _irq05Handler
GLOBAL _irq80Handler
GLOBAL _irq81Handler
GLOBAL _irq82Handler
GLOBAL _irq83Handler


GLOBAL _irq85Handler
GLOBAL _irq86Handler
GLOBAL _irq87Handler
GLOBAL _irq88Handler
GLOBAL _irq89Handler
GLOBAL _irq90Handler
GLOBAL _irq91Handler
GLOBAL _irq92Handler
GLOBAL _irq93Handler
GLOBAL _irq94Handler
GLOBAL _irq95Handler
GLOBAL _irq96Handler
GLOBAL _irq97Handler
GLOBAL _irq98Handler

GLOBAL _exception0Handler
GLOBAL _exception6Handler
GLOBAL _exception4Handler
GLOBAL _exception8Handler
GLOBAL _exception0xCHandler
GLOBAL _exception0xDHandler
GLOBAL _exception0xEHandler

GLOBAL __ForceTimerTick__


EXTERN irqDispatcher
EXTERN exceptionDispatcher

SECTION .text

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

%macro irqHandlerMaster 1
	pushState

	
	mov r9, r9 ; Quinto Param
	mov r8, rdx ; Cuarto Param
	mov rcx,rcx ; Tercer Param
	mov rdx,rbx ; Segundo Param
	mov rsi,rax ; Primer Param
	mov rdi, %1 ; Tipo de Interrupcion
	
	call irqDispatcher

	; signal pic EOI (End of Interrupt)
	mov al, 20h
	out 20h, al

	popState
	iretq
%endmacro



%macro exceptionHandler 1
	  	pushState
	
	  	mov rdi, %1 ; first parameter
	  	mov rsi, rsp ; second parameter

	  	call exceptionDispatcher
;		mov qword [rsp+8*15],SampleCodeAdress
	  	popState
		iretq
	%endmacro


__ForceTimerTick__:
	enter 0,0
	int 20h
	leave
	ret

_hlt:
	sti
	hlt
	ret

_cli:
	cli
	ret


_sti:
	sti
	ret

picMasterMask:
	push rbp
    mov rbp, rsp
    mov ax, di
    out	21h,al
    pop rbp
    retn

picSlaveMask:
	push    rbp
    mov     rbp, rsp
    mov     ax, di  ; ax = mascara de 16 bits
    out	0A1h,al
    pop     rbp
    retn


;8254 Timer (Timer Tick)
_irq00Handler:
	;irqHandlerMaster 0
	pushState

	
	mov r9, r9 ; Quinto Param
	mov r8, rdx ; Cuarto Param
	mov rcx,rcx ; Tercer Param
	mov rdx,rbx ; Segundo Param
	mov rsi,rsp ; Primer Param
	mov rdi, 0h; Tipo de Interrupcion
	
	call irqDispatcher

	cmp rax,0

	jz .skip

	mov rsp, rax

.skip:


	; signal pic EOI (End of Interrupt)
	mov al, 20h
	out 20h, al

	popState
	iretq


;Keyboard
_irq01Handler:
	irqHandlerMaster 1

;Cascade pic never called
_irq02Handler:
	irqHandlerMaster 2

;Serial Port 2 and 4
_irq03Handler:
	irqHandlerMaster 3

;Serial Port 1 and 3
_irq04Handler:
	irqHandlerMaster 4

; READ / WRITE 
_irq80Handler:
	irqHandlerMaster 80h

; DEVICEINFO
_irq81Handler:
	irqHandlerMaster 81h

; TIME
_irq82Handler:
	irqHandlerMaster 82h

; printAt
_irq83Handler:
	irqHandlerMaster 83h	

	


; CustomExceptions
_irq85Handler:
	irqHandlerMaster 85h

; _malloc
_irq86Handler:
	irqHandlerMaster 86h

; _free
_irq87Handler:
	irqHandlerMaster 87h

;mem_state
_irq88Handler:
	irqHandlerMaster 88h

;create_process
_irq89Handler:
	irqHandlerMaster 89h

;kill_process
_irq90Handler:
	irqHandlerMaster 90h

;nice_process
_irq91Handler:
	irqHandlerMaster 91h	

;block_process
_irq92Handler:
	irqHandlerMaster 92h	

;ps
_irq93Handler:
	irqHandlerMaster 93h	

;getpid
_irq94Handler:
	irqHandlerMaster 94h	

;exit
_irq95Handler:
	irqHandlerMaster 95h

;exit
_irq96Handler:
	irqHandlerMaster 96h		

;SleepUntilInput
_irq97Handler:
	irqHandlerMaster 97h		
	
;LoadFakeProcess
_irq98Handler:
	irqHandlerMaster 98h		


;USB
_irq05Handler:
	irqHandlerMaster 5


;Zero Division Exception
_exception0Handler:
	exceptionHandler 0

;Overflow Exception
_exception4Handler:
	exceptionHandler 4h

	
;Invalid Opcode Exception
_exception6Handler:
	exceptionHandler 6

;DoubleFault Exception
_exception8Handler:
	exceptionHandler 8h

;Stack Fault Exception
_exception0xCHandler:
	exceptionHandler 0ch

;General Protection FaultException      
_exception0xDHandler:
	exceptionHandler 0dh

;Page fault
_exception0xEHandler:
	exceptionHandler 0Eh




haltcpu:
	cli
	hlt
	ret



SECTION .bss
	aux resq 1
	SPBackup resq 1
	IPBackup resq 1

	SampleCodeAdress equ 0x400000