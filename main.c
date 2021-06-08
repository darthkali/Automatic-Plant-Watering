// --- Includes ---
#include "ports.h"
#include "system.h"
#include "timing.h"
#include "scheduler.h"
#include "counter.h"
#include "rs232.h"
#include "i2c.h"
#include "display.h"


// Main Task / Idle Task
int main(void){

	InitSystem();
	InitPorts();
	InitScheduler();
	InitCounter();
	InitRS232();
	InitI2C();

	InitDisplay();


    while(1){

    	int x = 10;

    	while(x < 120){
    		SetPixel(x++,10);
    	}


    }
}
