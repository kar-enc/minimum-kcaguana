#ifndef MINEMU_UART_H
#define MINEMU_UART_H
#define UART_NO_DATA (-1)
#define UART_INPUT_LOST (-2)

void uartStart(void);
void uartInterrupt(void);
void uartReadByte(void);

#endif 