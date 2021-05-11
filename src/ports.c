// --- Includes ---
#include <ports.h>

// --- Variables ---

// --- Prototypes ---
// init ports A und C
void InitPorts(){

	// init struct
	GPIO_InitTypeDef gpio_init = {0};

	// enable clock for ports A and C
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);

	//Lampe auf Board
	gpio_init.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6; 		// mögliche schreibweise um andere Ports auch noch anzusprechen | GPIO_Pin_6;
	gpio_init.GPIO_Mode = GPIO_Mode_OUT; 	// Output
	gpio_init.GPIO_OType = GPIO_OType_PP; 	//Outtype

	// init port pin
	GPIO_Init(GPIOA, &gpio_init);



	// Taster Blau
	gpio_init.GPIO_Pin = GPIO_Pin_13; 		// mögliche schreibweise um andere Ports auch noch anzusprechen | GPIO_Pin_6;
	gpio_init.GPIO_Mode = GPIO_Mode_IN; 	// Input

	// init port pin
	GPIO_Init(GPIOC, &gpio_init);

}


int GetGPIOPin(GPIO_TypeDef* pPort, int nPin){

	return pPort->IDR >> nPin & 1; 		// InputDataRegister & sorgt dafür, das nur das unterste Bit übrig bleibt
}


void SetGPIOPin(GPIO_TypeDef* pPort, int nPin, int nValue){

	int nMask = 1 << nPin; // nPin = 16 -> nMask = 16

	if (nValue){
		pPort->BSRRL = nMask;	//16Bit Register
	} else{
		pPort->BSRRH = nMask;	//16Bit Register
	}

}

// Toggle Pin in Port
void ToggleGPIOPin(GPIO_TypeDef* pPort, int nPin){

	int nMask = 1 << nPin; 	// nPin = 16 -> nMask = 16

	// BSRR with (ODR xor Mask) or (Mask shifted 16 Bits left)
	pPort->BSRR = (pPort->ODR ^ nMask) | (nMask << 16); 	//XOR Verknüpfung (^)	// | = Logisches Oder
}
