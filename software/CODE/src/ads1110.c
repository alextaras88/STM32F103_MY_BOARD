#include "ads1110.h"

/****************************************************************************************************/
void Write_ADS1110_Config(uint8_t addr, ads1110_datarate dr, ads1110__gain gain){
	
	uint8_t config = gain | dr | ADS1110_MODE_CONTINUOUS | BIT_5 | BIT_6 | RDY;
	
	Start_i2c(I2C1);
	Write_addr_i2c(I2C1, addr,0);
	Write_one_data_i2c(I2C1, config);
	Stop_i2c(I2C1);

}
/****************************************************************************************************/
uint16_t Get_ADS1110_Data(uint8_t addr){
  
  uint8_t byte1, byte2, byte3, conf;
  uint16_t data_adc;
  
  Start_i2c(I2C1);
	Write_addr_i2c(I2C1, addr,1);			
  byte1 = Read_data_i2c(I2C1);
  byte2 = Read_data_i2c(I2C1);
  byte3 = Read_last_data_i2c(I2C1);
	//Stop_i2c();
  
  conf = byte3;
  if( (conf & (1<<7)) == 0){
    
    data_adc = (byte1<<8)|byte2;
    
    return data_adc;
    
  }
  
  else return 0;
}
/****************************************************************************************************/


