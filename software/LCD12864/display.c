#include "display.h"

uint8_t disp1color_buff[(DISP1COLOR_Width * DISP1COLOR_Height) / 8];

/**********************************************************************************************/
void Display_Init(void){

	st7920_Init(DISP1COLOR_Width, DISP1COLOR_Height);

}
/**********************************************************************************************/
void disp1color_FillScreenbuff(uint8_t FillValue)
{
  memset(disp1color_buff, FillValue, sizeof(disp1color_buff));
}
/**********************************************************************************************/
void disp1color_UpdateFromBuff(void){

	ST7920_DisplayFullUpdate(disp1color_buff, sizeof(disp1color_buff));

}
/**********************************************************************************************/
void disp1color_printf(int16_t X, int16_t Y, uint8_t FontID, const char *args, ...){

	char StrBuff[100];
	char len;
	
	va_list ap;
	va_start(ap, args);
	len = vsnprintf(StrBuff, sizeof(StrBuff), args, ap);
	va_end(ap);

	disp1color_DrawString(X, Y, FontID, (uint8_t *)StrBuff);

}
/**********************************************************************************************/
void disp1color_DrawPixel(int16_t X, int16_t Y, uint8_t State)
{
	
	uint16_t ByteIdx;
	uint8_t BitIdx;
	int16_t error2;

  if ((X >= DISP1COLOR_Width) || (Y >= DISP1COLOR_Height) || (X < 0) || (Y < 0))
    return;

  ByteIdx = Y >> 3;
  BitIdx = Y - (ByteIdx << 3);
  ByteIdx *= DISP1COLOR_Width;
  ByteIdx += X;

  if (State)
    disp1color_buff[ByteIdx] |= (1 << BitIdx);
  else
    disp1color_buff[ByteIdx] &= ~(1 << BitIdx);
}
/**********************************************************************************************/
void disp1color_DrawLine(int16_t x1, int16_t y1, int16_t x2, int16_t y2)
{
 int16_t error2;
	
  const int16_t deltaX = abs(x2 - x1);
  const int16_t deltaY = abs(y2 - y1);
  const int16_t signX = x1 < x2 ? 1 : -1;
  const int16_t signY = y1 < y2 ? 1 : -1;

  int16_t error = deltaX - deltaY;

  disp1color_DrawPixel(x2, y2, 1);

  while (x1 != x2 || y1 != y2)
  {
    disp1color_DrawPixel(x1, y1, 1);
    error2 = error * 2;

    if (error2 > -deltaY)
    {
      error -= deltaY;
      x1 += signX;
    }
    if (error2 < deltaX)
    {
      error += deltaX;
      y1 += signY;
    }
  }
}
/**********************************************************************************************/
void disp1color_DrawRectangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2)
{
  disp1color_DrawLine(x1, y1, x1, y2);
  disp1color_DrawLine(x2, y1, x2, y2);
  disp1color_DrawLine(x1, y1, x2, y1);
  disp1color_DrawLine(x1, y2, x2, y2);
}
/**********************************************************************************************/
void disp1color_DrawCircle(int16_t x0, int16_t y0, int16_t radius)
{
  int x = 0;
  int y = radius;
  int delta = 1 - 2 * radius;
  int error = 0;

  while (y >= 0)
  {
    disp1color_DrawPixel(x0 + x, y0 + y, 1);
    disp1color_DrawPixel(x0 + x, y0 - y, 1);
    disp1color_DrawPixel(x0 - x, y0 + y, 1);
    disp1color_DrawPixel(x0 - x, y0 - y, 1);
    error = 2 * (delta + y) - 1;

    if (delta < 0 && error <= 0)
    {
      ++x;
      delta += 2 * x + 1;
      continue;
    }

    error = 2 * (delta - x) - 1;

    if (delta > 0 && error > 0)
    {
      --y;
      delta += 1 - 2 * y;
      continue;
    }

    ++x;
    delta += 2 * (x - y);
    --y;
  }
}
/**********************************************************************************************/
uint8_t disp1color_DrawChar(int16_t X, int16_t Y, uint8_t FontID, uint8_t Char)
{
	
	uint8_t row = 0;
	uint8_t col = 0;
	
  uint8_t *pCharTable = font_GetFontStruct(FontID, Char);
  uint8_t CharWidth = font_GetCharWidth(pCharTable);
  uint8_t CharHeight = font_GetCharHeight(pCharTable);
  pCharTable += 2;

  if (FontID == FONTID_6X8M)
  {
    for (row = 0; row < CharHeight; row++)
    {
      for (col = 0; col < CharWidth; col++)
        disp1color_DrawPixel(X + col, Y + row, pCharTable[row] & (1 << (7 - col)));
    }
  }
  else
  {
    for (row = 0; row < CharHeight; row++)
    {
      for (col = 0; col < CharWidth; col++)
      {
        if (col < 8)
          disp1color_DrawPixel(X + col, Y + row, pCharTable[row * 2] & (1 << (7 - col)));
        else
          disp1color_DrawPixel(X + col, Y + row, pCharTable[(row * 2) + 1] & (1 << (15 - col)));
      }
    }
  }

  return CharWidth;
}
/**********************************************************************************************/
void disp1color_DrawString(int16_t X, int16_t Y, uint8_t FontID, uint8_t *Str){

	uint8_t done = 0;
	int16_t Xstart = X;
	uint8_t StrHeight = 8;

	while (!done)
	{
    switch (*Str)
    {
    case '\0':
      done = 1;
      break;
    case '\n':
      Y += StrHeight;
      break;
    case '\r':
      X = Xstart;
      break;
    default:
      X += disp1color_DrawChar(X, Y, FontID, *Str);
      StrHeight = font_GetCharHeight(font_GetFontStruct(FontID, *Str));
      break;
    }
    Str++;
  }
}
/**********************************************************************************************/


