; structures
disk_address_packet:
  db 16 ; size
  db 0 ; reserved
  dap_blocks dw 0 ; blocks to copy, max 65536 bytes in realmode
  dap_target dd 0
  dq 1 ; start block

; funcs
disk_read:
  mov dap_target, [sp]
  mov dap_blocks, [sp - 2]
;  mov sp, bp

error: ; print 'E'
  mov ah, 0x0A
  mov al, 'E'
  mov bh, 0
  mov cx, 1
  int 0x10
  jmp exit
