/*
 * CAN_Config.h
 *
 *  Created on: Nov 24, 2023
 *      Author: Mahmoud Ahmed Ibrahim
 */

#ifndef CAN_CAN_CONFIG_H_
#define CAN_CAN_CONFIG_H_

typedef struct{
	u8 transmitPriority;
	u8 receiveLock;
	u8 noAutomaticTransmission;
	u8 automaticWakeup;
	u8 automaticBusOff;
	u8 timeTriggerMode;
}CAN_Config_t;

/* Transmit Priority */
#define CAN_PRIORITY_MSG_ID			0
#define CAN_PRIORITY_REQUEST_ORDER	1
/* In FIFO Choose the message based on
 * 0) Its ID (Higher priority transmitted first)
 * 1) The request order (requested first sent first)
*/

/* Receive Lock */
#define CAN_RECEIVE_UNLOCKED			0
#define CAN_RECEIVE_LOCKED				1
/* When Receive Lock mode is
 * 0) Unlocked Once a receive FIFO is full the next incoming message will overwrite the previous one.
 * 1) Locked Once a receive FIFO is full the next incoming message will be discarded
*/

/* No Automatic Transmission */
#define CAN_AUTOMATIC_TRANSMISSION_DISABLE		0
#define CAN_AUTOMATIC_TRANSMISSION_ENABLE		1
/* When Automatic Transmission
 * 0) Disabled CAN hardware will automatically retransmit the message until it has been successfully transmitted according to the CAN standard
 * 1) Enabled A message will be transmitted only once, independently of the transmission result (successful, error or arbitration lost).
 */

/* Automatic WakeUp */
#define CAN_AUTOMATIC_WAKEUP_DISABLE		0
#define CAN_AUTOMATIC_WAKEUP_ENABLE			1
/* When Automatic WakeUp
 * 0) Disabled Sleep mode is left on software
 * 1) Enabled Sleep mode is left automatically by hardware on CAN message detection
 */

/* Automatic BusOFF */


/* Time Trigger Mode */



#endif /* CAN_CAN_CONFIG_H_ */
