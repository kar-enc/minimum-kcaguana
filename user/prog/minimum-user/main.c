#include <stdint.h>
#include "minemu/user_abi.h"


void minemu_user_main(void) {
    static const char message[] = "hello world\n";
    (void)iotcl(MINEMU_FD_UART_OUT, MINEMU_IOCTL_UART_WRITE, message, sizeof(message));

    for (;;) {
        __asm__ volatile("nop");
    }
}
