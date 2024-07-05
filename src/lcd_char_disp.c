#include <lcd_char_disp.h>

// Internal Functions
static void send_function(uint8_t *data, bool rs, bool rw)
{
    if (rs)
        set_rs_pin();
    if (rw)
        set_rw_pin();

    set_e_pin();
    output_shift_register(data, 1);
    reset_e_pin();

    reset_rs_pin();
    reset_rw_pin();
}
// Write “00H” to DDRAM and set DDRAM address to “00H” from AC
void clear_display()
{
    uint8_t data = 0x00 | 1U << 0;
    send_function(&data, false, false);
    delay_ms(2); //Execution time

}
// Set DDRAM address to “00H” from AC and return cursor to its original position if shifted
void return_home()
{
    uint8_t data = 0x00 | 1U << 1;
    send_function(&data, false, false);
    delay_ms(2); //Execution time
}
// Assign cursor moving direction and enable the shift of entire display
void entry_mode_set(bool cursor_direction, bool shift_display)
{
    uint8_t data = 0x00 | 1U << 2 | cursor_direction << 1 | shift_display << 0;
    send_function(&data, false, false);
}
// Set display (D), cursor (C ), and blinking of cursor (B) on/off control bit
void display_control(bool display, bool cursor, bool blinking)
{
    uint8_t data = 0x00 | 1U << 3 | display << 2 | cursor << 1 | blinking << 0;
    send_function(&data, false, false);
}
// Cursor shift. right_left (H:L)
void shift_cursor(bool right_left)
{
    uint8_t data = 0x00 | 1U << 4 | right_left << 2;
    send_function(&data, false, false);
}
// Display shift. right_left (H:L). Cursor follow display shift
void shift_display(bool right_left)
{
    uint8_t data = 0x00 | 1U << 4 | 1U << 3 | right_left << 2;
    send_function(&data, false, false);
}
// Set interface data length (DL:8-bit/4-bit), numbers of display line (N:2-line/1-line), and display font type (F:5x11 dots/5x8 dots)
static void function_set(bool data_length, bool display_line, bool font)
{
    uint8_t data = 0x00 | 1U << 5 | data_length << 4 | display_line << 3 | font << 2;
    send_function(&data, false, false);
}
// Set CGRAM address in address counter
static void set_cgram_addr(uint8_t *addr)
{
    uint8_t data = 0x00 | 1U << 6 | *addr;
    send_function(&data, false, false);
}
// Set DDRAM address in address counter
static void set_ddram_addr(uint8_t *addr)
{
    uint8_t data = 0x00 | 1U << 7 | *addr;
    send_function(&data, false, false);
}
// Write data into internal RAM (DDRAM/CGRAM)
void write_ram(uint8_t *data)
{
    send_function(data, true, false);
}
// Add custom character in CGRAM
void add_custom_char(uint8_t base_addr, uint8_t *array, uint32_t length, bool set_cgram)
{
    if (length != 8)
        return;

    if (set_cgram)
        set_cgram_addr(&base_addr);

    for (uint32_t i = 0; i < length; i++)
        write_ram(&(array[i]));
}
// Output single character
void output_char(char *data, uint8_t position) // Position from 0 to 31
{
    if (position > 31)
        return;

    uint8_t addr = 0x00;

    // Convert from position to address
    if (position <= 15)
        addr = position;
    else if (position >= 16)
        addr = position % 16 + 0x40;

    set_ddram_addr(&addr);
    write_ram(data);
}
// Outputs string. If string is longer than 32, it prints over the first row
void output_string(char *string)
{
    uint32_t index = 0;
    while (string[index] != '\0')
    {
        write_ram(&string[index]);
        index++;

        if (!(index % 16))
            set_ddram_addr(&(uint8_t){0x40});
        if (!(index % 32))
            return_home();
    }
}
// Initialize the display
static void init_sequence()
{
    function_set(true, true, false);
    return_home();
    clear_display();
}
// Initialize the LCD character display
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

    // Cursor moves from left to right, display shift right
    entry_mode_set(true, false);

    // Display on, cursor and blinking
    display_control(true, false, false);
}
