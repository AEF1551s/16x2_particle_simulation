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

// Functions
void clear_display();
void return_home();
void entry_mode_set(bool cursor_direction, bool shift_display);
static void display_control(bool display, bool cursor, bool blinking);
static void cursor_display_shift(bool cursor_display, bool right_left);
static void function_set(bool data_length, bool display_line, bool font);
static void set_cgram_addr(uint8_t *addr);
static void set_ddram_addr(uint8_t *addr);
static bool is_busy();
static void write_ram(uint8_t *data);
static void read_ram();
void output_char(char *data);
static void init_sequence();
void lcd_char_disp_init();

//PIN set/reset
static inline void set_e_pin()
{
    GPIOC->BSRR = GPIO_BSRR_BS_5;
    // TODO: implement timer
    for (volatile int i = 0; i < 10000; i++)
        ;
}
static inline void set_rw_pin() { GPIOC->BSRR = GPIO_BSRR_BS_6; }
static inline void set_rs_pin() { GPIOC->BSRR = GPIO_BSRR_BS_7; }
static inline void reset_e_pin() { GPIOC->BSRR = GPIO_BSRR_BR_5; }
static inline void reset_rw_pin() { GPIOC->BSRR = GPIO_BSRR_BR_6; }
static inline void reset_rs_pin() { GPIOC->BSRR = GPIO_BSRR_BR_7; }

#endif // LCD_CHAR_DISP_H
