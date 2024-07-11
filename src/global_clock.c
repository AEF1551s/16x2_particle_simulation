#include <global_clock.h>
//Initialize TIM11
static void tim11_init()
{
    // AHB prescaler reset vaule = 0 = no prescaler
    // APB prescaler reset value = 0 = no prescaler
    // APB2 clock = 16MHz

    // Enable TIM11 APB2
    SET_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM11EN);
    // Enable auto-reload preload - AR changes take place after UE
    SET_BIT(TIM11->CR1, TIM_CR1_ARPE);
    // Update interrupt only from counter overflow/underflow
    SET_BIT(TIM11->CR1, TIM_CR1_URS);
    // Set prescaler to 16000.
    WRITE_REG(TIM11->PSC, (16000U - 1U));

    //  Enable interrupts
    SET_BIT(TIM11->DIER, TIM_DIER_UIE);
    NVIC_SetPriority(TIM1_TRG_COM_TIM11_IRQn, 8);
    NVIC_EnableIRQ(TIM1_TRG_COM_TIM11_IRQn);
}

//Initilize TIM11 and start couting. Interrupt occurs every ms cycle
void frame_time_ms(uint16_t ms)
{
    tim11_init();

    if (ms == 0)
        return;
    if (ms > 65000)
        ms = 65000;

    // Write how many cycles (ms based on config)
    WRITE_REG(TIM11->ARR, ms);
    // Counter enable
    SET_BIT(TIM11->CR1, TIM_CR1_CEN);
}
