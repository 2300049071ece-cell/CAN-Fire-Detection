This project is a simple CAN-based fire detection node built on the STM32F103 (Blue Pill). I created it to understand CAN communication, ADC sampling, and bare-metal STM32 programming without relying on HAL or CubeMX. A flame sensor outputs an analog voltage on PA0, which I read through the ADC. When the reading crosses a threshold, the LED on PC13 turns ON and a CAN alert frame (Std ID: 0x321) is transmitted. If not, the LED stays OFF. Everything is written using direct register-level access so the initialization of ADC, CAN bit timing, and GPIO configuration is completely transparent. The code is kept modular with separate drivers for GPIO, ADC, and CAN. Hardware used includes the Blue Pill, MCP2551/SN65HVD230 CAN transceiver, a flame sensor, and standard 120Ω CAN termination. Future improvements include CAN RX, DMA-based ADC, filtering, FreeRTOS tasks, and watchdog support. This project reflects how I learn embedded systems—building things from scratch and understanding the hardware deeply. If you have suggestions or want to collaborate, feel free to reach me at 2300049071ece@gmail.com
while (1)
{
    uint16_t sensor = ADC_Read_SingleChannel();

    if (sensor > 1500)
    {
        GPIO_SetLED(1);
        CAN_SendAlert(sensor);
    }
    else
    {
        GPIO_SetLED(0);
    }
}


