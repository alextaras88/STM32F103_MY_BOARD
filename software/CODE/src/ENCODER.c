#include "ENCODER.h"

int32_t capture = 0, capture_prev = 0, encoder = 0;

/****************************************************************************************************/
void Encoder_Init(TIM_TypeDef* TIMx, uint16_t period){
	
	if(TIMx == TIM1)
		RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;											// Enable clock TIM1
		RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;											// Enable clock port A
	
	GPIOA->CRH &= ~(GPIO_CRH_CNF8_0 | GPIO_CRH_CNF9_0);				// Setting PA8 and PA9 input pull-down
	GPIOA->CRH |= GPIO_CRH_CNF8_1 | GPIO_CRH_CNF9_1;
	GPIOA->ODR &= ~GPIO_ODR_ODR8 | GPIO_ODR_ODR9;
	/**************************************************************************************/
	if(TIMx == TIM2)
		RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;											// Enable clock TIM2
		RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;											// Enable clock port A
	
	GPIOA->CRL &= ~(GPIO_CRL_CNF0_0 | GPIO_CRL_CNF1_0);				// Setting PA0 and PA1 input pull-down
	GPIOA->CRL |= GPIO_CRL_CNF0_1 | GPIO_CRL_CNF1_1;
	GPIOA->ODR &= ~GPIO_ODR_ODR0 | GPIO_ODR_ODR1;
	/**************************************************************************************/
	if(TIMx == TIM3)
		RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;											// Enable clock TIM3
		RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;											// Enable clock port A
	
	GPIOA->CRL &= ~(GPIO_CRL_CNF6_0 | GPIO_CRL_CNF7_0);				// Setting PA6 and PA7 input pull-down
	GPIOA->CRL |= GPIO_CRL_CNF6_1 | GPIO_CRL_CNF7_1;
	GPIOA->ODR &= ~GPIO_ODR_ODR6 | GPIO_ODR_ODR7;
	/**************************************************************************************/
	if(TIMx == TIM4)
		RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;											// Enable clock TIM4
		RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;											// Enable clock port B
	
	GPIOB->CRL &= ~(GPIO_CRL_CNF6_0 | GPIO_CRL_CNF7_0);				// Setting PB6 and PB7 input pull-down
	GPIOB->CRL |= GPIO_CRL_CNF6_1 | GPIO_CRL_CNF7_1;
	GPIOB->ODR &= ~GPIO_ODR_ODR6 | GPIO_ODR_ODR7;
	/**************************************************************************************/
	
	TIMx->CCMR1 |= TIM_CCMR1_IC1F | TIM_CCMR1_IC2F;						// Set filter sampling
	TIMx->CCMR1 |= TIM_CCMR1_CC1S_0 | TIM_CCMR1_CC2S_0;				// Enable TI1 and TI2
	TIMx->CCER  &= ~(TIM_CCER_CC1P | TIM_CCER_CC2P); 					// Polarity front signal
	TIMx->SMCR  |= TIM_SMCR_SMS_0 | TIM_SMCR_SMS_1;						// Counter on both channel

	TIMx->ARR = period - 1;											      				// Period
	
	TIMx->CR1 |= TIM_CR1_CEN; 																// Enable counter
	
	TIMx->CNT = 0;
	
}

/****************************************************************************************************/
uint16_t Get_Encoder(TIM_TypeDef* TIMx){
	
	return TIMx->CNT;

}
/****************************************************************************************************/
float Get_Encoder_Angle(TIM_TypeDef* TIMx, uint16_t tic){
	
	return (float)Get_Encoder(TIMx)/((float)tic/360.0f);

}
/****************************************************************************************************/
float Get_Encoder_mm(TIM_TypeDef* TIMx){
	
	capture = TIMx->CNT;
		encoder += capture - capture_prev;
    if (abs(capture-capture_prev)>32767) {
			
      encoder += (capture<capture_prev ? 65535 : -65535);
      
    }
		
		capture_prev = capture;
		
		return (float)encoder/2750.0f;

}


