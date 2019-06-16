global halt
halt:
  cli
  hlt

; param: uint8_t* pageDirectory
; ret: none
global enablePaging
enablePaging:
  %define PAGE_DIRECTORY esp + 4
  mov eax, [PAGE_DIRECTORY]
  mov cr3, eax

  mov eax, cr0
  or eax, 0x80000001 ; enable PG and PE (paging & protection) bits 
  mov cr0, eax

  ret
