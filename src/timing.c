
#include "timing.h"

// --- Nap 1µs ---
void Nap(int microsec)
{
	while (microsec--)
	{
		volatile int nap = 6;

		while (nap--)
		{
			__asm("nop\n"
				  "nop\n"
				  "nop\n"
				  "nop\n"
				  "nop\n"
				  "nop\n");
		}
	}
}

// --- Delay ---
void Delay(int millisec)
{
	while (millisec--)
    	Nap(1000);
}
