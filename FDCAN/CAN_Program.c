/*
 * CAN_Program.c
 *
 *  Created on: Nov 29, 2023
 *      Author: Mahmoud Ahmed Ibrahim
 */

#include "CAN_Interface.h"

void CAN_voidInit(st_CAN_RegDef_t* A_canx, CAN_RxConfig_t* A_rxConfig, CAN_TxConfig_t* A_txConfig)
{
	st_CAN_MSG_SRAM_t* L_msg;
	if(A_canx == CAN1)
		L_msg = CAN1_MESSAGES;
	else if(A_canx == CAN2)
		L_msg = CAN2_MESSAGES;
	else if(A_canx == CAN3)
			L_msg = CAN3_MESSAGES;

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
	if(A_rxConfig->nonMatchingFrames == CAN_RX_ACCEPT_FIFO0){
		A_canx->RXGFC &= ~(0b11 << 4);
	}
	else if(A_rxConfig->nonMatchingFrames == CAN_RX_ACCEPT_FIFO1){
		A_canx->RXGFC &= ~(0b11 << 4);
		A_canx->RXGFC |= (1 << 4);
	}
	else{	// Reject
		A_canx->RXGFC |= (0b11 << 4);
	}

	if(A_rxConfig->FIFO0_Mode == CAN_RX_FIFO_BLOCKING)
		A_canx->RXGFC &= ~(1 << 9);
	else	// Overwrite
		A_canx->RXGFC |= (1 << 9);

	if(A_rxConfig->FIFO1_Mode == CAN_RX_FIFO_BLOCKING)
			A_canx->RXGFC &= ~(1 << 8);
		else
			A_canx->RXGFC |= (1 << 8);

	A_canx->RXGFC &= ~(0b11111 << 16);
	A_canx->RXGFC |= ((A_rxConfig->FIFO0_numberOfIDs + A_rxConfig->FIFO1_numberOfIDs) << 16);

	/* Store The IDs */
	u32 L_temp;
	u8 L_idIndex = 0;
	for(u8 i = 0; i < A_rxConfig->FIFO0_numberOfIDs; i++){
		L_temp = A_rxConfig->FIFO0_IDs[i];			// SID1
		L_temp |= (A_rxConfig->FIFO0_IDs[i] << 16);	// SID2
		L_temp |= (1 << 27);				// Store in FIFO0 (if filter matches)
		L_temp |= (1 << 30);				// 01: Dual ID filter for SFID1 or SFID2

		L_msg->standardID[L_idIndex++] = L_temp;
	}

	for(u8 i = 0; i < A_rxConfig->FIFO1_numberOfIDs; i++){
		L_temp = A_rxConfig->FIFO1_IDs[i];			// SID1
		L_temp |= (A_rxConfig->FIFO1_IDs[i] << 16);	// SID2
		L_temp |= (1 << 28);				// Store in FIFO1 (if filter matches)
		L_temp |= (1 << 30);				// 01: Dual ID filter for SFID1 or SFID2

		L_msg->standardID[L_idIndex++] = L_temp;
	}

	/* Transmitter Configuration */
	if(A_txConfig->bufferType == CAN_TX_BUFFER_FIFO)
		A_canx->TXBC &= ~(1 << 24);
	else // Queue FIFO
		A_canx->TXBC |= (1 << 24);

	if(A_txConfig->transmitPause == CAN_TX_PAUSE_DISABLE)
		A_canx->CCCR &= ~(1 << 14);
	else
		A_canx->CCCR |= (1 << 14);

	/* Exit Initialization and Enter Normal mode */
	A_canx->CCCR &= ~(1 << 1);
	A_canx->CCCR &= ~(1 << 0);
}

void CAN_voidReceiveDataFrame(st_CAN_RegDef_t* A_canx, CAN_Frame_t* A_frame, u8 A_fifox)
{
	st_CAN_MSG_SRAM_t* L_msg;
	if(A_canx == CAN1)
		L_msg = CAN1_MESSAGES;
	else if(A_canx == CAN2)
		L_msg = CAN2_MESSAGES;
	else if(A_canx == CAN3)
			L_msg = CAN3_MESSAGES;

	if(A_fifox == 0)
	{
		u8 L_getIndex = (u8)(A_canx->RXF0S & (0b11 << 8));

		A_frame->id = (L_msg->RxFIFO0->ID >> 18) & (0b11111111111);
		A_frame->dlc = (u8)((L_msg->RxFIFO0->DLC >> 16) & (0b111));
		for(u8 i = 0; i < A_frame->dlc; i++)
			A_frame->data[i] = (u8)((L_msg->RxFIFO0->data[i/4] >> 4*(i%4)) & (0xFF));

		// Acknowledge Reading
		A_canx->RXF0A |= L_getIndex;
	}
	else
	{
		u8 L_getIndex = (u8)(A_canx->RXF1S & (0b11 << 8));

		A_frame->id = (L_msg->RxFIFO1->ID >> 18) & (0b11111111111);
		A_frame->dlc = (u8)((L_msg->RxFIFO1->DLC >> 16) & (0b111));
		for(u8 i = 0; i < A_frame->dlc; i++)
			A_frame->data[i] = (u8)((L_msg->RxFIFO1->data[i/4] >> 4*(i%4)) & (0xFF));

		// Acknowledge Reading
		A_canx->RXF1A |= L_getIndex;
	}
}

u8 CAN_u8GetReceivedMessagesCount(st_CAN_RegDef_t* A_canx, u8 A_fifox)
{
	u8 L_result;
	if(A_fifox == CAN_RX_FIFO0)
		L_result = (u8)(A_canx->RXF0S & (0b11 << 0));
	else
		L_result = (u8)(A_canx->RXF1S & (0b11 << 0));
	return L_result;
}

void CAN_voidSendDataFrame(st_CAN_RegDef_t* A_canx, CAN_Frame_t* A_frame)
{
	st_CAN_MSG_SRAM_t* L_msg;
	if(A_canx == CAN1)
		L_msg = CAN1_MESSAGES;
	else if(A_canx == CAN2)
		L_msg = CAN2_MESSAGES;
	else if(A_canx == CAN3)
			L_msg = CAN3_MESSAGES;

	// Define the put index
	u8 L_putIndex = (u8)((A_canx->TXFQS >> 16) & 0b11);

	// write the message
	u32 L_tmp = 0;
	if(A_frame->ide == CAN_FRAME_EXTENDED_ID){
		L_tmp = A_frame->id;
		L_tmp |= (1 << 30); // XTD bit
	}
	else{
		L_tmp = A_frame->id << 18;
	}
	if(A_frame->rtr == CAN_FRAME_REMOTE)
		L_tmp |= (1 << 29);
	L_msg->TxBuffer[L_putIndex]->ID = L_tmp;

	L_msg->TxBuffer[L_putIndex]->DLC &= ~(1 << 23); // Don't store event
	L_msg->TxBuffer[L_putIndex]->DLC &= ~(1 << 21); // Classic Can
	L_msg->TxBuffer[L_putIndex]->DLC &= ~(1 << 20); // No bit rate switching

	L_msg->TxBuffer[L_putIndex]->DLC |= (A_frame->dlc << 16); // write DLC

	for(u8 i = 0; i < A_frame->dlc; i++)
		L_msg->TxBuffer[L_putIndex]->data[i/4] |= (u32)(A_frame->data[i] << (i%4));

	// Request Transmission
	A_canx->TXBAR |= (1 << L_putIndex);

	// Wait for transmission to be done
	//while(! ((A_canx->TXBTO >> L_putIndex) & 1) );
}

u8 CAN_u8GetPendingMessagesCount(st_CAN_RegDef_t* A_canx)
{
	/* This Function doesn't return the number of pending messages
	 * It return map for the 3 elements where
	 * 0 means no request pending
	 * 1 means request pending
	 *
	 * for example:
	 * if element0 pending, element1 pending, element2 no pending
	 * return value = 0b00000011
	 * if element0 no pending, element1 pending, element2 pending
	 * return value = 0b00000110
	 * */
	return (u8)(A_canx->TXBRP & 0b111);
}
