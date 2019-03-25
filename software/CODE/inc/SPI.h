#ifndef SPI_H_
#define SPI_H_


#include "stm32f10x.h"

/****************************************************/
#define		    CS_1_LOW 	    GPIOA->ODR &= ~GPIO_ODR_ODR4;
#define 	    CS_1_HIGH 	  GPIOA->ODR |= GPIO_ODR_ODR4;

#define		    CS_2_LOW 	    GPIOA->BSRR = GPIO_BSRR_BR8;
#define 	    CS_2_HIGH 	  GPIOA->BSRR = GPIO_BSRR_BS8;

#define 			SPI_IS_BUSY(SPIx)         (((SPIx)->SR & (SPI_SR_TXE | SPI_SR_RXNE)) == 0 || ((SPIx)->SR & SPI_SR_BSY))
#define 			SPI_WAIT(SPIx)            while (SPI_IS_BUSY(SPIx))
/****************************************************/
void Spi_1_Init(void);
void Spi_2_Init(void);
uint16_t Spi_Write_Read_Data16(SPI_TypeDef* SPIx, uint16_t data);
uint8_t Spi_transfer_8(SPI_TypeDef* SPIx, uint8_t data);
void Spi_multi_send_8(SPI_TypeDef* SPIx, uint8_t* data, uint16_t len);
/****************************************************/

#endif /* SPI_H_ */


