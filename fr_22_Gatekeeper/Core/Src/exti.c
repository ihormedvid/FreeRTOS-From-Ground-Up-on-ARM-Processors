#include "stm32f4xx_hal.h"
#include "exti.h"

void p13_interrupt_init(void) {

	// Enable GPIOC clock
	RCC->AHB1ENR |= 4; // 4 = 0B 0100

	// Enable SYSCFG clock
	RCC->APB2ENR |= 0x4000;

	// Configure PC13 for push button interrupt
	GPIOC->MODER &= ~0xC000000;

	// Clear port selection for EXTI13
	SYSCFG->EXTICR[3] &= ~0x00F0;

	// Select port C for EXTI13
	SYSCFG->EXTICR[3] |= 0x0020;

	// unmask EXTI13
	EXTI->IMR |= 0x2000;

	// Select falling edge trigger
	EXTI->FTSR |= 0x2000;

	  /*  set the priority of the interrupt associated with the EXTI (External Interrupt) lines 15 to 10 */
	NVIC_SetPriority(EXTI15_10_IRQn,6);

	    /* Enable EXTI  in the NVIC Nested Vector Interrupt Controller for the group of lines 15 till 10 */
	NVIC_EnableIRQ(EXTI15_10_IRQn); // EXTI15_10_IRQn refers to the group of external interrupt lines 15 to 10.
}

void gpio_init(void)
{
	//enable clock access to GPIO C
	RCC->AHB1ENR |= 4;

	//set Pin C13 Mode to input -> As default is 0x0000 0000 for other ports there is no need to do anything

}

uint8_t read_digital_sensor(void)
{
	//we use GPIO INPUT DATA REGISTER for PC13
	if(GPIOC->IDR & 0x2000)
	{
		return 1; // it depends on the MCU, either pressed or not pressed
	}
	else
	{
		return 0; // it depends on the MCU, viceversa of previous state
	}
}
