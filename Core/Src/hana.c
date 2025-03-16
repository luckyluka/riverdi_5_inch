#include "init.h"
#include "hana.h"

#define SCREEN_HEIGHT 480
#define SCREEN_WIDTH  800



__attribute__((section(".sram_fb"), used)) static uint16_t framebuffer1[800 * 480];
__attribute__((section(".sram_fb"), used)) static uint16_t framebuffer2[800 * 480];

static uint16_t *front_buffer = framebuffer1;
static uint16_t *back_buffer = framebuffer2;

DMA2D_HandleTypeDef * hdma2d;
LTDC_HandleTypeDef  * hltdc;

void InitHana(void)
{
	hdma2d = Get_HDMA2D_StructPtr(1);
	hltdc  = Get_HLTDC_StructPtr(1);
}


// CHAT GPT - BASIC SHAPE DRAWING
void SetPixel(int x, int y, uint32_t color)
{
  back_buffer[y * SCREEN_WIDTH + x] = color;
}

void DrawLine(int x0, int y0, int x1, int y1, uint32_t color) 
{
  int dx = abs(x1 - x0);
  int dy = abs(y1 - y0);
  int sx = (x0 < x1) ? 1 : -1;
  int sy = (y0 < y1) ? 1 : -1;
  int err = dx - dy;

  while (1) 
  {
      SetPixel(x0, y0, color);
      if (x0 == x1 && y0 == y1) break;
      int e2 = err * 2;
      if (e2 > -dy) { err -= dy; x0 += sx; }
      if (e2 < dx) { err += dx; y0 += sy; }
  }
}

void DrawHline(int x, int y, int width, uint32_t color) 
{
  for (int i = 0; i < width; i++) 
  {
    SetPixel(x + i, y, color);
  }
}


void DrawVLine(int x, int y, int height, uint32_t color) 
{
  for (int i = 0; i < height; i++) 
  {
    SetPixel(x, y + i, color);
  }
}

void DrawCircle(int xc, int yc, int r, uint32_t color)
{
  int x = 0, y = r;
  int d = 3 - 2 * r;

  while (y >= x) 
  {
    SetPixel(xc + x, yc + y, color);
    SetPixel(xc - x, yc + y, color);
    SetPixel(xc + x, yc - y, color);
    SetPixel(xc - x, yc - y, color);
    SetPixel(xc + y, yc + x, color);
    SetPixel(xc - y, yc + x, color);
    SetPixel(xc + y, yc - x, color);
    SetPixel(xc - y, yc - x, color);

    x++;
    if (d < 0) 
    {
        d += 4 * x + 6;
    }
    else 
    {
        y--;
        d += 4 * (x - y) + 10;
    }
  }
}

void DrawRectangle(int x, int y, int width, int height, uint32_t color)
{
 
  DrawHline(x, y, width, color);           // Top edge
  DrawHline(x, y + height - 1, width, color);  // Bottom edge
  DrawVLine(x, y, height, color);          // Left edge
  DrawVLine(x + width - 1, y, height, color);  // Right edge
}

void DrawRoundedRectangle(int x, int y, int w, int h, int r, uint32_t color) 
{
  // Draw center rectangle
  DrawRectangle(x + r, y, w - 2 * r, h, color);

  // Draw side rectangles
  DrawRectangle(x, y + r, r, h - 2 * r, color);
  DrawRectangle(x + w - r, y + r, r, h - 2 * r, color);

  // Draw rounded corners
  DrawCircle(x + r, y + r, r, color); // Top-left
  DrawCircle(x + w - r, y + r, r, color); // Top-right
  DrawCircle(x + r, y + h - r, r, color); // Bottom-left
  DrawCircle(x + w - r, y + h - r, r, color); // Bottom-right
}

//

void SwapBuffers(void) 
{
    uint16_t *temp = front_buffer;
    front_buffer = back_buffer;
    back_buffer = temp;

    __HAL_LTDC_LAYER(hltdc, 0)->CFBAR = (uint32_t)front_buffer;
    __HAL_LTDC_RELOAD_CONFIG(hltdc);
}

void DrawBackground(uint32_t color)
{
  hdma2d->Init.Mode = DMA2D_R2M; // Register to Memory mode
  hdma2d->Init.ColorMode = DMA2D_OUTPUT_RGB565;
  hdma2d->Init.OutputOffset = 0;

  if (HAL_DMA2D_Init(hdma2d) != HAL_OK)
  {
    Error_Handler();
  }

  if (HAL_DMA2D_Start(hdma2d, (uint32_t)color, (uint32_t)back_buffer, SCREEN_WIDTH, SCREEN_HEIGHT) != HAL_OK)
  {
      Error_Handler();
  }

  // Wait for the transfer to complete
  if (HAL_DMA2D_PollForTransfer(hdma2d, 100) != HAL_OK)
  {
      Error_Handler();
  }
}
