[BITS 16]
; Note this is included in the stage 1.
; Only must-have code due to the size limit!

; structures
disk_address_packet:
  db 16 ; size
  db 0 ; reserved
  dap_size dw 0 ; blocks to copy, max 65536 bytes in realmode
  dap_target dd 0
  dap_start_block dq 0


; funcs

; args: start_block, size, 4 bytes target
; return: ax - 0 on success, otherwise error code
disk_read:
  push bp
  mov bp, sp

  push 0
  %define return_val ebp - 2

  pusha
  xor ax, ax
  xor bx, bx
  xor cx, cx
  xor dx, dx

  mov bx, [ebp + 10]
  mov [dap_start_block], bx
  mov bx, [ebp + 8]
  mov [dap_size], bx
  mov ebx, [ebp + 4]
  mov [dap_target], ebx
  xor ebx, ebx

  mov ah, 0x42 ; extended read
  mov dl, 0x80 ; drive number, TODO: CHECK!
  mov si, disk_address_packet
  int 0x13
  mov [return_val], ah 
 
  popa
  pop ax
  pop bp
  ret
