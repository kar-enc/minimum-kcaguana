//updated with gpt6.1 sol
KERNEL_EXAMPLES := \
	mmio-basics \
	svc-context-switch \
	irq-context-switch

.PHONY: all runtime kernel-examples user-mode-hello clean $(KERNEL_EXAMPLES)

all: kernel-examples

kernel-examples: $(KERNEL_EXAMPLES)

runtime:
	$(MAKE) -C ../kernel runtime

$(KERNEL_EXAMPLES): runtime
	$(MAKE) -C $@ all

user-mode-hello:
	$(MAKE) -C user-mode-hello image

clean:
	@for example in $(KERNEL_EXAMPLES); do $(MAKE) -C $$example clean; done
	$(MAKE) -C user-mode-hello clean