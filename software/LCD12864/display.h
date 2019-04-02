#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "stm32f10x.h"

#include "st7920.h"
#include "fonts.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

/**********************************************************************************************/
#define DISP1COLOR_Width        128
#define DISP1COLOR_Height       64
/**********************************************************************************************/
void Display_Init(void);
void disp1color_TestMode(uint8_t TestOn);
void disp1color_SetBrightness(uint8_t Value);
void disp1color_FillScreenbuff(uint8_t FillValue);
void disp1color_UpdateFromBuff(void);

void disp1color_DrawLine(int16_t x1, int16_t y1, int16_t x2, int16_t y2);
void disp1color_DrawRectangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2);
void disp1color_DrawCircle(int16_t x0, int16_t y0, int16_t radius);
uint8_t disp1color_DrawChar(int16_t X, int16_t Y, uint8_t FontID, uint8_t Char);
void disp1color_DrawString(int16_t X, int16_t Y, uint8_t FontID, uint8_t *Str);
void disp1color_printf(int16_t X, int16_t Y, uint8_t FontID, const char *args, ...);
/**********************************************************************************************/
#endif /* DISPLAY_H_ */
