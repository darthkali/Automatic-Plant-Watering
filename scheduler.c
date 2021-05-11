// --- Includes ---
#include "scheduler.h"
#include "ports.h"

// --- Variables ---
THREAD arrThreads[MAX_THREADS] = {0};
int nThreadCount = 0;
int nSystemTick = 0;
int nThreadSlot = 0;

// --- Prototypes ---
void InitScheduler(){
	SysTick_Config(SystemCoreClock / 1000);				//Ticks zwischen 2 INterrupts - 1ms clock
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);	//HighSpeedClock - main clock as source
}

int GetSystemTick(){
	return nSystemTick;
}

// --- System Tick ---
void SysTick_Handler(){
	int nThread = 0;

	nSystemTick += 1;		//1 ms System Tick


	while(nThread < nThreadCount){
		THREAD* pThread = &arrThreads[nThread++];

		if (pThread->pfThreadFunction){				// function pointer not null
			pThread->nElapsedTime += 1;

			if (pThread->nElapsedTime > pThread->nCycleTime && pThread->nSlotNum == nThreadSlot){

				pThread->pfThreadFunction();		//call thread function
				pThread->nElapsedTime = 0;
			}
		}
	}

	if (++nThreadSlot >= MAX_SLOTS){
		nThreadSlot = 0;
	}

	//alle threads durchgehen
	// schauen ob bei einer die verstrichene Zeit mit der max zeit oder so
}

void ExecuteThread(THREAD_FUNC pfThreadFunc, int nCycleTime, int nSlotNum){

	THREAD* pThread = &arrThreads[nThreadCount++];

	pThread->pfThreadFunction = pfThreadFunc;
	pThread->nCycleTime = nCycleTime;
	pThread->nElapsedTime = 0;
	pThread->nSlotNum = 0;
}
