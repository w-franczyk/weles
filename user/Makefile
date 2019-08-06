include MakefileUser.inc

clean: clean-builds clean-output
	$(MAKE) -C echo $@
	$(MAKE) -C write $@
	$(MAKE) -C pwd $@
	$(MAKE) -C ls $@
	$(MAKE) -C cd $@
	$(MAKE) -C cat $@
	$(MAKE) -C rm $@

build: $(BUILD_DIR)/crt0.o
	$(MAKE) -C echo $@
	$(MAKE) -C write $@
	$(MAKE) -C pwd $@
	$(MAKE) -C ls $@
	$(MAKE) -C cd $@
	$(MAKE) -C cat $@
	$(MAKE) -C rm $@

vdisk: build
	$(ROOT_DIR)/util/mount.sh $(DISK_IMAGE)
	sudo mkdir -p /mnt/bin
	sudo cp $(BIN_USR_DIR)/* /mnt/bin/
	$(ROOT_DIR)/util/umount.sh
