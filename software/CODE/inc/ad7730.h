#ifndef AD7730_H_
#define AD7730_H_


/****************************************************/
#include "stm32f10x.h"
#include "SPI.h"
#include "Delay.h"
/****************************************************/
#define		    CS_AD7730_LOW 	  GPIOA->BSRR = GPIO_BSRR_BR1;
#define 	    CS_AD7730_HIGH 	  GPIOA->BSRR = GPIO_BSRR_BS1;
/****************************************************/
void ad7730_SPI_Init(void);
void ad7730_Init(void);
unsigned long  ad7730_GetData(void);
void reset_7730(void);
/****************************************************/

#endif /* AD7730_H_ */


