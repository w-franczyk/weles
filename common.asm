; structures
disk_address_packet:
  db 16 ; size
  db 0 ; reserved
  dap_size dw 0 ; blocks to copy, max 65536 bytes in realmode
  dap_target dd 0
  dap_start_block dq 0



; funcs:
; macros
%macro DEFINE_MSG 2
  %1 db %2, 0xd, 0xa
  %1_len equ $ - %1
%endmacro

DEFINE_MSG msgError, 'Error!'
DEFINE_MSG msgDone, 'Done!'

%macro PRINT 1
  push %1
  push %1_len
  call print
  add sp, 4
%endmacro

%macro ERROR 1
  push %1
  push %1_len
  jmp print_error
  add sp, 4
%endmacro


; args: start_block, size, target
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

error: ; print 'Error' and exit
  PRINT msgError
  jmp exit

; args: str pointer, size
; return: none
print:
  push bp
  mov bp, sp
  pusha

  %define str bp + 6
  %define len bp + 4

  xor ax, ax
  xor bx, bx
  xor cx, cx
  xor dx, dx

  mov ax, cs
  mov es, ax ; set up ES register

  ; get current cursor coords
  mov ah, 0x3
  mov bh, 0
  int 0x10 ; coords saved into dx

  ; get current page number
  mov ah, 0x0f
  int 0x10 ; page saved into bh

  ; print string
  mov ah, 0x13
  mov al, 0x1 ; update cursor
  mov bl, 0x07 ; color light grey
  mov cx, [len] ; length
  mov bp, [str] ; msg
  int 0x10

  popa
  pop bp

  ret

; args: same as print
print_error:
  call print
  jmp exit

; args: value, out str
printr_save:
  push bp
  mov bp, sp

  push 0
  %define i bp - 2
  push 3
  %define j bp - 4

  %define out_str bp + 4
  %define value bp + 6

  pusha

  hex_to_char_loop:
	mov cx, 4
	imul cx, [i]
	mov ax, [value]
	shr ax, cl
	and ax, 0x000f

	mov bl, 0x30
	cmp al, 0xa
	jl add_30
	mov bl, 0x57
	add_30:
	add al, bl

	mov bx, [out_str]
	add bx, [j]
	mov [bx], al

	mov ax, [j]
	dec ax
	mov [j], ax
	mov ax, [i]
	inc ax
	mov [i], ax
	cmp ax, 4
	jl hex_to_char_loop

  popa
  add sp, 4
  pop bp
  ret

printr:
  push ax
  push s_ax
  call printr_save
  add sp, 4

  push bx
  push s_bx
  call printr_save
  add sp, 4

  push cx
  push s_cx
  call printr_save
  add sp, 4

  push dx
  push s_dx
  call printr_save
  add sp, 4

  push printr_str
  push printr_str_len
  call print
  add sp, 4

  ret
  
  
  printr_str:
	db "AX: 0x"
	s_ax dd 0
	db ", BX: 0x"
	s_bx dd 0
	db ", CX: 0x"
	s_cx dd 0
	db ", DX: 0x"
	s_dx dd 0
	db 0x0a, 0xd
	printr_str_len equ $ - printr_str
