include ../../Makefile.inc

BOOTSTRAP_BINARY = bootstrap.bin
BOOTSTRAP_OBJECT = bootstrap_high.o
BOOTSTRAP_SRC = bootstrap.cpp

$(BOOTSTRAP_OBJECT): $(BOOTSTRAP_SRC)
	i686-elf-g++ -I../ -c $(BOOTSTRAP_SRC) -o $(BOOTSTRAP_OBJECT) -ffreestanding -Wall -Wextra -fno-exceptions -fno-rtti -masm=intel

$(BOOTSTRAP_BINARY): $(BOOTSTRAP_OBJECT) bootstrap_low.o bootstrap.ld
	i686-elf-g++ -T bootstrap.ld -o $(BOOTSTRAP_BINARY) -ffreestanding -nostdlib $(BOOTSTRAP_OBJECT) bootstrap_low.o -lgcc

build: $(BOOTSTRAP_BINARY)

vdisk: build
	./mount.sh
	sudo cp $(BOOTSTRAP_BINARY) /mnt/boot/bootstrp.bin
	./umount.sh

clean:
	$(ASM_CLEAN_TYPICAL)
	-./umount.sh


bootstrap_low.o: bootstrap.asm
	$(ASM) $(ASM_OPTIONS) -felf32 $< -o bootstrap_low.o -l bootstrap_low.o.lst
