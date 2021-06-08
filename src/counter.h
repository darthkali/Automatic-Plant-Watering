#ifndef COUNTER_H
#define COUNTER_H

// --- Constants ---
#define MAX_COUNTERS 10

// --- Counter ---

typedef struct COUNTER{
	int nLastPinState;
	int nCounterValue;
}COUNTER;



// --- Includes ---



// --- Prototypes ---
void InitCounter();

#endif
