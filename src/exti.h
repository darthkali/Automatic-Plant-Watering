
#ifndef EXTI_H
#define EXTI_H

// --- Includes ---
#include "conf.h"
#include "types.h"
#include "stm32f4xx.h"
#include "stm32f4xx_exti.h"

// --- Trigger edge ---
typedef enum tagTriggerEdge
{
	trigRAISING = EXTI_Trigger_Rising,
	trigFALLING	= EXTI_Trigger_Falling,
	trigANYEDGE	= EXTI_Trigger_Rising_Falling
} TRIGGER_EDGE;

// --- Edge detected (INT0, INT1) ---
typedef void (*EXT_CALLBACK)(int nLine);

// --- Prototypes ---
void SetExtCallback(EXT_CALLBACK pfCallback,TRIGGER_EDGE enTrigger,int nLine);

#endif
