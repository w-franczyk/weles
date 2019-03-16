.PHONY: build clean vdisk
build clean vdisk:
	$(MAKE) -C bootloader $@
	$(MAKE) -C kernel $@
