#ifndef MCP4725_H_
#define MCP4725_H_


/****************************************************/
#include "stm32f10x.h"
#include "i2c.h"
/****************************************************/
#define MCP_4725_ADDR                   (0x62)
#define MCP_4725_WRITE_DAC              (0x40)
#define MCP_4725_WRITE_DAC_EEPROM       (0x60)
/****************************************************/
void Write_mcp4725(uint8_t addr, uint16_t data, uint8_t config);
/****************************************************/

#endif /* MCP4725_H_ */

