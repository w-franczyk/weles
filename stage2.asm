start:
	mov ah, 0x0A ; print character only
	mov al, '2'
	mov bh, 0
	mov cx, 200
	int 0x10
  
  jmp exit



exit:
