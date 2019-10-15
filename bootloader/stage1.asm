%include "consts.asm"

[ORG STAGE1_BASE]
[BITS 16]

bootStart:
  jmp     _start
  nop
  osType      db  'MSDOS6.0'
  bpb
  bps         dw  512
  spc         db  8
  rs          dw  1
  fats        db  2
  re          dw  512
  ss          dw  0
  media       db  0xf8
  spfat       dw  0xc900
  spt         dw  0x3f00
  heads       dw  0x1000
  hidden      dw  0x3f00, 0
  ls          dw  0x5142,0x0600
  pdn         db  0x80
  cheads          db  0
  sig         db  0x29
  serialno    dw  0xce13, 0x4630
  label       db  'NO NAME'
  fattype     db  "FAT32"

%include "common_skinny.asm"

_start:
  cli
  ; setup the stack
  mov sp, STACK_ADDRESS
  mov bp, sp
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
  
  PRINT msgHello

  push 1 ; offset
  push 128 ; size, max stage2 size = 65k
  push DWORD STAGE2_BASE ; address
  call disk_read
  cmp ax, 0
  jne exit
  add sp, 8

  jmp STAGE2_BASE


DEFINE_MSG msgHello, 'Hello'

exit:
  jmp exit
