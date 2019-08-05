; syscall definitions:
%define SYS_PUTCHAR 0xffffffff
%define SYS_FILEDELETE 0xfffffffd
%define SYS_FILEREAD 0xfffffffc
%define SYS_FILEWRITE 0xfffffffb
%define SYS_STDIN 0xfffffffa
%define SYS_STDOUT 0xfffffff9
%define SYS_GETDIRCONTENTS 0xfffffff8
%define SYS_STAT 0xfffffff7

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

; param: const char* path
; ret: void
global sysFileDelete
sysFileDelete:
  push ebp
  mov ebp, esp
  pusha

  %define PATH ebp + 8
  mov eax, SYS_FILEDELETE
  mov ebx, [PATH]
  int 0x80

  popa
  pop ebp
  ret

; param: const char* path
; ret: int, read size if positive, error if negative
global sysFileRead
sysFileRead:
  push ebp
  mov ebp, esp

  push DWORD 0
  %define RET_VAL ebp - 4

  pusha

  %define PATH ebp + 8
  %define OUT_BUF ebp + 12
  %define MAX_BUF_SIZE ebp + 16
  mov eax, SYS_FILEREAD
  mov ebx, [PATH]
  mov ecx, [OUT_BUF]
  mov edx, [MAX_BUF_SIZE]
  lea edi, [RET_VAL]
  int 0x80

  popa
  pop eax ; RET_VAL
  pop ebp
  ret

; param: const char* path
; ret: int, write size if positive, error if negative
global sysFileWrite
sysFileWrite:
  push ebp
  mov ebp, esp

  push DWORD 0
  %define RET_VAL ebp - 4

  pusha

  %define PATH ebp + 8
  %define BUF ebp + 12
  %define SIZE ebp + 16
  mov eax, SYS_FILEWRITE
  mov ebx, [PATH]
  mov ecx, [BUF]
  mov edx, [SIZE]
  lea edi, [RET_VAL]
  int 0x80

  popa
  pop eax ; RET_VAL
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

; param: const char* path, char* outBuf, unsigned outBufSize
; ret: int (eax)
global sysGetDirContents
sysGetDirContents:
  push ebp
  mov ebp, esp
  pusha

  %define PATH ebp + 8
  %define OUT_BUF ebp + 12
  %define OUT_BUF_SIZE ebp + 16
  xor eax, eax
  mov eax, SYS_GETDIRCONTENTS
  xor ebx, ebx
  mov ebx, [PATH]
  xor ecx, ecx
  mov ecx, [OUT_BUF]
  xor edx, edx
  mov edx, [OUT_BUF_SIZE]
  int 0x80

  popa
  pop ebp
  ret

; param: const char* path
; ret: bool (eax)
global sysStat
sysStat:
  push ebp
  mov ebp, esp

  push DWORD 0
  %define RET_VAL ebp - 4

  pusha

  %define PATH ebp + 8
  xor eax, eax
  mov eax, SYS_STAT
  xor ebx, ebx
  mov ebx, [PATH]
  lea ecx, [RET_VAL]
  int 0x80

  popa
  pop eax ; RET_VAL
  pop ebp
  ret
