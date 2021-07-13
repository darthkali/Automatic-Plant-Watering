
#include "scheduler.h"

// --- Variables ---
THREAD arrThreads[MAX_THREADS] = {0};
int nThreadCount = 0;
int nThreadSlot = 0;
int nSystemTick = 0;

// --- Init scheduler ---
void InitScheduler()
{
	SysTick_Config(SystemCoreClock / 1000);					// 1ms clock
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);		// main clock as source
}

// --- Get system tick ---
int GetSysTick()
{
	return nSystemTick;
}

// --- System tick / Scheduler ---
void SysTick_Handler()
{
	int nThread = 0;

	nSystemTick += 1;										// 1ms System Tick

	while (nThread < nThreadCount)
	{
		THREAD* pThread = &arrThreads[nThread++];

		if (pThread->pfThreadFunction)						// function pointer not null
		{
			pThread->nElapsedTime += 1;

			if (pThread->nElapsedTime >= pThread->nCycleTime &&
				pThread->nSlotNum == nThreadSlot)
			{
				pThread->pfThreadFunction();				// call thread function
				pThread->nElapsedTime = 0;
			}
		}
	}

	if (++nThreadSlot >= MAX_SLOTS)							// next thread slot
		nThreadSlot = 0;
}

// --- Execute new thread ---
void ExecuteThread(THREAD_FUNC pfThreadFunc, int nCycleTime, int nSlotNum)
{
	THREAD* pThread = &arrThreads[nThreadCount++];

	pThread->pfThreadFunction = pfThreadFunc;
	pThread->nElapsedTime = 0;
	pThread->nCycleTime = nCycleTime;
	pThread->nSlotNum = nSlotNum;
}
