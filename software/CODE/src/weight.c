#include "weight.h"

/************************************************************************************/
uint32_t ad7799_GetZero(uint8_t time){
	
	uint32_t zero = 0;
	uint8_t i;
	
	for(i = 0; i<time; i++){
		
		zero += getADC7799();
		Delay_ms(5);
		
	}
	zero/=(uint32_t)time;
	
	return zero;

}
/************************************************************************************/
float ad7799_GetWeight(uint32_t time, float coff, uint32_t zero){
	
	float weight = 0;
	uint32_t i;
	
	for( i = 0; i<time; i++){
		
		weight += (float)getADC7799();
	}
	
	weight /= time;
	weight -= (float)zero;
	weight /= coff;
	
	return (float)weight;
	
}

/************************************************************************************/
float ad7799_GetCoff(uint8_t time, uint16_t weight){
	
	uint32_t zero = 0;
	uint32_t weight1 = 0;
	
	zero = ad7799_GetZero(time);
	GPIOC->ODR |= GPIO_ODR_ODR13;
	Delay_ms(5000);
	
  weight1 = ad7799_GetZero(time); 
	GPIOC->ODR &= ~GPIO_ODR_ODR13;
	
	return (float)(weight1 - zero)/weight;

}
/************************************************************************************/
///////////////////////////////////////////////////////////////////////////////////////
uint32_t ad7730_GetZero(uint8_t time){
	
	uint32_t zero = 0;
	uint8_t i;
	
	for(i = 0; i<time; i++){
		
		zero += ad7730_GetData();
		Delay_ms(50);
		
	}
	zero/=(uint32_t)time;
	
	return zero;

}
/************************************************************************************/
float ad7730_GetWeight(uint32_t time, float coff, uint32_t zero){
	
	float weight = 0;
	uint32_t i;
	
	for( i = 0; i<time; i++){
		
		weight += (float)ad7730_GetData();
	}
	
	weight /= time;
	weight -= (float)zero;
	weight /= coff;
	
	return (float)weight;
	
}

/************************************************************************************/
float ad7730_GetCoff(uint8_t time, uint16_t weight){
	
	uint32_t zero = 0;
	uint32_t weight1 = 0;
	
	zero = ad7730_GetZero(time);
	GPIOC->ODR |= GPIO_ODR_ODR13;
	Delay_ms(5000);
	
  weight1 = ad7730_GetZero(time); 
	GPIOC->ODR &= ~GPIO_ODR_ODR13;
	
	return (float)(weight1 - zero)/weight;

}
/************************************************************************************/
//////////////////////////////////////////////////////////////////////////////////////
int32_t ads1220_GetZero(uint8_t time){
	
	int32_t zero = 0;
	uint8_t i;
	
	for(i = 0; i<time; i++){
		
		zero += ads1220_GetData();
		Delay_ms(5);
		
	}
	zero/=(int32_t)time;
	
	return zero;

}
/************************************************************************************/
float ads1220_GetWeight(uint32_t time, float coff, int32_t zero){
	
	float weight = 0;
	uint32_t i;
	
	for( i = 0; i<time; i++){
		
		weight += (float)ads1220_GetData();
	}
	
	weight /= time;
	weight -= (float)zero;
	weight /= coff;
	
	return (float)weight;
	
}

/************************************************************************************/
float ads1220_GetCoff(uint8_t time, uint16_t weight){
	
	int32_t zero = 0;
	int32_t weight1 = 0;
	
	zero = ads1220_GetZero(time);
	GPIOC->ODR |= GPIO_ODR_ODR13;
	Delay_ms(5000);
	
  weight1 = ads1220_GetZero(time); 
	GPIOC->ODR &= ~GPIO_ODR_ODR13;
	
	return (float)(weight1 - zero)/weight;

}
/************************************************************************************/
///////////////////////////////////////////////////////////////////////////////////////
