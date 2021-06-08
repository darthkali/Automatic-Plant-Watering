
#ifndef DISPLAY_H
#define DISPLAY_H

// --- Includes ---
#include "i2c.h"

// --- Prototypes ---
void InitDisplay();
void ClrScr();
void UpdateDisplay();
void SetPixel(int x, int y);

#endif
