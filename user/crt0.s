section .text
extern main
section .crt0
global _start:function
_start:
  xor eax, eax
  mov al, [sigArgc]
  push sigArgv
  push eax
  call main
  pop ebx
  pop ebx
  ret

; 512 bytes max!!
; This section is written by ProcessController::SubprocessSig
; so the structure should be the same
section .sig
global sigIoReadReady:data
sigIoReadReady db 0
global sigArgc:data
sigArgc db 0
global sigArgv:data
sigArgv times 255 db 0
global sigCurrentPath:data
sigCurrentPath times 255 db 0
