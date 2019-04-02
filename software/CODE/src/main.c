#include "main.h"

uint8_t state = 0;
char str[20];
char str2[20];
//char str_1[100];
//int32_t adc = 0;
float temp = 0;
float cof = 0;
float weight = 0;
int zero = 0;

void Get_coff(void);
void Get_Weight(void);
void Get_Zero(void);
void USART_Mschine(uint8_t state);

int main(void){

	RCC_Init();
	Delay_Init();
	GPIO_Init();
	Usart1_Init();
	I2C_Init();
	ads1220_Init();
	Display_Init();

	Delay_ms(200);
	ssd1306_Init();

	ssd1306_SetCursor(2, 0);
	ssd1306_WriteString("ADS1220", Font_7x10, White);
	ssd1306_UpdateScreen();
	
	disp1color_FillScreenbuff(0);
	disp1color_printf(10, 50, FONTID_6X8M, "ADS1220 Load Cell",0x00);
	disp1color_UpdateFromBuff();
	Delay_ms(1000);
	disp1color_FillScreenbuff(0);
	disp1color_DrawRectangle(5, 5, 122, 58);
	disp1color_DrawRectangle(2, 2, 125, 61);
	disp1color_DrawLine(5, 27, 122, 27);

	disp1color_printf(30, 8, FONTID_10X16F, "ADS1220",0x00);
	disp1color_UpdateFromBuff();
	//Get_coff();
  Get_Zero();

	while(1){
		
		state = 0;
		Get_Weight();
		USART_Mschine(state);

	}
}
///////////////////////////////////////
void Get_coff(void){

	cof = ads1220_GetCoff(20, 1000);
	sprintf(str, "COFF:%.4f    ", cof);
	ssd1306_SetCursor(2, 12);
	ssd1306_WriteString(str, Font_11x18, White);
	ssd1306_UpdateScreen();

}
////////////////////////////////////////
void Get_Weight(void){

		if ((GPIOA->IDR & GPIO_IDR_IDR0) == 0){

			Delay_ms(100);

			if ((GPIOA->IDR & GPIO_IDR_IDR0) == 0){

				GPIOC->ODR |= GPIO_ODR_ODR13;
				zero =  ads1220_GetZero(20);  // get adc value
				GPIOC->ODR &= ~GPIO_ODR_ODR13;
				weight = 0;

		}

		}

		weight = ads1220_GetWeight(10, 133, zero);   // get adc value
		//sprintf(str, "%.3fKg  ", weight/1000.f);
		sprintf(str, "W%.3fKg\r\n", weight/1000.f);
		USART_Send_String (USART1, str);
		//sprintf(str2, "%.5fKg  ", weight/1000.f);
		
		//sprintf(str, "%.3fH   ", ((float)weight*9.81f)/1000.f);
		//ssd1306_SetCursor(2, 12);
		//ssd1306_WriteString(str2, Font_11x18, White);
		//ssd1306_UpdateScreen();
		
		disp1color_printf(35, 35, FONTID_10X16F, "%.3fKg  ",weight/1000.f);
		disp1color_UpdateFromBuff();
		weight = 0;
		
}

////////////////////////////////////////
void Get_Zero(void){
	
	zero = ads1220_GetZero(10);
	zero = 0;
	zero = ads1220_GetZero(20);

	}
////////////////////////////////////////
void USART1_IRQHandler(void){

	if (USART1->SR & USART_CR1_RXNEIE){

		USART1->SR &= ~USART_CR1_RXNEIE;

		if (USART1->DR == '0'){

			GPIOC->BSRR |= GPIO_BSRR_BR13;
			state = 1;

		}

		if (USART1->DR == '1'){

			state = 2;

		}

		if (USART1->DR == '2'){

			state = 3;

		}
		if (USART1->DR == '3'){

			state = 4;

		}
		if (USART1->DR == '4'){

			state = 5;

		}
		if (USART1->DR == '5'){

			state = 6;

		}
	}

}
/*********************************************************************************************************/
void USART_Mschine(uint8_t state){

	switch(state){

		case 0:
			break;
		
		case 1:
			GPIOC->ODR |= GPIO_ODR_ODR13;
			zero =  ads1220_GetZero(20);  // get adc value
			GPIOC->ODR &= ~GPIO_ODR_ODR13;
			weight = 0;
			USART_Send_String (USART1, "<0>\r\n");
			break;
		
		case 2:
			sprintf(str,"ADC_Zero: %i \r\n", zero);
			USART_Send_String (USART1, str);
			break;
		case 3:
			cof = ads1220_GetCoff(20, 1000);
			sprintf(str, "ADC Coff: %.3f\r\n", cof);
		  USART_Send_String (USART1, str);
			break;
		
		case 4:
			break;
		
		case 5:
			break;
		
		case 6:
			
			USART_Send_String (USART1, "Help!!!\r\n");
			USART_Send_String (USART1, "0 - Zero\r\n");
			USART_Send_String (USART1, "1 - ADC-zero\r\n");
			USART_Send_String (USART1, "2 - Get ADC Coff\r\n");
			USART_Send_String (USART1, "4 - ...\r\n");
			USART_Send_String (USART1, "5 - Help\r\n");
			break;

	}

}
