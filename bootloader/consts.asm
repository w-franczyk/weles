%define STAGE1_BASE 0x7c00
%define STACK_ADDRESS 0x7ff0 ; grows down, 512 bytes for STAGE1

%define SYSTEM_INFO 0x8000 ; 512 bytes for bootloader STACK, 1KB used so far
%define SYSTEM_INFO_DRIVE_NUMBER 0x8000 ; 1 byte, drive number

%define STAGE2_BASE 0x8300 ; 1024 bytes fo system info, 2KB used so far
%define BOOTSTRAP_STACK 0xBB70 ; 26KB for STAGE2, 28KB used so far
; TODO: calculate below and finish comments
;%define BOOTSTRAP_BASE 0xFC00 ; 4KB for BOOTSTRAP_STACK, 32KB used so far
%define BOOTSTRAP_BASE_PHYSICAL 0x10000 ; 4KB for BOOTSTRAP_STACK, 32KB used so far
%define BOOTSTRAP_BASE_SEGMENTED 0x10000000

; 33KB for BOOTSTRAP, 65KB max (and used) for realmode so the right bound is 0x18000
