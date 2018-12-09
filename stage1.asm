start:
	mov ah, 0x0A ; print character only
	mov al, 'W'
	mov bh, 0
	mov cx, 100
	int 0x10
  
  jmp exit



test:
	mov ah, 0x0A ; print character only
	mov al, 'T'
	mov bh, 0
	mov cx, 100
	int 0x10
  ret

exit:
