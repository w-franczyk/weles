section .text
extern _Z5kmainv
section .bootstrap
global _start:function
_start:
  call _Z5kmainv
