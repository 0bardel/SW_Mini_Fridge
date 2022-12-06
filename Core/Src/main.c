#include <stdbool.h>
#include "main.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "ssd1306.h"


void wait(uint32_t time){
uint32_t target = uwTick + time;
while(uwTick != target);
};

struct Data{
	bool fanEnable;
	bool peltEnable;

	float Kp;
	float Ki;
	float Kd;

	float measuredTemp;
	float targetTemp;
} data = {0,0,0,0,0,0,0};



void SystemClock_Config(void);

int main(void)
{

  HAL_Init();


  SystemClock_Config();


  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_USART2_UART_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();

  HAL_TIM_Base_Start_IT(&htim3);
  ssd1306_Init();
  ssd1306_Fill(0);
  ssd1306_UpdateScreen();

  bool flag = 0;
  uint8_t c = 0;
  char b[] = "30.0C";
  char b2[8];
  while (1)
  {
	  wait(500);
	  c++;
	  flag = !flag;

	  ssd1306_DrawRectangle(0, 0, 16*5+5, 31, flag);
	  ssd1306_SetCursor(1, 1);
	  ssd1306_WriteString(b, Font_16x26,  1);


	  ssd1306_SetCursor(0,32);
	  ssd1306_WriteString("Thread:", Font_6x8,  1);
	  ssd1306_SetCursor(0,40);
	  itoa(c,b2,10);
	  ssd1306_WriteString(b2, Font_11x18,  1);
	  ssd1306_SetCursor(64,40);
	  itoa(getTIM3Counter(),b2,10);
	  ssd1306_WriteString(b2, Font_11x18,  1);
	  ssd1306_UpdateScreen();
  }


}


void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

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

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

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
