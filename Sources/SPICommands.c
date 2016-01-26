/*** created to extract all SPI functionality for more readable code***
 * SPI_Commands.c
 *
 *  Created on: Jan 25, 2016
 *      Author: Samuel Nelson
 */

#include "SPICommands.h"
#include "utils.h"

//KL26z spi firmware globals
volatile bool spi_msg_in_progress = FALSE;
LDD_TDeviceData *MySPIPtr = NULL;

//NOTE: THIS FUNCTION MUST BE CALLED BEFORE ANY SPI COMMANDS WILL WORK
void initSPI(){
	MySPIPtr = CAN_SPI_Init(NULL); /* Initialization of SM1 component */
}

uint8_t readReg(uint8_t reg_address){
	uint8_t out_data[3] = {CMD_READ, reg_address, 0x00}; //last byte doesn't matter, just to provide clocking for response
	uint8_t in_data[3];
	LDD_TError LDD_Error;

	spi_msg_in_progress = TRUE;
	CAN_SS_ClrVal();
	LDD_Error = CAN_SPI_ReceiveBlock(MySPIPtr, in_data, 3);
	LDD_Error = CAN_SPI_SendBlock(MySPIPtr, out_data, 3);
	while (spi_msg_in_progress){};
	CAN_SS_SetVal();

	busyWait(25); //make sure SS line held high long enough for CAN device recognition

	return in_data[2];
}

void writeReg(uint8_t reg_address, uint8_t val){
	uint8_t in_data[3];
	uint8_t out_data[3] = {CMD_WRITE, reg_address, val};
	LDD_TError LDD_Error;

	spi_msg_in_progress = TRUE;
	CAN_SS_ClrVal();
	LDD_Error = CAN_SPI_ReceiveBlock(MySPIPtr, in_data, 3); /* Request 3 btes to be received before pulling SS high */
	LDD_Error = CAN_SPI_SendBlock(MySPIPtr, out_data, 3);
	while(spi_msg_in_progress){}; //wait for message complete before raising SS
	CAN_SS_SetVal();

	busyWait(25); //make sure SS line held high long enough for CAN device recognition
}

void bitModReg(uint8_t reg_address, uint8_t mask, uint8_t byte_to_write){
	uint8_t in_data[4];
	uint8_t out_data[4] = {CMD_BIT_MOD, reg_address, mask, byte_to_write};
	LDD_TError LDD_Error;

	spi_msg_in_progress = TRUE;
	CAN_SS_ClrVal();
	LDD_Error = CAN_SPI_ReceiveBlock(MySPIPtr, in_data, 4); /* Request 3 btes to be received before pulling SS high */
	LDD_Error = CAN_SPI_SendBlock(MySPIPtr, out_data, 4);
	while(spi_msg_in_progress){}; //wait for message complete before raising SS
	CAN_SS_SetVal();

	busyWait(25); //make sure SS line held high long enough for CAN device recognition
}

void resetCAN(){
	uint8_t reset_cmd = CMD_RESET;
	uint8_t byte_to_read; //arbitrary byte
	LDD_TError LDD_Error;

	spi_msg_in_progress = TRUE;
	CAN_SS_ClrVal();
	LDD_Error = CAN_SPI_ReceiveBlock(MySPIPtr, &byte_to_read, 1); // Request to receive 1 byte
	LDD_Error = CAN_SPI_SendBlock(MySPIPtr, &reset_cmd, 1); //send 1 byte
	while(spi_msg_in_progress){}; //wait until 1 byte received to keep slave select low - flag set in Events.c
	CAN_SS_SetVal(); //raise slave select

	busyWait(25000); //wait for device clock to stabilize
}


