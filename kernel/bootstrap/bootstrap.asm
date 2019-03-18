section .text
global p:function
p:
  push eax
  mov eax, 0xb8000
  mov [eax], BYTE 'C'
  mov eax, 0xb8001
  mov [eax], BYTE 0x1b
  pop eax
  ret
