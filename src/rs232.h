#ifndef RS232_H
#define RS232_H

// --- Includes ---

#include "fifo.h"

// --- Constants ---



// --- Prototypes ---

void InitRS232();
char GetCharRS232();
void PutCharRS232(char chChar);
void PutStringRS232(char* pszString);
int GetCountRS232();



#endif
