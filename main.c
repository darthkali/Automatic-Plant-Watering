// --- Includes ---
#include "ports.h"
#include "system.h"
#include "timing.h"
#include "scheduler.h"


// Thread 1
void MyThread1() {
	ToggleGPIOPin(GPIOA, 5);
}

// Thread 2
void MyThread2() {
	ToggleGPIOPin(GPIOA, 6);
}



// Main Task / Idle Task
int main(void){

	InitSystem();
	InitPorts();
	InitScheduler();

	ExecuteThread(MyThread1, 100, 0);
	ExecuteThread(MyThread2, 100, 0);
    while(1){}
}
