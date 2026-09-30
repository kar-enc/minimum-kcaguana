//after the original commit the fixes+syntax errors were implemeneted by gpt 6.1
#include "minemu/platform.h"
#include "minemu/printf.h"
#include "minemu/irq.h"
#include "minemu/uart.h"

#define UART_RX_BUFFER_SIZE 64U


static uint8_t rx_buffer[UART_RX_BUFFER_SIZE];
static uint32_t head;
static uint32_t tail;
static uint32_t overflow_count;

void uartStart(void) {
    //initialzing everything for the UART
    head = 0;
    tail = 0;
    overflow_count = 0;

    MINEMU_UART0->control = MINEMU_UART_CONTROL_RX_IRQ_ENABLE;
    MINEMU_INTERRUPT->enable = UINT32_C(1) << MINEMU_IRQ_UART0;
}

void uartInterrupt(void) {
    while ((MINEMU_UART0->status & MINEMU_UART_STATUS_RX_READY) != 0U) {
        uint8_t data = (uint8_t)MINEMU_UART0->rx_data;
        uint32_t next = (head + 1U) % UART_RX_BUFFER_SIZE;
    }

    if (next != tail) {
        rx_buffer[head] = data;
        head = next;
    } else {
        overflow_count = 1;  // A byte was lost.
    }
}

int uartReadByte(void) {

    minemu_irq_disable();
    uint8_t data = rx_buffer[tail];

    tail = (tail + 1U) % UART_RX_BUFFER_SIZE;
    
    if (head == tail) {
        return -1; //??
    }
    minemu_irq_enable();
    return 

}
// AI assistance disclosure: This _putchar implementation was generated
// with ChatGPT and reviewed by the author.
void _putchar(char character) {
    while ((MINEMU_UART0->status & MINEMU_UART_STATUS_TX_READY) == 0U) {
    }
    MINEMU_UART0->tx_data = (uint32_t)(unsigned char)character;
}