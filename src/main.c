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
int main()
{
    // Setup
    // gpio_init();
    // exti_init();
    // shift_register_init();

    char output;
    char* string = "do re mi fa sol";
    lcd_char_disp_init();
    // Loop
    while (true)
    {
        clear_display();
        return_home();
        //test
        output_char_stream(string);
        for (volatile int i = 0; i < 1000000; i++)
            ;
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