
#include "main.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "ssd1306.h"

#include "menuDisplay.h"
#include "ioManager.h"
#include "lwow/lwow.h"
#include "lwow/devices/lwow_device_ds18x20.h"
#include "scan_devices.h"

extern lwow_ll_drv_t lwow_ll_drv_stm32_hal; 		//Low-level LWOW driver. Defines UART writes, reads, inits, deinits.
extern UART_HandleTypeDef huart2; 					//UART port for LWOW connection
lwow_t ow; 											//One-wire instance
lwow_rom_t rom_ids[1]; 								//Found devices list.
size_t rom_found; 									// Number of found OW ROMs.


Data data = {1,0.1,-0.5,0,0,100,0,POWER_OFF,""};	//Data model used by pretty much everything

void SystemClock_Config(void);

int main(void)
{

  HAL_Init();
  SystemClock_Config();

  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_USART2_UART_Init();

  //Init display
  menuDisplay_Init();
  data.statusMessage = "LWOW scan";
  menuDisplay_Update(0);

  //Init LWOW
  lwow_init(&ow, &lwow_ll_drv_stm32_hal, &huart2);

  //Thermometer must be found to ensure safe operation.
  while(!scan_onewire_devices(&ow, rom_ids, LWOW_ARRAYSIZE(rom_ids), &rom_found) == lwowOK)
	  wait(100);

  //Configure found DS18B20 thermometer
  lwow_ds18x20_start(&ow, rom_ids);
  lwow_ds18x20_set_resolution(&ow, rom_ids, 12);

  //Start Peltier PWM timer.
  MX_TIM4_Init();
  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4);

  //Start display and logic timer.
  MX_TIM3_Init();
  HAL_TIM_Base_Start_IT(&htim3);

  //Start cooling!
  enableCooling();

  while (1);

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
