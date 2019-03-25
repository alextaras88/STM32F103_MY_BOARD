#ifndef I2C_H_
#define I2C_H_


#include "stm32f10x.h"

/****************************************************/
void I2C_Init(void);
void I2C2_Init(void);

void Start_i2c(I2C_TypeDef* I2Cx);
void Stop_i2c(I2C_TypeDef* I2Cx);
void Write_addr_i2c(I2C_TypeDef* I2Cx, uint8_t addr, uint8_t rw);
void Write_data_i2c(I2C_TypeDef* I2Cx, uint8_t data);
void Write_one_data_i2c(I2C_TypeDef* I2Cx, uint8_t data);
void Write_last_data_i2c(I2C_TypeDef* I2Cx, uint8_t data);
uint8_t Read_data_i2c(I2C_TypeDef* I2Cx);
uint8_t Read_last_data_i2c(I2C_TypeDef* I2Cx);
/****************************************************/

#endif /* I2C_H_ */
