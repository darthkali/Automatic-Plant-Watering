/*
// --- Includes ---
#include "exti.h"
#include "misc.h"
#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_syscfg.h"

// --- Pins ---
// PA0  = INT0
// PA1  = INT1

// --- Variables ---
EXT_CALLBACK pfCounter = NULL;

// --- Init external edge callbacks ---
void SetExtCallback(EXT_CALLBACK pfCallback,TRIGGER_EDGE enTrigger,int nLine)
{
	EXTI_InitTypeDef exti_init = {0};
	NVIC_InitTypeDef nvic_init = {0};

	if (nLine == 0)
	{
		SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);

		exti_init.EXTI_Line = EXTI_Line0;
		exti_init.EXTI_Trigger = enTrigger;
		exti_init.EXTI_Mode = EXTI_Mode_Interrupt;
		exti_init.EXTI_LineCmd = ENABLE;
		EXTI_Init(&exti_init);

		nvic_init.NVIC_IRQChannelPreemptionPriority = 3;
		nvic_init.NVIC_IRQChannel = EXTI0_IRQn;
		nvic_init.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&nvic_init);
	}
	else
	{
		SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource1);

		exti_init.EXTI_Line = EXTI_Line1;
		exti_init.EXTI_Trigger = enTrigger;
		exti_init.EXTI_Mode = EXTI_Mode_Interrupt;
		exti_init.EXTI_LineCmd = ENABLE;
		EXTI_Init(&exti_init);

		nvic_init.NVIC_IRQChannelPreemptionPriority = 3;
		nvic_init.NVIC_IRQChannel = EXTI1_IRQn;
		nvic_init.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&nvic_init);
	}

	pfCounter = pfCallback;
}

// --- IRQ handler (INT0) ---
void EXTI0_IRQHandler()
{
	if (EXTI_GetITStatus(EXTI_Line0) == SET)
	{
		EXTI_ClearITPendingBit(EXTI_Line0);

		if (pfCounter)
			pfCounter(0);
	}
}

// --- IRQ handler (INT1) ---
void EXTI1_IRQHandler()
{
	if (EXTI_GetITStatus(EXTI_Line1) == SET)
	{
		EXTI_ClearITPendingBit(EXTI_Line1);

		if (pfCounter)
			pfCounter(1);
	}
}

*/
