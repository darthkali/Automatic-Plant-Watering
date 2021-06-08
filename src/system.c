// --- Includes ---
#include "scheduler.h"
#include "ports.h"
#include "misc.h"
#include "system.h"

// --- Variables ---

// --- Prototypes ----
void InitSystem(){

	// clock setup
	SystemInit();

	// core Clock variable
	SystemCoreClockUpdate();


	// pre-emption priority only!
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
}
