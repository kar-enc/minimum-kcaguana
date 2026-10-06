#include "minemu/user_abi.h

int32_t minemu_ioctl_assembly(int fd,int op, int32_t arg, int32_t arg2);

int32_t minemu_ioctl(int fd, int32_t op, ...) {
    int32_t arg = 0;
    int32_t arg2 = 0;

    if (fd == MINEMU_FD_RNG_TASK) {
        if (op == MINEMU_OP_RNG_SET_SEED) {
            //need unsigned int seed
        } else if (op == MINEMU_OP_RNG_GET_DATA) {
            //need unsigned int *data
        }
    } else if (fd == MINEMU_FD_UART0) {
        if (op == MINEMU_OP_UART_READ) {
            //need char *dst, int n
        } else if (op == MINEMU_OP_UART_WRITE) {
            //need char *src, int n
        }
        
    } else if (fd == MINEMU_FD_UART1) {
        if (op == MINEMU_OP_UART_READ) {
            //need char *dst, int n
        } else if (op == MINEMU_OP_UART_WRITE) {
            //need char *src, int n
        }
    } else if (fd == MINEMU_FD_TRACE_TASK) {
        if (op == MINEMU_OP_TRACE_EVENT) {
            //need unsigned int value
        }
    }
}
