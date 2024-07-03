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

    struct particle p1;
    p1.pos.x = 0;
    p1.pos.y = 1;
    p1.acc.x = 0;
    p1.acc.y = 0;
    p1.vel.x = 1;
    p1.vel.y = 0;
    add_particle(&p1);

    struct particle p2;
    p2.pos.x = 0;
    p2.pos.y = 2;
    p2.acc.x = 0;
    p2.acc.y = 0;
    p2.vel.x = 2;
    p2.vel.y = 0;
    add_particle(&p2);

    struct particle p3;
    p3.pos.x = 0;
    p3.pos.y = 3;
    p3.acc.x = 0;
    p3.acc.y = 0;
    p3.vel.x = 3;
    p3.vel.y = 0;
    add_particle(&p3);

    struct particle p4;
    p4.pos.x = 0;
    p4.pos.y = 4;
    p4.acc.x = 0;
    p4.acc.y = 0;
    p4.vel.x = 4;
    p4.vel.y = 0;
    add_particle(&p4);

    struct particle p5;
    p5.pos.x = 79;
    p5.pos.y = 7;
    p5.acc.x = 0;
    p5.acc.y = 0;
    p5.vel.x = -5;
    p5.vel.y = 0;
    add_particle(&p5);

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