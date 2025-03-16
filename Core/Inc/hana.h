#include <stdint.h>

#define COLOR_BLACK        ((uint32_t)0x00000000)  // 0x0000
#define COLOR_WHITE        ((uint32_t)0x0000FFFF)  // 0xFFFF
#define COLOR_RED          ((uint32_t)0x0000F800)  // 0xF800
#define COLOR_GREEN        ((uint32_t)0x000007E0)  // 0x07E0
#define COLOR_BLUE         ((uint32_t)0x0000001F)  // 0x001F
#define COLOR_CYAN         ((uint32_t)0x000007FF)  // 0x07FF
#define COLOR_MAGENTA      ((uint32_t)0x0000F81F)  // 0xF81F
#define COLOR_YELLOW       ((uint32_t)0x0000FFE0)  // 0xFFE0
#define COLOR_ORANGE       ((uint32_t)0x0000FC00)  // 0xFC00
#define COLOR_PURPLE       ((uint32_t)0x0000801F)  // 0x801F
#define COLOR_PINK         ((uint32_t)0x0000F81F)  // 0xF81F
#define COLOR_BROWN        ((uint32_t)0x0000A145)  // 0xA145
#define COLOR_GRAY         ((uint32_t)0x00008410)  // 0x8410
#define COLOR_LIGHT_GRAY   ((uint32_t)0x0000C618)  // 0xC618
#define COLOR_DARK_GRAY    ((uint32_t)0x000052AA)  // 0x528A

void InitHana(void);
void SetPixel(int x, int y, uint32_t color);
void DrawLine(int x0, int y0, int x1, int y1, uint32_t color);
void DrawHline(int x, int y, int width, uint32_t color);
void DrawVLine(int x, int y, int height, uint32_t color);
void DrawCircle(int xc, int yc, int r, uint32_t color);
void DrawRectangle(int x, int y, int width, int height, uint32_t color);
void DrawRoundedRectangle(int x, int y, int w, int h, int r, uint32_t color);
void DrawBackground(uint32_t color);
void SwapBuffers(void) ;
