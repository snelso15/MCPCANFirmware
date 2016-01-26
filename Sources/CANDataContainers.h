/*
 * CANDataContainers.h
 *
 *  Created on: Jan 25, 2016
 *      Author: new
 */

#ifndef SOURCES_CANDATACONTAINERS_H_
#define SOURCES_CANDATACONTAINERS_H_

struct CANMsg {
	unsigned short senderId;
	uint8_t bufNum; //rx buf 0 or 1
	uint8_t ext; //1 -extended id sent w/ msg, 0 - std id
	uint8_t data[8]; //8 data bytes
};


#endif /* SOURCES_CANDATACONTAINERS_H_ */
