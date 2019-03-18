%define STAGE1_BASE 0x7c00
%define STACK_ADDRESS 0x7ffe ; grows down
%define SYSTEM_INFO 0x8000
%define STAGE2_BASE 0x8200
%define BOOSTRAP_BASE 0x8800

; maximum size of sectors can be read for FAT structure
; this number determines the size of space reserved
; for it (FAT_SECTORS_MAX * 512)
%define FAT_SECTORS_MAX 10
