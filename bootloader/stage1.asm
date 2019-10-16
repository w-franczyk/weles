%include "consts.asm"

[ORG STAGE1_BASE]
[BITS 16]

bootStart:
  jmp     _start

%include "common.asm"

_start:
  cli
  ; setup the stack
  mov ax, 0
  mov ss, ax
  mov sp, STACK_ADDRESS
  mov bp, sp
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax
  sti

  ; BIOS passed driver number into dl reg
  mov [SYSTEM_INFO_DRIVE_NUMBER], dl

  ; 80x25 text video mode
  mov ah, 0x0
  mov al, 0x03
  int 0x10

  ; set active display page 0
  mov ah, 0x05
  mov al, 0x0
  int 0x10
 
  push 1 ; offset
  push 128 ; size, max stage2 size = 65k
  push DWORD STAGE2_BASE ; address
  call disk_read
  cmp ax, 0
  je .stage2_ok

  ERROR errStage2Load
  jmp exit

  .stage2_ok
  add sp, 8
  jmp STAGE2_BASE

DEFINE_MSG errStage2Load, 'Stage2e'

exit:
  jmp exit
