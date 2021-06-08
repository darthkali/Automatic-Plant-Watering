
#ifndef I2C_H
#define I2C_H

// --- Includes ---
#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_i2c.h"
#include "stm32f4xx_gpio.h"

// --- Prototypes ---
void InitI2C();
void SendI2C(char nAddr, char Buffer[], short nCount);


#endif
