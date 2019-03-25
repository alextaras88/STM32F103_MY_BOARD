#include "zephyr_hafuht.h"

/************************************************************************************/
/* Honeywell ZephyrTM Digital Airflow Sensors                                       */
/* HAF Series—High Accuracy: 10 SLPM, 15 SLPM, 20 SLPM,                             */
/* 50 SLPM, 100 SLPM, 200 SLPM, 300 SLPM                                            */
/************************************************************************************/

uint16_t GetDataZephyr(uint8_t addr){
	
	uint8_t b1, b2;
	uint16_t data;
	
	Start_i2c(I2C1);
	Write_addr_i2c(I2C1, addr,1);
	b1 = Read_data_i2c(I2C1);
  b2 = Read_last_data_i2c(I2C1);    
		
	data =(b1 << 8) + b2;
	
	return data;		
}
/************************************************************************************/
/* addr - address I2C bus (0x49)                                                    */
/* splm - flow rate range                                                           */
/* time - flow rate 1 minute/60 minute(1 hour)                                      */
/************************************************************************************/
float GetFlowZephyr(uint8_t addr, uint16_t slpm, uint8_t time){
	
	 return  (slpm*(((float)GetDataZephyr(addr)/16384) - 0.1)/0.8)*time;
	
}
/************************************************************************************/
uint32_t GetSNZephyr(uint8_t addr){
	
	uint8_t b1, b2, b3, b4;
	uint32_t data;
	
	Start_i2c(I2C1);
	Write_addr_i2c(I2C1, addr,1);
  b1 = Read_data_i2c(I2C1);
  b2 = Read_last_data_i2c(I2C1); 
	Delay_ms(15);
	
	Start_i2c(I2C1);
	Write_addr_i2c(I2C1, addr,1);
  b3 = Read_data_i2c(I2C1);
  b4 = Read_last_data_i2c(I2C1);
	
	data = (b1<<24) + (b2<<16) + (b3<<8) + b4;
	
	return data;

}
/************************************************************************************/
