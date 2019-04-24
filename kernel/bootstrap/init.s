section .text
extern _Z5bmainv
section .bootstrap_init
global _start:function
_start:
  call _Z5bmainv
