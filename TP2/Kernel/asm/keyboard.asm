GLOBAL __ReadKey__


section .text


__ReadKey__:

      enter 0,0

      xor rax,rax

      in al,64h

      and al,00000001b

      jz .NoKey
      mov rax, 0
      in al,60h
      jmp .exit
.NoKey:
      mov rax,-1

 .exit:
      leave
      ret