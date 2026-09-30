// AI assistance disclosure: This UART implementation was generated
// with ChatGPT and should be reviewed by the author.
#include "minemu/platform.h"
#include "minemu/printf.h"
#include "minemu/irq.h"
#include "minemu/uart.h"

#define UART_RX_BUFFER_SIZE (MINEMU_UART_RX_CAPACITY + 1U)

static uint8_t rx_buffer[UART_RX_BUFFER_SIZE];
static uint32_t head;
static uint32_t tail;
static uint32_t input_lost;
static uint32_t discard_until_newline;

static uint32_t next_index(uint32_t index) {
    ++index;
    return index == UART_RX_BUFFER_SIZE ? 0U : index;
}

void uartStart(void) {
    head = 0U;
    tail = 0U;
    input_lost = 0U;
    discard_until_newline = 0U;

    MINEMU_UART0->control |= MINEMU_UART_CONTROL_RX_IRQ_ENABLE;
    MINEMU_INTERRUPT->enable |= UINT32_C(1) << MINEMU_IRQ_UART0;
}

void uartInterrupt(void) {
    while ((MINEMU_UART0->status & MINEMU_UART_STATUS_RX_READY) != 0U) {
        uint8_t data = (uint8_t)MINEMU_UART0->rx_data;

        if (discard_until_newline != 0U) {
            if (data == (uint8_t)'\n') {
                discard_until_newline = 0U;
            }
            continue;
        }

        uint32_t next = next_index(head);
        if (next == tail) {
            /* The buffer is full. Drop its contents and the rest
               of the current input line. */
            head = tail;
            input_lost = 1U;
            discard_until_newline = data != (uint8_t)'\n';

            continue;
        
        }

        rx_buffer[head] = data;
        head = next;
    }
}

int uartReadByte(void) {
    uint32_t cpsr;
    int result;

    __asm__ volatile("mrs %0, cpsr" : "=r"(cpsr) : : "memory");
    minemu_irq_disable();

    if (discard_until_newline != 0) {
        result = UART_NO_DATA;
    } else if (input_lost != 0U) {
        input_lost = 0U;
        result = UART_INPUT_LOST;
    } else if (head == tail) {
        result = UART_NO_DATA;
    } else {
        result = (int)rx_buffer[tail];
        tail = next_index(tail);
    }

    /* Restore the previous IRQ state; do not enable IRQs if the
       caller already had them disabled. */
    if ((cpsr & UINT32_C(0x80)) == 0U) {
        minemu_irq_enable();
    }

    return result;
}

void _putchar(char character) {
    while ((MINEMU_UART0->status & MINEMU_UART_STATUS_TX_READY) == 0U) {
    }
    MINEMU_UART0->tx_data = (uint32_t)(unsigned char)character;
}