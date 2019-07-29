section .text
extern main
section .crt0
global _start:function
_start:
  call main
  ret

; 512 bytes max!!
section .sig
global sigIoReadReady:data
sigIoReadReady db 0 ; ioReadReady
