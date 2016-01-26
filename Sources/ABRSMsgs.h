/*
 * ABRSMsgs.h
 *
 *  Created on: Jan 26, 2016
 *      Author: Samuel Nelson
 */

#ifndef SOURCES_ABRSMSGS_H_
#define SOURCES_ABRSMSGS_H_

#include "PE_Types.h"
//messages for the bike rack's communication protocol.
//see MsgProtocolDef.txt for details

int sendUnlockBikeReq(uint8_t slaveId);
int sendUnlockBikeAck(uint8_t unlockStatus);
int sendReturnBikeReq(uint8_t slaveId);
int sendReturnBikeAck(uint8_t unlockStatus);
int sendBikeReturnedNotif(unsigned short bikeId);
int sendBikeReturnedAck(uint8_t slaveId);
int sendStatusReq();
int sendStatusResp(uint8_t bikePresent, unsigned short bikeId, uint8_t lockState);

#endif /* SOURCES_ABRSMSGS_H_ */
