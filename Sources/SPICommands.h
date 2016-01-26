/*
 * SPICommands.h
 *
 *  Created on: Jan 25, 2016
 *      Author: new
 */

#ifndef SOURCES_SPICOMMANDS_H_
#define SOURCES_SPICOMMANDS_H_

#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "CAN_SPI.h"
#include "CAN_SS.h"
#include "BitIoLdd1.h"
#include "utils.h"
#include "CANConstants.h"
#include "SPICommands.h"


 /* MCP firmware globals */
extern volatile bool spi_msg_in_progress; //defined in SPICommands.c
//extern LDD_TDeviceData *MySPIPtr; //defined in SPICommands.c

void initSPI();
uint8_t readReg(uint8_t reg_address);
void writeReg(uint8_t reg_address, uint8_t val);
void bitModReg(uint8_t reg_address, uint8_t mask, uint8_t byte_to_write);
void resetCAN();
#endif /* SOURCES_SPICOMMANDS_H_ */
