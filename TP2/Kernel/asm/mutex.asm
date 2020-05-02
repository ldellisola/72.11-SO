
;
;   Spinlock inplementation taken from https://en.wikipedia.org/wiki/Spinlock
;
;
;

GLOBAL spin_lock
GLOBAL spin_unlock


section .bss

locked:                      ; The lock variable. 1 = locked, 0 = unlocked.
     dd      0


section .text
spin_lock:
    enter 0,0

    mov     ecx, 1             ; Set the ECX register to 1.
retry:
    xor     eax, eax           ; Zero out EAX, because cmpxchg compares against EAX.
    XACQUIRE lock cmpxchg ecx, [locked]
                               ; atomically decide: if locked is zero, write ECX to it.
                               ;  XACQUIRE hints to the processor that we are acquiring a lock.
    je      out                ; If we locked it (old value equal to EAX: 0), return.
pause:
    mov     eax, [locked]      ; Read locked into EAX.
    test    eax, eax           ; Perform the zero-test as before.
    jz      retry              ; If it's zero, we can retry.
    rep nop                    ; Tell the CPU that we are waiting in a spinloop, so it can
                               ;  work on the other thread now. Also written as the "pause".
    jmp     pause              ; Keep check-pausing.
out:
    leave
    ret                        ; All done.

spin_unlock:
    enter 0,0
    XRELEASE mov [locked], 0   ; Assuming the memory ordering rules apply, release the 
                               ;  lock variable with a "lock release" hint.
    leave
    ret                        ; The lock has been released.