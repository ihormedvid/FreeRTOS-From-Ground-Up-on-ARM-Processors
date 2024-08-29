#include <stdio.h>
#include "main.h"
#include "cmsis_os.h"
#include "uart.h"
#include "exti.h"
#include "adc.h"

typedef uint32_t TaskProfiler_t;

TaskProfiler_t Oragne_TaskProfiler, Red_TaskProfiler, Green_TaskProfiler, Blue_TaskProfiler;


void SystemClock_Config(void);
static void MX_GPIO_Init(void);
int __io_putchar(int ch);

void vBlueLedControllerTask(void *pvParams);
void vRedLedControllerTask(void *pvParams);
void vOrangeLedControllerTask(void *pvParams);
void vGreenLedControllerTask(void *pvParams);

const TickType_t _50ms = pdMS_TO_TICKS(50);

int main(void)
{

  HAL_Init();

  SystemClock_Config();


  MX_GPIO_Init();
  USART2_UART_TX_Init();


  printf("System was initialized...\n\r");

  xTaskCreate(vOrangeLedControllerTask,
		  "Orange Task",
		  100,
		  NULL,
		  1,
		  NULL);

  xTaskCreate(vBlueLedControllerTask,
		  "Blue Task",
		  100,
		  NULL,
		  1,
		  NULL);

  xTaskCreate(vRedLedControllerTask,
		  "Red Task",
		  100,
		  NULL,
		  1,
		  NULL);

  xTaskCreate(vGreenLedControllerTask,
		  "Green Task",
		  100,
		  NULL,
		  1,
		  NULL);

  vTaskStartScheduler();



  while (1)
  {



  }

}



void vBlueLedControllerTask(void *pvParams)
{
	int i=0;

	while(1) {
		Blue_TaskProfiler++;
		for(i; i<70000; i++){};
		vTaskDelay(_50ms);
	}

}

void vRedLedControllerTask(void *pvParams)
{
	int i=0;

	while(1) {
		Red_TaskProfiler++;
		for(i; i<70000; i++){};
		vTaskDelay(_50ms);
	}

}

void vOrangeLedControllerTask(void *pvParams)
{
	int i=0;

	while(1) {
		Oragne_TaskProfiler++;
		for(i; i<70000; i++){};
		vTaskDelay(_50ms);
	}

}

void vGreenLedControllerTask(void *pvParams)
{
	int i=0;

	while(1) {
		Green_TaskProfiler++;
		for(i; i<70000; i++){};
		vTaskDelay(_50ms);
	}
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


