#include "stm32f4xx_hal.h"
#include "adc.h"


#define GPIOAEN			(1U<<0)
#define ADC1EN			(1U<<8)
#define ADC_CH1			(1U<<0)
#define ADC_SEQ_LEN_1	0x00
#define CR2_AD0N		(1U<<0)
#define CR2_SWSTART		(1U<<30)
#define SR_EOC			(1U<<1)

void adc_init(void){

	//*** Configure the ADC GPIO pin ***


	// Enable clock access to  GPIOA
	RCC->AHB1ENR |= GPIOAEN;

	// Set the mode of PA1 to analog
	GPIOA->MODER |= (1U<<2);
	GPIOA->MODER |= (1U<<3);

	//*** Configure the ADC module ***

	// Enable clock access to  ADC
	RCC->APB2ENR |= ADC1EN;

	// Conversion sequence start
	ADC1->SQR3 |= ADC_CH1;

	// Conversion sequence length
	ADC1->SQR1 = ADC_SEQ_LEN_1;
	// Enable ADC module
	ADC1->CR2 |= CR2_AD0N;

}

uint32_t read_analog_sensor(void) {

	//Start the conversion
	ADC1->CR2 |= (1U<<30);

	//Wait until the conversion is finished
	while(!(ADC1->SR & 2)){}

	//Return converted data
	return (ADC1->DR);
}
