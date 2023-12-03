/*
 * CAN_Interface.h
 *
 *  Created on: Nov 29, 2023
 *      Author: Mahmoud Ahmed Ibrahim
 */

#ifndef FDCAN_CAN_INTERFACE_H_
#define FDCAN_CAN_INTERFACE_H_

#include "../../Utilities/STD_TYPES.h"
#include "CAN_Registers.h"
#include "CAN_Config.h"

/************************************************************************************************************************/
/************************************************** Important typedefs **************************************************/
/************************************************************************************************************************/
typedef struct{
	u32 id;		// Identifier
	u8 dlc;		// Data length code
	u8 rtr;		// Remote transmission request
	u8 ide; 	// Identifier extension
	u8 data[8];
}CAN_Frame_t;

/* RTR(Remote transmission request) */
#define CAN_DATA_FRAME		0
#define CAN_REMOTE_FRAME	1

/* IDE(Identifier extension) */
#define CAN_STANDARD_IDENTIFIER		0
#define CAN_EXTENDED_IDENTIFIER		1

/************************************************************************************************************************/
/************************************************* Functions Prototypes *************************************************/
/************************************************************************************************************************/

// Initialization Function
void CAN_voidInit(st_CAN_RegDef_t* A_canx, CAN_RxConfig_t* A_rxConfig, CAN_TxConfig_t* A_txConfig);

// Receiving functions
#define CAN_RX_FIFO0		0
#define CAN_RX_FIFO1		1
void CAN_voidReceiveDataFrame(st_CAN_RegDef_t* A_canx, CAN_Frame_t* A_frame, u8 A_fifox);
u8 CAN_u8GetReceivedMessagesCount(st_CAN_RegDef_t* A_canx, u8 A_fifox);
u8 CAN_u8IsRxBufferFull(u8 A_fifox);

// Sending functions
void CAN_voidSendDataFrame(st_CAN_RegDef_t* A_canx, CAN_Frame_t* A_frame);
u8 CAN_u8GetPendingMessagesCount(st_CAN_RegDef_t* A_canx);
u8 CAN_u8IsTxBufferFull(u8 A_fifox);

#endif /* FDCAN_CAN_INTERFACE_H_ */
