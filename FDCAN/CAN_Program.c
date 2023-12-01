/*
 * CAN_Program.c
 *
 *  Created on: Nov 29, 2023
 *      Author: Mahmoud Ahmed Ibrahim
 */

#include "CAN_Interface.h"

void CAN_voidInit(st_CAN_RegDef_t* A_canx, CAN_Config_t A_config)
{
	st_CAN_MSG_SRAM_t* L_msg;
	if(canx == CAN1)
		L_msg = CAN1_MESSAGES;

	/* Enter Initialization mode */
	A_canx->CCCR |= (1 << 0);
	A_canx->CCCR |= (1 << 1);

/* Setup General Configuration */
#if CAN_AUTOMATIC_TRANSMISSION == CAN_AUTOMATIC_TRANSMISSION_ENABLE
		A_canx->CCCR &= ~(1 << 6);
#else
		A_canx->CCCR |= (1 << 6);
#endif

#if CAN_FDCAN_OPERATION == CAN_FDCAN_DISABLE
		A_canx->CCCR &= ~(1 << 8);
#else
		A_canx->CCCR |= (1 << 8);
#endif

#if CAN_EDGE_FILTERING == CAN_FILTERING_DISABLE
		A_canx->CCCR &= ~(1 << 13);
#else
		A_canx->CCCR |= (1 << 13);
#endif

#if CAN_EXCEPTION_HANDLING == CAN_EXCEPTION_ENABLE
		A_canx->CCCR &= ~(1 << 12);
#else
		A_canx->CCCR |= (1 << 12);
#endif

	/* Receiver Configuration */
	if(A_config.nonMatchingFrames == CAN_ACCEPT_FIFO0){
		A_canx->RXGFC &= ~(0b11 << 4);
	}
	else if(A_config.nonMatchingFrames == CAN_ACCEPT_FIFO0){
		A_canx->RXGFC &= ~(0b11 << 4);
		A_canx->RXGFC |= (1 << 4);
	}
	else{
		A_canx->RXGFC |= (0b11 << 4);
	}

	if(A_config.FIFO0_Mode == CAN_FIFO_BLOCKING)
		A_canx->RXGFC &= ~(1 << 9);
	else
		A_canx->RXGFC |= (1 << 9);

	if(A_config.FIFO1_Mode == CAN_FIFO_BLOCKING)
			A_canx->RXGFC &= ~(1 << 8);
		else
			A_canx->RXGFC |= (1 << 8);

	A_canx->RXGFC &= ~(0b11111 << 16);
	A_canx->RXGFC |= (A_config.numberOfIDs << 16);

	/* Store The IDs */
	u32 L_temp;
	for(u8 i = 0; i < A_config.numberOfIDs; i++){
		L_temp = A_config.IDs[i];			// SID1
		L_temp |= (A_config.IDs[i] << 16);	// SID2
		L_temp |= (1 << 27);				// Store in FIFO0 (if filter matches)
		L_temp |= (1 << 30);				// 01: Dual ID filter for SFID1 or SFID2

		L_msg->standardID[i] = L_tmp;
	}

	/* Exit Initialization and Enter Normal mode */
	A_canx->CCCR &= ~(1 << 1);
	A_canx->CCCR &= ~(1 << 0);
}
