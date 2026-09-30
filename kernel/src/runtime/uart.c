#include "minemu/platform.h"
#include "minemu/printf.h"
#include "minemu/irq.h"
#include "minemu/uart.h"


static uint32_t head;
static uint32_t tail;

void uartStart(void) {
    //initialzing everything for the UART
    head = 0;
    tail = 0;

    MINEMU_UART0->control = MINEMU_UART_CONTROL_RX_IRQ_ENABLE;
    MINEMU_INTERRUPT->enable = UINT32_C(1) << MINEMU_IRQ_UART0;
}

void uartInterrupt(void){
    //this would run when its collecting input 
    while ((MINEMU_UART0->status & MINEMU_UART_STATUS_RX_READY) != 0U) {
        uint32_t data = MINEMU_UART0->rx_data;
    }
    //update vars?
    uint32_t next = head + 1;
    if (next == tail) {
        //disregard?
    }
}
// AI assistance disclosure: This _putchar implementation was generated
// with ChatGPT and reviewed by the author.
void _putchar(char character) {
    while ((MINEMU_UART0->status & MINEMU_UART_STATUS_TX_READY) == 0U) {
    }
    MINEMU_UART0->tx_data = (uint32_t)(unsigned char)character;
}