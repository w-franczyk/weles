%include "consts.asm"

[ORG STAGE1_BASE]
[BITS 16]
jmp _start

%include "common.asm"

_start:
  ; setup the stack
  mov sp, STACK_ADDRESS
  mov bp, sp

  push 1 ; offset
  push 128 ; size, max stage2 size = 65k
  push STAGE2_BASE ; address
  call disk_read
  cmp ax, 0
  jne error
  add sp, 6

  jmp STAGE2_BASE

exit:
  jmp exit

