#include "stm32f10x.h"

#define FIRE_THRESHOLD 1800

void GPIO_Init_LED(void);
void ADC_Init_FlameSensor(void);
void CAN_InitBasic(void);
void CAN_SendAlert(uint16_t value);
uint16_t ADC_Read(void);

int main(void)
{
    GPIO_Init_LED();
    ADC_Init_FlameSensor();
    CAN_InitBasic();

    while (1)
    {
        uint16_t flame = ADC_Read();

        if (flame > FIRE_THRESHOLD)
        {
            GPIOC->BSRR = GPIO_BSRR_BR13;   // LED ON
            CAN_SendAlert(flame);
        }
        else
        {
            GPIOC->BSRR = GPIO_BSRR_BS13;   // LED OFF
        }
    }
}

void GPIO_Init_LED(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
    GPIOC->CRH &= ~(0xF << 20);
    GPIOC->CRH |=  (0x1 << 20);
}

void ADC_Init_FlameSensor(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN | RCC_APB2ENR_IOPAEN;
    GPIOA->CRL &= ~0xF;

    ADC1->CR2 |= ADC_CR2_ADON;
    for (volatile int i = 0; i < 50000; i++);
    ADC1->CR2 |= ADC_CR2_CAL;
    while (ADC1->CR2 & ADC_CR2_CAL);
}

uint16_t ADC_Read(void)
{
    ADC1->SQR3 = 0;
    ADC1->CR2 |= ADC_CR2_ADON;

    while (!(ADC1->SR & ADC_SR_EOC));
    return ADC1->DR;
}

void CAN_InitBasic(void)
{
    RCC->APB1ENR |= RCC_APB1ENR_CAN1EN;

    CAN1->MCR |= CAN_MCR_INRQ;
    while (!(CAN1->MSR & CAN_MSR_INAK));

    CAN1->BTR = (4 << 16) | (3 << 20) | (1 << 0);

    CAN1->MCR &= ~CAN_MCR_INRQ;
    while (CAN1->MSR & CAN_MSR_INAK);
}

void CAN_SendAlert(uint16_t value)
{
    CAN1->sTxMailBox[0].TIR = (0x321 << 21);
    CAN1->sTxMailBox[0].TDLR = value;
    CAN1->sTxMailBox[0].TDTR = 2;
    CAN1->sTxMailBox[0].TIR |= CAN_TI0R_TXRQ;

    while (!(CAN1->TSR & CAN_TSR_RQCP0));
}
