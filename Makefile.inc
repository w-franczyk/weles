# USEFUL VARS DEFINITIONS ==============================================================
SHELL := /bin/bash
ROOT_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
BIN_DIR := $(ROOT_DIR)/bin
BIN_LIB_DIR := $(BIN_DIR)/lib
BUILD_DIR := ./build
DISK_IMAGE := $(ROOT_DIR)/disk.img

H_FILES := $(wildcard *.h)
SRC_FILES := $(wildcard *.cpp) $(wildcard *.s) $(wildcard *.c)
OBJ_FILES := $(SRC_FILES:.cpp=.o)
OBJ_FILES := $(OBJ_FILES:.s=.o)
OBJ_FILES := $(OBJ_FILES:.c=.o)
OBJ_FILES := $(addprefix $(BUILD_DIR)/,$(OBJ_FILES))

GCC := i686-elf-gcc
GCCFLAGS := -ffreestanding -Wall -Wextra -Werror -masm=intel -m32 -g
GXX := i686-elf-g++
GXXFLAGS := $(GCCFLAGS) -fno-rtti -fno-exceptions -fno-threadsafe-statics -m32 -g -Wall -Wextra -Werror 
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
COMPILE_CPP = $(GXX) $(INCLUDE_DIR) -c $< -o $(BUILD_DIR)/$(<:.cpp=.o) $(GXXFLAGS)
$(BUILD_DIR)/%.o: %.cpp
	mkdir -p $(BUILD_DIR)
	$(COMPILE_CPP)

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(BUILD_DIR)
	$(GCC) $(INCLUDE_DIR) -c $< -o $(BUILD_DIR)/$(<:.c=.o) $(GCCFLAGS)

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
