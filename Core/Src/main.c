/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

#define TOUCH_I2C_ADDRESS 0x41 // Replace with your touch controller's I2C address

uint16_t colors[] = {
  0xF800, // Red
  0x07E0, // Green
  0x001F, // Blue
  0xFFFF, // White
  0x0000, // Black
  0xFFE0, // Yellow
  0xF81F, // Magenta
  0x07FF  // Cyan
};



/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
//__attribute__((section(".sram_fb"), used))	static uint16_t framebuffer[800 * 480]; // RGB565, requires 768KB




volatile uint8_t TouchINT_irq = 0;
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */

void HAL_GPIO_EXTI_Falling_Callback(uint16_t GPIO_Pin)
{
	if (GPIO_Pin == CTP_INT_Pin)
	{
		TouchINT_irq = 1;
	}
}

int main(void)
{
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

  while (1)
  {
    // for (int i = 0; i < sizeof(colors) / sizeof(colors[0]); i++)
    // {
    //   drawBackground(colors[i], back_buffer);
    
    //     // Use DMA2D to transfer the back buffer to the front buffer
    //     HAL_DMA2D_Start(&hdma2d, (uint32_t)back_buffer, (uint32_t)front_buffer, SCREEN_WIDTH, SCREEN_HEIGHT);
    //     HAL_DMA2D_PollForTransfer(&hdma2d, 100);
    
    //     // Swap the buffers
    //     swap_buffers();
    
    //     // Delay to see the color change
    //     HAL_Delay(1000);
    // }
  }
  /* USER CODE END 3 */
}






/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

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
  if (htim->Instance == TIM2) {
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
