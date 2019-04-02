#include "fonts.h"

#include <stdio.h>
#include <string.h>
#include <stdint.h>

/**********************************************************************************************/
const t_font_getchar font_table_funcs[] =
{
  f6x8m_GetCharTable,
  f10x16f_GetCharTable
};
/**********************************************************************************************/

uint8_t *font_GetFontStruct(uint8_t FontID, uint8_t Char){

	return font_table_funcs[FontID](Char);

}
/**********************************************************************************************/
uint8_t font_GetCharWidth(uint8_t *pCharTable){

	return *pCharTable;

}
/**********************************************************************************************/
uint8_t font_GetCharHeight(uint8_t *pCharTable){

	pCharTable++;
	return *pCharTable;

}
/**********************************************************************************************/

