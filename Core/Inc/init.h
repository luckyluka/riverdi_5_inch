#include <stdint.h>
#include "stm32u5xx_hal.h"

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);
void Error_Handler(void);

/* Private defines -----------------------------------------------------------*/
#define LCD_DISP_RESET_Pin GPIO_PIN_7
#define LCD_DISP_RESET_GPIO_Port GPIOH
#define CTP_RST_Pin GPIO_PIN_3
#define CTP_RST_GPIO_Port GPIOE
#define CTP_INT_Pin GPIO_PIN_6
#define CTP_INT_GPIO_Port GPIOE
#define R_RST_Pin GPIO_PIN_4
#define R_RST_GPIO_Port GPIOF
#define R_CS_Pin GPIO_PIN_1
#define R_CS_GPIO_Port GPIOG
#define R_INT_Pin GPIO_PIN_4
#define R_INT_GPIO_Port GPIOC

ADC_HandleTypeDef Get_HADC_StructPtr(uint8_t nr);
DAC_HandleTypeDef Get_HDAC_StructPtr(uint8_t nr);
DCACHE_HandleTypeDef Get_DCACHE_StructPtr(uint8_t nr);
DMA2D_HandleTypeDef * Get_HDMA2D_StructPtr(uint8_t nr);
GPU2D_HandleTypeDef Get_HGPU2D_StructPtr(uint8_t nr);
I2C_HandleTypeDef Get_HI2C_StructPtr(uint8_t nr);
LTDC_HandleTypeDef Get_HLTDC_StructPtr(uint8_t nr);
OSPI_HandleTypeDef Get_HOSPI_StructPtr(uint8_t nr);
RTC_HandleTypeDef Get_HRTC_StructPtr(uint8_t nr);
SD_HandleTypeDef Get_HSD_StructPtr(uint8_t nr);
SPI_HandleTypeDef Get_HSPI_StructPtr(uint8_t nr);
TIM_HandleTypeDef Get_HTIM_StructPtr(uint8_t nr);
UART_HandleTypeDef Get_HUART_StructPtr(uint8_t nr);


void InitPeripherals(void);
void InitClocks(void);
