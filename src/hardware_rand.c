#include <hardware_rand.h>

void hard_rand_init()
{
    // Enable AHB1 clock
    SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_RNGEN);
    //  Configure PLL clock
    CLEAR_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLM);
    CLEAR_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLN);
    CLEAR_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLQ);
    SET_BIT(RCC->PLLCFGR, 8U << RCC_PLLCFGR_PLLM_Pos);
    SET_BIT(RCC->PLLCFGR, 72U << RCC_PLLCFGR_PLLN_Pos);
    SET_BIT(RCC->PLLCFGR, 3U << RCC_PLLCFGR_PLLQ_Pos);
    // Enable PLL
    SET_BIT(RCC->CR, RCC_CR_PLLON);

    // Enable interrupts
    SET_BIT(RNG->CR, RNG_CR_IE);
    NVIC_EnableIRQ(RNG_IRQn);
}
// Generates random number in RNG low-power mode. Time for ready data is 46 RNG cycles in LPM
uint32_t random_uint32()
{
    // Enable RNG
    SET_BIT(RNG->CR, RNG_CR_RNGEN);
    // Wait for interrupt, read DRDY, if true - get RNG data, if not - wait until ready After reading interrupt flag is automatically cleared.
    while (!drrdy_flag)
        ;

    return rand_int;
}

/* Interrupts

No error occurred. The SEIS and CEIS bits should be set to ‘0’ in the RNG_SR
register.
–A random number is ready. The DRDY bit must be set to ‘1’ in the RNG_SR
register.
–If above two conditions are true the content of the RNG_DR register can be read.
*/

void HASH_RNG_IRQHandler(void)
{
    // Check for errors
    int temp1 = READ_REG(RNG->SR);
    if (READ_BIT(RNG->SR, RNG_SR_SEIS) || READ_BIT(RNG->SR, RNG_SR_CEIS))
    {
        clear_display();
        output_string((char *){"RNG ERROR"});

        drrdy_flag = false;
        CLEAR_REG(RNG->SR);
        return;
    }
    // Check if data is ready
    if (READ_BIT(RNG->SR, RNG_SR_DRDY))
    {
        rand_int = READ_REG(RNG->DR);
        drrdy_flag = true;
        CLEAR_REG(RNG->SR);
        // Disable RNG
        CLEAR_BIT(RNG->CR, RNG_CR_RNGEN);
    }
}
