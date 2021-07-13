#include "adc.h"

// macros

#define ADC_PORT		GPIOC
#define ADC_PIN1		GPIO_Pin_0
#define ADC_PIN2		GPIO_Pin_1
#define ADC_PIN3		GPIO_Pin_2
#define ADC_PIN4		GPIO_Pin_3
#define ADC_PIN_SRC		GPIO_PinSource10

// --- Init ADC ---

void InitADC(){

	GPIO_InitTypeDef gpio_init = {0};
	ADC_InitTypeDef adc_init = {0};
	ADC_CommonInitTypeDef adc_common = {0};

	// enable ADC port and ADC1 clock
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);



	// configure analog pins
	gpio_init.GPIO_Pin = ADC_PIN1 | ADC_PIN2 | ADC_PIN3 | ADC_PIN4;
	gpio_init.GPIO_Mode = GPIO_Mode_AN;
	gpio_init.GPIO_PuPd = GPIO_PuPd_NOPULL;


	// init ADC pins
	GPIO_Init(ADC_PORT, &gpio_init);


	// setup common adc params
	adc_common.ADC_Mode = ADC_Mode_Independent;
	adc_common.ADC_Prescaler = ADC_Prescaler_Div2;
	adc_common.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;


	// common adc init
	ADC_CommonInit(&adc_common);


	// setup adc1 parameters
	adc_init.ADC_Resolution = ADC_Resolution_12b;
	adc_init.ADC_ContinuousConvMode = DISABLE;
	adc_init.ADC_ScanConvMode = DISABLE;
	adc_init.ADC_NbrOfConversion = 1;


	// init adc
	ADC_Init(ADC1, &adc_init);


	// enable adc
	ADC_Cmd(ADC1, ENABLE);

}

// --- read analog channel ---
short GetAnalog(int channel){

	if (channel >= 0 && channel < 4){
		ADC_RegularChannelConfig(ADC1, ADC_Channel_10 + channel, 1, ADC_SampleTime_480Cycles);

		ADC_SoftwareStartConv(ADC1);
		while (ADC_GetFlagStatus(ADC1, ADC_CSR_EOC1) == RESET);
	}

	return ADC_GetConversionValue(ADC1);
}
