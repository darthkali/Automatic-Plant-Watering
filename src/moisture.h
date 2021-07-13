#ifndef MOISTURE_H
#define MOISTURE_H

#define THRESHOLD     		3300  	// Breakpoint on which humidity the system will react [0.59]
#define WAIT_TIME       	10  	// how long the system will stay in the WAIT State [1800 - every 30 minutes]
#define PUMP_TIME       	3		// how long the system will stay in the PUMP State [2]
#define Y_MIN				10.0		// Minimum Y-Value to draw the line
#define Y_MAX				53.0		// Maximum Y-Value to draw the line
#define SENSOR_VALUE_MIN 	2520.0
#define SENSOR_VALUE_MAX	4095.0


enum STATE { stINIT, stCHECK, stPUMP, stWAIT };

void InitMoisture();
void StateMachine();
void StateMachine2();
void DrawMoistureCurve();
void UpdateMoistureValueOnScreen();
void DrawMoistureCurveAndUpdateMoistureValueOnScreen();

#endif


