#ifndef ST7920_H_
#define ST7920_H_

#include "stm32f10x.h"
#include "SPI.h"
#include "Delay.h"


#define DELAY 30
/**********************************************************************************************/
#define ST7920_CS_LOW				GPIOA->ODR &= ~GPIO_ODR_ODR8;
#define ST7920_CS_HIGH			GPIOA->ODR |= GPIO_ODR_ODR8;
/**********************************************************************************************/
#define ST7920_StartByte_RWmask       (1 << 2)
#define ST7920_StartByte_RSmask       (1 << 1)
/**********************************************************************************************/
#define ST7920_CmdBasic_Clear                   0x01
#define ST7920_CmdBasic_Home                    0x02
#define ST7920_CmdBasic_EntryMode               0x04
#define ST7920_CmdBasic_DisplayOnOff            0x08
#define ST7920_CmdBasic_CursorDisplayControl    0x10
#define ST7920_CmdBasic_FunctionSet             0x20
#define ST7920_CmdBasic_SetCGRAMaddr            0x40
#define ST7920_CmdBasic_SetDDRAMaddr            0x80

#define ST7920_CmdExt_StandBy                   0x01
#define ST7920_CmdExt_SelScrollOrRamAddr        0x02
#define ST7920_CmdExt_Reverse                   0x04
#define ST7920_CmdExt_FunctionSet               0x20
#define ST7920_CmdExt_SetIRAMOrSccrollAddr      0x40
#define ST7920_CmdExt_SetGDRAMAddr              0x80
/**********************************************************************************************/
void st7920_spi_Init(void);
void st7920_Init(uint8_t width, uint8_t height);
void st7920_Write(SPI_TypeDef* SPIx, int8_t IsCmd,  uint8_t data);
void st7920_Basic_Clear(void);
void st7920_Basic_Home(void);
void ST7920_Basic_EntryMode(uint8_t ShiftOn, uint8_t MoveRight);
void ST7920_Basic_DisplayOnOff(uint8_t DisplayOn, uint8_t CursorOn, uint8_t BlinkOn);
void ST7920_Basic_CursorDisplayControl(uint8_t DisplayMoveRight, uint8_t CursorMoveRight);
void ST7920_Basic_FunctionSet(uint8_t ExtendedMode);
void ST7920_Basic_SetCGRAMaddr(uint8_t Addr);
void ST7920_Basic_SetDDRAMaddr(uint8_t Addr);
void ST7920_Ext_StandBy(void);
void ST7920_Ext_SelScrollOrRamAddr(uint8_t SelectScroll);
void ST7920_Ext_Reverse(uint8_t Row);
void ST7920_Ext_FunctionSet(uint8_t ExtendedMode, uint8_t GraphicMode);
void ST7920_Ext_SetIRAMOrSccrollAddr(uint8_t Addr);
void ST7920_Ext_SetGDRAMAddr(uint8_t VertAddr, uint8_t HorizAddr);
uint8_t ST7920_GetHorizontalByte(uint8_t *pBuff, uint8_t Row, uint8_t Col);
void ST7920_DisplayFullUpdate(uint8_t *pBuff, uint16_t BuffLen);
void ST7920_InitInTextMode(void);
void ST7920_InitInGraphMode(void);
/**********************************************************************************************/

#endif /* ST7920_H_ */
