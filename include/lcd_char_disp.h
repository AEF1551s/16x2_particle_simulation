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

//Functions
void clear_display();
void return_home();
static void function_set(bool data_lenght, bool display_line, bool font);
static void display_control(bool display, bool cursor, bool blinking);
static void init_sequence();
static bool is_busy();
//PIN set/reset
static inline void set_e_pin()
{
    GPIOC->BSRR = GPIO_BSRR_BS_5;
    // TODO: implement timer
    for (volatile int i = 0; i < 100000; i++)
        ;
}
static inline void set_rw_pin() { GPIOC->BSRR = GPIO_BSRR_BS_6; }
static inline void set_rs_pin() { GPIOC->BSRR = GPIO_BSRR_BS_7; }
static inline void reset_e_pin() { GPIOC->BSRR = GPIO_BSRR_BR_5; }
static inline void reset_rw_pin() { GPIOC->BSRR = GPIO_BSRR_BR_6; }
static inline void reset_rs_pin() { GPIOC->BSRR = GPIO_BSRR_BR_7; }

#endif // LCD_CHAR_DISP_H
