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
