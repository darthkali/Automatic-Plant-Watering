
#ifndef RS232
#define RS232

// --- Includes ---
#include "fifo.h"

// --- Prototypes ---
void InitRS232();
int  GetCountRS232();
char GetCharRS232();
void PutCharRS232(char chChar);
void PutStringRS232(char* pszString);

#endif
