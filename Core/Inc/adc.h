#ifndef ADC_DRIVER_H
#define ADC_DRIVER_H

#include "stm32f10x.h"
#include <stdint.h>

void ADC_Init_FlameSensor(void);
uint16_t ADC_Read_SingleChannel(void);

#endif // ADC_DRIVER_H
