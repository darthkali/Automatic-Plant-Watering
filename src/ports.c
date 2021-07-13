
#include "ports.h"

// init ports A and C
void InitPorts()
{
	// init struct
	GPIO_InitTypeDef gpio_init = {0};

	// enable clock for ports A and C
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

	// define Port A pins
	gpio_init.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6;
	gpio_init.GPIO_Mode = GPIO_Mode_OUT;
	gpio_init.GPIO_OType = GPIO_OType_PP;

	// init port pin
	GPIO_Init(GPIOA, &gpio_init);

	// define Port B pins
	gpio_init.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
	gpio_init.GPIO_Mode = GPIO_Mode_OUT;
	gpio_init.GPIO_OType = GPIO_OType_PP;

	// init port pin
	GPIO_Init(GPIOB, &gpio_init);

	// define Port C pins
	gpio_init.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 |
			             GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13;
	gpio_init.GPIO_Mode = GPIO_Mode_IN;
	gpio_init.GPIO_PuPd = GPIO_PuPd_DOWN;

	// init port pin
	GPIO_Init(GPIOC, &gpio_init);
}

// --- Get GPIO Pin ---
int GetGPIOPin(GPIO_TypeDef* pPort, int nPin)
{
	return pPort->IDR >> nPin & 1;
}

// --- Set GPIO Pin ---
void SetGPIOPin(GPIO_TypeDef* pPort, int nPin, int nValue)
{
	int nMask = 1 << nPin;

	if (nValue)
		pPort->BSRRL = nMask;
	else
		pPort->BSRRH = nMask;
}

// --- Toggle Pin in Port ---
void ToggleGPIOPin(GPIO_TypeDef* pPort, int nPin)
{
	int nMask = 1 << nPin;

	// BSRR with (ODR xor Mask) or (Mask shifted 16 Bits left)
	pPort->BSRR = (pPort->ODR ^ nMask) | (nMask << 16);
}

#define OPTIMAL

// --- Get logical input pin ---
int GetInput(int nInput)
{
	#ifdef OPTIMAL

		if (nInput >= 0 && nInput < 10)
			return GetGPIOPin(IN0 + nInput);

	#else

		switch (nInput)
		{
			case 0: return GetGPIOPin(IN0);
			case 1: return GetGPIOPin(IN1);
			case 2: return GetGPIOPin(IN2);
			case 3: return GetGPIOPin(IN3);
			case 4: return GetGPIOPin(IN4);
			case 5: return GetGPIOPin(IN5);
			case 6: return GetGPIOPin(IN6);
			case 7: return GetGPIOPin(IN7);
			case 8: return GetGPIOPin(IN8);
			case 9: return GetGPIOPin(IN9);
		}

	#endif

	return 0;
}

// --- Set logical output pin ---
void SetOutput(int nOutput,int nValue)
{
	#ifdef OPTIMAL

		if (nOutput >= 0 && nOutput < 5)
			return SetGPIOPin(OUT0 + nOutput,nValue);

	#else

		switch (nInput)
		{
			case 0:
				SetGPIOPin(OUT0,nValue);
				break;
			case 1:
				SetGPIOPin(OUT1,nValue);
				break;
			case 2:
				SetGPIOPin(OUT2,nValue);
				break;
			case 3:
				SetGPIOPin(OUT3,nValue);
				break;
			case 4:
				SetGPIOPin(OUT4,nValue);
				break;
			case 5:
				SetGPIOPin(OUT5,nValue);
				break;
		}

	#endif
}






