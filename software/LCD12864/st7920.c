#include "st7920.h"



uint8_t ST7920_Width, ST7920_Height;


/**********************************************************************************************/
void st7920_spi_Init(void){

	RCC->APB2ENR  |= (RCC_APB2ENR_IOPBEN |
	RCC_APB2ENR_IOPAEN |
	RCC_APB2ENR_AFIOEN);  
	
	// PB13(SCK)
	GPIOB->CRH &= ~GPIO_CRH_CNF13_0;
	GPIOB->CRH |= GPIO_CRH_CNF13_1;	
	GPIOB->CRH |= GPIO_CRH_MODE13_0
	|GPIO_CRH_MODE13_1 ;	
	
	// PB14(MISO)	
	GPIOB->CRH &= ~GPIO_CRH_CNF14_1;
	GPIOB->CRH |= GPIO_CRH_CNF14_0;
	
	// PB15(MOSI)
	GPIOB->CRH &= ~GPIO_CRH_CNF15_0;
	GPIOB->CRH |= GPIO_CRH_CNF15_1;	
	GPIOB->CRH |= GPIO_CRH_MODE15_0
	|GPIO_CRL_MODE5_1;
	
	// PA8(ST7920_CS)
	GPIOA->CRH &= ~GPIO_CRH_CNF8;
	GPIOA->CRH |= GPIO_CRH_MODE8_0
	|GPIO_CRH_MODE8_1;
	
/***********************************/	

	RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;     	// Clock SPI2 enable   
	
  SPI2->CR1 |=  SPI_CR1_BR_2|SPI_CR1_BR_1;  // Baud rate = Fpclk/8  36mhz/8 = 4.5mhz
  SPI2->CR1 &= ~SPI_CR1_CPOL;             	// Polarity cls signal CPOL = 0;
	SPI2->CR1 &= ~SPI_CR1_CPHA;             	// Phase cls signal    CPHA = 0;
  SPI2->CR1 &= ~SPI_CR1_DFF;               	// 8 bit data
  SPI2->CR1 &= ~SPI_CR1_LSBFIRST;         	// MSB first
  SPI2->CR1 |= SPI_CR1_SSM | SPI_CR1_SSI;  	// Software slave management & Internal slave select
	
  SPI2->CR1 |= SPI_CR1_MSTR;              	// Mode Master
  SPI2->CR1 |= SPI_CR1_SPE;               	// Enable SPI1

}
/**********************************************************************************************/
void st7920_Init(uint8_t width, uint8_t height){

	ST7920_Width = width;
	ST7920_Height = height;

	st7920_spi_Init();
	Delay_ms(100);

	ST7920_Basic_FunctionSet(0);

	//ST7920_InitInTextMode();
	ST7920_InitInGraphMode();
	st7920_Basic_Clear();
}
/**********************************************************************************************/
void st7920_Write(SPI_TypeDef* SPIx, int8_t IsCmd,  uint8_t data){

	uint8_t StartByte = 0xF8;
	if (!IsCmd)
    StartByte |= ST7920_StartByte_RSmask;

	ST7920_CS_HIGH;

	Spi_multi_send_8(SPIx, &StartByte, 1);		// Send Start Byte

	StartByte = data & 0xF0;
	Spi_multi_send_8(SPIx, &StartByte, 1);		// Send High Byte

	StartByte = data << 4;
	Spi_multi_send_8(SPIx, &StartByte, 1);		// Send Low Byte
	
	ST7920_CS_LOW;

}
/**********************************************************************************************/
void st7920_Basic_Clear(void){

	st7920_Write(SPI2, 1, ST7920_CmdBasic_Clear);

	Delay_us(320);

}
/**********************************************************************************************/
void st7920_Basic_Home(void){

	st7920_Write(SPI2, 1, ST7920_CmdBasic_Home);

	Delay_us(DELAY);

}
/**********************************************************************************************/
void ST7920_Basic_EntryMode(uint8_t ShiftOn, uint8_t MoveRight){

	uint8_t Data = ST7920_CmdBasic_EntryMode;
	if (ShiftOn)
	  Data |= (1 << 0);
	if (MoveRight)
	  Data |= (1 << 1);

	 st7920_Write(SPI2, 1, Data);

	 Delay_us(DELAY);

}

/**********************************************************************************************/
void ST7920_Basic_DisplayOnOff(uint8_t DisplayOn, uint8_t CursorOn, uint8_t BlinkOn){

	uint8_t Data = ST7920_CmdBasic_DisplayOnOff;

	if (DisplayOn)
		Data |= (1 << 2);
	if (CursorOn)
	    Data |= (1 << 1);
	if (BlinkOn)
	    Data |= (1 << 0);

	st7920_Write(SPI2, 1, Data);

	  Delay_us(DELAY);

}

/**********************************************************************************************/
void ST7920_Basic_CursorDisplayControl(uint8_t DisplayMoveRight, uint8_t CursorMoveRight){

	uint8_t Data = ST7920_CmdBasic_CursorDisplayControl;

	if (DisplayMoveRight)
	Data |= (1 << 3);
	if (CursorMoveRight)
	Data |= (1 << 2);

	st7920_Write(SPI2, 1, Data);

	Delay_us(DELAY);

}
/**********************************************************************************************/
void ST7920_Basic_FunctionSet(uint8_t ExtendedMode){

	uint8_t Data = ST7920_CmdBasic_FunctionSet;

	if (ExtendedMode)
	Data |= (1 << 2);

	st7920_Write(SPI2, 1, Data);

	Delay_us(DELAY);

}
/**********************************************************************************************/
void ST7920_Basic_SetCGRAMaddr(uint8_t Addr){

	uint8_t Data = ST7920_CmdBasic_SetCGRAMaddr;
	Data |= (Addr & 0x3F);
	st7920_Write(SPI2, 1, Data);

	Delay_us(DELAY);

}
/**********************************************************************************************/
void ST7920_Basic_SetDDRAMaddr(uint8_t Addr){

	uint8_t Data = ST7920_CmdBasic_SetDDRAMaddr;
	Data |= (Addr & 0x3F);
	st7920_Write(SPI2, 1, Data);

	Delay_us(DELAY);

}
/**********************************************************************************************/
void ST7920_Ext_StandBy(void){

	st7920_Write(SPI2, 1, ST7920_CmdExt_StandBy);

	Delay_us(DELAY);

}
/**********************************************************************************************/
void ST7920_Ext_SelScrollOrRamAddr(uint8_t SelectScroll){

	uint8_t Data = ST7920_CmdExt_SelScrollOrRamAddr;

	if (SelectScroll)
	   Data |= 0x01;

	  st7920_Write(SPI2, 1, Data);

	  Delay_us(DELAY);

}
/**********************************************************************************************/
void ST7920_Ext_Reverse(uint8_t Row){

	uint8_t Data = ST7920_CmdExt_Reverse;
	Data |= (Row & 0x03);
	st7920_Write(SPI2, 1, Data);

	Delay_us(DELAY);

}
/**********************************************************************************************/
void ST7920_Ext_FunctionSet(uint8_t ExtendedMode, uint8_t GraphicMode){

	 uint8_t Data = ST7920_CmdExt_FunctionSet;

	  if (ExtendedMode)
	    Data |= (1 << 2);

	  if (GraphicMode)
	    Data |= (1 << 1);

	  st7920_Write(SPI2, 1, Data);

	  Delay_us(DELAY);


}
/**********************************************************************************************/
void ST7920_Ext_SetIRAMOrSccrollAddr(uint8_t Addr){

	uint8_t Data = ST7920_CmdExt_SetIRAMOrSccrollAddr;
	Data |= (Addr & 0x3F);
	st7920_Write(SPI2, 1, Data);

	Delay_us(DELAY);

}
/**********************************************************************************************/
void ST7920_Ext_SetGDRAMAddr(uint8_t VertAddr, uint8_t HorizAddr){

	uint8_t Data = ST7920_CmdExt_SetGDRAMAddr;
	Data |= (VertAddr & 0x7F);
	st7920_Write(SPI2, 1, Data);

	Data = ST7920_CmdExt_SetGDRAMAddr;
	Data |= (HorizAddr & 0x0F);
	st7920_Write(SPI2, 1, Data);

	Delay_us(DELAY);

}
/**********************************************************************************************/
uint8_t ST7920_GetHorizontalByte(uint8_t *pBuff, uint8_t Row, uint8_t Col){


	uint8_t Byte = 0;
	uint8_t Bit = 0;
	uint8_t BitMask = 0;


	uint16_t ByteIdx = (Row >> 3) * ST7920_Width;
	ByteIdx += (Col << 3);

	BitMask = Row % 8;
	BitMask = (1 << BitMask);


	for (Bit = 0; Bit < 8; Bit++)
	{
	  if (pBuff[ByteIdx + Bit] & BitMask)
	      Byte |= (1 << (7 - Bit));
	}

	  return Byte;

}
/**********************************************************************************************/
void ST7920_DisplayFullUpdate(uint8_t *pBuff, uint16_t BuffLen){
	
	uint8_t Row = 0;
	uint8_t Col = 0;
	

	for (Row = 0; Row < 32; Row++)
	  {

	    ST7920_Ext_SetGDRAMAddr(Row, 0);


	    for (Col = 0; Col < 16; Col++)
	      st7920_Write(SPI2, 0, ST7920_GetHorizontalByte(pBuff, Row, Col));

	    for (Col = 0; Col < 16; Col++)
	      st7920_Write(SPI2, 0, ST7920_GetHorizontalByte(pBuff, Row + 32, Col));
	  }

}
/**********************************************************************************************/
void ST7920_InitInTextMode(void){

	ST7920_Basic_FunctionSet(0);
	ST7920_Basic_DisplayOnOff(1, 0, 0);
	st7920_Basic_Clear();
	ST7920_Basic_EntryMode(0, 1);

}
/**********************************************************************************************/
void ST7920_InitInGraphMode(void){

	ST7920_Basic_FunctionSet(1);
	ST7920_Ext_FunctionSet(1, 1);

}
/**********************************************************************************************/


