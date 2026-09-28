#include "minemu/platform.h"
#include "minemu/printf.h"

// AI assistance disclosure: This _putchar implementation was generated
// with ChatGPT and reviewed by the author.
void _putchar(char character) {
    while ((MINEMU_UART0->status & MINEMU_UART_STATUS_TX_READY) == 0U) {
    }
    MINEMU_UART0->tx_data = (uint32_t)(unsigned char)character;
}