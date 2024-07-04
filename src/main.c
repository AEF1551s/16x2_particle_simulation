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
#include <physics.h>

int main()
{
    // Setup
    lcd_char_disp_init();
    clear_display();

    struct particle particles[5];
    for (int i = 0; i < 5; i++)
    {
        randomize_particle(&particles[i]);
        add_particle(&particles[i]);
    }

    // Loop
    while (true)
    {
        display_all_particles();
        for (volatile int i = 0; i < 50000; i++) // If delay is smaller then 30000, LCD doesnt reach its maximum contrast, hard to see the particle.
            ;
        clear_display();
        update_all_particles();
    }
    free_all_particles();
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