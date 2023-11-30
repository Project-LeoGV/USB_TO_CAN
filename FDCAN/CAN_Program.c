/*
 * CAN_Program.c
 *
 *  Created on: Nov 29, 2023
 *      Author: Mahmoud Ahmed Ibrahim
 */

#include "CAN_Interface.h"

void CAN_voidInit(st_CAN_RegDef_t* canx)
{
	/* Enter Initialization mode */
	canx->CCCR |= (1 << 0);
	canx->CCCR |= (1 << 1);

/* Setup Configuration */
#if CAN_AUTOMATIC_TRANSMISSION == CAN_AUTOMATIC_TRANSMISSION_ENABLE
		canx->CCCR &= ~(1 << 6);
#else
		canx->CCCR |= (1 << 6);
#endif

#if CAN_FDCAN_OPERATION == CAN_FDCAN_DISABLE
		canx->CCCR &= ~(1 << 8);
#else
		canx->CCCR |= (1 << 8);
#endif

#if CAN_EDGE_FILTERING == CAN_FILTERING_DISABLE
		canx->CCCR &= ~(1 << 13);
#else
		canx->CCCR |= (1 << 13);
#endif

#if CAN_EXCEPTION_HANDLING == CAN_EXCEPTION_ENABLE
		canx->CCCR &= ~(1 << 12);
#else
		canx->CCCR |= (1 << 12);
#endif

	/* Exit Initialization and Enter Normal mode */
	canx->CCCR &= ~(1 << 1);
	canx->CCCR &= ~(1 << 0);
}
