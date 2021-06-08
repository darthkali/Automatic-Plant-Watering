
// --- Includes ---
#include "i2c.h"

// --- Init I2C ---
void InitI2C()
{
	GPIO_InitTypeDef gpio_init = {0};
	I2C_InitTypeDef i2c_init = {0};

	// enable clock
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	// alternate function pins
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_I2C1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_I2C1);

	// initialize scl, sda
	gpio_init.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
	gpio_init.GPIO_Mode = GPIO_Mode_AF;
	gpio_init.GPIO_OType = GPIO_OType_OD;
	gpio_init.GPIO_PuPd = GPIO_PuPd_UP;

	GPIO_Init(GPIOB, &gpio_init);

	// i2c configuration
	i2c_init.I2C_Mode = I2C_Mode_I2C;
	i2c_init.I2C_DutyCycle = I2C_DutyCycle_2;
	i2c_init.I2C_Ack = I2C_Ack_Enable;
	i2c_init.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	i2c_init.I2C_ClockSpeed = 1000000;

	I2C_Init(I2C1, &i2c_init);

	I2C_Cmd(I2C1, ENABLE);
}

// --- Send data ---
void SendI2C(char nAddr, char* pBuffer, short nCount)
{
	// wait when busy
	while (I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));

	// START condition
	I2C_GenerateSTART(I2C1, ENABLE);

	// bus ready
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));

	// send slave address
	I2C_Send7bitAddress(I2C1, nAddr, I2C_Direction_Transmitter);

	// bus ready
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

	while (nCount--)
	{
		// send data byte
		I2C_SendData(I2C1, *pBuffer++);

		// bus clear
		while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	}

	// STOP condition
	I2C_GenerateSTOP(I2C1, ENABLE);
}

