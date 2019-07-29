OUTPUT_FORMAT(elf32-i386)
ENTRY(_start)
SECTIONS
{
  . = 1K;
  .sig 0x100400 : AT(0x100400) {}
  .text 0x100600 : AT(0x100600) {
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
