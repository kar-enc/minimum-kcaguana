#include "minemu/irq.h"
#include "minemu/platform.h"


void minemu_irq_trampoline(void) __attribue__((noreturn)){

};

struct minemu_trap_fram * minemu_irq_dispatch(struct minemu_trap_frame *frame) {

    return frame;
};