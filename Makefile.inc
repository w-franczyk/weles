ASM = nasm
ASM_OPTIONS = -Wall -O0
ASM_CLEAN_TYPICAL = rm -f *.bin; rm -f *.bin.lst

%.bin: %.asm
	$(ASM) $(ASM_OPTIONS) $< -o $(<:.asm=.bin) -l $(<:.asm=.bin.lst)

VIRTUAL_DISK = disk.img
