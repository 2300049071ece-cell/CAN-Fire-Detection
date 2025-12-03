What this project actually does

Reads flame/IR sensor value on PA0 using ADC

Checks if the reading is above the “fire detected” threshold

If yes → turns ON LED on PC13 and sends a CAN alert (ID: 0x321)

If no fire → LED stays OFF

Everything is written using register-level programming

Very small and easy-to-understand codebase

Project Structure 
CAN-Fire-Detection/
├── Core/
│   ├── main.c          // Fire-detection logic
│   ├── gpio.c          // LED driver
│   ├── adc.c           // Sensor reading
│   └── can.c           // CAN TX logic
├── Inc/
│   ├── gpio.h
│   ├── adc.h
│   ├── can.h
│   └── system_config.h
└── README.md

Hardware I used

STM32F103C8T6 (Blue Pill)

MCP2551 / SN65HVD230 CAN transceiver

Flame sensor (analog output)

On-board LED at PC13

Standard 120Ω CAN termination

How the firmware runs (human explanation)

MCU boots

Initializes GPIO, ADC, CAN

Reads sensor value

If reading > threshold → “ok, something’s burning”

LED turns ON

CAN frame sends the value

Repeat in a loop

Testing

Import project into STM32CubeIDE or Keil

Flash with ST-Link

Use lighter near flame sensor

Check CAN TX frames using analyzer

Use logic analyzer on CAN_TX pin

Future improvements

CAN RX + filtering

DMA-based ADC

Noise filtering

FreeRTOS version

Watchdog + error handling

About me

I’m Pardha Saradhi, an embedded engineer learning by building real projects.
📧 2300049071ece@gmail.com
