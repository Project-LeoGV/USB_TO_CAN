/*
 * CAN_Interface.h
 *
 *  Created on: Nov 29, 2023
 *      Author: Mahmoud Ahmed Ibrahim
 */

#ifndef FDCAN_CAN_INTERFACE_H_
#define FDCAN_CAN_INTERFACE_H_

#include "../../LIB/STD_TYPES.h"
#include "CAN_Registers.h"
#include "CAN_Config.h"

/************************************************************************************************************************/
/************************************************** Important typedefs **************************************************/
/************************************************************************************************************************/

/***************************** CAN Frame ******************************/
typedef struct{
	u32 id;		// Identifier
	u8 dlc;		// Data length code
	u8 rtr;		// Remote transmission request
	u8 ide; 	// Identifier extension
	u8 data[8];
}CAN_Frame_t;

/* RTR(Remote transmission request) */
#define CAN_FRAME_DATA				0
#define CAN_FRAME_REMOTE			1

/* IDE(Identifier extension) */
#define CAN_FRAME_STANDARD_ID		0
#define CAN_FRAME_EXTENDED_ID		1

/********************* Transmission Configuration *********************/
typedef struct{
	u8 transmitPause;
	u8 bufferType;
	u8 automaticTransmission;
}CAN_TxConfig_t;

/* Transmit Pause */
#define CAN_TX_PAUSE_DISABLE		0
#define CAN_TX_PAUSE_ENABLE			1

/* Buffer Type */
#define CAN_TX_BUFFER_FIFO			0
#define CAN_TX_BUFFER_QUEUE			1

/* Automatic Transmission */
#define CAN_AUTOMATIC_TRANSMISSION_ENABLE		0
#define CAN_AUTOMATIC_TRANSMISSION_DISABLE		1
/* When Automatic Transmission
 * 0) Enabled CAN hardware will automatically retransmit the message until it has been successfully transmitted according to the CAN standard
 * 1) Disabled A message will be transmitted only once, independently of the transmission result (successful, error or arbitration lost).
 */

/*********************** Receiving Configuration **********************/
typedef struct{
	u8 nonMatchingFrames;
	u8 FIFO0_Mode;
	u8 FIFO1_Mode;
	u8 FIFO0_numberOfIDs;
	u8 FIFO1_numberOfIDs;
	u32* FIFO0_IDs;
	u32* FIFO1_IDs;
}CAN_RxConfig_t;

/* Non Matching Frames */
#define CAN_RX_ACCEPT_FIFO0			0
#define CAN_RX_ACCEPT_FIFO1			1
#define CAN_RX_REJECT				2

/* FIFO Mode */
#define CAN_RX_FIFO_BLOCKING		0
#define CAN_RX_FIFO_OVERWRITE		1

/************************************************************************************************************************/
/************************************************* Functions Prototypes *************************************************/
/************************************************************************************************************************/

// Initialization Function
void CAN_voidInit(CAN_RegMap_t* A_canx, CAN_RxConfig_t* A_rxConfig, CAN_TxConfig_t* A_txConfig);

// Receiving functions
#define CAN_RX_FIFO0		0
#define CAN_RX_FIFO1		1
void CAN_voidReceiveDataFrame(CAN_RegMap_t* A_canx, CAN_Frame_t* A_frame, u8 A_fifox);
u8 CAN_u8GetReceivedMessagesCount(CAN_RegMap_t* A_canx, u8 A_fifox);
u8 CAN_u8IsRxBufferFull(CAN_RegMap_t* A_canx, u8 A_fifox);

// Sending functions
void CAN_voidSendDataFrame(CAN_RegMap_t* A_canx, CAN_Frame_t* A_frame);
u8 CAN_u8GetPendingMessagesCount(CAN_RegMap_t* A_canx);
u8 CAN_u8IsTxBufferFull(CAN_RegMap_t* A_canx);

#endif /* FDCAN_CAN_INTERFACE_H_ */
