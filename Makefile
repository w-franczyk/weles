MODULES = bootloader kernel

.PHONY: build
build: $(MODULES)
	$(MAKE) -C $<

.PHONY: all
all: build

.PHONY: build-vdisk
build-vdisk:
	for dir in $(MODULES); do \
	  (cd $$dir; ${MAKE} build-vdisk); \
	done

.PHONY: vdisk
vdisk: build build-vdisk



#.PHONY
