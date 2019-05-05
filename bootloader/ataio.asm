; protected mode only!
[BITS 32]

; param: port, value
; ret: void
global outb
outb:
  push ebp
  mov ebp, esp
  pusha

  %define PORT ebp + 12
  %define VALUE ebp + 8
  mov dx, [PORT]
  mov al, [VALUE]
  out dx, al


  popa
  pop ebp
  ret

; param: port
; ret: al
global inb
inb:
  xor eax, eax
  push edx
  mov dx, [esp + 8] ; port param
  in al, dx
  pop edx
  ret

; param: port, outBuff, count
; ret: void
global inwn
inwn:
  push ebp
  mov ebp, esp
  pusha

  %define PORT ebp + 16
  %define OUTBUFF ebp + 12
  %define COUNT ebp + 8

  xor edi, edi
  xor edx, edx
  xor ecx, ecx
  mov edi, [OUTBUFF]
  mov dx, [PORT]
  mov cx, [COUNT]
  rep insw

  popa
  pop ebp
  ret

; params none
; ret eax, 0 = success
ata_init:
  push ebx

  %define NO_DRIVES_BYTE 0xff
  %define REG_STATUS 0x1f7
  push DWORD REG_STATUS
  call inb
  add esp, 4
  cmp al, NO_DRIVES_BYTE
  je .err_no_drives_detected

  ; *** select primary master and LBA mode
  %define MASTER_DRIVE_BIT 0xa0
  %define LBA_MODE_BIT 0x40
  %define REG_DRIVE_HEAD 0x1f6
  
  ; set flags
  xor eax, eax
  mov al, MASTER_DRIVE_BIT
  or al, LBA_MODE_BIT
  push eax

  push DWORD REG_DRIVE_HEAD
  call outb
  add esp, 8

  ; *** give some time to the drive, call 5 cmds
  push DWORD REG_STATUS
  call inb
  call inb
  call inb
  call inb
  call inb
  add esp, 4

  ; *** reset sector selectors
  %define REG_SECTOR_COUNT 0x1f2
  push DWORD REG_SECTOR_COUNT
  push DWORD 0
  call outb
  add esp, 8

  %define REG_LBA_LOW 0x1f3
  push DWORD REG_LBA_LOW
  push DWORD 0
  call outb
  add esp, 8

  %define REG_LBA_MID 0x1f4
  push DWORD REG_LBA_MID
  push DWORD 0
  call outb
  add esp, 8

  %define REG_LBA_HIGH 0x1f5
  push DWORD REG_LBA_HIGH
  push DWORD 0
  call outb
  add esp, 8

  ; *** identify
  %define REG_COMMAND 0x1f7
  %define CMD_IDENTIFY 0xec
  push DWORD REG_COMMAND
  push DWORD CMD_IDENTIFY
  call outb
  add esp, 8
  
  ; check status
  push DWORD REG_STATUS
  call inb
  add esp, 4
  cmp al, 0
  je .err_no_primary_master

  ; *** wait for not busy
  %define ST_BSY_BIT 128
  xor ebx, ebx
  mov bl, ST_BSY_BIT
  push DWORD REG_STATUS
.busy_loop:
  call inb
  and al, bl
  cmp al, 0
  jne .busy_loop
  add esp, 4

  ; *** check LBA registers
  push DWORD REG_LBA_MID
  call inb
  add esp, 4
  cmp al, 0
  jne .err_not_ata_device

  push DWORD REG_LBA_HIGH
  call inb
  add esp, 4
  cmp al, 0
  jne .err_not_ata_device

  ; *** wait for finish init until done or err
  %define ST_ERR_BIT 1
	%define ST_DRQ_BIT 8
  xor ebx, ebx
  mov bl, ST_DRQ_BIT
  mov bh, ST_ERR_BIT
  push DWORD REG_STATUS
.init_loop:
  call inb
  and al, bh
  cmp al, 0
  jne .err_init
  call inb
  and al, bl
  cmp al, 0
  je .init_loop
  add esp, 4

  ; *** read driver identifier
  %define REG_DATA 0x1f0
  push DWORD REG_DATA
  push DWORD ata_driver_identifier
  push DWORD 512
  call inwn
  add esp, 12

  mov eax, 0
  jmp .ret
.err_no_drives_detected:
  mov eax, 1
  jmp .ret
.err_no_primary_master:
  mov eax, 2
  jmp .ret
.err_not_ata_device:
  mov eax, 3
  jmp .ret
.err_init:
  mov eax, 4
  jmp .ret

.ret:
  pop ebx
  ret

ata_driver_identifier:
  times 512 db 0
