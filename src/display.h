
#ifndef DISPLAY_H
#define DISPLAY_H

// --- Includes ---
#include "i2c.h"

// --- Prototypes ---
void InitDisplay();

void ClrScr();
void PutChar(char chChar);

void SetPixel(int x,int y);
void DrawLine(int x0,int y0, int x1, int y1);
void DrawFullCircle(int x0, int y0, int radius);


#endif
