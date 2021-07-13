
#include "ports.h"
#include "counter.h"
#include "scheduler.h"

// --- Variables ---
COUNTER arrCounters[MAX_COUNTERS] = {0};

// --- Prototypes ---
void CounterThread();

// --- Init counters ---
void InitCounter()
{
	// todo: init last pin state from pin!

	ExecuteThread(CounterThread,10,0);
	ExecuteThread(CounterThread,10,5);
}

// --- Counter thread (5ms) ---
void CounterThread()
{
	int nCounter = 0;

	while (nCounter < MAX_COUNTERS)
	{
		COUNTER* pCounter = &arrCounters[nCounter++];
		int nPinState = GetInput(nCounter);

		// any change in pin state
		//if (pCounter->nLastPinState != nPinState)

		// any raising edge on pin
		//if (pCounter->nLastPinState < nPinState)

		// any falling edge on pin
		if (pCounter->nLastPinState > nPinState)
		{
			pCounter->nCounterValue += 1;
			pCounter->nLastPinState = nPinState;
		}
	}
}

// --- return counter value ---
int GetCounter(int nCounter)
{
	if (nCounter >= 0 && nCounter < MAX_COUNTERS)
	{
		COUNTER* pCounter = &arrCounters[nCounter];

		return pCounter->nCounterValue;
	}

	return 0;
}
