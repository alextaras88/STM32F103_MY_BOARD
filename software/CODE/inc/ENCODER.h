#ifndef ENCODER_H_
#define ENCODER_H_


#include "stm32f10x.h"

#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

/****************************************************/
void Encoder_Init(TIM_TypeDef* TIMx, uint16_t period);
uint16_t Get_Encoder(TIM_TypeDef* TIMx);
float Get_Encoder_Angle(TIM_TypeDef* TIMx, uint16_t tic);
float Get_Encoder_mm(TIM_TypeDef* TIMx);
/****************************************************/
#endif /* ENCODER_H_ */
