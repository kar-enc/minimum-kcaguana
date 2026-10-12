#include "minemu/user_abi.h"
#include <stdarg.h>

int32_t minemu_ioctl_assembly(int fd, uint32_t op, uint32_t arg, uint32_t arg2);

int32_t ioctl(int fd, uint32_t op, ...) {
    uint32_t arg = 0;
    uint32_t arg2 = 0;
    va_list args;
    va_start(args, op);

    int error = 0;

    if (fd == MINEMU_FD_RNG_TASK) {
        if (op == MINEMU_OP_RNG_SET_SEED) {
            //need unsigned int seed
            arg = va_arg(args, unsigned int);
        } else if (op == MINEMU_OP_RNG_GET_DATA) {
            //need unsigned int *data
            arg = va_arg(args, unsigned int *);
        } else {
            error = 1;
        }
    } else if (fd == MINEMU_FD_UART0) {
        if (op == MINEMU_OP_UART_READ) {
            //need char *dst, int n
            arg = va_arg(args, char *);
            arg2 = va_arg(args, int);
        } else if (op == MINEMU_OP_UART_WRITE) {
            //need char *src, int n
            arg = va_arg(args, char *);
            arg2 = va_arg(args, int);
        } else {
            error = 1;
        }
        
    } else if (fd == MINEMU_FD_UART1) {
        if (op == MINEMU_OP_UART_READ) {
            //need char *dst, int n
            arg = va_arg(args, char *);
            arg2 = va_arg(args, int);
        } else if (op == MINEMU_OP_UART_WRITE) {
            //need char *src, int n
            arg = va_arg(args, char *);
            arg2 = va_arg(args, int);
        } else {
            error = 1;
        }
    } else if (fd == MINEMU_FD_TRACE_TASK) {
        if (op == MINEMU_OP_TRACE_EVENT) {
            //need unsigned int value
            arg = va_arg(args, unsigned int);
        } else {
            error = 1;
        }
    } if (fd == MINEMU_FD_RNG_TASK) {
        if (op == MINEMU_OP_RNG_SET_SEED) {
            //need unsigned int seed
            arg = va_arg(args, unsigned int);
        } else if (op == MINEMU_OP_RNG_GET_DATA) {
            //need unsigned int *data
            arg = va_arg(args, unsigned int *);
        } else {
            error = 1;
        }
    } 
    //interface for tests
        else if (fd == MINEMU_FD_UART_IN) {
        if (op == MINEMU_IOCTL_UART_READ) {
            // Need void *dst, unsigned int n
            arg = (uint32_t)(uintptr_t)va_arg(args, void *);
            arg2 = va_arg(args, unsigned int);
        } else {
            error = 1;
        }
    } else if (fd == MINEMU_FD_UART_OUT) {
        if (op == MINEMU_IOCTL_UART_WRITE) {
            // Need void *src, unsigned int n
            arg = (uint32_t)(uintptr_t)va_arg(args, void *);
            arg2 = va_arg(args, unsigned int);
        } else {
            error = 1;
        }
    } else if (fd == MINEMU_FD_RNG) {
        if (op == MINEMU_IOCTL_RNG_SEED) {
            // Need unsigned int seed
            arg = va_arg(args, unsigned int);
        } else if (op == MINEMU_IOCTL_RNG_NEXT) {
            // Need unsigned int *data
            arg = (uint32_t)(uintptr_t)
                va_arg(args, unsigned int *);
        } else if (op == MINEMU_IOCTL_RNG_STATE) {
            // Need unsigned int *state
            arg = (uint32_t)(uintptr_t)
                va_arg(args, unsigned int *);
        } else {
            error = 1;
        }
    } else if (fd == MINEMU_FD_TRACE) {
        if (op == MINEMU_IOCTL_TRACE_EVENT) {
            // Need unsigned int value
            arg = va_arg(args, unsigned int);
        } else {
            error = 1;
        }
    } else {
        error = 1;
    }
    
    if (error) {
        return MINEMU_IOCTL_ERROR;
    }
    va_end(args);
    return minemu_ioctl_assembly(fd, op, arg, arg2);
}
