/*
 * CAN_Interface.h
 *
 *  Created on: Nov 24, 2023
 *      Author: Mahmoud Ahmed Ibrahim
 */

#ifndef CAN_CAN_INTERFACE_H_
#define CAN_CAN_INTERFACE_H_

#include "../../Utilities/STD_TYPES.h"
#include "CAN_Registers.h"
#include "CAN_Config.h"
#include "CAN_Private.h"

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


void CAN_voidInit(st_CAN_RegDef_t* canx, CAN_Config_t* config);

void CAN_voidSendDataFrame(st_CAN_RegDef_t* canx, CAN_Frame_t* frame);

#endif /* CAN_CAN_INTERFACE_H_ */
