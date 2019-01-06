%define STAGE2_BASE 0x7e00

[ORG STAGE2_BASE]
[BITS 16]
start:
	mov ah, 0x0A ; print character only
	mov al, '3'
	mov bh, 0
	mov cx, 200
	int 0x10

  cli ; disable any other interrupts
  xor ax, ax
  mov ds, ax ; set data segment to 0
  
  ; load GDT
  lgdt [gdt_descriptor]

  ; enable protected mode
  mov eax, cr0
  or eax, 1 ; enable the flag...
  mov cr0, eax ; ...and save it back to cr0
  jmp 0x8:protected_mode
  
[BITS 32]
protected_mode:
  ; set segment registers to data segment (0x10)
  mov ax, 0x10
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax
  mov ss, ax
  mov esp, 0x10000 ; move the stack pointer right after already loaded BIOS stuff

  mov eax, 0xb8000
  mov [eax], BYTE 'P'
  mov eax, 0xb8001
  mov [eax], BYTE 0x1b
 
hang:
  jmp hang

; structures
gdt:
  gdt_null:
  dq 0

  gdt_code:
  dw 0xffff ; limit 4GB TODO: detect memory sz
  dw 0
  db 0 ; base (start) address

  ; access byte:
  ; 1 present bit
  ; 00 privilege bits, kernel level
  ; 1 descriptor type, data/code
  ; 1 executable bit, code
  ; 0 direction bit, ring 0 only
  ; 1 readable/writeable bit, code readable
  ; 0 accessed bit
  db 10011010b

  ; limit & flags:
  ; 1 granularity, 4kb granularity (segment size)
  ; 1 size, 32bit protected mode
  ; 00
  ; 1111 limit continuation
  db 11001111b

  ; remaning base address:
  db 0

  gdt_data:
  dw 0xffff ; limit. 4GB TODO: detect memory sz
  dw 0
  db 0 ; base (start) address. let's just make overapping data and code because the kernel is of course a safe piece of code :) and will rewrite the gdt anyway

  ; access byte:
  ; 1 present bit
  ; 00 privilege bits, kernel level
  ; 1 descriptor type, data/code
  ; 0 executable bit, data
  ; 0 direction bit, ring 0 only
  ; 1 readable/writeable bit, data writeable
  ; 0 accessed bit
  db 10010010b

  ; limit & flags:
  ; 1 granularity, 4kb granularity (segment size)
  ; 1 size, 32bit protected mode
  ; 00
  ; 1111 limit continuation
  db 11001111b

  ; remaning base address:
  db 0
gdt_end:

gdt_descriptor:
  dw gdt_end - gdt ; gdt size
  dd gdt ; gdt address

[BITS 32]
exit:
  jmp exit
