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

struct SlaveState {
	uint8_t status; //0 - locked w/ bike
				   //1 - unlocked w/ bike, before user removes
				   //2 - locked w/o bike, after user has removed
				   //3 - unlocked w/o bike, waiting for return
	short bikeId;   //ID of the locked bike, reads 0 if bike not present
	uint8_t bikeBattery; //value (if implemented) of the Bike's on-board battery
};

#endif /* SOURCES_CANDATACONTAINERS_H_ */
