; para compilar este archivo:  nasm -f elf64 test.asm
; en el makefile para compilar el server: gcc server.c test.o -o server

GLOBAL dum1
GLOBAL dum2
GLOBAL dum3

SECTION .data:


_dum1:
	ret

SECTION .comment:
_dum2:
	ret

SECTION .RUN_ME:
_dum3:
	ret
