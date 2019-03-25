/************************************************** Library ************************************************************************************/

#include "Start_init.h"

/************************************************* Use functions *******************************************************************************/

void RCC_Init(void){

  RCC->CR |= ((uint32_t)RCC_CR_HSEON); 												// Включаем HSE
	while (!(RCC->CR & RCC_CR_HSERDY));													// Ждем готовности HSE
	
	FLASH->ACR = FLASH_ACR_PRFTBE | FLASH_ACR_LATENCY_2;				// Настраиваем тактирование Flash memory

	RCC->CFGR |= RCC_CFGR_HPRE_DIV1;														// Настройка общей шины тактирования AHB = SYSCLK/1
	RCC->CFGR |= RCC_CFGR_PPRE2_DIV1;                           // Настройка переферийной  шины тактирования APB2 = HCLK/2
	RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;														// Настройка переферийной  шины тактирования APB1 = HCLK/1
	
	RCC->CFGR &= ~RCC_CFGR_PLLMULL;               							// Cбрасываем бит PLLMULL bits
	RCC->CFGR &= ~RCC_CFGR_PLLSRC;															// Cбрасываем бит PLLSRC bits
	RCC->CFGR &= ~RCC_CFGR_PLLXTPRE;	                         	// Cбрасываем бит PLLXTPRE bits
	
	RCC->CFGR |= RCC_CFGR_PLLSRC_HSE; 											    // Источник HSE
	RCC->CFGR |= RCC_CFGR_PLLXTPRE_HSE; 							          // Источник HSE
	RCC->CFGR |= RCC_CFGR_PLLMULL9; 														// PLL x9: clock = 8 MHz * 9 = 72 MHz
	
	RCC->CR |= RCC_CR_PLLON;                      							// Включаем PLL
	while((RCC->CR & RCC_CR_PLLRDY) == 0) {}      							// Ждем готовности PLL
		
	RCC->CFGR &= ~RCC_CFGR_SW;                   							 	// Cбрасываем бит SW bits
  RCC->CFGR |= RCC_CFGR_SW_PLL;                 							// Выбор тактирования системной шины SYSCLK = PLL
  while((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_1) {}      // Ждем флаг установки тактирования системной шины SYSCLK
		
}

/*********************************************************************************************************/
void GPIO_Init(void){
	// PC13 OutPut
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;                         // Включаем тактирование на порту GPIOC
  // PA11 InPut
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;                         // Включаем тактирование на порту GPIOA
	
	GPIOC->CRH &= ~GPIO_CRH_CNF13;                              //PC13
  GPIOC->CRH |= (GPIO_CRH_MODE13_0 | GPIO_CRH_MODE13_1);
	//////////////////////////////////
	GPIOA->CRL &= ~GPIO_CRL_CNF2;                              //PA2 down power
  GPIOA->CRL |= (GPIO_CRL_MODE2_0 | GPIO_CRL_MODE2_1);
////////////////////////////////////////////////
	GPIOA->CRH &= ~GPIO_CRH_CNF12;                              //P12 up power
  GPIOA->CRH |= (GPIO_CRH_MODE12_0 | GPIO_CRH_MODE12_1);
	
  
	

}
/*********************************************************************************************************/
void MCO_Out(void){

	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;                       	// Включаем тактирование на порту А
	
	GPIOA->CRH &= ~GPIO_CRH_CNF8_0;															// Альтернативный выход на PA8
	GPIOA->CRH |= GPIO_CRH_CNF8_1;
	GPIOA->CRH |= (GPIO_CRH_MODE8_0 | GPIO_CRH_MODE8_1);				// Скорость порта 50 MHz
	
	RCC->CFGR |= RCC_CFGR_MCO_SYSCLK;													  // Выводим сигнал SYSCLK
	//RCC->CFGR |= RCC_CFGR_MCO_HSE;														// Выводим сигнал HSE
	//RCC->CFGR |= RCC_CFGR_MCO_HSI;														// Выводим сигнал HSI
	//RCC->CFGR |= RCC_CFGR_MCO_PLL;														// Выводим сигнал PLL

}
/*********************************************************************************************************/

