// --- Includes ---
#include "counter.h"
#include "scheduler.h"
#include "ports.h"

// --- Variables ---
COUNTER arrCounters[MAX_COUNTERS] = {0};

// --- Prototypes ---
void CounterThread();


void InitCounter(){

	// TODO: nLastPinState müsste anfangs mit 0 initialisieren

	ExecuteThread(CounterThread, 10, 0);
	ExecuteThread(CounterThread, 10, 5);

}


void CounterThread(){
	int nCounter = 0;

	while (nCounter < MAX_COUNTERS){
		COUNTER* pCounter = &arrCounters[nCounter++];
		int nPinState = GetInput(nCounter); //einlesen jedes einzelnen Pins

		// jede Änderung registrieren
		/*if(pCounter->nLastPinState != nPinState){	// Hat sich das Pin verändert seit dem letzten aufruf
			pCounter->nCounterValue += 1;			// Counter hochsetzen
			pCounter->nLastPinState = nPinState;	// neuen State speichern
		}

		// Steigende Flanke
		if(pCounter->nLastPinState > 0){			// Hat sich das Pin verändert seit dem letzten aufruf
			pCounter->nCounterValue += 1;			// Counter hochsetzen
			pCounter->nLastPinState = nPinState;	// neuen State speichern
		}*/

		// Fallende Flanke
		if(pCounter->nLastPinState < 0){			// Hat sich das Pin verändert seit dem letzten aufruf
			pCounter->nCounterValue += 1;			// Counter hochsetzen
			pCounter->nLastPinState = nPinState;	// neuen State speichern
		}


	}
}


int GetCounter (int nCounter){
	if(nCounter >= 0 && nCounter < MAX_COUNTERS){
		COUNTER* pCounter = &arrCounters[nCounter];
		return pCounter->nCounterValue;
	}
	return 0;

}
