#ifndef CAN_DRIVER_H
#define CAN_DRIVER_H

#include "stm32f10x.h"
#include <stdint.h>

void CAN_InitBasic(void);
void CAN_SendAlert(uint16_t value);

#endif // CAN_DRIVER_H
