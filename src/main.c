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
    struct particle p1;
    p1.pos.x = 40;
    p1.pos.y = 15;
    p1.acc.x = 0;
    p1.acc.y = 0;
    p1.vel.x = 2;
    p1.vel.y = 8;
    spawn_particle(&p1);
    // Loop
    while (true)
    {
        // TEST
        update_particle(&p1);

        for (volatile int i = 0; i < 100000; i++) // If delay is smaller then 30000, LCD doesnt reach its maximum contrast, hard to see the particle.
            ;

        clear_display();
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