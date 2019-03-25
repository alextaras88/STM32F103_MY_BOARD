#include "ad7799.h"

/************************************************************************************/
void Spi_AD7799_Init(void)
{
	
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
	
	//PA3(CS max6675)
	GPIOA->CRL &= ~GPIO_CRL_CNF3;
	GPIOA->CRL |= GPIO_CRL_MODE3_0
	|GPIO_CRL_MODE3_1;
	
	GPIOA->ODR |= GPIO_ODR_ODR3;
	
	
	//PA4(CS2)
	GPIOA->CRL &= ~GPIO_CRL_CNF4;
	GPIOA->CRL |= GPIO_CRL_MODE4_0
	|GPIO_CRL_MODE4_1;
	CS_1_HIGH;
	

	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;     // Clock SPI1 enable   
	
  SPI1->CR1 |= SPI_CR1_BR_0|SPI_CR1_BR_2;   // Baud rate = Fpclk/64
  SPI1->CR1 |= SPI_CR1_CPOL;             	  // Polarity cls signal CPOL = 1;
	SPI1->CR1 |= SPI_CR1_CPHA;             		// Phase cls signal    CPHA = 1;
  SPI1->CR1 &= ~SPI_CR1_DFF;               	// 8 bit data
  SPI1->CR1 &= ~SPI_CR1_LSBFIRST;         	// MSB first
  SPI1->CR1 |= SPI_CR1_SSM | SPI_CR1_SSI;  	// Software slave management & Internal slave select
	
  SPI1->CR1 |= SPI_CR1_MSTR;              	// Mode Master
  SPI1->CR1 |= SPI_CR1_SPE;               	// Enable SPI1
}
/************************************************************************************/
void AD7799_Init(void){
	
	Spi_AD7799_Init();
	
	Delay_ms(200);
	
	AD7799_Reset();
	Delay_ms(50);
	
	CS_1_LOW;
	Delay_ms(1);
	Spi_transfer_8(SPI1, 0x00);		// mode reg 0x000A
	Spi_transfer_8(SPI1, 0x0A);
	Delay_ms(1);
	Spi_transfer_8(SPI1, 0x00);
	Spi_transfer_8(SPI1, 0x09); 	  //fADC = 16.6 Hz, 50 Hz only
	//Spi_transfer_8(SPI1, 0x0F); 		//fADC = 4.17 Hz
	//Spi_transfer_8(SPI1, 0x05);		//fADC = 50 Hz
	//Spi_transfer_8(SPI1, 0x0C);		//fADC = 10 Hz
	CS_1_HIGH;
	
}
/************************************************************************************/
void AD7799_Reset(void){
	
	Delay_ms(1);
	CS_1_LOW;
	Spi_transfer_8(SPI1, 0xFF);
	Spi_transfer_8(SPI1, 0xFF);
	Spi_transfer_8(SPI1, 0xFF);
	Spi_transfer_8(SPI1, 0xFF);
	CS_1_HIGH;
	Delay_ms(500);
	
}
/************************************************************************************/
unsigned long getADC7799(void){
	
	unsigned char b1 = 0x00, b2 = 0x00, b3 = 0x00 ;
	unsigned long value = 0x00000000;
	
	CS_1_LOW;
	while(!(GPIOA->IDR & GPIO_IDR_IDR6));
	Spi_transfer_8(SPI1, 0x58);
	b1 = Spi_transfer_8(SPI1, 0x00);
	b2 = Spi_transfer_8(SPI1, 0x00);
	b3 = Spi_transfer_8(SPI1, 0x00);
	
	CS_1_HIGH;
	
	value += (b1<<16);
	value += (b2<<8);
	value += (b3<<0);
	
	return value;
	
}
/************************************************************************************/
void AD7799_Set_CH_1(void){
	CS_1_LOW;
	//Config REG
	Delay_ms(1);
	Spi_transfer_8(SPI1, 0x07); //0x0710 CONFIGURATION REGISTER 
	Spi_transfer_8(SPI1, 0x10);
	Delay_ms(1);
	Spi_transfer_8(SPI1, 0x4F);
	Spi_transfer_8(SPI1, 0x90);   
	CS_1_HIGH;
	
}
/************************************************************************************/
void AD7799_Set_CH_2(void){
	CS_1_LOW;
	//Config REG
	Delay_ms(1);
	Spi_transfer_8(SPI1, 0x07); //0x0710 CONFIGURATION REGISTER 
	Spi_transfer_8(SPI1, 0x10);
	Delay_ms(1);
	Spi_transfer_8(SPI1, 0x48);
	Spi_transfer_8(SPI1, 0x91);   
	CS_1_HIGH;
	
}
/************************************************************************************/
void AD7799_Set_CH_3(void){
	CS_1_LOW;
	//Config REG
	Delay_ms(1);
	Spi_transfer_8(SPI1, 0x07); //0x0710 CONFIGURATION REGISTER 
	Spi_transfer_8(SPI1, 0x10);
	Delay_ms(1);
	Spi_transfer_8(SPI1, 0x48);
	Spi_transfer_8(SPI1, 0x92);   
	CS_1_HIGH;
	
}
/************************************************************************************/






