/************************************************** Library ************************************************************************************/

#include "Start_init.h"

/************************************************* Use functions *******************************************************************************/

void RCC_Init(void){

  RCC->CR |= ((uint32_t)RCC_CR_HSEON); 												// �������� HSE
	while (!(RCC->CR & RCC_CR_HSERDY));													// ���� ���������� HSE
	
	FLASH->ACR = FLASH_ACR_PRFTBE | FLASH_ACR_LATENCY_2;				// ����������� ������������ Flash memory

	RCC->CFGR |= RCC_CFGR_HPRE_DIV1;														// ��������� ����� ���� ������������ AHB = SYSCLK/1
	RCC->CFGR |= RCC_CFGR_PPRE2_DIV1;                           // ��������� ������������  ���� ������������ APB2 = HCLK/2
	RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;														// ��������� ������������  ���� ������������ APB1 = HCLK/1
	
	RCC->CFGR &= ~RCC_CFGR_PLLMULL;               							// C��������� ��� PLLMULL bits
	RCC->CFGR &= ~RCC_CFGR_PLLSRC;															// C��������� ��� PLLSRC bits
	RCC->CFGR &= ~RCC_CFGR_PLLXTPRE;	                         	// C��������� ��� PLLXTPRE bits
	
	RCC->CFGR |= RCC_CFGR_PLLSRC_HSE; 											    // �������� HSE
	RCC->CFGR |= RCC_CFGR_PLLXTPRE_HSE; 							          // �������� HSE
	RCC->CFGR |= RCC_CFGR_PLLMULL9; 														// PLL x9: clock = 8 MHz * 9 = 72 MHz
	
	RCC->CR |= RCC_CR_PLLON;                      							// �������� PLL
	while((RCC->CR & RCC_CR_PLLRDY) == 0) {}      							// ���� ���������� PLL
		
	RCC->CFGR &= ~RCC_CFGR_SW;                   							 	// C��������� ��� SW bits
  RCC->CFGR |= RCC_CFGR_SW_PLL;                 							// ����� ������������ ��������� ���� SYSCLK = PLL
  while((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_1) {}      // ���� ���� ��������� ������������ ��������� ���� SYSCLK
		
}

/*********************************************************************************************************/
void GPIO_Init(void){
	// PC13 OutPut
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;                         // �������� ������������ �� ����� GPIOC
  // PA11 InPut
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;                         // �������� ������������ �� ����� GPIOA
	
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

	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;                       	// �������� ������������ �� ����� �
	
	GPIOA->CRH &= ~GPIO_CRH_CNF8_0;															// �������������� ����� �� PA8
	GPIOA->CRH |= GPIO_CRH_CNF8_1;
	GPIOA->CRH |= (GPIO_CRH_MODE8_0 | GPIO_CRH_MODE8_1);				// �������� ����� 50 MHz
	
	RCC->CFGR |= RCC_CFGR_MCO_SYSCLK;													  // ������� ������ SYSCLK
	//RCC->CFGR |= RCC_CFGR_MCO_HSE;														// ������� ������ HSE
	//RCC->CFGR |= RCC_CFGR_MCO_HSI;														// ������� ������ HSI
	//RCC->CFGR |= RCC_CFGR_MCO_PLL;														// ������� ������ PLL

}
/*********************************************************************************************************/

