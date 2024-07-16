#if !defined(SERIAL_COM_H)
#define SERIAL_COM_H

// CMSIS
#include <stm32f410rx.h>
#include <stm32f4xx.h>
// STD
#include <stdio.h>
// USER
#include <uart2.h>

/*
UART2 (USART2) interface with ST-LINK
Uses pins PA2, PA3
*/

#ifndef NDEBUG
// Do only when debug is enabled with #define NDEBUG before serial_com.h or compiler flag -DNDEBUG

void serial_com_init();
int _write(int file, char *ptr, int len);

#endif // end NDEBUG

#endif // SERIAL_COM_H
