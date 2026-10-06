#include "minemu/user_abi.h"

minemu_ioctl_assembly:
    sub sp, sp, #8
    //was initially missing return isntruc
    str r7, [sp]
    str lr, [sp, #4]
    mov r7, #MINEMU_SYSCALL_IOCTL
    svc #0
    ldr lr, [sp, #4]
    ldr r7, [sp]
    add sp, sp, #8
    bx lr


