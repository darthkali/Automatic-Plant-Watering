
#include "misc.h"
#include "system.h"

// init main clock
void InitSystem()
{
	// clock setup
	SystemInit();

	// set core clock variable
	SystemCoreClockUpdate();

	// pre-emption priority only!
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
}
