include ../Makefile.inc

STAGE1_BINARY = stage1.bin
STAGE2_BINARY = stage2.bin

build: $(STAGE1_BINARY) $(STAGE2_BINARY)

vdisk: build
	./stage1.sh $(STAGE1_BINARY) ../$(VIRTUAL_DISK)
	./stage2.sh $(STAGE2_BINARY) ../$(VIRTUAL_DISK)

clean:
	$(ASM_CLEAN_TYPICAL)
