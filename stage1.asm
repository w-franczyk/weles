start:
	mov ah, 0x0A ; print character only
	mov al, 'W'
	mov bh, 0
	mov cx, 100
	int 0x10

  ; Load stage 2
  mov ah, 0x42 ; extended load
  mov dl, 0x80 ; drive number, to check
  
  
  jmp exit



test:
	mov ah, 0x0A ; print character only
	mov al, 'T'
	mov bh, 0
	mov cx, 100
	int 0x10
  ret

exit:
