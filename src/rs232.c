
// --- Includes ---
#include "rs232.h"
#include "misc.h"
#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_usart.h"

// --- Variables ---
BUFFER RxBuffer = {0};
BUFFER TxBuffer = {0};

// --- Init RS232 ---
void InitRS232()
{
	USART_InitTypeDef uart_init = {0};
	GPIO_InitTypeDef  gpio_init = {0};
	NVIC_InitTypeDef  nvic_init = {0};

	// enable clock for USART module
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	// config PA2 and PA3 as alternate function USART2
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2);

	// config pins as AF pins
	gpio_init.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
	gpio_init.GPIO_Mode = GPIO_Mode_AF;
	gpio_init.GPIO_OType = GPIO_OType_PP;

	GPIO_Init(GPIOA, &gpio_init);

	// config uart
	uart_init.USART_Mode		= USART_Mode_Rx | USART_Mode_Tx;
	uart_init.USART_WordLength 	= USART_WordLength_8b;
	uart_init.USART_StopBits	= USART_StopBits_1;
	uart_init.USART_Parity		= USART_Parity_No;
	uart_init.USART_BaudRate	= 115200;

	USART_Init(USART2, &uart_init);

	// config interrupt
	nvic_init.NVIC_IRQChannelPreemptionPriority = 8;
	nvic_init.NVIC_IRQChannel = USART2_IRQn;
	nvic_init.NVIC_IRQChannelCmd = ENABLE;

	// interrupt config
	NVIC_Init(&nvic_init);

	// enable receive interrupt
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);

	// finally
	USART_Cmd(USART2, ENABLE);
}

// --- USART2 interrupt handler ---
void USART2_IRQHandler()
{
	// IRQ from receive char
	if (USART_GetITStatus(USART2, USART_IT_RXNE) == SET)
	{
		char chData = USART_ReceiveData(USART2);

		WriteBuffer(&RxBuffer,chData);
	}

	// IRQ from transmit char
	if (USART_GetITStatus(USART2, USART_IT_TXE) == SET)
	{
		if (CountBuffer(&TxBuffer) > 0)
		{
			char chData = ReadBuffer(&TxBuffer);

			USART_SendData(USART2, chData);
		}
		else
			USART_ITConfig(USART2, USART_IT_TXE, DISABLE);
	}
}

// --- Get count char in rx buffer---
int GetCountRS232()
{
	return CountBuffer(&RxBuffer);
}

// --- Get char from RS232 ---
char GetCharRS232()
{
	char chData;

	// synchronization required!
	USART_ITConfig(USART2, USART_IT_RXNE, DISABLE);
	chData = ReadBuffer(&RxBuffer);
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);

	return chData;
}

// --- Put char to RS232 ---
void PutCharRS232(char chChar)
{
	while (CountBuffer(&TxBuffer) > MAXBUFFER / 2);

	USART_ITConfig(USART2, USART_IT_TXE, DISABLE);
	WriteBuffer(&TxBuffer,chChar);
	USART_ITConfig(USART2, USART_IT_TXE, ENABLE);
}

// --- Put string to RS232 ---
void PutStringRS232(char* pszString)
{
	while (*pszString)
	{
		PutCharRS232(*pszString);
		pszString += 1;
	}
}
