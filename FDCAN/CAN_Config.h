/*
 * CAN_Config.h
 *
 *  Created on: Nov 29, 2023
 *      Author: Mahmoud Ahmed Ibrahim
 */

#ifndef FDCAN_CAN_CONFIG_H_
#define FDCAN_CAN_CONFIG_H_

/************************************************************************************************************************/
/********************************************** Transmission Configuration **********************************************/
/************************************************************************************************************************/

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

/************************************************************************************************************************/
/*********************************************** Receiving Configuration ************************************************/
/************************************************************************************************************************/

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
/************************************************ General Configuration *************************************************/
/************************************************************************************************************************/

/* Baud Rate */
#define CAN_BAUD_RATE_125K    		8	// 8 means that bit time = 8 us
#define CAN_BAUD_RATE_250K    		4
#define CAN_BAUD_RATE_500K    		2
#define CAN_BAUD_RATE_1000K   		1

/* FDCAN Operation  */
#define CAN_FDCAN_DISABLE					0
#define CAN_FDCAN_ENABLE					1

/* Bit Rate Switching */
#define CAN_BIT_RATE_SWITCHING_DISABLE		0
#define CAN_BIT_RATE_SWITCHING_ENABLE		1

/* Edge Filtering  */
#define CAN_FILTERING_DISABLE 				0
#define CAN_FILTERING_ENABLE				1

/* Exception Handling  */
#define CAN_EXCEPTION_ENABLE 				0
#define CAN_EXCEPTION_DISABLE				1

/* Bus Monitoring */
#define CAN_BUS_MONITORING_DISABLE			0
#define CAN_BUS_MONITORING_ENABLE			1

/* Restricted Operation Mode */
#define CAN_MODE_NORMAL_OPERATION			0
#define CAN_MODE_RESTRICTED_OPERATION		1

/************************************************************************************************************************/
/************************************************** User Configuration **************************************************/
/************************************************************************************************************************/
#define CAN_BAUD_RATE				CAN_BAUD_RATE_1000K
#define CAN_FDCAN_OPERATION			CAN_FDCAN_DISABLE
#define CAN_BIT_RATE_SWITCHING		CAN_BIT_RATE_SWITCHING_DISABLE
#define CAN_EDGE_FILTERING			CAN_FILTERING_DISABLE
#define CAN_EXCEPTION_HANDLING		CAN_EXCEPTION_ENABLE
#define CAN_BUS_MONITORING			CAN_BUS_MONITORING_DISABLE
#define CAN_OPERATION_MODE			CAN_MODE_NORMAL_OPERATION

#endif /* FDCAN_CAN_CONFIG_H_ */
