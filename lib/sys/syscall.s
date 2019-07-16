; syscall definitions:
%define SYS_PUTCHAR 0xffffffff


; param: char
; ret: void
global sysPutchar
sysPutchar:
  push ebp
  mov ebp, esp
  pusha

  %define CHAR ebp + 8
  xor eax, eax
  mov eax, SYS_PUTCHAR
  xor ebx, ebx
  mov ebx, [CHAR]
  int 0x80

  popa
  pop ebp
  ret
