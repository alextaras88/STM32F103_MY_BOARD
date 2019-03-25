#ifndef WEIGHT_H_
#define WEIGHT_H_


/****************************************************/
#include "stm32f10x.h"
#include "ad7730.h"
#include "ad7799.h"
#include "ads1220.h"
#include "Delay.h"
/****************************************************/
uint32_t ad7799_GetZero(uint8_t time);
float ad7799_GetWeight(uint32_t time, float coff, uint32_t zero);
float ad7799_GetCoff(uint8_t time, uint16_t weight);

uint32_t ad7730_GetZero(uint8_t time);
float ad7730_GetWeight(uint32_t time, float coff, uint32_t zero);
float ad7730_GetCoff(uint8_t time, uint16_t weight);

int32_t  ads1220_GetZero(uint8_t time);
float  ads1220_GetWeight(uint32_t time, float coff, int32_t zero);
float  ads1220_GetCoff(uint8_t time, uint16_t weight);
/****************************************************/

#endif /* WEIGHT_H_ */


