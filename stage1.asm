%define STAGE1_BASE 0x7c00
%define STAGE2_BASE 0x7e00

[ORG STAGE1_BASE]
[BITS 16]
_start:
  ; Load stage 2
  mov ah, 0x42 ; extended read
  mov dl, 0x80 ; drive number, TODO: CHECK!
  mov si, disk_address_packet
  int 0x13
  jc error ; something went wrong
  jmp STAGE2_BASE

; structures
disk_address_packet:
  db 16 ; size
  db 0 ; reserved
  dw 128 ; blocks to copy, max 65536 bytes in realmode
  dd STAGE2_BASE
  dq 1 ; start block

; functions
error: ; print 'E'
  mov ah, 0x0A
  mov al, 'E'
  mov bh, 0
  mov cx, 1
  int 0x10
  jmp exit
 

exit:
  jmp exit
