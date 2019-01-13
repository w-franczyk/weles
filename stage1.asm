%include "consts.asm"

[ORG STAGE1_BASE]
[BITS 16]
jmp _start

%include "common.asm"

_start:
  ; setup the stack
  mov sp, STACK_ADDRESS
  mov bp, sp
  mov ss, sp

  push 128
  push STAGE2_BASE

  ; Load stage 2
;  mov ah, 0x42 ; extended read
;  mov dl, 0x80 ; drive number, TODO: CHECK!
;  mov si, disk_address_packet
;  int 0x13
;  jc error ; something went wrong
;  push 1
;  jmp STAGE2_BASE

; structures
;disk_address_packet:
;  db 16 ; size
;  db 0 ; reserved
;  dw 128 ; blocks to copy, max 65536 bytes in realmode
;  dd STAGE2_BASE
;  dq 1 ; start block

exit:
  jmp exit
