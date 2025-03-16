/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "nema_core.h"
#include "nema_hal.h"
#include "nema_utils.h"
#include "nema_graphics.h"
#include "nema_cmdlist.h"
#include "nema_sys_defs.h"
#include "hana.h"
#include "init.h"

#define TOUCH_I2C_ADDRESS 0x41 // Replace with your touch controller's I2C address
volatile uint8_t TouchINT_irq = 0;
uint16_t colors[] =
{
  0xF800, // Red
  0x07E0, // Green
  0x001F, // Blue
  0xFFFF, // White
  0x0000, // Black
  0xFFE0, // Yellow
  0xF81F, // Magenta
  0x07FF  // Cyan
};

int main(void)
{
  HAL_Init();
  InitClocks();
  InitPeripherals();
  InitHana();

  HAL_GPIO_WritePin(LCD_DISP_RESET_GPIO_Port, LCD_DISP_RESET_Pin, GPIO_PIN_SET);
  HAL_NVIC_SetPriority(EXTI6_IRQn, 7, 0);
  HAL_NVIC_EnableIRQ(EXTI6_IRQn);
  HAL_GPIO_WritePin(CTP_RST_GPIO_Port, CTP_RST_Pin, GPIO_PIN_SET);
  HAL_Delay(10);
  HAL_GPIO_WritePin(CTP_RST_GPIO_Port, CTP_RST_Pin, GPIO_PIN_RESET);
  HAL_Delay(10);
  HAL_GPIO_WritePin(CTP_RST_GPIO_Port, CTP_RST_Pin, GPIO_PIN_SET);
  HAL_Delay(10);

  DrawBackground(COLOR_WHITE);
  DrawHline(100, 10, 100, 0xF800);
  DrawVLine(300, 100, 100, 0xF900);
  DrawCircle(120, 300, 100, 0x3333);
  DrawRectangle(150, 150, 200, 200, 0x5555);
  DrawRoundedRectangle(500, 100, 100, 100, 10, 0x4444);
  SwapBuffers();

  while (1)
  {
  }
}

void HAL_GPIO_EXTI_Falling_Callback(uint16_t GPIO_Pin)
{
	if (GPIO_Pin == CTP_INT_Pin)
	{
		TouchINT_irq = 1;
	}
}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM2 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM2)
  {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */


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
