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
