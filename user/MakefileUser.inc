USER_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
include $(USER_DIR)/../Makefile.inc

GCCFLAGS := $(GCCFLAGS) -DPRINTF_DISABLE_SUPPORT_LONG_LONG
GXXFLAGS := $(GXXFLAGS) -DPRINTF_DISABLE_SUPPORT_LONG_LONG

INCLUDE_DIR := -I $(ROOT_DIR)/lib/libc/include -I $(ROOT_DIR)/lib
BIN_USR_DIR := $(BIN_DIR)/user
LIBS += -lLibc -lSys

ifneq ($(TARGETBIN_NAME),)
TARGETBIN = $(BIN_USR_DIR)/$(TARGETBIN_NAME)

build: $(TARGETBIN)

$(TARGETBIN): $(OBJ_FILES)
	mkdir -p $(BIN_USR_DIR)
	$(GXX) -T $(USER_DIR)/crt0.ld -o $(TARGETBIN) $(LDFLAGS) $(OBJ_FILES) $(USER_DIR)/$(BUILD_DIR)/crt0.o $(LIBS)

clean-output:
	rm -f $(TARGETBIN)
else
clean-output:
endif
