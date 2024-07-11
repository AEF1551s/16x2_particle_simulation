// CMSIS
#include <stm32f410rx.h>
#include <stm32f4xx.h>
// STD
#include <stdbool.h>
#include <stdlib.h>
// USER
#include <sipo_sreg.h>               //SERIAL IN PARRALEL OUT SHIFT REGISTER
#include <lcd_char_disp.h>           //16x2 CHARACTER DISPLAY
#include <particle_char_generator.h> //PARTICLE GENERATOR FOR 16X2 CHAR DISPLAY
#include <physics.h>                 //PARTICLES AND PHYSICS
#include <hardware_rand.h>           //HARDWARE RNG
#include <delay.h>                   //DELAY TIM6
#include <global_clock.h>            //GLOBAL CLOCK

//  All board conifigurations add here
void initialize()
{
    /*
    Setup
    Initialization functions MUST be initialized in this order.
    For example, if delay is not initialized but its functions called, it will not perform counting and get stuck in loop
    */
    NVIC_SetPriorityGrouping(TIM5_IRQn);
    delay_init();
    hard_rand_init();
    lcd_char_disp_init();
    output_string((char *){"Initialization  complete"});
    delay_ms(1000);
    // delay is more then frame
}

volatile bool ready = false;
volatile bool frame = false;
// Time in ms
uint16_t frame_time = 80;
uint16_t skipped_wait_time = 10;
struct char_seq_cgram_count *particle_buffer = NULL;

// Main
int main()
{
    // Initialization and checks
    initialize();

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

    // Start global frame time
    frame_time_ms(frame_time);

    while (true)
    {
        /*
        LCD max response time is 200ms, typical 150, with no lower limit.
        Lowering the delay, LCD doesnt reach its maximum contrast and harder to see pixels
        Wait until frame time is passed. Then generate next particles
        Clear display, before writing new CGRAM (bufffer particles),
        because these addreses are written into DDRAM, causing artefacts
        */
        clear_display();
        frame = false;
        particle_buffer = buffer_particles();
        ready = true;
        while (!frame)
            ;
        update_all_particles();
    }
    free_all_particles();
    return 0;
}

// Interrupts
void TIM1_TRG_COM_TIM11_IRQHandler(void)
{
    static int dt = 0;
    static uint32_t skipped_frames = 0;

    if (READ_BIT(TIM11->SR, TIM_SR_UIF))
    {
        CLEAR_BIT(TIM11->CR1, TIM_CR1_CEN);
        CLEAR_BIT(TIM11->SR, TIM_SR_UIF);
        if (ready)
        {
            frame = true;
            ready = false;
            display_particles(particle_buffer);
            delay_ms(10);
        }
        else
        {
            skipped_frames++;
            // Wait in 10ms increments until frame is ready
            WRITE_REG(TIM11->ARR, skipped_wait_time);
            /*
            Simple frame time compensation. If skipped wait time exceeds frame time,
            there is no delay betweem frames - calculation of each frame takes longer then
            frame time and performance drop is seen
            */
            dt = frame_time - skipped_wait_time * skipped_frames;
            if (dt < 0)
            {
                dt = 0;
            }
            WRITE_REG(TIM11->ARR, (uint16_t)dt);
        }
    }
    dt = 0;
    skipped_frames = 0;
    SET_BIT(TIM11->CR1, TIM_CR1_CEN);
}