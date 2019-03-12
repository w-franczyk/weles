NASM = nasm
NASM_OPT = -Wall -O0

SRC = $(wildcard *.asm)
OUT = bootstrap.bin

$(OUT): *.asm
	$(NASM) $(NASM_OPT) $< -o $@ -l $@.lst

build: $(OUT)

build-vdisk:
	./mount.sh
	sudo cp $(OUT) /mnt/boot/bootstrp.bin
	./umount.sh
