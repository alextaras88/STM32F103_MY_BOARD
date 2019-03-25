#include "SPI.h"


/******************************************************************************************/
void Spi_1_Init(void)
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
	
	//PA4(CS1)
	GPIOA->CRL &= ~GPIO_CRL_CNF4;
	GPIOA->CRL |= GPIO_CRL_MODE4_0
	|GPIO_CRL_MODE4_1;
	
	CS_1_HIGH;
	
/***********************************/	

	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;     	// Clock SPI1 enable   
	
  SPI1->CR1 |= SPI_CR1_BR_2;                // Baud rate = Fpclk/16
  SPI1->CR1 &= ~SPI_CR1_CPOL;             	// Polarity cls signal CPOL = 0;
	SPI1->CR1 |= SPI_CR1_CPHA;             		// Phase cls signal    CPHA = 1;
  SPI1->CR1 |= SPI_CR1_DFF;               	// 16 bit data
  SPI1->CR1 &= ~SPI_CR1_LSBFIRST;         	// MSB first
  SPI1->CR1 |= SPI_CR1_SSM | SPI_CR1_SSI;  	// Software slave management & Internal slave select
	
  SPI1->CR1 |= SPI_CR1_MSTR;              	// Mode Master
  SPI1->CR1 |= SPI_CR1_SPE;               	// Enable SPI1
}
/*********************************************************************************************************/
void Spi_2_Init(void){
	
	RCC->APB2ENR  |= (RCC_APB2ENR_IOPBEN |
	RCC_APB2ENR_IOPAEN |
	RCC_APB2ENR_AFIOEN);  									// Clock port A and B, AF enable 
	
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
	
	// PA8(CS_2)
	GPIOA->CRH &= ~GPIO_CRH_CNF8;
	GPIOA->CRH |= GPIO_CRH_MODE8_0
	|GPIO_CRH_MODE8_1;
	
	
/***********************************/	
	RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;     	// Clock SPI2 enable   
	
  SPI2->CR1 |=  SPI_CR1_BR_2;               // Baud rate = Fpclk/8  36mhz/8 = 4.5mhz
  SPI2->CR1 &= ~SPI_CR1_CPOL;             	// Polarity cls signal CPOL = 0;
	SPI2->CR1 &= ~SPI_CR1_CPHA;             	// Phase cls signal    CPHA = 0;
  SPI2->CR1 &= ~SPI_CR1_DFF;               	// 8 bit data
  SPI2->CR1 &= ~SPI_CR1_LSBFIRST;         	// MSB first
  SPI2->CR1 |= SPI_CR1_SSM | SPI_CR1_SSI;  	// Software slave management & Internal slave select
	
  SPI2->CR1 |= SPI_CR1_MSTR;              	// Mode Master
  SPI2->CR1 |= SPI_CR1_SPE;               	// Enable SPI1



}
/*********************************************************************************************************/
uint16_t Spi_Write_Read_Data16(SPI_TypeDef* SPIx, uint16_t data)
{   
		
	while(!(SPIx->SR & SPI_SR_TXE));      
	SPIx->DR = data;   
	while(!(SPIx->SR & SPI_SR_RXNE));
	data = SPIx->DR;   
	while((SPIx->SR & SPI_SR_BSY)!=0){}
	
  return data; 
		
}
/*********************************************************************************************************/
uint8_t Spi_transfer_8(SPI_TypeDef* SPIx, uint8_t data){ 
	
	SPI_WAIT(SPIx);
	SPIx->DR = data;
	SPI_WAIT(SPIx);
	
	return SPIx->DR;
	
}
/*********************************************************************************************************/
void Spi_multi_send_8(SPI_TypeDef* SPIx, uint8_t* data, uint16_t len){ 
	
	uint16_t i;

	SPI_WAIT(SPIx);
	for(i=0;i<len;i++){

		SPIx->DR = data[i];
		SPI_WAIT(SPIx);
		
	}
}
/*********************************************************************************************************/


