#if !defined(SIPO_SREG_H)
#define SIPO_SREG_H

// CMSIS
#include <stm32f410rx.h>
#include <stm32f4xx.h>
// STD
#include <stdbool.h>

/*
SER before SRCLK high is 20ns. AHB1 period is 10ns
Without compiler optimization still works because each function takes more than 1 period. Maybe add NOP
Everything works on rising edge

Pins
GPIOC PIN0 - SER - Serial In
GPIOC PIN1 - OE - Output Enable (Low to enable)
GPIOC PIN2 - RCLK - Register Clock
GPIOC PIN3 - SRCLK - Shift Register Clock
GPIOC PIN4 - SRCLR - Shift Register Clear
SR outputs - QA-QH (0-7) MSB!
*/

// BSRR registers for enabling GPIO pins used in bit shift register
void shift_register_init();
void shift_register_enable();
void shift_register_disable();
void output_shift_register(uint8_t *data, uint32_t length);

// Possible to use #define, but this is safer and only in header scope
//  All pins are GPIO PORT C
//  SET PINS
static inline void set_ser_pin() { GPIOC->BSRR = GPIO_BSRR_BS_0; }
static inline void set_oe_pin() { GPIOC->BSRR = GPIO_BSRR_BS_1; }
static inline void set_rclk_pin() { GPIOC->BSRR = GPIO_BSRR_BS_2; }
static inline void set_srclk_pin() { GPIOC->BSRR = GPIO_BSRR_BS_3; }
static inline void set_srclr_pin() { GPIOC->BSRR = GPIO_BSRR_BS_4; }
// RESET PINS
static inline void reset_ser_pin() { GPIOC->BSRR = GPIO_BSRR_BR_0; }
static inline void reset_oe_pin() { GPIOC->BSRR = GPIO_BSRR_BR_1; }
static inline void reset_rclk_pin() { GPIOC->BSRR = GPIO_BSRR_BR_2; }
static inline void reset_srclk_pin() { GPIOC->BSRR = GPIO_BSRR_BR_3; }
static inline void reset_srclr_pin() { GPIOC->BSRR = GPIO_BSRR_BR_4; }
#endif // SIPO_SREG_H
