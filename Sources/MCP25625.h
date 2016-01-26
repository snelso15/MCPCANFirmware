/*
 * MCP25625.h
 *
 *  Created on: Jul 18, 2015
 *      Author: Sam Nelson
 */

#ifndef SOURCES_MCP25625_H_
#define SOURCES_MCP25625_H_


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
#include "CANDataContainers.h"

/* Unit standard (11-bit) ID
 * !!!!!!!!!!!!!!!!!!!!!!!
 * HARDCODE UNIT's ID HERE
 * !!!!!!!!!!!!!!!!!!!!!!!
 * To allow for simple filtering methods:
 * MASTER (KIOSK) ID is always 2047  (first bit out of 11 is a 1)
 * ALL SLAVE (RACK) ID's ARE <= 1023 (first bit out of 11 is a 0)
 *  */
static volatile unsigned short unitId = 2047; //slave <= 255, master = 2047


/* ************************************************
 * Functions for Initializing CAN controller
 *
 * */
void initializeCAN(unsigned short identifier);
void setCANSpeed();
void setStdId(unsigned short id);
uint8_t setCANMode(uint8_t mode);
void setCANRXRegisters(uint8_t RXSetting);
void setMasksAndFilters();
void setCANInterrupts(uint8_t val);


/* ************************************************
 * Functions for reading CAN registers of interest
 *
 * */
uint8_t readCANSTATReg();
uint8_t readCANInterrupts();
uint8_t readCANErrorFlags();
uint8_t readTxErrorCount();


/* ************************************************
 * Functions for writing to CAN registers of interest
 * TODO - include return error codes for robustness
 * */
void writeCANCTRLReg(uint8_t val);
void clearSpecificCANInterrupts(uint8_t mask_byte);
void clearAllCANInterrupts();


/* ************************************************
 * Misc. CAN Functions
 *
 * */
void readCANMsg(int bufNum, struct CANMsg *msg);
int sendCANMsg(uint8_t *data, uint8_t msg_size);
int isRxMsgPending();


#endif /* SOURCES_MCP25625_H_ */
