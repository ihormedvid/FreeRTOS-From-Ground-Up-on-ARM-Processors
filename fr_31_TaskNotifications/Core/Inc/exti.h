#ifndef INC_EXTI_H_
#define INC_EXTI_H_

void p13_interrupt_init(void);
void gpio_init(void);
uint8_t read_digital_sensor(void);
#include "stm32f4xx_hal.h"

#endif
