KERN_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
include $(KERN_DIR)/../Makefile.inc

GCCFLAGS := $(GCCFLAGS) -DWELES_KERNEL
GXXFLAGS := $(GXXFLAGS) -DWELES_KERNEL

INCLUDE_DIR := -I $(ROOT_DIR)/kernel -I $(ROOT_DIR)/kernel/libk/include
