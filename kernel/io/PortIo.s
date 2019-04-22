; param: port, value
; ret: void
global outb
outb:
  push ebp
  mov ebp, esp
  pusha

  %define PORT ebp + 8
  %define VALUE ebp + 12
  mov dx, [PORT]
  mov al, [VALUE]
  out dx, al


  popa
  pop ebp
  ret

; param: port
; ret: al
global inb
inb:
  xor eax, eax
  push edx
  mov dx, [esp + 8] ; port param
  in al, dx
  pop edx
  ret

; param: port, outBuff, count
; ret: void
global inwn
inwn:
  push ebp
  mov ebp, esp
  pusha

  %define PORT ebp + 8
  %define OUTBUFF ebp + 12
  %define COUNT ebp + 16

  xor edi, edi
  xor edx, edx
  xor ecx, ecx
  mov edi, [OUTBUFF]
  mov dx, [PORT]
  mov cx, [COUNT]
  rep insw

  popa
  pop ebp
  ret
