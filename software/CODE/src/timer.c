#include "timer.h"

/*********************************************************************************************************/
void TIM4_step_init(void){
	
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;										// enable clock for basic TIM4
	
	TIM4->PSC = 1800-1;																		// div, frequency  40khz
  TIM4->ARR = 8000; 																		// count to 40khz/8000 - 5Hz
  TIM4->DIER |= TIM_DIER_UIE; 													// enable interrupt for timer
  TIM4->CR1 |= TIM_CR1_CEN; 														// start count
  NVIC_EnableIRQ(TIM4_IRQn); 	
	
}
/*********************************************************************************************************/


//void TIM4_IRQHandler(void){
//	
//	TIM4->SR &= ~TIM_SR_UIF; 	
//	

//		
//	}
