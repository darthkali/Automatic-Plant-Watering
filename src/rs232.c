// --- Includes ---
#include  "rs232.h"
#include "misc.h"
#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_gpio.h"



// --- Variables ---

BUFFER RxBuffer =  {0};
BUFFER TxBuffer =  {0};


// --- Prototypes ---
void InitRS232(){

	USART_InitTypeDef uart_init = {0};
	GPIO_InitTypeDef gpio_init 	= {0};
	NVIC_InitTypeDef nvic_init = {0};


	// enable Clock for USART module
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	// config PA2 and PA3 as alternate function
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);

	gpio_init.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;	// Pin 2 & 3 ansprechen
	gpio_init.GPIO_Mode = GPIO_Mode_AF;				// als alternative Funktionen
	gpio_init.GPIO_OType = GPIO_OType_PP;			// Push Pull

	GPIO_Init(GPIOA, &gpio_init);

	//config uart
	uart_init.USART_Mode 		= USART_Mode_Rx | USART_Mode_Tx;
	uart_init.USART_WordLength 	= USART_WordLength_8b;
	uart_init.USART_StopBits 	= USART_StopBits_1;
	uart_init.USART_Parity 		= USART_Parity_No;
	uart_init.USART_BaudRate 	= 115200;

	USART_Init(USART2, &uart_init);


	//config interrupt
	nvic_init.NVIC_IRQChannelPreemptionPriority = 8;
	nvic_init.NVIC_IRQChannel = USART2_IRQn;
	nvic_init.NVIC_IRQChannelCmd = ENABLE;

	//interrupt config
	NVIC_Init(&nvic_init);

	// enable recieve interrupt
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);


	// erst ab hier laeuft di UART
	USART_Cmd(USART2, ENABLE);
}

// USART2 interrupt handler
void USART2_IRQHandler(){

	// was IRQ from receive char
	if(USART_GetITStatus(USART2, USART_IT_RXNE) == SET){
		char chData = USART_ReceiveData(USART2);

		WriteBuffer(&RxBuffer, chData);
	}

	// was IRQ from transmit char
	if(USART_GetITStatus(USART2, USART_IT_TXE)== SET){

		if(CountBuffer(&TxBuffer) > 0){
			char chData = ReadBuffer(&TxBuffer);
			USART_SendData(USART2, chData);
		}else{
			USART_ITConfig(USART2, USART_IT_TXE, DISABLE);
		}
	}
}

int GetCountRS232(){
	return CountBuffer(&RxBuffer);
}


char GetCharRS232(){

	char chData;

	// dont allow interrupt
	USART_ITConfig(USART2, USART_IT_RXNE,DISABLE);

	//Read char from Buffer
	chData = ReadBuffer(&RxBuffer);

	//  allow interrupt
	USART_ITConfig(USART2, USART_IT_RXNE,ENABLE);

	return chData;
}


void PutCharRS232(char chChar){

	while(CountBuffer(&TxBuffer) >= MAXBUFFER /2);

	// dont allow interrupt
	USART_ITConfig(USART2, USART_IT_TXE, DISABLE);

	//Write char to Buffer
	WriteBuffer(&TxBuffer,chChar);

	// dont allow interrupt
	USART_ITConfig(USART2, USART_IT_TXE, ENABLE);

}


void PutStringRS232(char* pszString){
	while (*pszString){
		PutCharRS232(*pszString++);
	}
}
