#include "main.h"


char str[20];
//char str_1[100];
//int32_t adc = 0;
float temp = 0;

float cof = 0;
float weight = 0;
int zero = 0;

void Get_coff(void);
void Get_Weight(void);
void Get_Zero(void);


int main(void){	

	RCC_Init();
	Delay_Init();
	GPIO_Init();
	I2C_Init();
	ads1220_Init();
	
	Delay_ms(200);
	ssd1306_Init();
	
	ssd1306_SetCursor(2, 0);
	ssd1306_WriteString("ADS1220", Font_7x10, White);
	ssd1306_UpdateScreen();
 
	//Get_coff();
  Get_Zero();
	
	
	while(1){	
		
//    adc = ads1220_GetData();
//	  mv = ads1220_Get_V();
//    sprintf(str, "V:%.4f mV", mv);
//    sprintf(str_1, "ADC:%i  ", adc);
//	  ssd1306_SetCursor(2, 12);
//    ssd1306_WriteString(str, Font_7x10, White);
//    ssd1306_SetCursor(2, 20);
//    ssd1306_WriteString(str_1, Font_7x10, White);
//    ssd1306_UpdateScreen();
//    GPIOC->ODR ^= GPIO_ODR_ODR13;
		
//		temp = ads1220_Get_temp();
//		sprintf(str, "T:%.3f   ", temp);
//		ssd1306_SetCursor(2, 12);
//	  ssd1306_WriteString(str, Font_11x18, White);
//		ssd1306_UpdateScreen();
		
		Get_Weight();
		
		
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

		weight = ads1220_GetWeight(10, 15.75, zero);   // get adc value
		sprintf(str, "%.3fKg  ", weight/1000.f);
		//sprintf(str, "%.3fH   ", ((float)weight*9.81f)/1000.f);
		ssd1306_SetCursor(2, 12);
		ssd1306_WriteString(str, Font_11x18, White);
		ssd1306_UpdateScreen();
		weight = 0;
		
}
////////////////////////////////////////
void Get_Zero(void){
	zero = ads1220_GetZero(10);
	zero = 0;
	zero = ads1220_GetZero(20);
	
}
////////////////////////////////////////
