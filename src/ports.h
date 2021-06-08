#ifndef PORTS_H
#define PORTS_H

// --- Includes ---
#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"

// --- Pin definitions ---

// Digital IN
#define IN0			GPIOC,4
#define IN1			GPIOC,5
#define IN2			GPIOC,6
#define IN3			GPIOC,7
#define IN4			GPIOC,8
#define IN5			GPIOC,9
#define IN6			GPIOC,10
#define IN7			GPIOC,11
#define IN8			GPIOC,12
#define IN9			GPIOC,13

// Digital OUT
#define OUT0		GPIOB,4
#define OUT1		GPIOB,5
#define OUT2		GPIOB,6
#define OUT3		GPIOB,7
#define OUT4		GPIOB,8
#define OUT5		GPIOB,9



// --- Prototypes ---
void InitPorts();
int GetGPIOPin(GPIO_TypeDef* pPort, int nPin);
void SetGPIOPin(GPIO_TypeDef* pPort, int nPin, int nValue);
void ToggleGPIOPin(GPIO_TypeDef* pPort, int nPin);

int GetInput(int nInput);
void SetOutput (int nOutput, int nValue);
#endif
