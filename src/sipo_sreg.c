#include <sipo_sreg.h>

void shift_register_init()
{
    SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOCEN); // Enable PORT C clock source AHB1
    // Set PIN 0 - 4 as general purpose outputs 0b01
    SET_BIT(GPIOC->MODER, GPIO_MODER_MODER0_0);
    SET_BIT(GPIOC->MODER, GPIO_MODER_MODER1_0);
    SET_BIT(GPIOC->MODER, GPIO_MODER_MODER2_0);
    SET_BIT(GPIOC->MODER, GPIO_MODER_MODER3_0);
    SET_BIT(GPIOC->MODER, GPIO_MODER_MODER4_0);

    shift_register_enable();
}

void shift_register_enable()
{
    reset_oe_pin(); // Enable shift register output
}

void shift_register_disable()
{
    set_oe_pin();
}

void output_shift_register(uint8_t *data, uint32_t length)
{
    if (length <= 0)
        return;

    uint8_t mask = 0;

    reset_srclr_pin(); // Clear existing shift register
    set_srclr_pin();   // HIGH while writing serial data

    for (uint32_t i = 0; i < length; i++)
    {
        // On rising edge of SRCLK SER input (LOW or HIGH) is written into shift register
        for (uint32_t j = 0; j < 8; j++)
        {
            mask = 1 << j;

            if (data[i] & mask)
            {
                set_ser_pin();
            }
            else
            {
                reset_ser_pin();
            }

            set_srclk_pin();
            reset_srclk_pin();
            mask = 0;
        }
    }

    // Output shift register, set ready for next output
    set_rclk_pin();
    reset_rclk_pin();
}