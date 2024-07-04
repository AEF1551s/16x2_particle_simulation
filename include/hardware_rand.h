#if !defined(HARDWARE_RAND_H)
#define HARDWARE_RAND_H

// CMSIS
#include <stm32f410rx.h>
#include <stm32f4xx.h>
// STD
#include <stdbool.h>
#include <stdlib.h>
// USER
#include <lcd_char_disp.h>

/*
Generated random number using STM32F4 RNG and interrupts
*/

static bool drrdy_flag = false;
static uint32_t rand_int = 0;

void hard_rand_init();
uint32_t random_uint32();

#endif // HARDWARE_RAND_H
