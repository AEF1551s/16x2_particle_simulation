#if !defined(LCD_CHAR_DISP_H)
#define LCD_CHAR_DISP_H

// CMSIS
#include <stm32f410rx.h>
#include <stm32f4xx.h>
// STD
#include <stdbool.h>
// Hardware
#include <sipo_sreg.h>

// Uses SIPO shift register to write D0-D7 pins

// GPIOC PIN5 - E - Chip Enable Signal
// GPIOC PIN6 - R/W - H: Read(MPU(Module) L: Write(MPU(Module) - Used
// GPIOC PIN7 - RS - H: DATA, L: Instruction code

void lcd_char_disp_init();
// void clear_display();
// static bool is_busy();

static inline void set_e_pin()
{
    GPIOC->BSRR = GPIO_BSRR_BS_5;
    //TODO: implement timer
    for (volatile int i = 0; i < 100000; i++)
        ;
}
static inline void set_rw_pin() { GPIOC->BSRR = GPIO_BSRR_BS_6; }
static inline void set_rs_pin() { GPIOC->BSRR = GPIO_BSRR_BS_7; }
static inline void reset_e_pin() { GPIOC->BSRR = GPIO_BSRR_BR_5; }
static inline void reset_rw_pin() { GPIOC->BSRR = GPIO_BSRR_BR_6; }
static inline void reset_rs_pin() { GPIOC->BSRR = GPIO_BSRR_BR_7; }

#endif // LCD_CHAR_DISP_H
