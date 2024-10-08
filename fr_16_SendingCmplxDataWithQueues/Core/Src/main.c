#include <stdio.h>
#include "main.h"
#include "cmsis_os.h"


UART_HandleTypeDef huart2;
typedef uint32_t TaskProfiler;


void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
int __io_putchar(int ch);

typedef enum {
	humidity_sensor,
	pressure_sensor
} DataSource_t;

// Define structure type to be passed to the queue
typedef struct {
	uint8_t ucValue;
	DataSource_t sDataSource;
} Data_t;

// Declare two "Data_t" variables that will be passed to the queue
static const Data_t xStructstoSend[2] = { {12, humidity_sensor} , {45, pressure_sensor} };
TaskHandle_t  hum_task_handle, press_task_handle, receiver_handle;

QueueHandle_t  xQueue;

void SenderTask(void *pvParmaters);
void ReceiverTask(void *pvParmaters);

int main(void)
{

  HAL_Init();

  SystemClock_Config();


  MX_GPIO_Init();
  MX_USART2_UART_Init();

  // Create queue to hold a maximum of 3 structures

  xQueue = xQueueCreate(3, sizeof(Data_t));
  // Create a receiver task with a priority of 1

	xTaskCreate(ReceiverTask, "Receiver Task", 100, NULL, 1, &receiver_handle);


  // Create task to send humidity data with a priority of 2

	xTaskCreate(SenderTask, "Humidity Sender Task", 100, (void *) &(xStructstoSend[0]), 2, &hum_task_handle);


  // Create task to send pressure data with a priority of 2

	xTaskCreate(SenderTask, "Pressure Sender Task", 100, (void *) &(xStructstoSend[1]), 2, &press_task_handle);


	vTaskStartScheduler();

  while (1)
  {


  }

}

void SenderTask(void *pvParams)
{
	BaseType_t qStatus;
	const TickType_t wait_time = pdMS_TO_TICKS(100);

	while(1)
	{
		qStatus = xQueueSend(xQueue,pvParams, wait_time); // if the queue is full , then wait for the 'wait_time' until it gets a new slot

		if(qStatus != pdPASS)
		{
			//Do something cause it is an error
		}

		for(int i=0; i<100000; i++);
	}

}
void ReceiverTask(void *pvParams)
{
	BaseType_t qStatus;
	Data_t xStructReceived;

	while(1)
	{
		qStatus = xQueueReceive(xQueue, &xStructReceived, 0);

		//Determine to which member of the struct refers the incoming data

		if(qStatus == pdPASS)
		{
			if(xStructReceived.sDataSource == humidity_sensor)
			{
				printf("The value read by the humidity sensor = %d. \r\n", xStructReceived.ucValue);
			}
			else
			{
				printf("The value read by the pressure sensor = %d. \r\n", xStructReceived.ucValue);
			}
		}
		else
		{
			//some error occurred upon receiving data
		}
	}
}

int uart2_wrtie(int ch) {
	while(!(USART2->SR &0x0080)) {}
	USART2->DR = (ch & 0xFF);

	return ch;
}


int __io_putchar(int ch){
	//HAL_UART_Transmit(&huart2, (uint8_t *)&ch,1,0xFFFF);
	uart2_wrtie(ch);
	return ch;

//	for (uint32_t i = 0; i < 1000; i++) {
//	        __NOP();
//	}
}



void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */


/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM1 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM1) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
