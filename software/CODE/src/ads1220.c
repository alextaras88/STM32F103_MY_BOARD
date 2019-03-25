#include "ads1220.h"
#include "ssd1306.h"


char str1[100];

/****************************************************************************************************/
void ads1220_SPI_Init(void){
	
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
	
	// PA4(CS_ADS1220)
	GPIOA->CRL &= ~GPIO_CRL_CNF4;
	GPIOA->CRL |= GPIO_CRL_MODE4_0
	|GPIO_CRL_MODE4_1;
	
	
	GPIOA->ODR |= GPIO_ODR_ODR4;
	/******************************/
	
	// PA3 - RDY Pin ADS1220

	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;     	// Clock SPI1 enable   
	
  SPI1->CR1 |= SPI_CR1_BR_0|SPI_CR1_BR_2;   // Baud rate = Fpclk/64 1.125 mhz
  SPI1->CR1 &= ~SPI_CR1_CPOL;             	// Polarity cls signal CPOL = 0;
	SPI1->CR1 |= SPI_CR1_CPHA;             		// Phase cls signal    CPHA = 1;
  SPI1->CR1 &= ~SPI_CR1_DFF;               	// 8 bit data
  SPI1->CR1 &= ~SPI_CR1_LSBFIRST;         	// MSB first
  SPI1->CR1 |= SPI_CR1_SSM | SPI_CR1_SSI;  	// Software slave management & Internal slave select
	
  SPI1->CR1 |= SPI_CR1_MSTR;              	// Mode Master
  SPI1->CR1 |= SPI_CR1_SPE;               	// Enable SPI1
	
}
/****************************************************************************************************/
void ads1220_WREG(uint8_t reg, uint8_t data){
	
	CS_ADS1220_LOW;
	Delay_ms(5);
	Spi_transfer_8(SPI1, 0x40|(reg<<2));
	Spi_transfer_8(SPI1, data);
  Delay_ms(5);
	CS_ADS1220_HIGH;

}
/****************************************************************************************************/
uint8_t ads1220_RREG(uint8_t reg){
	
	uint8_t data;
	
	CS_ADS1220_LOW;
	Delay_ms(5);
	Spi_transfer_8(SPI1, 0x20|(reg<<2));
	while(!(GPIOA->IDR & GPIO_IDR_IDR3)){}
	data = Spi_transfer_8(SPI1, 0x00);
	Delay_ms(5);
	CS_ADS1220_HIGH;
	
	return data;
}
/****************************************************************************************************/
void ads1220_Init(void){
	
	ads1220_SPI_Init();
	
	CS_ADS1220_LOW;
	Delay_ms(100);
	Spi_transfer_8(SPI1, 0x06);							// Reset
	Delay_ms(100);
	CS_ADS1220_HIGH;
	
	
	
	ads1220_WREG(CONFIG_REG0 , 0x0A);		// AINP = AIN0, AINN = AIN1, gain = 32, PGA enabled
	ads1220_WREG(CONFIG_REG1 , 0x04);		// DR = 45 SPS, normal, continuous conversion mode
	ads1220_WREG(CONFIG_REG2 , 0x10);		// External voltage reference(AVDD-AVCC), simultaneous 50-Hz and 60-Hz rejection
	ads1220_WREG(CONFIG_REG3 , 0x00);		// No IDACs used
	
	
	
	
}
/****************************************************************************************************/
 int32_t ads1220_GetData(void){
	
	uint8_t i;
	static char buff[3];
	int32_t bit24 = 0;
  int32_t value = 0;
	 
	while(!(GPIOA->IDR & GPIO_IDR_IDR3)){}
		
	CS_ADS1220_LOW;
		
	for(i=0;i<3;i++){
	buff[i] = Spi_transfer_8(SPI1, 0xFF);
	}
	
	CS_ADS1220_HIGH;
		
	bit24 = buff[0];
	bit24 = (bit24<<8)|buff[1];
	bit24 = (bit24<<8)|buff[2];
	
	bit24 = (bit24<<8);
	value = (bit24>>8);
		
	return value;
	
}
/****************************************************************************************************/
extern void ads1220_ReadReg(void){
	
  uint8_t buff[4];
	
	buff[0] = ads1220_RREG(CONFIG_REG0);

	buff[1] = ads1220_RREG(CONFIG_REG1);
	
	buff[2] = ads1220_RREG(CONFIG_REG2);
	
	buff[3] = ads1220_RREG(CONFIG_REG3);
	
	
  sprintf(str1, "%X %X %X %X", buff[0], buff[1], buff[2], buff[3]);
	
	ssd1306_SetCursor(0, 16);
	ssd1306_WriteString(str1, Font_7x10, White);
	ssd1306_UpdateScreen();
	
	Delay_ms(2000);
	
	
}
/************************************************************************************/
float ads1220_Get_temp(void){
	
	uint32_t data = 0;
	float temp = 0;
	
	uint8_t b1, b2, b3;
	
	CS_ADS1220_LOW;
	b1 = Spi_transfer_8(SPI1, 0xFF);
	b2 = Spi_transfer_8(SPI1, 0xFF);
	b3 = Spi_transfer_8(SPI1, 0xFF);
	CS_ADS1220_HIGH;
	
	data += (b1<<16);
	data += (b2<<8);
	data += (b3<<0);
	
	data = (uint16_t)data>>2;
	temp = (float)data*0.03125;
	
	return temp;
	
}
/************************************************************************************/
float ads1220_Get_V(void){
	
	return (float)((ads1220_GetData()*VFSR*1000)/FSR);

}
/************************************************************************************/


