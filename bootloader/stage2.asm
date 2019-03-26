%include "consts.asm"

[ORG STAGE2_BASE]
[BITS 16]
  jmp start

%include "common.asm"

DEFINE_MSG msgBootVer, 'The bootloader'
DEFINE_MSG msgWelcome, 'Welcome!'
DEFINE_MSG msgLoadPartitionData, 'Loading partition data'
DEFINE_MSG msgLoadBpb, 'Loading BIOS Parameter Block'
DEFINE_MSG msgLoadGdt, 'Setting up Global Descriptor Table'
DEFINE_MSG msgEnterProtected, 'Entering protected mode'
DEFINE_MSG msg_load_bootstrap, 'Loading bootstrap'
DEFINE_MSG err_fat_table, 'Error: Cannot load FAT table'
DEFINE_MSG err_fat_offset_too_big, 'Error: attampted to read to big FAT table offset. Finish freakin TODOs!'
DEFINE_MSG err_path_boot, 'Error: Cannot find /boot directory'
DEFINE_MSG err_path_bootstrap, 'Error: Cannot find /boot/bootstrp.bin'
DEFINE_MSG err_cluster_read, 'Error: Unable to read FAT cluster sector'
DEFINE_MSG err_bootstrap_too_big, 'Error: Bootstrap size too big'
DEFINE_MSG err_boostrap_read, 'Error: Cannot load bootstrap'

g_first_data_sector dw 0
g_partition_offset dw 0

path_boot db 'BOOT'
path_boot_len equ $ - path_boot
path_bootstrap db 'BOOTSTRPBIN'
path_bootstrap_len equ $ - path_bootstrap

start:
  PRINT msgBootVer
  PRINT msgWelcome
  
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
  push DWORD bios_parameter_block
  call disk_read
  cmp ax, 0
  jne error
  add sp, 8

  ; read FAT table
  mov ax, [g_partition_offset]
  add ax, [bpb_reserved_sector_count]
  push ax
  push FAT_SECTORS_MAX
  push DWORD fat_table
  call disk_read
  cmp ax, 0
  je lpd_fat_noerror
  ERROR err_fat_table
  lpd_fat_noerror:
  add sp, 8

  mov ax, WORD [fat_table + 8]
  mov bx, WORD [fat_table + 10]

  ; get first data sector
  ; needed to calculate sector of N cluster
  xor eax, eax
  xor ebx, ebx
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

  ; TODO move below to another function!
  push DWORD [bpb_root_cluster]
  push path_boot
  push path_boot_len
  call find_name_in_cluster
  cmp eax, 0
  jne lpd_path_boot_noerror
  ERROR err_path_boot
  lpd_path_boot_noerror:
  add sp, 8 ; 4 bytes root_cluster!

  push eax ; /boot cluster
  push path_bootstrap
  push path_bootstrap_len
  call find_name_in_cluster
  cmp eax, 0
  jne lpd_path_bootstrap_noerror
  ERROR err_path_bootstrap
  lpd_path_bootstrap_noerror:
  add sp, 8

  ; size really needed?
  mov ecx, ebx ; size in ebx
  shr ecx, 16
  cmp ecx, 0
  je lpd_boostrap_size_noerror
  ERROR err_bootstrap_too_big ; unfortunately, only 2 bytes size supported for now
  lpd_boostrap_size_noerror:

  
  PRINT msg_load_bootstrap

  ; TODO: make read any FAT offset possible
  mov ebx, eax
  imul ebx, 4
  cmp ebx, FAT_SECTORS_MAX * 512
  jle lpd_fat_offset_ok
	ERROR err_fat_offset_too_big
  lpd_fat_offset_ok:

  push eax ; first cluster of a bootstrap file
  push DWORD BOOTSTRAP_BASE_SEGMENTED ; destination
  call read_file
  add sp, 8

  popa
  pop bp
  ret

;args: 4b start cluster, 4b destination address
read_file:
  push bp
  mov bp, sp

  %define destination bp + 4 ; 4 bytes!
  %define start_cluster bp + 8 ; 4 bytes!

  pusha

  xor ecx, ecx
  mov ecx, [start_cluster]
  xor edi, edi
  mov edi, [destination]

  rf_loop:
	push ecx
	call get_first_sector_of_cluster
	add sp, 4

	push ax ; bootstrap sector
	xor dx, dx
	mov dl, [bpb_sectors_per_cluster]
	push dx
	push edi ; destination	
	call disk_read
	add sp, 8
	cmp ax, 0
	je rf_bootstrap_read_noerror
	  ERROR err_boostrap_read
	rf_bootstrap_read_noerror:

	; move destination pointer
	imul edx, 512
	add edi, edx

	; read the FAT entry for current cluster
	mov ebx, ecx ; current cluster
	imul ebx, 4
	mov ecx, fat_table
	add ecx, ebx
	mov ebx, [ecx]
	; if it's an end or bad cluster - not found, end loop
	and ebx, 0x0fffffff
	mov ecx, ebx ; new current cluster
	cmp ebx, 0x0ffffff7
	jl rf_loop

  popa
  pop bp
  ret


; args 4b cluster number, name to find, name size
; ret eax: cluster number where found the name
;		   0 on error
;     ebx: target size
find_name_in_cluster:
  push bp
  mov bp, sp

  push DWORD 0
  %define ret_cluster bp - 4

  push DWORD 0
  %define ret_size bp - 8

  push 0
  %define cluster_ptr bp - 10

  push 0
  %define i bp - 12

  push DWORD 0
  %define current_cluster bp - 14

  %define name_size bp + 4
  %define name_to_find bp + 6
  %define cluster_number bp + 8 ; 4 bytes!

  pusha

  mov eax, [cluster_number]
  mov [current_cluster], eax
  xor eax, eax
  fnic_read_cluster_loop:
	; get sector nb
	push DWORD [current_cluster]
	call get_first_sector_of_cluster
	add sp, 4

	; read sector
	push ax
	push 1
	push DWORD fat_cluster_entry
	call disk_read
	add sp, 8
	cmp ax, 0
	je fnic_disk_noerror
	ERROR err_cluster_read
	fnic_disk_noerror:
	
	; ax counter (i), dx pointer at current cluster entry

	mov ax, [i]
	xor dx, dx
	fnic_parse_cluster_loop:
	  ; parse cluster entries
	  mov si, [name_to_find]

	  mov dx, ax
	  imul dx, 32 ; cluster entry size
	  add dx, fat_cluster_entry
	  mov di, dx

	  ; check first byte for an entry correctness
	  cmp BYTE [di], 0 ; no entry
	  je fnic_end_of_cluster
	  cmp BYTE [di], 0xe5 ; unused
	  je fnic_bad_entry
		; we're good compare first 11 bytes (name)
		cld ; direction flag: left to right (clear)
		mov cx, [name_size]
		repe cmpsb
		cmp cx, 0
		jne fnic_bad_entry
		  ; comparison ok, we still need to check for spaces padding
		  mov cx, 11
		  sub cx, [name_size]
		  mov si, fnic_spaces
		  repe cmpsb
		  cmp cx, 0
		  jne fnic_bad_entry
			; found!
			mov di, dx
			mov bx, [di + 20] ; hi 2 bytes of cluster nb
			shl ebx, 16
			mov bx, [di + 26] ; lo 2 bytes of cluster nb
			mov [ret_cluster], ebx
			mov ebx, [di + 28] ; size
			mov [ret_size], ebx
			jmp fnic_end
	  fnic_bad_entry:
	  inc ax
	  jmp fnic_parse_cluster_loop

	fnic_end_of_cluster:
	; read the FAT entry for current cluster
	mov eax, fat_table
	mov ebx, [current_cluster]
	imul ebx, 4
	add eax, ebx
	mov ebx, [eax]
	; if it's end or bad cluster - not found, end loop
	and ebx, 0x0fffffff
	cmp ebx, 0x0ffffff7
	jge fnic_end_not_found
	; otherwise the value is the next cluster in chain
	mov [current_cluster], ebx
	xor eax, eax
	xor ebx, ebx
	mov [i], WORD 0
	jmp fnic_read_cluster_loop
	
  fnic_end_not_found:
  mov [ret_cluster], DWORD 0

  fnic_end:
  popa
  add sp, 8
  pop ebx
  pop eax
  pop bp
  ret

  fnic_spaces times 11 db 0x20
	

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
  xor ebx, ebx
  mov bl, [bpb_sectors_per_cluster]
  imul eax, ebx
  add ax, [g_first_data_sector]
  add ax, [g_partition_offset]
  mov [ret_val], ax

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
  mov esp, BOOTSTRAP_STACK ; move the stack pointer right after already loaded BIOS stuff

  jmp BOOTSTRAP_BASE_PHYSICAL + 1024 ; .text area will always be at 1KB offset in bootstrap.bin
 
hang:
  jmp hang



; structures
fat_table:
  times 512 * FAT_SECTORS_MAX db 0

fat_cluster_entry:
  times 512 db 0
  

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
