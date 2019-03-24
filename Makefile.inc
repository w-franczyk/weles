ROOT_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
BIN_DIR := $(ROOT_DIR)/bin
BIN_LIB_DIR := $(ROOT_DIR)/bin/lib
BUILD_DIR := ./build

SRC_FILES := $(wildcard *.cpp) $(wildcard *.s)
OBJ_FILES := $(SRC_FILES:.cpp=.o)
OBJ_FILES := $(OBJ_FILES:.s=.o)
OBJ_FILES := $(addprefix $(BUILD_DIR)/,$(OBJ_FILES))

GCC := i686-elf-g++
INCLUDE_DIR := $(ROOT_DIR)/kernel
GCCFLAGS := -fPIC -ffreestanding -Wall -Wextra -fno-exceptions -fno-rtti -masm=intel -m32
LDFLAGS := -fPIC -ffreestanding -nostdlib -m32
LIBS := -lgcc

ASM := nasm
ASMFLAGS += -Wall -O0
ASM_CLEAN_TYPICAL := rm -f *.o; rm -f *.bin; rm -f *.bin.lst; rm -rf $(BUILD_DIR)

$(BUILD_DIR)/%.o: %.cpp
	mkdir -p $(BUILD_DIR)
	$(GCC) -I $(INCLUDE_DIR) -c $< -o $(BUILD_DIR)/$(<:.cpp=.o) $(GCCFLAGS)

$(BUILD_DIR)/%.o: %.s
	mkdir -p $(BUILD_DIR)
	$(ASM) $(ASMFLAGS) -felf32 $< -o $(BUILD_DIR)/$(<:.s=.o)

%.bin: %.asm
	$(ASM) $(ASMFLAGS) $< -o $(<:.asm=.bin) -l $(<:.asm=.bin.lst)

VIRTUAL_DISK = disk.img
