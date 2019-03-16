[BITS 32]

times 490 nop

begin:
mov eax, 0xb8000
mov [eax], BYTE 'm'
mov eax, 0xb8001
mov [eax], BYTE 0x1b
hang:
  jmp hang


