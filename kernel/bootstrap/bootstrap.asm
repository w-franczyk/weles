[BITS 32]

times 4900 nop

begin:
mov eax, 0xb8000
mov [eax], BYTE 'm'
mov eax, 0xb8001
mov [eax], BYTE 0x1b
hang:
  jmp hang

times 10 nop
dw 0
times 10 nop
dw 0
times 10 nop
