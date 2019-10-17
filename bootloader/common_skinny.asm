[BITS 16]
; Note this is included in the stage 1.
; Only must-have code due to the size limit!

%macro DEFINE_MSG 2
  %1 db %2, 0xd, 0xa
  %1_len equ $ - %1
%endmacro

%macro PRINT 1
  push %1
  push %1_len
  call print
  add sp, 4
%endmacro

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
  mov di, bp
  mov bp, [str] ; msg
  int 0x10
  mov bp, di

  popa
  pop bp

  ret

; structures
disk_address_packet:
  db 16 ; size
  db 0 ; reserved
  dap_size dw 0 ; blocks to copy, max 65536 bytes in realmode
  dap_target dd 0
  dap_start_block dq 0


drNumberOfHeads db 0
drSectorsPerTrack db 0
; funcs

; args: start_block, size, 4 bytes target
; return: ax - 0 on success, otherwise error code
disk_read:
;  push bp
;  mov bp, sp
;
;  push 0
;  %define return_val ebp - 2
;
;  pusha
;  xor ax, ax
;  xor bx, bx
;  xor cx, cx
;  xor dx, dx
;
;  mov dl, [drNumberOfHeads]
;  cmp dl, 0
;  jz .need_read
;  mov dl, [drSectorsPerTrack]
;  cmp dl, 0
;  jnz .already_read
;  .need_read:
;  mov ah, 8
;  mov dl, [SYSTEM_INFO_DRIVE_NUMBER]
;  int 0x13
;  mov [drNumberOfHeads], dh
;  mov [drSectorsPerTrack], cl
;
;  .already_read:
;
;  mov dx, 0
;  mov ax, WORD [ebp + 10] ; start lba
;  mov cx, WORD [ebp + 8] ; count
;  mov es, dx
;  mov ebx, DWORD [ebp + 4] ; target buffer
;  
;ReadSector:
;        pusha
;
;ReadSectorNext:
;        mov     di, 5                   ; attempts to read
;
;ReadSectorRetry:
;        pusha
;
;        div     word [drSectorsPerTrack]
;                ; ax = LBA / SPT
;                ; dx = LBA % SPT         = sector - 1
;
;        mov     cx, dx
;        inc     cx
;                ; cx = sector no.
;
;        xor     dx, dx
;        div     word [drNumberOfHeads]
;                ; ax = (LBA / SPT) / HPC = cylinder
;                ; dx = (LBA / SPT) % HPC = head
;
;        mov     ch, al
;                ; ch = LSB 0...7 of cylinder no.
;        shl     ah, 6
;        or      cl, ah
;                ; cl = MSB 8...9 of cylinder no. + sector no.
;
;        mov     dh, dl
;                ; dh = head no.
;
;        mov     dl, [SYSTEM_INFO_DRIVE_NUMBER]
;                ; dl = drive no.
;
;        mov     ax, 201h
;                                        ; al = sector count = 1
;                                        ; ah = 2 = read function no.
;
;        int     13h                     ; read sectors
;        jnc     ReadSectorDone          ; CF = 0 if no error
;
;        xor     ah, ah                  ; ah = 0 = reset function
;        int     13h                     ; reset drive
;
;        popa
;        dec     di
;        jnz     ReadSectorRetry         ; extra attempt
;        ; jmp     short ErrRead
;        jmp     drProcError3
;
;ReadSectorDone:
;        popa
;        dec     cx
;        jz      ReadSectorDone2         ; last sector
;
;        add     bx, 512 ; adjust offset for next sector
;        add     ax, 1
;        adc     dx, 0                   ; adjust LBA for next sector
;        jmp     short ReadSectorNext
;
;ReadSectorDone2:
;        popa
;;        ret
;
;  mov [return_val], WORD 0
;  jnc drProcNoerror
;  mov [return_val], WORD 2
;
;  drProcError3:
;  mov [return_val], WORD 3
;
;  drProcNoerror:
;  popa
;  pop ax
;  pop bp
;  ret

  push bp
  mov bp, sp

  push 0
  %define return_val ebp - 2

  pusha
  xor ax, ax
  xor bx, bx
  xor cx, cx
  xor dx, dx

  mov bx, [ebp + 10]
  mov [dap_start_block], bx
  mov bx, [ebp + 8]
  mov [dap_size], bx
  mov ebx, [ebp + 4]
  mov [dap_target], ebx
  xor ebx, ebx

  mov ah, 0x42 ; extended read
  mov dl, [SYSTEM_INFO_DRIVE_NUMBER] ; drive number
  mov ds, bx
  mov si, disk_address_packet
  int 0x13
  mov [return_val], ah
  
  popa
  pop ax
  pop bp
  ret
