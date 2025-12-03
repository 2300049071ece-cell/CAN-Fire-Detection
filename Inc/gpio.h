#ifndef GPIO_H
#define GPIO_H

#include "stm32f10x.h"
#include <stdint.h>

void GPIO_Init_LED(void);
void GPIO_SetLED(uint8_t state);

#endif // GPIO_H
