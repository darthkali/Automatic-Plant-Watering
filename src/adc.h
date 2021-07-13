#ifndef _ADC_H
#define _ADC_H

// header

#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_adc.h"
#include "stm32f4xx_gpio.h"

// prototypes

void InitADC();
short GetAnalog(int channel);

#endif
