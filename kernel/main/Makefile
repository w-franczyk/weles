include ../../Makefile.inc

KERNEL_BINARY := $(BIN_DIR)/kernel.bin
LIBS += -lIo -lFatfs

build: $(KERNEL_BINARY)

$(KERNEL_BINARY): $(OBJ_FILES)
	$(GXX) -T kmain.ld -o $(KERNEL_BINARY) $(LDFLAGS) $(OBJ_FILES) $(LIBS)

vdisk: build
	$(ROOT_DIR)/util/mount.sh
	sudo cp $(KERNEL_BINARY) /mnt/boot/kernel.bin
	$(ROOT_DIR)/util/umount.sh

clean:
	$(ASM_CLEAN_TYPICAL)
	rm -f $(KERNEL_BINARY)
	-./umount.sh
