#include <stdbool.h>
#include "main.h"
#include "i2c.h"
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

int main(void)
{

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_USART2_UART_Init();
  ssd1306_Init();
  ssd1306_Fill(0);
  ssd1306_UpdateScreen();

  bool flag = 0;
  uint8_t c = 0;
  char b[] = "30.0C";
  char b2[4];
  while (1)
  {
	  wait(500);
	  c++;
	  flag = !flag;
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, flag);
	  ssd1306_DrawRectangle(0, 0, 16*5+5, 31, flag);
	  ssd1306_SetCursor(1, 1);
	  ssd1306_WriteString(b, Font_16x26,  1);


	  ssd1306_SetCursor(0,32);
	  ssd1306_WriteString("Target:", Font_6x8,  1);
	  ssd1306_SetCursor(0,40);
	  itoa(c,b2,4);
	  ssd1306_WriteString(b2, Font_11x18,  1);

	  ssd1306_UpdateScreen();
  }

}


void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

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


void Error_Handler(void)
{
  __disable_irq();
}
