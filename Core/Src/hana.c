#include "init.h"
#include "hana.h"

#define SCREEN_HEIGHT 480
#define SCREEN_WIDTH  800

__attribute__((section(".sram_fb"), used)) static uint16_t framebuffer1[800 * 480];
__attribute__((section(".sram_fb"), used)) static uint16_t framebuffer2[800 * 480];

static uint16_t *front_buffer = framebuffer1;
static uint16_t *back_buffer = framebuffer2;

DMA2D_HandleTypeDef * hdma2d;

void InitHana(void)
{
	hdma2d = Get_HDMA2D_StructPtr(1);
}

void swap_buffers(void) {
    uint16_t *temp = front_buffer;
    front_buffer = back_buffer;
    back_buffer = temp;
}

void draw_moving_gradient(uint32_t frame, uint16_t *framebuffer) {
    // Calculate the color for the gradient
    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            float t = (float)x / (SCREEN_WIDTH - 1);  // Normalize x position (0.0 to 1.0)

            // Animate the red, green, and blue channels based on time
            uint8_t red   = (uint8_t)((0.5f + 0.5f * sinf(frame * 0.05f)) * 31);  // Animate red
            uint8_t green = (uint8_t)((0.5f + 0.5f * sinf((frame + 100) * 0.05f)) * 63);  // Animate green
            uint8_t blue  = (uint8_t)((0.5f + 0.5f * sinf((frame + 200) * 0.05f)) * 31);  // Animate blue

            // Convert to RGB565 (5 bits red, 6 bits green, 5 bits blue)
            uint16_t color = (red << 11) | (green << 5) | blue;

            // Fill the framebuffer with the calculated color
            framebuffer[y * SCREEN_WIDTH + x] = color;
        }
    }
}

void draw_screen(uint16_t *framebuffer, uint16_t color)
{
  for (int y = 0; y < SCREEN_HEIGHT; y++) 
  {
    for (int x = 0; x < SCREEN_WIDTH; x++)
    {
      framebuffer[y * SCREEN_WIDTH + x] = color;
    }
  }
}

uint8_t draw_screen_sm(uint16_t *framebuffer, uint16_t color)
{
  static int x = 0;
  static int y = 0;

  for (;y < SCREEN_HEIGHT; y++) 
  {
    for (;x < SCREEN_WIDTH; x++)
    {
      framebuffer[y * SCREEN_WIDTH + x] = color;
      return 0;
    }
  }
  return 1;
}

void draw_frame(uint32_t frame) {
	
    draw_moving_gradient(frame, back_buffer);
    // Use DMA2D to transfer the back buffer to the front buffer
    HAL_DMA2D_Start(&hdma2d, (uint32_t)back_buffer, (uint32_t)front_buffer, SCREEN_WIDTH, SCREEN_HEIGHT);
    HAL_DMA2D_PollForTransfer(&hdma2d, 100);

    // Swap the buffers
    swap_buffers();
}

void draw_funct_1(void)
{
  static uint16_t color = 0xFFFF;

  for(int i = 0; i < 10; i++)
  {
    draw_screen(back_buffer, color);
    swap_buffers();
    color-= 0x1999;

    HAL_DMA2D_Start(&hdma2d, (uint32_t)back_buffer, (uint32_t)front_buffer, SCREEN_WIDTH, SCREEN_HEIGHT);
    HAL_DMA2D_PollForTransfer(&hdma2d, 100);
  }
  color = 0xFFFF;
}

void draw_funct_2(void)
{
  static uint16_t color = 0xFFFF;

  for(int i = 0; i < 10; i++)
  {
    if(draw_screen_sm(back_buffer, color))
    {
      swap_buffers();
      color-= 0x1999;

      HAL_DMA2D_Start(&hdma2d, (uint32_t)back_buffer, (uint32_t)front_buffer, SCREEN_WIDTH, SCREEN_HEIGHT);
      HAL_DMA2D_PollForTransfer(&hdma2d, 100);
    }
  }
  color = 0xFFFF;
}

void drawBackground(uint16_t color, uint16_t *framebuffer)
{
  hdma2d->Init.Mode = DMA2D_R2M; // Register to Memory mode
  hdma2d->Init.ColorMode = DMA2D_OUTPUT_RGB565;
  hdma2d->Init.OutputOffset = 0;

  if (HAL_DMA2D_Init(&hdma2d) != HAL_OK)
  {
    Error_Handler();
  }

  if (HAL_DMA2D_Start(&hdma2d, (uint32_t)color, (uint32_t)framebuffer, SCREEN_WIDTH, SCREEN_HEIGHT) != HAL_OK)
  {
      Error_Handler();
  }

  // Wait for the transfer to complete
  if (HAL_DMA2D_PollForTransfer(&hdma2d, 100) != HAL_OK)
  {
      Error_Handler();
  }
  //swap_buffers();
}
