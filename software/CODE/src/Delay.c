#include "Delay.h"

volatile uint32_t msTicks;

void SysTick_Handler (void) //Enter here every 1 ms
{
  msTicks++;
}

/*********************************************************************************************************/
void Delay_ms(uint32_t dlyTicks)
{
  uint32_t curTicks;
  curTicks = msTicks;
  while ((msTicks - curTicks) < dlyTicks);
	
}
/*********************************************************************************************************/
void Delay_us(uint32_t us){
	
   volatile uint32_t delay = (us * (SystemCoreClock / 720000)/13);
   while (delay--);   
	
}
/*********************************************************************************************************/
void Delay_Init(void){
	
	SysTick->LOAD = TimerTick;
	SysTick->VAL = TimerTick;
	SysTick->CTRL =	SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;
  //SysTick_Config(SystemCoreClock/1000); // 'prescaler' of SysTick for 1 ms

}
/*********************************************************************************************************/




