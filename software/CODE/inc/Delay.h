#ifndef DELAY_H_
#define DELAY_H_


#include "stm32f10x.h"

/****************************************************/
#define F_CPU 72000000UL
#define TimerTick		F_CPU/1000
/****************************************************/
void Delay_Init(void);
void Delay_ms(uint32_t dlyTicks);
void Delay_us(uint32_t us);
/****************************************************/

#endif /* DELAY_H_ */




