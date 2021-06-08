#ifndef FIFO_H
#define FIFO_H

// --- Defines ---
#define MAXBUFFER		    256					// max buffers

// --- buffer ---
typedef struct BUFFER
{
	char  arrBuffer[MAXBUFFER];					// buffer
	short nCount;								// count
	short nHead;								// head - position Schreibzeiger
	short nTail;								// tail - position Lesezeigerzeiger
} BUFFER;

// --- Prototypes ---
void  WriteBuffer(BUFFER* pBuffer,char chData);
short CountBuffer(BUFFER* pBuffer);
void  ClearBuffer(BUFFER* pBuffer);
char  ReadBuffer(BUFFER* pBuffer);

#endif
