#include "moisture.h"
#include "ports.h"

// --- Variables ---
int nNextCallState = 0;
int nTime = 0;

int analogIn = 0;
int analog = 0;
int test = 0;
int threshold =  0;

char moistureString[20] = {0};


// --- Types ---
enum STATE enState = stINIT;


int CalcLinear(float yMax, float yMin, float xMax, float xMin, float value){
	float m = 0;
	float n = 0;

	m = (yMax - yMin) / (xMax - xMin);
	n = yMin - m * xMin;

	return (int)(m * value  + n);
}

void InitMoisture(){
	analog = GetAnalog(0);
	analogIn = GetAnalog(0);
	threshold =  CalcLinear(Y_MAX, Y_MIN, SENSOR_VALUE_MAX, SENSOR_VALUE_MIN, THRESHOLD);

	ExecuteThread(StateMachine, 1000, 0);
	ExecuteThread(DrawMoistureCurveAndUpdateMoistureValueOnScreen, 100, 0);
}


int analogInput() {
	analogIn = GetAnalog(0);
	return analog =(analog * 29 + analogIn) / 30;
}


void setNextStateAndTheWaitTime(enum STATE state, int time) {
	nNextCallState = nTime + time;
	enState = state;
}

void StateMachine2() {
	//test != test;
	//SetOutput(2, test); //Pump OFF
	ToggleGPIOPin(OUT2);

}
void StateMachine() {

	switch (enState) {
		case stINIT:
			SetOutput(2, 0); //Pump OFF
			enState = stCHECK;
			break;

		case stCHECK:
			if(analogInput() > THRESHOLD){
				setNextStateAndTheWaitTime(stPUMP, PUMP_TIME); //pump for x second
				break;
			}

			setNextStateAndTheWaitTime(stWAIT, WAIT_TIME);    //wait y minutes
			break;

		case stPUMP:
			SetOutput(2, 1); //Pump ON

			if (nNextCallState - nTime <= 0) {
				SetOutput(2, 0); //Pump OFF
				setNextStateAndTheWaitTime(stWAIT, WAIT_TIME);    //wait y minutes
			}
			break;

		case stWAIT:
			if (nNextCallState - nTime <= 0) {
				enState = stCHECK;                  //check Status
			}
			break;
	}
	nTime++;
}



void DrawMoistureCurve(){
	float moisture = (float)analogInput();
	int y = 0;

	y = CalcLinear(Y_MAX, Y_MIN, SENSOR_VALUE_MAX, SENSOR_VALUE_MIN, moisture);

	if (y < Y_MIN){ y = Y_MIN; }
	if (y > Y_MAX){ y = Y_MAX; }

	SetPixel(126,y);
	ScrollDisplayArea(1,6,1,126);

	DrawLine(0,threshold,127,threshold);
	SetPixel(126,9);
	SetPixel(126,55);
}

void UpdateMoistureValueOnScreen(){
	float moisture = (float)analogInput();
	LocateLCD(1,56);
	sprintf(moistureString, "Moisture:=%4d%%", CalcLinear(0, 100, SENSOR_VALUE_MAX, SENSOR_VALUE_MIN, moisture));
	PutStringLCD(moistureString);
}

void DrawMoistureCurveAndUpdateMoistureValueOnScreen(){
	DrawMoistureCurve();
	UpdateMoistureValueOnScreen();
}

