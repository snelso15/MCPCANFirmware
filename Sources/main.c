/* ###################################################################
**     Filename    : main.c
**     Project     : CANDataTest
**     Processor   : MKL26Z64VLH4
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-01-21, 13:42, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "CAN_SS.h"
#include "BitIoLdd1.h"
#include "CAN_SPI.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* User includes (#include below this line is not maintained by Processor Expert) */

#include "MCP25625.h"
#include "SPICommands.h"
#include "CANDataContainers.h"

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
	PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  initializeCAN(unitId);

  /* Write your code here */
  for(;;) {

		int dummy = 0;
		uint8_t count = 0;
		uint8_t mode = 51;


		mode = setCANMode(MODE_NORMAL);

		while(1){

			if(unitId != 2047){ //i am a slave node
				while(1){
					int rxBufNum = isRxMsgPending();
					if(rxBufNum){
						unsigned short senderID = 55;
						struct CANMsg msg;
						readCANMsg(rxBufNum-1, &msg);
						senderID = msg.senderId;
						uint8_t outdata[8] = {3, 3, 3, 3, 3, 3, msg.data[6], msg.data[7]};
						int tries = sendCANMsg(outdata, (uint8_t) 8);
					}
				}
			}
			else{//master
				while(1){
					uint8_t outdata[8] = {1, 1, 1, 1, 1, 1, count++, 42};
					int tries = sendCANMsg(outdata, (uint8_t) 8);
					//busyWait(100000);  //this order of wait is required to receive msg in this iteration of loop
					int rxBufNum = isRxMsgPending();
					while(!rxBufNum){
						busyWait(100);
						rxBufNum = isRxMsgPending();
					}
					unsigned short senderID = 55;
					struct CANMsg msg;
					readCANMsg(rxBufNum-1, &msg);
					senderID = msg.senderId;
					dummy = 1;
				}
			}
		}
	}

  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
