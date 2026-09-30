#include "minemu/msh.h"
#include "minemu/uart.h"
#include "minemu/printf.h"

void executeLine(char *line) {
    /* Implement the command execution logic here. */
}
void mshStart(void) {
    char line[21];             /* 20 bytes plus the terminating '\0' */
    unsigned int length = 0U;
    unsigned int excess = 0U;


    printf("msh> ");

    for (;;) {
        int value = uartReadByte();

        if (value == UART_NO_DATA) {
            continue;
        }

        if (value == UART_INPUT_LOST) {
            length = 0U;
            excess = 0U;
            line[0] = '\0';
            /* Reset any overlong-line state you add later. */
            printf("\ninput lost; line discarded\nmsh> ");
            continue;
        }

        if (value == '\n') {
            line[length] = '\0';

            if (excess != 0U) {
                printf("too long\n");
            } else {
                executeLine(line);
            }

            length = 0U;
            excess = 0U;
            printf("msh> ");
            continue;
        }

        //backspace
        if (value == 0x08 || value == 0x7F) {
            if (excess != 0U) {
                excess--;
            } else if (length != 0U) {
                length--;
                line[length] = '\0';
            }
            continue;
        }

        //if lines over 20 bytes
        
        if (length < 20U) {
            line[length] = (char)value;
            length++;
        } else {
            excess++;
        }
    }
}