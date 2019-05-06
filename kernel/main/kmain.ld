OUTPUT_FORMAT(elf32-i386)
ENTRY(_start)
/* TODO: finish him! (the rest of sections) */
SECTIONS
{
  /* . = 1K; */
  . = 0x10400;
  .text 0x10400 : AT(0x10400) {
    code = .;
    *(.bootstrap)
    *(.text)
    *(.rodata)
    . = ALIGN(4096);
  }
}
