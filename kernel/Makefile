# the order is important!
.PHONY: build clean vdisk
build clean vdisk:
	$(MAKE) -C io $@
	$(MAKE) -C thirdparty/fatfs $@
	$(MAKE) -C main $@
