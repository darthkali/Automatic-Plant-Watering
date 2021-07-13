
// --- Includes ---
#include "fifo.h"

// --- Clear buffer ---
void ClearBuffer(BUFFER* pBuffer)
{
	pBuffer->nCount = 0;								// clear buffer
	pBuffer->nHead = 0;									// clear head
	pBuffer->nTail = 0;									// clear tail
}

// --- Get buffer count ---
short CountBuffer(BUFFER* pBuffer)
{
	return pBuffer->nCount;
}

// --- Write char to buffer ---
void WriteBuffer(BUFFER* pBuffer,char chData)
{
	if (pBuffer->nCount < MAXBUFFER)					// buffer free
	{
		pBuffer->arrBuffer[pBuffer->nHead++] = chData;	// add to buffer

		if (pBuffer->nHead >= MAXBUFFER)				// head overflow
			pBuffer->nHead  = 0;						// reset head

		pBuffer->nCount += 1;							// inc count
	}
}

// --- Read char from buffer ---
char ReadBuffer(BUFFER* pBuffer)
{
	if (pBuffer->nCount > 0)							// not empty
	{
		char chData = pBuffer->arrBuffer[pBuffer->nTail++];

		if (pBuffer->nTail >= MAXBUFFER)				// tail overflow
			pBuffer->nTail  = 0;						// reset tail

		pBuffer->nCount-= 1;							// dec count

		return chData;
	}

	return 0;
}
