#ifndef AD7799_H_
#define AD7799_H_


#include "stm32f10x.h"
#include "Delay.h"
#include "SPI.h"

/****************************************************/
void Spi_AD7799_Init(void);
void AD7799_Init(void);
void AD7799_Reset(void);
unsigned long getADC7799(void);
void AD7799_Set_CH_1(void);
void AD7799_Set_CH_2(void);
void AD7799_Set_CH_3(void);
/****************************************************/

#endif /* AD7799_H_ */



