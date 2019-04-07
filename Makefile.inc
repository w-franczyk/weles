# USEFUL VARS DEFINITIONS ==============================================================
SHELL := /bin/bash
ROOT_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
BIN_DIR := $(ROOT_DIR)/bin
BIN_LIB_DIR := $(ROOT_DIR)/bin/lib
BUILD_DIR := ./build

H_FILES := $(wildcard *.h)
SRC_FILES := $(wildcard *.cpp) $(wildcard *.s)
OBJ_FILES := $(SRC_FILES:.cpp=.o)
OBJ_FILES := $(OBJ_FILES:.s=.o)
OBJ_FILES := $(addprefix $(BUILD_DIR)/,$(OBJ_FILES))

GCC := i686-elf-g++
INCLUDE_DIR := $(ROOT_DIR)/kernel
GCCFLAGS := -ffreestanding -Wall -Wextra -fno-exceptions -fno-rtti -masm=intel -m32 -g
LDFLAGS := -ffreestanding -nostdlib -m32
LIBS := -L$(BIN_LIB_DIR) -lgcc

ASM := nasm
ASMFLAGS += -Wall -O0
ASM_CLEAN_TYPICAL := rm -f *.o; rm -f *.bin; rm -f *.bin.lst; rm -rf $(BUILD_DIR)

AR := i686-elf-ar
OBJCOPY := i686-elf-objcopy



# TARGETS PER TYPE ==============================================================

ifneq ($(TARGETLIB_NAME),)
TARGETLIB_SUFFIX := .a
TARGETLIB_PREFIX := lib
TARGETLIB = $(BIN_LIB_DIR)/$(TARGETLIB_PREFIX)$(TARGETLIB_NAME)$(TARGETLIB_SUFFIX)

build: $(TARGETLIB)

$(TARGETLIB): $(OBJ_FILES)
	mkdir -p $(BIN_LIB_DIR)
	$(AR) rcs $(TARGETLIB) $(OBJ_FILES)

clean-output:
	rm -f $(TARGETLIB)
else
clean-output:
endif




# GENERAL TARGETS ==============================================================

$(BUILD_DIR)/%.o: %.cpp
	mkdir -p $(BUILD_DIR)
	$(GCC) -I $(INCLUDE_DIR) -c $< -o $(BUILD_DIR)/$(<:.cpp=.o) $(GCCFLAGS)

$(BUILD_DIR)/%.o: %.s
	mkdir -p $(BUILD_DIR)
	$(ASM) $(ASMFLAGS) -felf32 $< -o $(BUILD_DIR)/$(<:.s=.o)

%.bin: %.asm
	$(ASM) $(ASMFLAGS) $< -o $(<:.asm=.bin) -l $(<:.asm=.bin.lst)

vdisk: build

clean-builds:
	rm -rf $(BUILD_DIR);

clean: clean-builds clean-output

VIRTUAL_DISK = disk.img
