
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

// Bildspeicher
char Pixels[8][128] = {0}; // -> 8 Seiten mit je 128 Bytes
char byModiefiedFlags = 0; //welche Seite hat sich veraendert

void UpdateDisplay();

// --- Write single cmd ---
void WriteCmd(char chCmd)
{
	char arrData[2] = {0};

	arrData[1] = chCmd;

	SendI2C(OLED_ADDR, &arrData, sizeof(arrData));
}

// --- Write data ---
void WriteMem(char* pData,char nSize)
{
	char arrData[129] = {0};
	int nIdx = 0;

	arrData[0] = 0x40;

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

	ExecuteThread(UpdateDisplay, 10,0);
	ClrScr();
}


void  UpdateDisplay(){

	static int nPage = 0;

	if(byModiefiedFlags & (1 << nPage)){
		WriteCmd(0xB0 + nPage);
		WriteCmd(0x00);
		WriteCmd(0x10);

		WriteMem(&Pixels[nPage],128);

		byModiefiedFlags &= ~(1 << nPage);
	}


	nPage += 1;
	nPage &=7;
}


// --- Clear screen ---
void ClrScr()
{
	int nPage = 0;

	while (nPage < 8)
	{
		int xPos = 0;

		while(xPos < 128){
			Pixels[nPage][xPos++] = 0;
		}
			byModiefiedFlags |= (1 << nPage);
			nPage += 1;




	}
}


void SetPixel(int x, int y){


	if( x>= 0 && x<= 127 && y >= 0 && y<=63){
		int nPage = y / 8;
		int nBit = y % 8;

		Pixels[nPage][x] |= (1 << nBit);
		byModiefiedFlags |= (1 << nPage);


	}
}


