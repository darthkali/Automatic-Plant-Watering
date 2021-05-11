#ifndef PORTS_H
#define PORTS_H

// --- Includes ---
#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"

// --- Prototypes ---
void InitPorts();
int GetGPIOPin(GPIO_TypeDef* pPort, int nPin);
void SetGPIOPin(GPIO_TypeDef* pPort, int nPin, int nValue);
void ToggleGPIOPin(GPIO_TypeDef* pPort, int nPin);

#endif
