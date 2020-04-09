GLOBAL cpuVendor

GLOBAL raxRegister
GLOBAL rbxRegister
GLOBAL rcxRegister
GLOBAL rdxRegister
GLOBAL rdiRegister
GLOBAL rsiRegister
GLOBAL r8Register
GLOBAL r9Register
GLOBAL r10Register
GLOBAL r11Register
GLOBAL r12Register
GLOBAL r13Register
GLOBAL r14Register
GLOBAL r15Register
GLOBAL ipRegister



section .text


	
cpuVendor:
	push rbp
	mov rbp, rsp

	push rbx

	mov rax, 0
	cpuid


	mov [rdi], ebx
	mov [rdi + 4], edx
	mov [rdi + 8], ecx

	mov byte [rdi+13], 0

	mov rax, rdi

	pop rbx


	mov rsp, rbp
	pop rbp
	ret





