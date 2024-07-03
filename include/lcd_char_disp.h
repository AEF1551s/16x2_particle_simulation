#if !defined(LCD_CHAR_DISP_H)
#define LCD_CHAR_DISP_H

// CMSIS
#include <stm32f410rx.h>
#include <stm32f4xx.h>
// STD
#include <stdbool.h>
// Hardware
#include <sipo_sreg.h>

/*
Uses SIPO shift register to write D0-D7 pins
GPIOC PIN5 - E - Chip Enable Signal
GPIOC PIN6 - R/W - H: Read(MPU(Module) L: Write(MPU(Module)
GPIOC PIN7 - RS - H: DATA, L: Instruction code
*/

// PIN set/reset
static inline void set_e_pin()
{
    GPIOC->BSRR = GPIO_BSRR_BS_5;
    for (volatile int i = 0; i < 2500; i++)
        ;
}
static inline void reset_e_pin() { GPIOC->BSRR = GPIO_BSRR_BR_5; }
static inline void set_rw_pin() { GPIOC->BSRR = GPIO_BSRR_BS_6; }
static inline void reset_rw_pin() { GPIOC->BSRR = GPIO_BSRR_BR_6; }
static inline void set_rs_pin() { GPIOC->BSRR = GPIO_BSRR_BS_7; }
static inline void reset_rs_pin() { GPIOC->BSRR = GPIO_BSRR_BR_7; }

// Initialization and Configuration Functions
static void function_set(bool data_length, bool display_line, bool font);
static void set_cgram_addr(uint8_t *addr);
static void set_ddram_addr(uint8_t *addr);
static void init_sequence();

void lcd_char_disp_init();

// Command Functions
void clear_display();
void return_home();
void entry_mode_set(bool cursor_direction, bool shift_display);
void shift_display(bool right_left);
void shift_cursor(bool right_left);
void display_control(bool display, bool cursor, bool blinking);

// Data Functions
void write_ram(uint8_t *data);
void output_char(char *data, uint8_t position);
void output_string(char *string);

// Custom Character Functions
void add_custom_char(uint8_t addr, uint8_t *array, uint32_t length, bool set_cgram);

#endif // LCD_CHAR_DISP_H
