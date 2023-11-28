/*
 * CAN_Program.c
 *
 *  Created on: Nov 24, 2023
 *      Author: Mahmoud Ahmed Ibrahim
 */


#include "CAN_Interface.h"

void CAN_voidInit(st_CAN_RegDef_t* canx, CAN_Config_t* config)
{
	/* Setup the Configuration */
	if(config->transmitPriority == CAN_PRIORITY_MSG_ID)
		canx->MCR &= ~(1<<2);
	else
		canx->MCR |= (1<<2);

	if(config->receiveLock == CAN_RECEIVE_UNLOCKED)
		canx->MCR &= ~(1<<3);
	else
		canx->MCR |= (1<<3);

	if(config->noAutomaticTransmission == CAN_AUTOMATIC_TRANSMISSION_DISABLE)
		canx->MCR &= ~(1<<4);
	else
		canx->MCR |= (1<<4);

	if(config->automaticWakeup == CAN_AUTOMATIC_WAKEUP_DISABLE)
		canx->MCR &= ~(1<<5);
	else
		canx->MCR |= (1<<5);

	/* Setup The Timing */

	/* Setup the filters */


	/* Enter Initialization mode */

	// Request Initialization
	canx->MCR |= (1<<0);

	// Clear sleep mode
	canx->MCR &= ~(1<<0);

	// Wait for Acknowledge initialization
	while( ! ((canx->MSR & (1<<0))>>0) );

	// Wait for entering Normal Mode
	while(  ((canx->MSR & (1<<0))>>0) );
}

void CAN_voidSendDataFrame(st_CAN_RegDef_t* canx, CAN_Frame_t* frame)
{
	/* Set the ID */
	if(frame->ide == CAN_STANDARD_IDENTIFIER){
		canx->TI0R &= ~(1 << 2);
		canx->TI0R &= ~(0b11111111111 << 21); 	// Clear the previous id
		canx->TI0R |= (frame->id << 21);		// Set the new id
	}
	else{
		canx->TI0R |= (1<<2);
		canx->TI0R &= ~(0xFFFFFFF8 << 3); 		// Clear the previous id
		canx->TI0R |= (frame->id << 3);			// Set the new id
	}

	/* Set The DLC(Data Length Code) */
	canx->TDT0R &= ~(0b1111 << 0);
	canx->TDT0R |= (frame->dlc << 0);

	/* Set The Data */
	for(u8 i = 0; i < frame->dlc; i++)
	{
		if(i < 4){
			canx->TDL0R &= ~(0xFF << i * 8);
			canx->TDL0R |= (frame->data[i] << i * 8);
		}
		else{
			canx->TDH0R &= ~(0xFF << (i - 4) * 8);
			canx->TDH0R |= (frame->data[i] << (i - 4) * 8);
		}
	}

	/* Request Transmission */
	canx->TI0R |= (1 << 0);

	while( !((canx->TSR & (1<<0))>>1) );	// Wait for Successful Transmission

}
