#include "gpio.h"
#include "system_config.h"

void GPIO_Init_LED(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;

    GPIOC->CRH &= ~(0xF << 20);
    GPIOC->CRH |=  (0x1 << 20);

    GPIOC->BSRR = GPIO_BSRR_BS13;
}

void GPIO_SetLED(uint8_t state)
{
    if (state)
    {
        GPIOC->BSRR = GPIO_BSRR_BR13;
    }
    else
    {
        GPIOC->BSRR = GPIO_BSRR_BS13;
    }
}
