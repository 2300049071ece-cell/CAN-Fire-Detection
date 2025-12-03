#include "can.h"
#include "system_config.h"

/* Basic CAN initialization and TX-only transmission.
   Enough to demonstrate embedded firmware design, register usage,
   and understanding of CAN peripheral on STM32F103. */

void CAN_InitBasic(void)
{
    /* Enable CAN + GPIO clocks */
    RCC->APB1ENR |= RCC_APB1ENR_CAN1EN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_AFIOEN;

    /* PA11 = CAN RX (input PU/PD), PA12 = CAN TX (AF push-pull) */

    // PA11 (RX)
    GPIOA->CRH &= ~(0xF << 12);
    GPIOA->CRH |=  (0x8 << 12);

    // PA12 (TX)
    GPIOA->CRH &= ~(0xF << 16);
    GPIOA->CRH |=  (0xA << 16);

    /* Enter init mode */
    CAN1->MCR |= CAN_MCR_INRQ;
    while (!(CAN1->MSR & CAN_MSR_INAK));

    /* Bit timing: example values (~500 kbps) */
    CAN1->BTR =  (0 << 30)      // SJW = 1
               | (7 << 16)      // BS1 = 8
               | (2 << 20)      // BS2 = 3
               | (3 << 0);      // Prescaler = 4

    /* Exit init mode */
    CAN1->MCR &= ~CAN_MCR_INRQ;
    while (CAN1->MSR & CAN_MSR_INAK);
}

void CAN_SendAlert(uint16_t value)
{
    /* Load TX mailbox 0 */
    CAN1->sTxMailBox[0].TIR = (0x321 << 21);  // Standard ID 0x321
    CAN1->sTxMailBox[0].TDTR = 2;             // DLC = 2 bytes
    CAN1->sTxMailBox[0].TDLR = value;         // Data to send

    /* Request transmission */
    CAN1->sTxMailBox[0].TIR |= CAN_TI0R_TXRQ;

    /* Wait for completion */
    while (!(CAN1->TSR & CAN_TSR_RQCP0));
}
