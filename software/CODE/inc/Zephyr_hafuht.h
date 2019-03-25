#ifndef ZEPHYR_HAFUHT_H_
#define ZEPHYR_HAFUHT_H_


#include "stm32f10x.h"
#include "i2c.h"
#include "Delay.h"

/****************************************************/
uint16_t GetDataZephyr(uint8_t addr);
float GetFlowZephyr(uint8_t addr, uint16_t slpm, uint8_t time);
uint32_t GetSNZephyr(uint8_t addr);
/****************************************************/

#endif /* ZEPHYR_HAFUHT_H_ */
