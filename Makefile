include Makefile.inc

.PHONY: build clean vdisk
build clean vdisk:
	$(MAKE) -C lib $@
	$(MAKE) -C bootloader $@
	$(MAKE) -C kernel $@
	$(MAKE) -C user $@

.PHONY: doxy
doxy: $(ROOT_DIR)/Doxyfile
	doxygen $(ROOT_DIR)/Doxyfile
