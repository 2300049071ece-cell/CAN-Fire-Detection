#include "adc.h"
#include "system_config.h"

/* Basic ADC driver for reading analog flame sensor on PA0 (ADC1 channel 0).
   This is a simple polling implementation to keep things clean. */

void ADC_Init_FlameSensor(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN | RCC_APB2ENR_IOPAEN;

    // PA0 as analog input
    GPIOA->CRL &= ~(0xF << 0);

    // Power up ADC
    ADC1->CR2 |= ADC_CR2_ADON;
    for (volatile int i = 0; i < 50000; i++);

    // Calibrate ADC
    ADC1->CR2 |= ADC_CR2_CAL;
    while (ADC1->CR2 & ADC_CR2_CAL);
}

uint16_t ADC_Read_SingleChannel(void)
{
    // Channel 0 (PA0)
    ADC1->SQR3 = 0;

    // Start conversion
    ADC1->CR2 |= ADC_CR2_ADON;
    ADC1->CR2 |= ADC_CR2_ADON; // second write triggers conversion

    // Wait until conversion completes
    while (!(ADC1->SR & ADC_SR_EOC));

    return (uint16_t)ADC1->DR;
}
