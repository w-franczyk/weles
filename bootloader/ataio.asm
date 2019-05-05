; protected mode only!
[BITS 32]

%define REG_DATA 0x1f0
%define REG_ERROR 0x1f1
%define REG_SECTOR_COUNT 0x1f2
%define REG_LBA_LOW 0x1f3
%define REG_LBA_MID 0x1f4
%define REG_LBA_HIGH 0x1f5
%define REG_DRIVE_HEAD 0x1f6
%define REG_STATUS 0x1f7
%define REG_COMMAND 0x1f7

%define CMD_READ 0x20
%define CMD_IDENTIFY 0xec

%define ST_ERR_BIT 1
%define ST_IDX_BIT 2
%define ST_CORR_BIT 4
%define ST_DRQ_BIT 8
%define ST_SRV_BIT 16
%define ST_DF_BIT 32
%define ST_RDY_BIT 64
%define ST_BSY_BIT 128

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
  push DWORD REG_STATUS
  call inb
  add esp, 4
  cmp al, NO_DRIVES_BYTE
  je .err_no_drives_detected

  ; *** select primary master and LBA mode
  %define MASTER_DRIVE_BIT 0xa0
  %define LBA_MODE_BIT 0x40
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
  push DWORD REG_SECTOR_COUNT
  push DWORD 0
  call outb
  add esp, 8

  push DWORD REG_LBA_LOW
  push DWORD 0
  call outb
  add esp, 8

  push DWORD REG_LBA_MID
  push DWORD 0
  call outb
  add esp, 8

  push DWORD REG_LBA_HIGH
  push DWORD 0
  call outb
  add esp, 8

  ; *** identify
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
  push DWORD REG_DATA
  push DWORD ata_driver_identifier
  push DWORD 256
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

; args: sector, count, target
; return: ax - 0 on success, otherwise error code
ata_read:
  push ebp
  mov ebp, esp

  push DWORD 0
  %define RETURN_VAL ebp - 4
  
  %define SECTOR ebp + 16
  %define COUNT ebp + 12
  %define TARGET ebp + 8

  pusha
  xor eax, eax
  xor ebx, ebx
  xor ecx, ecx
  xor edx, edx

  ; set sectors
  push DWORD REG_SECTOR_COUNT
  push DWORD [COUNT]
  call outb
  add esp, 8

  mov eax, [SECTOR]
  cmp eax, 0x0fffffff
  jg .err_sector_too_big

  push DWORD REG_LBA_LOW
  and eax, 0x000000ff
  push eax
  call outb
  add esp, 8
  
  push DWORD REG_LBA_MID
  mov eax, [SECTOR]
  shr eax, 8
  and eax, 0x000000ff
  push eax
  call outb
  add esp, 8
  
  push DWORD REG_LBA_HIGH
  mov eax, [SECTOR]
  shr eax, 16
  and eax, 0x000000ff
  push eax
  call outb
  add esp, 8

  ; read
  push DWORD REG_COMMAND
  push DWORD CMD_READ
  call outb
  add esp, 8

  ; wait
  xor ebx, ebx
  mov bl, ST_DRQ_BIT
  mov bh, ST_ERR_BIT
  push DWORD REG_STATUS
.read_loop:
  call inb
  and al, bh
  cmp al, 0
  jne .err_read
  call inb
  and al, bl
  cmp al, 0
  je .read_loop
  add esp, 4

  ; copy to the target buffer
  push DWORD REG_DATA
  push DWORD [TARGET]
  mov eax, [COUNT]
  imul eax, 256 ; we read words, not bytes
  push eax
  call inwn
  add esp, 12
  mov DWORD [RETURN_VAL], 0
  jmp .end

.err_sector_too_big:
  mov DWORD [RETURN_VAL], 1
  jmp .end
.err_read:
  mov DWORD [RETURN_VAL], 2
  jmp .end

.end:
  popa
  pop eax
  pop ebp
  ret

ata_driver_identifier:
  times 512 db 0
