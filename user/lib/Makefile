#updated with gpt6.1 sol
ARM_PREFIX ?= arm-none-eabi-
CC := $(ARM_PREFIX)gcc
AR := $(ARM_PREFIX)ar

BUILD := build
LIBRARY := $(BUILD)/libminimum_user.a

SOURCES_C := $(wildcard src/*.c)
SOURCES_S := $(wildcard src/*.S)

OBJECTS := $(patsubst src/%.c,$(BUILD)/%.o,$(SOURCES_C)) \
	$(patsubst src/%.S,$(BUILD)/%.o,$(SOURCES_S))

DEPENDENCIES := $(OBJECTS:.o=.d)

ARCH_FLAGS := -mcpu=cortex-a9 -marm -mfloat-abi=soft
CPPFLAGS := -Iinclude -I../../kernel/include

CFLAGS := $(ARCH_FLAGS) -ffreestanding -fno-builtin -fdata-sections \
	-ffunction-sections -fno-stack-protector -std=c11 \
	-Wall -Wextra -Werror -MMD -MP

ASFLAGS := $(ARCH_FLAGS) -ffreestanding -MMD -MP

.PHONY: all clean

all: $(LIBRARY)

$(LIBRARY): $(OBJECTS) Makefile
	@mkdir -p $(dir $@)
	rm -f $@
	$(AR) rcs $@ $(OBJECTS)

$(BUILD)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BUILD)/%.o: src/%.S
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(ASFLAGS) -c $< -o $@

$(OBJECTS): Makefile

clean:
	rm -rf $(BUILD)

-include $(DEPENDENCIES)