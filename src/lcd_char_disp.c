#include <lcd_char_disp.h>

// Functions
//Set interface data length (DL:8-bit/4-bit), numbers of display line (N:2-line/1-line)and, display font type (F:5x11 dots/5x8 dots)
static void function_set(bool data_lenght, bool display_line, bool font) 
{
    uint8_t data = 0x20 | data_lenght << 4 | display_line << 3 | font << 2;

    reset_rs_pin();
    reset_rw_pin();

    set_e_pin();
    output_shift_register(&data, 1);
    reset_e_pin();
}

static void clear_display()
{
    reset_rs_pin();
    reset_rw_pin();
    set_e_pin();
    output_shift_register(&(uint8_t){0x01}, 1);
    reset_e_pin();
}

static void return_home()
{
    reset_rs_pin();
    reset_rw_pin();
    set_e_pin();
    output_shift_register(&(uint8_t){0x02}, 1);
    reset_e_pin();
}

static void display_control(bool display, bool cursor, bool blinking)
{
    uint8_t data = 0x08 | display << 2 | cursor << 1 | blinking << 0;

    reset_rs_pin();
    reset_rw_pin();
    set_e_pin();
    output_shift_register(&data, 1);
    reset_e_pin();
}
static void init_sequence()
{
    function_set(true, true, false);
    return_home();
    clear_display();
}
// End Functions

void lcd_char_disp_init()
{
    // Init pins for SIPO shift register
    shift_register_init();

    // Enable PORT C clock source AHB1
    SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOCEN);

    // Set PIN 5 - 7 as general purpose outputs 0b01
    SET_BIT(GPIOC->MODER, GPIO_MODER_MODER5_0);
    SET_BIT(GPIOC->MODER, GPIO_MODER_MODER6_0);
    SET_BIT(GPIOC->MODER, GPIO_MODER_MODER7_0);

    init_sequence();
}

static bool is_busy()
{
    // D7 which is connected to sipo shift register Q7 is busy flag.
    // TODO: Add input pin for D7/Q7 to read busy flag - on going internal operation or not
}
