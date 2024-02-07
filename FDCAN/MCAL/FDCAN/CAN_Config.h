/*
 * CAN_Config.h
 *
 *  Created on: Nov 29, 2023
 *      Author: Mahmoud Ahmed Ibrahim
 */

#ifndef FDCAN_CAN_CONFIG_H_
#define FDCAN_CAN_CONFIG_H_


/************************************************************************************************************************/
/************************************************ General Configuration *************************************************/
/************************************************************************************************************************/

/* Baud Rate */
#define CAN_BAUD_RATE_125K    		7	// 8 means that bit time = 8 us
#define CAN_BAUD_RATE_250K    		3
#define CAN_BAUD_RATE_500K    		1
#define CAN_BAUD_RATE_1000K   		0

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
#define CAN_BAUD_RATE				CAN_BAUD_RATE_250K
#define CAN_FDCAN_OPERATION			CAN_FDCAN_DISABLE
#define CAN_BIT_RATE_SWITCHING		CAN_BIT_RATE_SWITCHING_DISABLE
#define CAN_EDGE_FILTERING			CAN_FILTERING_DISABLE
#define CAN_EXCEPTION_HANDLING		CAN_EXCEPTION_ENABLE
#define CAN_BUS_MONITORING			CAN_BUS_MONITORING_DISABLE
#define CAN_OPERATION_MODE			CAN_MODE_NORMAL_OPERATION

#endif /* FDCAN_CAN_CONFIG_H_ */
