%include "consts.asm"

[ORG STAGE2_BASE]
[BITS 16]
  jmp start

%include "common.asm"

DEFINE_MSG msgLoadPartitionData, 'Loading partition data'
DEFINE_MSG msgLoadBpb, 'Loading BIOS Parameter Block'
DEFINE_MSG msgLoadGdt, 'Setting up Global Descriptor Table'
DEFINE_MSG msgEnterProtected, 'Entering protected mode'

g_first_data_sector dw 0
g_partition_offset dw 0

start:
  PRINT msgLoadPartitionData
  call load_partition_data

  cli ; disable any other interrupts
  xor ax, ax
  mov ds, ax ; set data segment to 0
  
  ; load GDT
  PRINT msgLoadGdt
  lgdt [gdt_descriptor]

  ; enable protected mode
  PRINT msgEnterProtected
  mov eax, cr0
  or eax, 1 ; enable the flag...
  mov cr0, eax ; ...and save it back to cr0
  jmp 0x8:protected_mode

; functions
load_partition_data:
  push bp
  mov bp, sp
  pusha

  PRINT msgLoadBpb
  ; load the partition 1 BPB
  %define PARTITION1_TABLE STAGE1_BASE + 0x1be
  %define PARTITION1_OFFSET PARTITION1_TABLE + 0x8
  mov ax, WORD [PARTITION1_OFFSET + 2]
  cmp ax, 0
  jne error ; 32 bit addresses not supported for now
  mov ax, WORD [PARTITION1_OFFSET]
  mov [g_partition_offset], ax
  push WORD [g_partition_offset]
  push 1
  push bios_parameter_block
  call disk_read
  cmp ax, 0
  jne error
  add sp, 6
  mov ax, bios_parameter_block

  ; get sector of the root directory
  ; note: there will be used some 32 bit instructions
  ; nasm should automatically use the operand size override prefix
  xor eax, eax
  xor ecx, ecx
  mov ax, [bpb_table_size_16]
  cmp eax, 0
  jne lpd_got_fat_size
  mov eax, [bpb_table_size_32]
  lpd_got_fat_size:
  mov cl, [bpb_table_count]
  imul eax, ecx
  add ax, [bpb_reserved_sector_count] 
  mov [g_first_data_sector], ax ; now we have first_data_sector

  push DWORD [bpb_root_cluster]
  call get_first_sector_of_cluster
  add sp, 4

  popa
  pop bp
  ret

; args: 4 byte cluster number
; return: ax
get_first_sector_of_cluster:
  push bp
  mov bp, sp

  push 0
  %define ret_val bp - 2

  pusha

  %define cluster_number bp + 4 ; 4 bytes!

  mov eax, [cluster_number]
  sub eax, 2
  mov bl, [bpb_sectors_per_cluster]
  xor ebx, ebx
  imul eax, ebx
  add ax, [g_first_data_sector]
  add ax, [g_partition_offset]
  mov [ret_val], ax

  call printr

  popa
  pop ax ; ret_val
  pop bp
  ret



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
 
hang:
  jmp hang



; structures
bios_parameter_block:
  times 13 db 0
  bpb_sectors_per_cluster db 0
  bpb_reserved_sector_count dw 0
  bpb_table_count db 0
  times 5 db 0
  bpb_table_size_16 dw 0
  times 12 db 0
  bpb_table_size_32 dd 0
  times 4 db 0
  bpb_root_cluster dd 0
  times 42 db 0
  times 512 - ($ - bios_parameter_block) db 0

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
