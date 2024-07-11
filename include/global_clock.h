#if !defined(GLOBAL_CLOCK_H)
#define GLOBAL_CLOCK_H

// CMSIS
#include <stm32f410rx.h>
#include <stm32f4xx.h>

/*
Timer 11 clock used for framerate in main
This timer is used only for interrupts and time count for when to display previosly calculated LCD chars
*/
static void tim11_init();
void frame_time_ms(uint16_t ms);

#endif // GLOBAL_CLOCK_H
