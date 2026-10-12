#updated with gpt6.1 sol
MINEMU ?= minemu

IMAGE := build/minimum.img
KERNEL := ../kernel/build/minimum-kernel.elf
USER_PROGRAM := ../user/prog/minimum-user/build/minimum-user.elf

.PHONY: all clean FORCE

all: $(IMAGE)

$(KERNEL): FORCE
	$(MAKE) -C ../kernel all

$(USER_PROGRAM): FORCE
	$(MAKE) -C ../user/prog/minimum-user all

FORCE:

$(IMAGE): minimum.toml $(KERNEL) $(USER_PROGRAM)
	@mkdir -p $(dir $@)
	$(MINEMU) image minimum.toml --output $@

clean:
	rm -rf build