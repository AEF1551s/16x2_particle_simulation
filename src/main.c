// CMSIS
#include <stm32f410rx.h>
#include <stm32f4xx.h>
// STD
#include <stdbool.h>
#include <stdlib.h>
// USER
#include <gpio.h>                    //GPIO
#include <sipo_sreg.h>               //SERIAL IN PARRALEL OUT SHIFT REGISTER
#include <lcd_char_disp.h>           //16x2 CHARACTER DISPLAY
#include <particle_char_generator.h> //PARTICLE GENERATOR FOR 16X2 CHAR DISPLAY
#include <physics.h>                 //PARTICLES AND PHYSICS
#include <hardware_rand.h>           //HARDWARE RNG
#include <delay.h>                   //DELAY TIM6

// All board conifigurations add here
void initialize()
{
    /*
    Setup
    Initialization functions MUST be initialized in this order.
    For example, if delay is not initialized but its functions called, it will not perform counting and get stuck in loop
    */
    delay_init();
    hard_rand_init();
    lcd_char_disp_init();
}

// Main
int main()
{
    // Initialization and checks
    initialize();
    output_string((char *){"Initialization  complete"});
    delay_ms(1000);

    // Add particles and randomize
    struct particle particles[3];
    for (int i = 0; i < 3; i++)
    {
        randomize_particle(&particles[i]);
        add_particle(&particles[i]);
    }

    clear_display();
    output_string((char *){"Random particlesgenerated"});
    delay_ms(1000);

    // END - Initialization and checks

    while (true)
    {
        clear_display();
        display_all_particles();
        // LCD max response time is 200ms, typical 150, with no lower limit.
        // Lowering the delay, LCD doesnt reach its maximum contrast and harder to see pixels
        delay_ms(75);
        update_all_particles();
    }
    free_all_particles();
    return 0;
}