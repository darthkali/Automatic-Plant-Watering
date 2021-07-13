// --- Includes ---
#include "ports.h"
#include "system.h"
#include "timing.h"
#include "scheduler.h"
#include "counter.h"
#include "rs232.h"
#include "i2c.h"
#include "adc.h"
#include "display.h"
#include "moisture.h"

char bNewCurve = 1;
int y = 0;
int x = 0;

int wert = 0;

/*
void MyThread5(){
	ToggleGPIOPin(GPIOA, 5);
}

void MyThread(){
	ToggleGPIOPin(GPIOA, 6);
}
*/

// Main Task / Idle Task
int main(void){

	InitSystem();
	InitPorts();
	InitScheduler();
	InitCounter();
	InitRS232();
	InitI2C();
	InitADC();
	//InitMoisture();

	InitDisplay();
	LocateLCD(20, 0);
	PutStringLCD("Hello World!\r\nSecondLine :)");
	DrawFrame(0,0, 127, 63);
	DrawFrame(0,0, 127, 8);



    while(1){

    	//ExecuteThread(MyThread, 100,5);
    	//ExecuteThread(MyThread5, 100,0);

    	int nAdc = GetAnalog(0);

    	y = 64 - nAdc * 54 / 4096;

    	if (bNewCurve){
    		LocateLCD(0, y);
    		bNewCurve = 0;
    	}
    	DrawLineTo(x++,y);

    	if(x == 128){
    		bNewCurve = 1;

    		x = 0;
    	}

    	Delay(100);
    }
}
