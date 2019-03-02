%include "consts.asm"

[BITS 32]
mov eax, 0xb8000
mov [eax], BYTE 'B'
mov eax, 0xb8001
mov [eax], BYTE 0x1b
