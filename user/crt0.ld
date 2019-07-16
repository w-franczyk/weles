OUTPUT_FORMAT(elf32-i386)
ENTRY(_start)
SECTIONS
{
  . = 1K;
  /* . = 0x100000; */
  .text 0x100400 : AT(0x100400) {
    code = .;
    *(.crt0)
    *(.text)
    *(.data)
    *(.bss)
    *(.rodata)
    *(.eh_frame)
    . = ALIGN(4096);
  }
}
