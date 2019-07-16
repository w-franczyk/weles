section .text
extern main
section .crt0
global _start:function
_start:
  call main
  ret
