#include "ad7730.h"

/************************************************************************************/
void ad7730_SPI_Init(void){
	
	RCC->APB2ENR  |= (RCC_APB2ENR_IOPAEN | RCC_APB2ENR_AFIOEN);  // Clock port PORTA and AF enable 
	
	//PA5(SCK)
	GPIOA->CRL &= ~GPIO_CRL_CNF5_0;
	GPIOA->CRL |= GPIO_CRL_CNF5_1;	
	GPIOA->CRL |= GPIO_CRL_MODE5_0
	|GPIO_CRL_MODE5_1 ;	
	
	//PA6(MISO)	
	GPIOA->CRL &= ~GPIO_CRL_CNF6_1;
	GPIOA->CRL |= GPIO_CRL_CNF6_0;
	
	//PA7(MOSI)
	GPIOA->CRL &= ~GPIO_CRL_CNF7_0;
	GPIOA->CRL |= GPIO_CRL_CNF7_1;	
	GPIOA->CRL |= GPIO_CRL_MODE7_0
	|GPIO_CRL_MODE7_1;
	
	// PA1(CS_AD7730)
	GPIOA->CRL &= ~GPIO_CRL_CNF1;
	GPIOA->CRL |= GPIO_CRL_MODE1_0
	|GPIO_CRL_MODE1_1;
	
	// PA3(CS1)
	GPIOA->CRL &= ~GPIO_CRL_CNF3;
	GPIOA->CRL |= GPIO_CRL_MODE3_0
  |GPIO_CRL_MODE3_1;
	
	// PA4(CS2)
	GPIOA->CRL &= ~GPIO_CRL_CNF4;
	GPIOA->CRL |= GPIO_CRL_MODE4_0
	|GPIO_CRL_MODE4_1;
	
	// PA0 RESET)
	GPIOA->CRL &= ~GPIO_CRL_CNF0;
	GPIOA->CRL |= GPIO_CRL_MODE0_0
	|GPIO_CRL_MODE0_1;
	
	GPIOA->ODR |= GPIO_ODR_ODR0;
	/******************************/
	
	
	CS_AD7730_HIGH;
	
	// PA2 - RDY Pin AD7730

	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;     	// Clock SPI1 enable   
	
  SPI1->CR1 |= SPI_CR1_BR_0|SPI_CR1_BR_1|SPI_CR1_BR_2;   // Baud rate = Fpclk/256
  SPI1->CR1 &= ~SPI_CR1_CPOL;             	// Polarity cls signal CPOL = 0;
	SPI1->CR1 |= SPI_CR1_CPHA;             		// Phase cls signal    CPHA = 1;
  SPI1->CR1 &= ~SPI_CR1_DFF;               	// 8 bit data
  SPI1->CR1 &= ~SPI_CR1_LSBFIRST;         	// MSB first
  SPI1->CR1 |= SPI_CR1_SSM | SPI_CR1_SSI;  	// Software slave management & Internal slave select
	
  SPI1->CR1 |= SPI_CR1_MSTR;              	// Mode Master
  SPI1->CR1 |= SPI_CR1_SPE;               	// Enable SPI1
	
}
/************************************************************************************/
void ad7730_Init(void){
	
	ad7730_SPI_Init();
	
	reset_7730();
//----------------------------------
	CS_AD7730_LOW;
	
	Spi_transfer_8(SPI1, 0x03);	// filter	
	
	Spi_transfer_8(SPI1, 0x80);			
	Spi_transfer_8(SPI1, 0x00);
	Spi_transfer_8(SPI1, 0x10);
//----------------------------------		
	Spi_transfer_8(SPI1, 0x04);   // dac
	
	Spi_transfer_8(SPI1, 0x23);
//----------------------------------
	Spi_transfer_8(SPI1, 0x02);	// mode	
	
	Spi_transfer_8(SPI1, 0xA0);
  Spi_transfer_8(SPI1, 0x90);	
	while(!(GPIOA->IDR & GPIO_IDR_IDR2));  
//----------------------------------	
	Spi_transfer_8(SPI1, 0x02);	// mode	
	
	Spi_transfer_8(SPI1, 0x90);			
	Spi_transfer_8(SPI1, 0x90);
	while(!(GPIOA->IDR & GPIO_IDR_IDR2));  	
//----------------------------------	
	CS_AD7730_HIGH;
}
/************************************************************************************/
unsigned long ad7730_GetData(void){
	
  unsigned long value = 0x00000000;
	unsigned char byte1 = 0x00, byte2 = 0x00, byte3 = 0x00;
	
	CS_AD7730_LOW;
	
	Spi_transfer_8(SPI1, 0x02);
	Spi_transfer_8(SPI1, 0x21);
	Spi_transfer_8(SPI1, 0x90);
	Spi_transfer_8(SPI1, 0x21);
	
	CS_AD7730_HIGH;
	
	GPIOA->ODR &= ~GPIO_ODR_ODR6;	 
	while(!(GPIOA->IDR & GPIO_IDR_IDR2)){}
	
  CS_AD7730_LOW;
	
	byte1 = Spi_transfer_8(SPI1, 0x00);
	byte2 = Spi_transfer_8(SPI1, 0x00);
	byte3 = Spi_transfer_8(SPI1, 0x00);
	
	Spi_transfer_8(SPI1, 0x30);
	
	CS_AD7730_HIGH;
	
	value += (byte1<<16);
	value += (byte2<<8);
	value += (byte3<<0);
	
	if (value>16000000) value = 0;
	
	return value;
	
}
/************************************************************************************/
void reset_7730(void){
	
	GPIOA->ODR &= ~GPIO_ODR_ODR0;
	Delay_ms(200);
	GPIOA->ODR |= GPIO_ODR_ODR0;
	Delay_ms(200);

}
/************************************************************************************/
