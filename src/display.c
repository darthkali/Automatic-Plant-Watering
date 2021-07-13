
// --- Includes ---
#include "display.h"

// --- Constants ---
#define OLED_ADDR	0x78					// i2c addr

// Init sequence
char arrOLEDInit[] =
{
		0xAE,
		0x20,
		0x10,
		0xB0,
		0xC8,
		0x00,
		0x10,
		0x40,
		0x81,
		0xFF,
		0xA1,
		0xA6,
		0xA8,
		0x3F,
		0xA4,
		0xD3,
		0x00,
		0xD5,
		0xF0,
		0xD9,
		0x22,
		0xDA,
		0x12,
		0xDB,
		0x20,
		0x8D,
		0x14,
		0xAF
};

// --- Pixels ---
char arrPixels[8][128] = {0};			// 8 pages with 128 bytes each
char byModifiedFlags = 0;				// 8 bits = 8 pages modified
int  nColumn = 0;						// cursor position
int  nRow = 0;

// --- font ---
#include "fonts.c"

// --- Prototypes ---
void UpdateDisplay();

// --- Write single cmd ---
void WriteCmd(char chCmd)
{
	char arrData[2] = {0,chCmd};

	SendI2C(OLED_ADDR, &arrData, sizeof(arrData));
}

// --- Write data ---
void WriteMem(char* pData,char nSize)
{
	char arrData[129] = {0x40};
	int nIdx = 0;

	while (nIdx < nSize)
	{
		arrData[nIdx + 1] = pData[nIdx];
		nIdx += 1;
	}

	SendI2C(OLED_ADDR, &arrData, sizeof(arrData));
}

// --- Init display ---
void InitDisplay()
{
	int nCmd = 0;

	while (nCmd < sizeof(arrOLEDInit))
		WriteCmd(arrOLEDInit[nCmd++]);

	ExecuteThread(UpdateDisplay,10,0);

	ClrScr();
}

// --- Update Display ---
void UpdateDisplay()
{
	static int nPage = 0;

	if (byModifiedFlags & (1 << nPage))
	{
		WriteCmd(0xB0 + nPage);
		WriteCmd(0x00);
		WriteCmd(0x10);

		WriteMem(&arrPixels[nPage],128);

		byModifiedFlags &= ~(1 << nPage);
	}

	nPage += 1;
	nPage &= 7;
}

// --- Clear screen ---
void ClrScr()
{
	int nPage = 0;

	while (nPage < 8)
	{
		int xPos = 0;

		while (xPos < 128)
			arrPixels[nPage][xPos++] = 0;

		byModifiedFlags |= (1 << nPage);
		nPage += 1;

		nColumn = 0;
		nRow = 0;
	}
}

// --- Put single char ---
void PutChar(char chChar)
{
	int nPos = 0;
	int nWidth = 6;

	while (nPos < nWidth)
		arrPixels[nRow][nColumn++] = abFont6x8[chChar - ' '][nPos++];
}

// --- Set pixel at x,y ---
void SetPixel(int x,int y)
{
	if (x >= 0 && x <= 127 &&
		y >= 0 && y <= 63)
	{
		int nPage = y / 8;
		int nBit  = y % 8;

		arrPixels[nPage][x] |= (1 << nBit);
		byModifiedFlags     |= (1 << nPage);
	}
}

#define abs(a) ((a) <  0  ? -(a) : (a))

// --- Draw line ---
void DrawLine(int x0,int y0, int x1, int y1)
{
	int dx =  abs(x1-x0), sx = x0<x1 ? 1 : -1;
	int dy = -abs(y1-y0), sy = y0<y1 ? 1 : -1;
	int err = dx + dy, e2;

	while (1)
	{
		SetPixel(x0,y0);

		if (x0 == x1 && y0 == y1) break;

		e2 = 2 * err;

		if (e2 > dy) { err += dy; x0 += sx; }
		if (e2 < dx) { err += dx; y0 += sy; }
	}
}

// --- Draw Full Circle from x0 y0 with a radius
void DrawFullCircle(int x0, int y0, int radius)
{
    int f = 1 - radius;
    int ddF_x = 0;
    int ddF_y = -2 * radius;
    int x = 0;
    int y = radius;
    // Orthogonal Points
    SetPixel(x0, y0 + radius);
    SetPixel(x0, y0 - radius);
    SetPixel(x0 + radius, y0);
    SetPixel(x0 - radius, y0);
    //
    while(x < y)
    {
      if(f >= 0)
      {
        y--;
        ddF_y += 2;
        f += ddF_y;
      }
      x++;
      ddF_x += 2;
      f += ddF_x + 1;
      SetPixel(x0 + x, y0 + y);
      SetPixel(x0 - x, y0 + y);
      SetPixel(x0 + x, y0 - y);
      SetPixel(x0 - x, y0 - y);
      SetPixel(x0 + y, y0 + x);
      SetPixel(x0 - y, y0 + x);
      SetPixel(x0 + y, y0 - x);
      SetPixel(x0 - y, y0 - x);
    }
}

