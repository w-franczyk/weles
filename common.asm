; structures
disk_address_packet:
  db 16 ; size
  db 0 ; reserved
  dap_size dw 0 ; blocks to copy, max 65536 bytes in realmode
  dap_target dd 0
  dap_start_block dq 0

; funcs

; args: start_block, size, target
; return: ax - 0 on success, otherwise error code
disk_read:
  push bp
  mov bp, sp

  push 0
  %define return_val ebp - 2

  pusha

  mov bx, [ebp + 8]
  mov [dap_start_block], bx
  mov bx, [ebp + 6]
  mov [dap_size], bx
  mov bx, [ebp + 4]
  mov [dap_target], bx

  mov ah, 0x42 ; extended read
  mov dl, 0x80 ; drive number, TODO: CHECK!
  mov si, disk_address_packet
  int 0x13
  mov [return_val], ah 
  
  popa
  pop ax
  pop bp
  ret

error: ; print 'E'
  mov ah, 0x0A
  mov al, 'E'
  mov bh, 0
  mov cx, 1
  int 0x10
  jmp exit
