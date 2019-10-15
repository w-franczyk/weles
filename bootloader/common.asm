[BITS 16]
%include "common_skinny.asm"

; funcs:
; macros

DEFINE_MSG msgError, 'Error!'
DEFINE_MSG msgDone, 'Done!'

%macro ERROR 1
  push %1
  push %1_len
  jmp print_error
%endmacro

error: ; print 'Error' and exit
  PRINT msgError
  jmp exit


; args: same as print
print_error:
  call print
  add sp, 4
  call printr
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
  pusha

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

  popa
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
