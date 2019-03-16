%include "consts.asm"

[ORG STAGE1_BASE]
[BITS 16]
jmp _start

%include "common_skinny.asm"

_start:
  ; 80x25 text video mode
  mov ah, 0x0
  mov al, 0x03
  int 0x10

  ; set active display page 0
  mov ah, 0x05
  mov al, 0x0
  int 0x10

  ; setup the stack
  mov sp, STACK_ADDRESS
  mov bp, sp

  push 1 ; offset
  push 128 ; size, max stage2 size = 65k
  push STAGE2_BASE ; address
  call disk_read
  cmp ax, 0
  jne exit
  add sp, 6

  jmp STAGE2_BASE

exit:
  jmp exit
