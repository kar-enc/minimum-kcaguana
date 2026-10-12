#include <stdint.h>
#include "minemu/user_abi.h"


void minemu_user_main(void) {
    // static char message[] = "hello world\n";
    // (void)ioctl(MINEMU_FD_UART0, MINEMU_OP_UART_WRITE, message, sizeof(message)-1U);

    // for (;;) {
    //     __asm__ volatile("nop");
    // }
    minemu_trace_event(1);
    uartStart();
    mshStart();
}
