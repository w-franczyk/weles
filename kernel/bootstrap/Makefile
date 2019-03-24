include ../../Makefile.inc

BOOTSTRAP_BINARY := bootstrap.bin
LIBS += -lIo

build: $(BOOTSTRAP_BINARY)

$(BOOTSTRAP_BINARY): $(OBJ_FILES)
	$(GCC) -T bootstrap.ld -o $(BOOTSTRAP_BINARY) $(LDFLAGS) $(OBJ_FILES) $(LIBS)

vdisk: build
	./mount.sh
	sudo cp $(BOOTSTRAP_BINARY) /mnt/boot/bootstrp.bin
	./umount.sh

clean:
	$(ASM_CLEAN_TYPICAL)
	-./umount.sh
