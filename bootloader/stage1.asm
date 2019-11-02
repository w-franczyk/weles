%include "consts.asm"

[ORG STAGE1_BASE]
[BITS 16]

bootStart:
  jmp     _start
  TIMES 3-($-$$) DB 0x90   ; Support 2 or 3 byte encoded JMPs before BPB.

  ; Dos 4.0 EBPB 1.44MB floppy
  OEMname:           db    "mkfs.fat"  ; mkfs.fat is what OEMname mkdosfs uses
  bytesPerSector:    dw    512
  sectPerCluster:    db    1
  reservedSectors:   dw    1
  numFAT:            db    2
  numRootDirEntries: dw    224
  numSectors:        dw    2880
  mediaType:         db    0xf0
  numFATsectors:     dw    9
  sectorsPerTrack:   dw    18
  numHeads:          dw    2
  numHiddenSectors:  dd    0
  numSectorsHuge:    dd    0
  driveNum:          db    0
  reserved:          db    0
  signature:         db    0x29
  volumeID:          dd    0x2d7e5a1a
  volumeLabel:       db    "WELES      "
  fileSysType:       db    "FAT32   "

%include "common_skinny.asm"

_start:
  cli
  ; setup the stack
  mov ax, 0
  mov ss, ax
  mov sp, STACK_ADDRESS
  mov bp, sp
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax
;  mov ax, STAGE1_BASE
;  mov cs, ax
  sti

  ; BIOS passed driver number into dl reg
  mov [SYSTEM_INFO_DRIVE_NUMBER], dl

  cld

  ; 80x25 text video mode
  mov ah, 0x0
  mov al, 0x03
  int 0x10

  ; set active display page 0
  mov ah, 0x05
  mov al, 0x0
  int 0x10
  
;  ; we will see
;  mov ah, 0x41
;  mov bx, 0x55aa
;  mov dl, [SYSTEM_INFO_DRIVE_NUMBER]
;  int 0x13
;  jnc .success
;  ERROR fail
  
;  .success:
;  ERROR success
 
  push 1 ; offset
  push 40 ; size, max stage2 size = 65k
  push DWORD STAGE2_BASE ; address
  call disk_read
  cmp ax, 0
  je .stage2_ok

  PRINT errStage2Load
  jmp exit

  .stage2_ok:
  add sp, 8
  jmp STAGE2_BASE

DEFINE_MSG errStage2Load, 'Stage2 load failed'

exit:
  jmp exit
