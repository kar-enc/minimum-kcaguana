#updated with gpt6.1 sol
ARM_PREFIX ?= arm-none-eabi-
CC := $(ARM_PREFIX)gcc

USER_DIR := $(abspath $(dir $(lastword $(MAKEFILE_LIST)))/..)
PROGRAM ?= $(notdir $(CURDIR))
BUILD := build
ELF := $(BUILD)/$(PROGRAM).elf

SOURCES_C := $(wildcard *.c)
SOURCES_S := $(wildcard *.S)

OBJECTS := $(patsubst %.c,$(BUILD)/%.o,$(SOURCES_C)) \
	$(patsubst %.S,$(BUILD)/%.o,$(SOURCES_S))

DEPENDENCIES := $(OBJECTS:.o=.d)
USER_LIBRARY := $(USER_DIR)/lib/build/libminimum_user.a

ARCH_FLAGS := -mcpu=cortex-a9 -marm -mfloat-abi=soft
CPPFLAGS := -I$(USER_DIR)/lib/include -I$(USER_DIR)/../kernel/include

CFLAGS := $(ARCH_FLAGS) -ffreestanding -fno-builtin -fdata-sections \
	-ffunction-sections -fno-stack-protector -std=c11 \
	-Wall -Wextra -Werror -MMD -MP

ASFLAGS := $(ARCH_FLAGS) -ffreestanding -MMD -MP

LDFLAGS := $(ARCH_FLAGS) -nostdlib \
	-Wl,-T,$(USER_DIR)/common/user.ld \
	-Wl,--gc-sections \
	-Wl,-Map,$(BUILD)/$(PROGRAM).map

LIBGCC := $(shell $(CC) $(ARCH_FLAGS) -print-libgcc-file-name)

.PHONY: all clean FORCE

all: $(ELF)

# Let the library Makefile check its source and header dependencies.
$(USER_LIBRARY): FORCE
	$(MAKE) -C $(USER_DIR)/lib all

FORCE:

$(ELF): $(OBJECTS) $(USER_LIBRARY) $(USER_DIR)/common/user.ld
	@mkdir -p $(dir $@)
	$(CC) $(LDFLAGS) $(OBJECTS) $(USER_LIBRARY) $(LIBGCC) -o $@

$(BUILD)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BUILD)/%.o: %.S
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(ASFLAGS) -c $< -o $@

$(OBJECTS): Makefile $(USER_DIR)/common/common.mk

clean:
	rm -rf $(BUILD)

-include $(DEPENDENCIES)