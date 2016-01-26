/* firmware source for MCP 25625 CAN controller/transceiver package
 * Author: Sam Nelson
 * Date: 7/18/15
 * */

#include "MCP25625.h"

/* ************************************************
 * Functions for Initializing CAN controller
 *
 * */
void initializeCAN(unsigned short identifier){
	initSPI(); //initialize KL26's SPI peripheral
	busyWait(25000); //wait for CAN device clock to stabilize
	resetCAN();
	setStdId(identifier);
	//setCANSpeed();
	setMasksAndFilters();
	setCANRXRegisters(RX_ALL_FILTERS_ON);
	setCANInterrupts(0x03); //set to trigger interrupts when msg is received in rx buffer
	setCANMode(MODE_NORMAL);
	clearAllCANInterrupts();
}

void setCANSpeed(){
	//vals i think should work with 500kbs
	writeReg(REG_CNF1, 0xC0);//0x3F);
	writeReg(REG_CNF2, 0xDF);//0xFF);
	writeReg(REG_CNF3, 0x03);//0x87);
}

void setStdId(unsigned short id){
	uint8_t id_high = (uint8_t)(id>>3);
	uint8_t id_low = (uint8_t)((id & 0x07) << 5);
	//unsigned short full_id = ((id_low >> 5) | (id_high << 3));
	writeReg(REG_TXB0SIDH, id_high);
	writeReg(REG_TXB0SIDL, id_low);
	writeReg(REG_TXB1SIDH, id_high);
	writeReg(REG_TXB1SIDL, id_low);
	writeReg(REG_TXB2SIDH, id_high);
	writeReg(REG_TXB2SIDL, id_low);

	//to set msg to transmit ext ID
	//bitModReg(REG_TXB0SIDL, 0x0F, 0x0F);
}

uint8_t setCANMode(uint8_t mode){
	uint8_t retVal = mode;
	int tries = 0;
	uint8_t curMode = readCANSTATReg() & 0xE0; //keep only 3 most sig digits
	while(curMode != mode){
		writeCANCTRLReg(mode);
		busyWait(MODE_SWITCH_WAIT);
		curMode = readCANSTATReg() & 0xE0;
		if(tries++ > 4){
			retVal = -1;
			break;
		}
	}
	return curMode;
}

void setCANRXRegisters(uint8_t RXSetting){
	//(04) -> 0 - unimpl, 00 - receive any std/exd id msg, 0 -unimpl, 0 - readonly, 1 - rollover enable, 00 - readonly
	writeReg(REG_RXB0CTRL, RXSetting | 0x04); // bitwise or to enable rollover
	//(00) -> 0 - unimpl, 00 - receive any std/exd id msg, 0 -unimpl, 0000 - readonly
	writeReg(REG_RXB1CTRL, RXSetting);
}

//must be called in config mode
void setMasksAndFilters(){
	if(unitId != 2047){ //i am a slave node
		//masks
		writeReg(REG_RXM0SIDH, SLAVE_MASK_HIGH);
		writeReg(REG_RXM0SIDL, SLAVE_MASK_LOW);
		writeReg(REG_RXM0EID8, SLAVE_MASK_LOW);
		writeReg(REG_RXM0EID0, SLAVE_MASK_LOW);
		writeReg(REG_RXM1SIDH, SLAVE_MASK_HIGH);
		writeReg(REG_RXM1SIDL, SLAVE_MASK_LOW);
		writeReg(REG_RXM1EID8, SLAVE_MASK_LOW);
		writeReg(REG_RXM1EID0, SLAVE_MASK_LOW);
		//filters
		writeReg(REG_RXF0SIDH, SLAVE_FILTER);
		writeReg(REG_RXF0SIDL, 0x00);
		writeReg(REG_RXF1SIDH, SLAVE_FILTER);
		writeReg(REG_RXF1SIDL, 0x00);
		writeReg(REG_RXF2SIDH, SLAVE_FILTER);
		writeReg(REG_RXF2SIDL, 0x00);
		writeReg(REG_RXF3SIDH, SLAVE_FILTER);
		writeReg(REG_RXF3SIDL, 0x00);
		writeReg(REG_RXF4SIDH, SLAVE_FILTER);
		writeReg(REG_RXF4SIDL, 0x00);
		writeReg(REG_RXF5SIDH, SLAVE_FILTER);
		writeReg(REG_RXF5SIDL, 0x00);
	}
	else{ //master - kiosk
		//masks
		writeReg(REG_RXM0SIDH, MASTER_MASK_HIGH);
		writeReg(REG_RXM0SIDL, MASTER_MASK_LOW);
		writeReg(REG_RXM0EID8, MASTER_MASK_LOW);
		writeReg(REG_RXM0EID0, MASTER_MASK_LOW);
		writeReg(REG_RXM1SIDH, MASTER_MASK_HIGH);
		writeReg(REG_RXM1SIDL, MASTER_MASK_LOW);
		writeReg(REG_RXM1EID8, MASTER_MASK_LOW);
		writeReg(REG_RXM1EID0, MASTER_MASK_LOW);
		//filters - all 0, not needed?
		writeReg(REG_RXF0SIDH, 0x00);
		writeReg(REG_RXF0SIDL, 0x00);
		writeReg(REG_RXF1SIDH, 0x00);
		writeReg(REG_RXF1SIDL, 0x00);
		writeReg(REG_RXF2SIDH, 0x00);
		writeReg(REG_RXF2SIDL, 0x00);
		writeReg(REG_RXF3SIDH, 0x00);
		writeReg(REG_RXF3SIDL, 0x00);
		writeReg(REG_RXF4SIDH, 0x00);
		writeReg(REG_RXF4SIDL, 0x00);
		writeReg(REG_RXF5SIDH, 0x00);
		writeReg(REG_RXF5SIDL, 0x00);
	}
}

void setCANInterrupts(uint8_t val){
	writeReg(REG_CANINTE, val);
}


/* ************************************************
 * Functions for reading CAN registers of interest
 *
 * */
//TODO - create structs for more meaningful register reading
uint8_t readCANSTATReg(){
	return readReg(REG_CANSTAT);
}

uint8_t readCANInterrupts(){
	return readReg(REG_CANINTF);
}

uint8_t readCANErrorFlags(){
	return readReg(REG_EFLG);
}

uint8_t readTxErrorCount(){
	return readReg(REG_TEC);
}


/* ************************************************
 * Functions for writing to CAN registers of interest
 *
 * */
void writeCANCTRLReg(uint8_t val){
	writeReg(REG_CANCTRL, val);
}

void clearSpecificCANInterrupts(uint8_t maskByte){
	bitModReg(REG_CANINTF, maskByte, 0x00);
}

void clearAllCANInterrupts(){
	return writeReg(REG_CANINTF, 0x00);
}

/* ************************************************
 * Misc. CAN Functions
 *
 * */

void readCANMsg(int bufNum, struct CANMsg *msg){
	uint8_t senderIdHigh; //only standard identifiers are being used in the system (11 bits)
	uint8_t senderIdLow;
	msg->bufNum = (uint8_t) bufNum;
	if(bufNum == 0){ //read rx buffer 0
		senderIdHigh = readReg(REG_RXB0SIDH);//Most Sig. 8 bits are in RXB0SIDH
		senderIdLow = readReg(REG_RXB0SIDL);//least Sig. 3 bits are the leftmost bits in RXB0SIDL
		msg->ext = (senderIdLow & 0x08) >> 3;
		msg->senderId = ((senderIdLow >> 5) | (senderIdHigh << 3));
		for (int i = 0; i<8; i++){
			msg->data[i] = readReg((REG_RXB0D0 + i));
		}
		clearSpecificCANInterrupts(RX0IF);
	} else{
		senderIdHigh = readReg(REG_RXB1SIDH);//Most Sig. 8 bits are in RXB1SIDH
		senderIdLow = readReg(REG_RXB1SIDL);//least Sig. 3 bits are the leftmost bits in RXB1SIDL
		msg->ext = (senderIdLow & 0x08) >> 3;
		msg->senderId = ((senderIdLow >> 5) | (senderIdHigh << 3));
		for (int i = 0; i<8; i++){
			msg->data[i] = readReg((REG_RXB1D0 + i));
		}
		clearSpecificCANInterrupts(RX1IF);
	}
}

//will return -1 if message was not loaded in buffer
int sendCANMsg(uint8_t *data, uint8_t msg_size){
	//make sure to disable interrupt req - not using interrupts at this moment
	//bitModeReg(REG_CANINTE, TX0IF, 0x00);
	int tries = 0;
	uint8_t TXReqBit = readReg(REG_TXB0CTRL) & 0x08; // check to see if last transmission is not still pending
	while(TXReqBit){
		busyWait(TRANSMIT_BUFFER_WAIT);
		TXReqBit = readReg(REG_TXB0CTRL) & 0x08;
		if(tries++ > 4){ //transmit buffer never was freed, abort msg and return error code //TODO - see if I need to be more patient here
			return -1;
		}
	}
	writeReg(REG_TXB0DLC, msg_size & 0x0F); //note: msg_size (in bytes) must range from 0-8 (&0x0F restricts to only 4 bits (anything over 8 = 8)
	for (int i = 0; i<msg_size; i++){
		writeReg((REG_TXB0D0 + i), data[i]);
	}
	writeReg(REG_TXB0CTRL, 0x08); //(08) -> 0000 readonly/unimpl, 1 - req transmission, 0 - unimpl, 00 - lowest priority
	return tries; //return number of attempt made before msg was loaded into buffer
}

int isRxMsgPending(){
	uint8_t regVal = readCANInterrupts();
	regVal = regVal & 0x03;

	if(regVal == 0x01 || regVal == 0x03){ //match 0000 0110 - if true, RXB0 has interrupt
		return 1; //returns 1 for buf 0
	}
	else if(regVal == 0x02){ //match 0000 0111 - if true, RXB1 has interrupt
		return 2; //returns 2 for buf 1
	}
	else{
		return 0; // return of 0 means no msg was rcvd
	}
}


