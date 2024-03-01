/*
 * CAN_Program.c
 *
 *  Created on: Nov 29, 2023
 *      Author: Mahmoud Ahmed Ibrahim
 */

#include "CAN_Interface.h"

void CAN_voidInit(CAN_RegMap_t* A_canx, CAN_RxConfig_t* A_rxConfig, CAN_TxConfig_t* A_txConfig)
{
	CAN_MSG_SRAM_t* L_msg;
	if(A_canx == CAN1)
		L_msg = CAN1_MESSAGES;
	else if(A_canx == CAN2)
		L_msg = CAN2_MESSAGES;
	else if(A_canx == CAN3)
			L_msg = CAN3_MESSAGES;

	/* Enter Initialization mode */
	A_canx->CCCR |= (1 << 0);
	while(! ((A_canx->CCCR >> 0) & 1));  // Wait to make sure INIT bit has been written (Recommendation from reference manual)

	// might configure Timeout value here
	A_canx->CCCR |= (1 << 1);

/* Setup General Configuration */
#if CAN_FDCAN_OPERATION == CAN_FDCAN_DISABLE
		A_canx->CCCR &= ~(1 << 8);
#else
		A_canx->CCCR |= (1 << 8);
#endif

#if CAN_BIT_RATE_SWITCHING == CAN_BIT_RATE_SWITCHING_DISABLE
		A_canx->CCCR &= ~(1 << 9);
#else
		A_canx->CCCR |= (1 << 9);
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

#if CAN_BUS_MONITORING == CAN_BUS_MONITORING_DISABLE
		A_canx->CCCR &= ~(1 << 5);
#else
		A_canx->CCCR |= (1 << 5);
#endif

#if CAN_OPERATION_MODE == CAN_MODE_NORMAL_OPERATION
		A_canx->CCCR &= ~(1 << 2);
#else
		A_canx->CCCR |= (1 << 2);
#endif

	/* Timing Configuration */
	u32 L_timing = 0;
	L_timing |= (3 << 25);		// 3 is default value for NSJW (Nominal (re)synchronization jump width)
	// L_timing |= (0 << 16);		// 0 is the default value for NBRP (Bit rate prescaler)
	L_timing |= (10 << 8);		// 10 is the default value for NTSEG1
	L_timing |= (3 << 0);		// 3 is the default value for NTSEG2

	/* Baud rate = 1 / total bit time
	 * total bit time = (3 + NTSEG1 + NTSEG2) * tq
	 * tq = (BRB + 1) * fdcan_clk
	 *
	 * suppose
	 * fdcan_clk = 1/16 us (clk = 16 MHz)
	 * we use default values for NTSEG1 and NTSEG2
	 * then
	 * total bit time = 16 * 1/16 * (BRB + 1)
	 *
	 * for 125kb  (8us)	 BRB = 8
	 * for 250kb  (4us)  BRB = 4
	 * for 500kb  (2us)  BRB = 2
	 * for 1000kb (1us)  BRB = 1
	 * */
	L_timing |= (CAN_BAUD_RATE << 16);

	A_canx->NBTP = L_timing;

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

	/* Flush SRAM */
	u32 pointer;
	pointer = (u32)L_msg;
	for(u8 i = 0; i < 212; i++){
		*(u32 *)(pointer) = 0x00000000U;
		pointer += 4;
	}

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

	if (A_txConfig->automaticTransmission == CAN_AUTOMATIC_TRANSMISSION_ENABLE)
		A_canx->CCCR &= ~(1 << 6);
	else
		A_canx->CCCR |= (1 << 6);

	/* Exit Initialization and Enter Normal mode */
	A_canx->CCCR &= ~(1 << 1);
	A_canx->CCCR &= ~(1 << 0);
}

void CAN_voidReceiveDataFrame(CAN_RegMap_t* A_canx, CAN_Frame_t* A_frame, u8 A_fifox)
{
	CAN_MSG_SRAM_t* L_msg;
	if(A_canx == CAN1)
		L_msg = CAN1_MESSAGES;
	else if(A_canx == CAN2)
		L_msg = CAN2_MESSAGES;
	else if(A_canx == CAN3)
			L_msg = CAN3_MESSAGES;

	if(A_fifox == 0)
	{
		u8 L_getIndex = (u8)((A_canx->RXF0S & (0b11 << 8)) >> 8);

		A_frame->ide = ((L_msg->RxFIFO0[L_getIndex].ID >> 30) & 1);
		A_frame->rtr = ((L_msg->RxFIFO0[L_getIndex].ID >> 29) & 1);

		if(A_frame->ide == CAN_FRAME_STANDARD_ID)
			A_frame->id = (L_msg->RxFIFO0[L_getIndex].ID >> 18) & (0b11111111111);
		else
			A_frame->id = L_msg->RxFIFO0[L_getIndex].ID & (0x1FFFFFFF);

		if(A_frame->rtr == CAN_FRAME_DATA)
		{
			A_frame->dlc = (u8)((L_msg->RxFIFO0[L_getIndex].DLC >> 16) & (0b1111));
			for(u8 i = 0; i < A_frame->dlc; i++)
				A_frame->data[i] = ((L_msg->RxFIFO0[L_getIndex].data[i/4] >> (8*(i%4))) & (0xFF));
		}

		// Acknowledge Reading
		A_canx->RXF0A = L_getIndex;
	}
	else
	{
		u8 L_getIndex = (u8)((A_canx->RXF1S & (0b11 << 8)) >> 8);

		A_frame->ide = ((L_msg->RxFIFO1[L_getIndex].ID >> 30) & 1);
		A_frame->rtr = ((L_msg->RxFIFO1[L_getIndex].ID >> 29) & 1);

		if(A_frame->ide == CAN_FRAME_STANDARD_ID)
			A_frame->id = (L_msg->RxFIFO1[L_getIndex].ID >> 18) & (0b11111111111);
		else
			A_frame->id = L_msg->RxFIFO1[L_getIndex].ID & (0x1FFFFFFF);

		if(A_frame->rtr == CAN_FRAME_DATA)
		{
			A_frame->dlc = (u8)((L_msg->RxFIFO1[L_getIndex].DLC >> 16) & (0b1111));
			for(u8 i = 0; i < A_frame->dlc; i++)
				A_frame->data[i] = ((L_msg->RxFIFO1[L_getIndex].data[i/4] >> (8*(i%4))) & (0xFF));
		}

		// Acknowledge Reading
		A_canx->RXF1A |= (1 << L_getIndex);
	}
}

u8 CAN_u8GetReceivedMessagesCount(CAN_RegMap_t* A_canx, u8 A_fifox)
{
	u8 L_result;
	if(A_fifox == CAN_RX_FIFO0)
		L_result = (u8)(A_canx->RXF0S & (0b1111 << 0));
	else
		L_result = (u8)(A_canx->RXF1S & (0b1111 << 0));
	return L_result;
}

u8 CAN_u8IsRxBufferFull(CAN_RegMap_t* A_canx, u8 A_fifox)
{
	u8 L_result;
	if(A_fifox == CAN_RX_FIFO0)
		L_result = (A_canx->RXF0S & (1 << 24)) >> 24;
	else
		L_result = (A_canx->RXF1S & (1 << 24)) >> 24;
	return L_result;
}

void CAN_voidSendDataFrame(CAN_RegMap_t* A_canx, CAN_Frame_t* A_frame)
{
	CAN_MSG_SRAM_t* L_msg;
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
	if(A_frame->rtr == CAN_FRAME_REMOTE){
		L_tmp |= (1 << 29);
		A_frame->dlc = 0;
	}
	L_msg->TxBuffer[L_putIndex].ID = L_tmp;

/*
	L_msg->TxBuffer[L_putIndex].DLC &= ~(1 << 23); // Don't store event
	L_msg->TxBuffer[L_putIndex].DLC &= ~(1 << 21); // Classic Can
	L_msg->TxBuffer[L_putIndex].DLC &= ~(1 << 20); // No bit rate switching
*/

	L_msg->TxBuffer[L_putIndex].DLC = (A_frame->dlc << 16); // write DLC

	u32 data0 = 0;
	u32 data1 = 0;
	for(u8 i = 0; i < A_frame->dlc; i++)
	{
		 if(i < 4)
			 data0 |= (u32)(A_frame->data[i] << (8 * (i%4)));
		 else
			 data1 |= (u32)(A_frame->data[i] << (8 * (i%4)));
	}
	L_msg->TxBuffer[L_putIndex].data[0] = data0;
	L_msg->TxBuffer[L_putIndex].data[1] = data1;

	// Request Transmission
	A_canx->TXBAR |= (1 << L_putIndex);

	// Wait for transmission to be done
	//while(! ((A_canx->TXBTO >> L_putIndex) & 1) );
}

u8 CAN_u8GetPendingMessagesCount(CAN_RegMap_t* A_canx)
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

u8 CAN_u8IsTxBufferFull(CAN_RegMap_t* A_canx)
{
	return ((A_canx->TXFQS & (1 << 21)) >> 21);
}
