#ifndef SCHEDULER_H
#define SCHEDULER_H

// --- Includes ---
#include "misc.h"
#include "stm32f4xx.h"


// --- Constants ---
#define MAX_THREADS 16
#define MAX_SLOTS 	10

// --- Thread functions ---
typedef void (*THREAD_FUNC)();

// --- Thread structure ---
typedef struct tagTHREAD{

	THREAD_FUNC pfThreadFunction;
	int			nElapsedTime;
	int 		nCycleTime;
	int 		nSlotNum;
} THREAD;


// --- Prototypes ---
void InitScheduler();
int GetSystemTick();

void ExecuteThread(THREAD_FUNC pfThreadFunc, int nCycleTime, int nSlotNum);

#endif
