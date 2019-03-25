#include "i2c.h"

/**********************************************************************************************/
/*  I2C1																																											*/
/**********************************************************************************************/
void I2C_Init(void){

	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;				// Clock PORTB
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;				// Clock AF

/**********************************************/
	AFIO->MAPR |= AFIO_MAPR_I2C1_REMAP;				// Reap I2C1 Pins

	// SCL (PB8)
	GPIOB->CRH |= GPIO_CRH_CNF8;  						// Alternate Function output, open drain
	GPIOB->CRH |= GPIO_CRH_MODE8_1;
	// SDA (PB9)
	GPIOB->CRH |= GPIO_CRH_CNF9;							// Alternate Function output, open drain
	GPIOB->CRH |= GPIO_CRH_MODE9_1;
/**********************************************/

	RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;				// Clock I2C2

	I2C1->CR1 |= I2C_CR1_SWRST;								// Soft Reset
	I2C1->CR1 &= ~I2C_CR1_SWRST;

	I2C1->CR2 &= ~I2C_CR2_FREQ;								// Peripheral clock frequency
	I2C1->CR2 |= 36;

	I2C1->CCR &= ~I2C_CCR_CCR;
	I2C1->CCR = 90;

	I2C1->TRISE = 37;
	
	I2C1->CR1 |= I2C_CR1_PE;									// Enable I2C1

}
/************************************************************************************/

/****************************************************************************************************/
void Start_i2c(I2C_TypeDef* I2Cx){
	
	I2Cx->CR1 |= I2C_CR1_START;   						// Start i2c
	while (!(I2Cx->SR1 & I2C_SR1_SB)){};			// Wait Start
	(void) I2Cx->SR1;
	
}
/****************************************************************************************************/
void Stop_i2c(I2C_TypeDef* I2Cx){
	
	
	I2Cx->CR1 |= I2C_CR1_STOP;
	
}
/****************************************************************************************************/
void Write_addr_i2c(I2C_TypeDef* I2Cx, uint8_t addr, uint8_t rw){

	switch(rw){

	case 0:
		I2Cx->DR = (addr<<1)+0;
		 break;
	case 1:
		I2Cx->DR = (addr<<1)+1;
			 break;

	}

	while (!(I2Cx->SR1 & I2C_SR1_ADDR)){}
	(void) I2Cx->SR1;
	(void) I2Cx->SR2;
		
	}
/****************************************************************************************************/
void Write_data_i2c(I2C_TypeDef* I2Cx, uint8_t data){

	while (!(I2Cx->SR1 & I2C_SR1_TXE)){}
	I2Cx->DR = data;	
	(void) I2Cx->SR1;
	I2Cx->CR1 |= I2C_CR1_ACK;
	(void) I2Cx->SR2;

}
/****************************************************************************************************/
void Write_one_data_i2c(I2C_TypeDef* I2Cx, uint8_t data){

	while (!(I2Cx->SR1 & I2C_SR1_TXE)){};
	I2Cx->DR = data;	
	while (!(I2Cx->SR1 & I2C_SR1_BTF)){};

}
/****************************************************************************************************/
void Write_last_data_i2c(I2C_TypeDef* I2Cx, uint8_t data){
		
	while (!(I2Cx->SR1 & I2C_SR1_TXE)){}
	I2Cx->DR = data;	
	(void) I2Cx->SR1;
	(void) I2Cx->SR2;
		
}
/****************************************************************************************************/	
uint8_t Read_data_i2c(I2C_TypeDef* I2Cx){
	
	I2Cx->CR1 |= I2C_CR1_ACK;	
  while (!(I2Cx->SR1 & I2C_SR1_RXNE)){};
			
  return I2Cx->DR;
		
}
/****************************************************************************************************/
uint8_t Read_last_data_i2c(I2C_TypeDef* I2Cx){
	
	uint8_t data;
	
	(void) I2Cx->SR1;
	(void) I2Cx->SR2;
	I2Cx->CR1 &= ~I2C_CR1_ACK;
  while (!(I2Cx->SR1 & I2C_SR1_RXNE)){};
	data = I2Cx->DR;
	Stop_i2c(I2C1);
		
  return data;
		
}
/**********************************************************************************************/
/*  I2C2																																											*/
/**********************************************************************************************/
void I2C2_Init(void){

	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;				// Clock PORTB
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;				// Clock AF

/**********************************************/
	
	// SCL (PB10)
	GPIOB->CRH |= GPIO_CRH_CNF10;  						// Alternate Function output, open drain
	GPIOB->CRH |= GPIO_CRH_MODE10_1;
	// SDA (PB11)
	GPIOB->CRH |= GPIO_CRH_CNF11;							// Alternate Function output, open drain
	GPIOB->CRH |= GPIO_CRH_MODE11_1;
/**********************************************/

	RCC->APB1ENR |= RCC_APB1ENR_I2C2EN;				// Clock I2C2

	I2C2->CR1 |= I2C_CR1_SWRST;								// Soft Reset
	I2C2->CR1 &= ~I2C_CR1_SWRST;

	I2C2->CR2 &= ~I2C_CR2_FREQ;								// Peripheral clock frequency
	I2C2->CR2 |= 36;

	I2C2->CCR &= ~I2C_CCR_CCR;
	I2C2->CCR = 180;

	I2C2->TRISE = 37;

	I2C2->CR1 |= I2C_CR1_PE;									// Enable I2C2

}
/**********************************************************************************************/

	
