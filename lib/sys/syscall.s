; syscall definitions:
%define SYS_PUTCHAR 0xffffffff
%define SYS_FILEOPEN 0xfffffffe
%define SYS_FILECLOSE 0xfffffffd
%define SYS_FILEREAD 0xfffffffc
%define SYS_FILEWRITE 0xfffffffb
%define SYS_STDIN 0xfffffffa
%define SYS_STDOUT 0xfffffff9

; signals
extern sigIoReadReady

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

; param: const char*
; ret: int (eax)
global fileOpen
fileOpen:
  push ebp
  mov ebp, esp
  pusha

  %define PATH ebp + 8
  xor eax, eax
  mov eax, SYS_FILEOPEN
  xor ebx, ebx
  mov ebx, [PATH]
  int 0x80

  popa
  pop ebp
  ret

; param: char
; ret: void
global sysStdin
sysStdin:
  push ebp
  mov ebp, esp
  pusha

  %define DESTINATION ebp + 8
  xor eax, eax
  mov eax, SYS_STDIN
  xor ebx, ebx
  mov ebx, [DESTINATION]
  int 0x80

  .loop:
  cmp BYTE [sigIoReadReady], 1
  jne .loop

  mov BYTE [sigIoReadReady], 0

  popa
  pop ebp
  ret
