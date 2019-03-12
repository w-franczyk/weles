MODULES = bootloader kernel

.PHONY: build
build:
	for dir in $(MODULES); do \
	  (cd $$dir; ${MAKE}); \
	done

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
