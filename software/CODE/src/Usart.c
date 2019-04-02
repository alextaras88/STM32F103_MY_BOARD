/************************************************** Library ************************************************************************************/

#include "Usart.h"

/************************************************* Use functions *******************************************************************************/
void Usart1_Init(void){

	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;        // Включаем тактирование USART1
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;          // Включаем тактирование порта А
  RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;				   // Включаем тактирование альтернативных выводов
	
	AFIO->MAPR |= AFIO_MAPR_USART1_REMAP;        // Remap USART1 Pins PB6, PB7
	
	GPIOB->CRL |= GPIO_CRL_CNF6_1;               // TX альтернативный выход PUSH_PULL
	GPIOB->CRL |= GPIO_CRL_MODE6;                // 50 мГц
	
	GPIOB->CRL |= GPIO_CRL_CNF7_0;               // RX плавающий вход
	GPIOB->CRL &= ~GPIO_CRL_MODE7; 
         		
	USART1->BRR = 0x271;	// fck = 72mHz, baudrate = 115200 USART_BRR = (fck + baudrate /2 ) / baudrate
	//USART1->BRR = 0x1DC4;  //9600
	
	USART1->CR1 |= USART_CR1_TE;                 // Включаем передачу по USART
	USART1->CR1 |= USART_CR1_RE;                 // Включаем приём по USART
	USART1->CR1 |= USART_CR1_UE;                 // Включаем сам USART
	
	USART1->CR1 |= USART_CR1_RXNEIE;	           // Включаем прерывание по приёму
	NVIC_EnableIRQ(USART1_IRQn);                 // Вектор прерывания по приёму

}
/*********************************************************************************************************/
void USART_Send(USART_TypeDef* USARTx, char chr){                   // Передаём один символ
	
	while (!(USARTx->SR & USART_SR_TC));
	USARTx->DR = chr;
	
}
/*********************************************************************************************************/
void USART_Send_Data(USART_TypeDef* USARTx, uint8_t data){                   // Передаём uint8_t
	
	while (!(USARTx->SR & USART_SR_TC));
	USARTx->DR = data;
	
}
/*********************************************************************************************************/
void USART_Send_String (USART_TypeDef* USARTx, char* str){            // Передаём строку
	
	uint8_t i = 0;
 	
	while(str[i])
	USART_Send(USARTx, str[i++]);

}
/*********************************************************************************************************/





