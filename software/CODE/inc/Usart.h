#ifndef USART_H_
#define USART_H_


#include "stm32f10x.h"

/****************************************************/
void Usart1_Init(void);
void USART_Send (USART_TypeDef* USARTx, char chr);
void USART_Send_Data(USART_TypeDef* USARTx, uint8_t data);
void USART_Send_String (USART_TypeDef* USARTx, char* str);
void USART_IRQHandler (USART_TypeDef* USARTx);
/****************************************************/

#endif /* USART_H_ */

