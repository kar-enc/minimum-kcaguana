#include "minemu/user_abi.h"

minemu_ioctl:
    sub sp, sp, #4
    str r7, [sp]
    mov r7, #MINEMU_SYSCALL_IOCTL
    svc #0
    ldr r7, [sp]
    add sp, sp, #4


