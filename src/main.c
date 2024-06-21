// CMSIS
#include <stm32f410rx.h>
#include <stm32f4xx.h>
// STD
#include <stdbool.h>
#include <stdlib.h>
// USER
#include <gpio.h>      //GPIO
#include <exti.h>      //EXTERNAL INTERUPS
#include <sipo_sreg.h> //SERIAL IN PARRALEL OUT SHIFT REGISTER
#include <lcd_char_disp.h>
#include <particle_char_generator.h>

int main()
{
    // Setup
    lcd_char_disp_init();

    // Loop
    while (true)
    {
        // TEST
        for (int i = 0; i < CHAR_HEIGTH; i++)
        {
            for (size_t j = 0; j < CHAR_WIDTH; j++)
            {
                generate_single_pixel_char(i, j);
                for (volatile int i = 0; i < 100000; i++)
                    ;
                output_char(&(uint8_t){0x00}, 31);
            }
        }
    }
    return 0;
}

// Interrupts
void EXTI15_10_IRQHandler(void)
{
    // switch (EXTI->PR)
    // {
    // case EXTI_PR_PR11:
    //     break;

    // default:
    //     break;
    // }
    // // if interrupt happens on 11 pin
    // if (READ_BIT(EXTI->PR, EXTI_PR_PR11))
    // {
    //     // Clear pending bit by writing 1 per RefManual. reset interupt request
    //     SET_BIT(EXTI->PR, EXTI_PR_PR11);
    // }
}