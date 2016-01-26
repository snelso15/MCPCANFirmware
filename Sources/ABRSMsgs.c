/*
 * ABRSMsgs.c
 *
 *  Created on: Jan 26, 2016
 *      Author: Samuel Nelson
 *
 */

#include "ABRSMsgs.h"
#include "MCP25625.h"

int sendUnlockBikeReq(uint8_t slaveId){
	uint8_t data[8] = {1, slaveId, 0, 0, 0, 0, 0, 0};
	return sendCANMsg(data, 8);
}

int sendUnlockBikeAck(uint8_t unlockStatus){
	uint8_t data[8] = {2, unlockStatus, 0, 0, 0, 0, 0, 0};
	return sendCANMsg(data, 8);
}

int sendReturnBikeReq(uint8_t slaveId){
	uint8_t data[8] = {3, slaveId, 0, 0, 0, 0, 0, 0};
	return sendCANMsg(data, 8);
}

int sendReturnBikeAck(uint8_t unlockStatus){
	uint8_t data[8] = {4, unlockStatus, 0, 0, 0, 0, 0, 0};
	return sendCANMsg(data, 8);
}

int sendBikeReturnedNotif(unsigned short bikeId){
	uint8_t data[8] = {5, (bikeId >> 8), (bikeId & 0xFF), 0, 0, 0, 0, 0};
	return sendCANMsg(data, 8);
}

int sendBikeReturnedAck(uint8_t slaveId){
	uint8_t data[8] = {6, slaveId, 0, 0, 0, 0, 0, 0};
	return sendCANMsg(data, 8);
}

int sendStatusReq(){
	uint8_t data[8] = {7, 0, 0, 0, 0, 0, 0, 0};
	return sendCANMsg(data, 8);
}

int sendStatusResp(uint8_t bikePresent, unsigned short bikeId, uint8_t lockState){
	uint8_t data[8] = {8, bikePresent, (bikeId >> 8), (bikeId & 0xFF), lockState, 0, 0, 0};
	return sendCANMsg(data, 8);
}

