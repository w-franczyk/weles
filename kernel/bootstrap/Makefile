include ../../Makefile.inc

BOOTSTRAP_BINARY = bootstrap.bin

build: $(BOOTSTRAP_BINARY)

vdisk: build
	./mount.sh
	sudo cp $(BOOTSTRAP_BINARY) /mnt/boot/bootstrp.bin
	./umount.sh

clean:
	$(ASM_CLEAN_TYPICAL)
	-./umount.sh
