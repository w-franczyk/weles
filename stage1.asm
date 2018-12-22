_start:
	;mov ah, 0x0A ; print character only
	;mov al, 'W'
	;mov bh, 0
	;mov cx, 100
	;int 0x10

  ; Load stage 2
  mov ah, 0x42 ; extended load
  mov dl, 0x80 ; drive number, TO CHECK!
  mov si, disk_address_packet
  int 0x13
  ; jmp 0x7e00
 
	mov ah, 0x0A ; print character only
  mov edx, 0x7e00
	mov al, [edx]
	mov bh, 0
	mov cx, 100
	int 0x10

disk_address_packet:
  db 16 ; size
  db 0 ; reserved
  dw 10 ; blocks to copy, TODO: sprawdzic 128
  stage2_address dd 0x7e00
;  dq 1 ; start block
  dd 1
  dd 0

test:
	mov ah, 0x0A ; print character only
	mov al, 'T'
	mov bh, 0
	mov cx, 100
	int 0x10
  ret

exit:
