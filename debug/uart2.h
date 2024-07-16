#if !defined(UART2_H)
#define UART2_H

// CMSIS
#include <stm32f410rx.h>
#include <stm32f4xx.h>

/*
USART2 UART communication, used to send and receive data from ST-LINK.
Baudrate 115200b/s
1 start bit (default)
8 data bytes (set)
1 stop bit (set)
PA2 - TX
PA3 - RX
*/
static void uart2_pin_init();

void uart2_init();
void uart2_write(char ch);
char uart2_read();

#endif // UART2_H
