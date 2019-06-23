.PHONY: build clean vdisk
build clean vdisk:
	$(MAKE) -C lib $@
	$(MAKE) -C bootloader $@
	$(MAKE) -C kernel $@
