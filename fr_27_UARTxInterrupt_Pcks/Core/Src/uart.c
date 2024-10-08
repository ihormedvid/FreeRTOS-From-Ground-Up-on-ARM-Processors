#include "stm32f4xx_hal.h"
#include "uart.h"
int __io_putchar(int ch);

UART_HandleTypeDef huart2;


void USART2_UART_TX_Init(void)
{

  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK) {}
}


void USART2_UART_RX_Init(void)
{

  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK) {}
}

int USART2_write(int ch) {
	while(!(USART2 -> SR & 0x0080)) {}
	USART2-> DR = (ch & 0xFF);

	return ch;
}

// Read a character from USART2
char USART2_read(void) {

	while(!(USART2->SR & 0x0020)) {} // wait until char arrives
	return USART2->DR;
}

int __io_putchar(int ch){
	USART2_write(ch);

	return ch;
}
