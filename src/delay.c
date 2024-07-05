#include <delay.h>

void delay_init()
{
    // AHB prescaler reset vaule = 0 = no prescaler
    // APB prescaler reset value = 0 = no prescaler
    // APB1 clock = 16MHz

    // Enable TIM6 APB1
    SET_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM6EN);
    // Enable auto-reload preload - AR changes take place after UE
    SET_BIT(TIM6->CR1, TIM_CR1_ARPE);
    // One-pulse mode
    SET_BIT(TIM6->CR1, TIM_CR1_OPM);
    // Update interrupt only from counter overflow/underflow
    SET_BIT(TIM6->CR1, TIM_CR1_URS);
    // Set prescaler to 16000.
    WRITE_REG(TIM6->PSC, (16000U - 1U));

    //  Enable interrupts
    SET_BIT(TIM6->DIER, TIM_DIER_UIE);
    NVIC_EnableIRQ(TIM6_DAC_IRQn);
}
// Delay in ms. Maximum achievable delay is 65000ms. Actual maximum is 16 bit max value 2^16 -1
void delay_ms(uint16_t ms)
{
    if (ms == 0)
        return;
    if (ms > 65000)
        ms = 65000;

    // Write how many cycles (ms based on config)
    WRITE_REG(TIM6->ARR, ms);
    // Counter enable
    SET_BIT(TIM6->CR1, TIM_CR1_CEN);

    while (!flag)
        ;

    flag = false;
}

// Interrupts
void TIM6_DAC_IRQHandler(void)
{
    if (READ_BIT(TIM6->SR, TIM_SR_UIF))
        flag = true;

    CLEAR_BIT(TIM6->SR, TIM_SR_UIF);
}