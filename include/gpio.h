#if !defined(GPIO_H)
#define GPIO_H

// CMSIS
#include <stm32f410rx.h>
#include <stm32f4xx.h>

/*
Used to configure GPIO pins. 
!!Every function is defined by user manually!!
*/

// Enable clock for used pins
static void clock_init();
// Confiure used pins
static void pin_init();
// Locks configuration
static void lock();

// Initialize GPIO pins
void gpio_init();

#endif // GPIO_H
