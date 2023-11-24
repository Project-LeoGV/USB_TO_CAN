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

void CAN_voidInit(st_CAN_RegDef_t* canx, CAN_Config_t* config);

#endif /* CAN_CAN_INTERFACE_H_ */
