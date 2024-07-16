#include <uart2.h>

static void uart2_pin_init()
{
    // Configure GPIOA 2, 3 pins for UART
    // Enable AHB1 clock for port A
    SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOAEN);
    // Set PA2 and PA3 to AF for UART
    SET_BIT(GPIOA->MODER, 0b10 << GPIO_MODER_MODER2_Pos);
    SET_BIT(GPIOA->MODER, 0b10 << GPIO_MODER_MODER3_Pos);
    // Set AF7 (0b0111) to both pins (from Alternate Function Mapping)
    SET_BIT(GPIOA->AFR[0], GPIO_AFRL_AFRL2_0 | GPIO_AFRL_AFRL2_1 | GPIO_AFRL_AFRL2_2); // AF7 = 0b0111
    SET_BIT(GPIOA->AFR[0], GPIO_AFRL_AFRL3_0 | GPIO_AFRL_AFRL3_1 | GPIO_AFRL_AFRL3_2); // AF7 = 0b0111
}

void uart2_init()
{
    // Enable RCC clock
    SET_BIT(RCC->APB1ENR, RCC_APB1ENR_USART2EN);

    uart2_pin_init();

    // Set baudrate to 115200b/s with oversampling 16 OVER8=0 at 16MHz
    WRITE_REG(USART2->BRR, 0x8B);

    // Configure transmit enable
    SET_BIT(USART2->CR1, USART_CR1_TE);

    // Configure receive enable.
    SET_BIT(USART2->CR1, USART_CR1_RE);

    // Configure start, 1 stop and 8 data bits.
    CLEAR_BIT(USART2->CR1, USART_CR1_M);
    CLEAR_BIT(USART2->CR2, USART_CR2_STOP_0 | USART_CR2_STOP_1);

    // Enable UART;
    SET_BIT(USART2->CR1, USART_CR1_UE);
}

void uart2_write(char ch)
{
    // Make sure the transmit data register is empty
    while (!(READ_BIT(USART2->SR, USART_SR_TXE)))
        ;

    // Write to transmit data register
    // USART2->DR = (uint8_t)ch;
    USART2->DR = (uint8_t)ch;
}

char uart2_read()
{
    // Make sure the receive data register is not empty
    while (!READ_BIT(USART2->SR, USART_SR_RXNE))
        ;

    return USART2->DR;
}