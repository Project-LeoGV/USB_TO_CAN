/*
 * mainRx.c
 *
 *  Created on: Feb 29, 2024
 *      Author: Mahmoud Ahmed
 */

#include "../MCAL/RCC/RCC_Interface.h"
#include "../MCAL/GPIO/GPIO_Interface.h"
#include "../MCAL/FDCAN/CAN_Interface.h"

void APP_voidGpioInit(void);
void APP_voidCanInit(void);
void delay(u32 ms);

int main()
{
	RCC_voidInit();
	RCC->CCIPR |= (1 << 25);

	RCC_voidPeripheralClockEnable(RCC_AHB2, GPIO_A);
	RCC_voidPeripheralClockEnable(RCC_AHB2, GPIO_B);
	RCC_voidPeripheralClockEnable(RCC_AHB2, GPIO_C);
	RCC_voidPeripheralClockEnable(RCC_APB1_1, FDCAN);

	APP_voidGpioInit();
	APP_voidCanInit();

	// Initialize Variables
	CAN_Frame_t Frame[4];
	Frame[0].ide = CAN_FRAME_STANDARD_ID;
	Frame[0].id = 0x008;
	Frame[0].rtr = CAN_FRAME_DATA;
	Frame[0].dlc = 8;
	Frame[0].data[0] = 'H';
	Frame[0].data[1] = 'e';
	Frame[0].data[2] = 'l';
	Frame[0].data[3] = 'l';
	Frame[0].data[4] = 'o';
	Frame[0].data[5] = ' ';
	Frame[0].data[6] = 'H';
	Frame[0].data[7] = 'i';

	Frame[1].ide = CAN_FRAME_STANDARD_ID;
	Frame[1].id = 0x009;
	Frame[1].rtr = CAN_FRAME_DATA;
	Frame[1].dlc = 5;
	Frame[1].data[0] = 'H';
	Frame[1].data[1] = 'e';
	Frame[1].data[2] = 'l';
	Frame[1].data[3] = 'l';
	Frame[1].data[4] = 'o';
	Frame[1].data[5] = ' ';
	Frame[1].data[6] = 'H';
	Frame[1].data[7] = 'i';

	Frame[2].ide = CAN_FRAME_STANDARD_ID;
	Frame[2].id = 0x00F;
	Frame[2].rtr = CAN_FRAME_REMOTE;
	Frame[2].dlc = 5;
	Frame[2].data[0] = 'M';
	Frame[2].data[1] = 'a';
	Frame[2].data[2] = 'h';
	Frame[2].data[3] = 'm';
	Frame[2].data[4] = 'o';
	Frame[2].data[5] = 'u';
	Frame[2].data[6] = 'd';
	Frame[2].data[7] = '0';

	Frame[3].ide = CAN_FRAME_STANDARD_ID;
	Frame[3].id = 0x00F;
	Frame[3].rtr = CAN_FRAME_REMOTE;

	CAN_Frame_t receiveFrame;

	GPIO_voidSetPinValue(GPIO_PORTA, 3, 1);
	GPIO_voidSetPinValue(GPIO_PORTA, 9, 1);
	GPIO_voidSetPinValue(GPIO_PORTA, 10, 1);
	GPIO_voidSetPinValue(GPIO_PORTC, 13, 1);

	u8 leds[3] = {9, 10, 3};
	u8 matched = 0;
	while(1)
	{

		if(CAN_u8GetReceivedMessagesCount(CAN1, CAN_RX_FIFO0) != 0)
		{
			CAN_voidReceiveDataFrame(CAN1, &receiveFrame, CAN_RX_FIFO0);

			for(u8 i = 0; i < 3; i++)
			{
				if(receiveFrame.id == Frame[i].id
				&& receiveFrame.dlc == Frame[i].dlc
				&& receiveFrame.rtr == Frame[i].rtr
				)
				{
					matched = 1;
					for(u8 j = 0; j < Frame[i].dlc; j++){
						if(receiveFrame.data[j] != Frame[i].data[j]){
							matched = 0;
							break;
						}
					}
					if(matched){
						GPIO_voidTogglePin(GPIO_PORTA, leds[i]);
						break;
					}
				}
			}
		}
	}
}

void APP_voidGpioInit(void)
{
	MGPIO_Config_t Tx2 = {.Port = GPIO_PORTA, .Pin = GPIO_PIN2, .Mode = GPIO_MODE_OUTPUT,.AltFunc = GPIO_AF9,.OutputSpeed = GPIO_SPEED_LOW,.OutputType = GPIO_OT_PUSHPULL};
	MGPIO_Config_t Rx2 = {.Port = GPIO_PORTA, .Pin = GPIO_PIN3, .Mode = GPIO_MODE_OUTPUT,.AltFunc = GPIO_AF9,.OutputSpeed = GPIO_SPEED_LOW,.OutputType = GPIO_OT_PUSHPULL};
	MGPIO_Config_t Tx1 = {.Port = GPIO_PORTA, .Pin = GPIO_PIN9, .Mode = GPIO_MODE_OUTPUT,.AltFunc = GPIO_AF9,.OutputSpeed = GPIO_SPEED_LOW,.OutputType = GPIO_OT_PUSHPULL};
	MGPIO_Config_t Rx1 = {.Port = GPIO_PORTA, .Pin = GPIO_PIN10, .Mode = GPIO_MODE_OUTPUT,.AltFunc = GPIO_AF9,.OutputSpeed = GPIO_SPEED_LOW,.OutputType = GPIO_OT_PUSHPULL};

	MGPIO_Config_t PC13 = {.Port = GPIO_PORTC, .Pin = GPIO_PIN13, .Mode = GPIO_MODE_OUTPUT,.AltFunc = GPIO_AF9,.OutputSpeed = GPIO_SPEED_LOW,.OutputType = GPIO_OT_PUSHPULL};

	GPIO_voidInitPin(&Tx1);
	GPIO_voidInitPin(&Rx1);
	GPIO_voidInitPin(&Tx2);
	GPIO_voidInitPin(&Rx2);

	GPIO_voidInitPin(&PC13);
}

void APP_voidCanInit(void)
{
	MGPIO_Config_t canTxPin = {.Port = GPIO_PORTB, .Pin = GPIO_PIN9, .Mode = GPIO_MODE_ALTF,.AltFunc = GPIO_AF9,.OutputSpeed = GPIO_SPEED_LOW,.OutputType = GPIO_OT_PUSHPULL};
	MGPIO_Config_t canRxPin = {.Port = GPIO_PORTB, .Pin = GPIO_PIN8, .Mode = GPIO_MODE_ALTF,.AltFunc = GPIO_AF9,.OutputSpeed = GPIO_SPEED_LOW,.OutputType = GPIO_OT_PUSHPULL};

	CAN_TxConfig_t txCfg;
	txCfg.automaticTransmission = CAN_AUTOMATIC_TRANSMISSION_DISABLE;
	txCfg.bufferType = CAN_TX_BUFFER_FIFO;
	txCfg.transmitPause = CAN_TX_PAUSE_DISABLE;

	CAN_RxConfig_t rxCfg;
	rxCfg.FIFO0_Mode = CAN_RX_FIFO_OVERWRITE;
	rxCfg.FIFO1_Mode = CAN_RX_FIFO_OVERWRITE;
	rxCfg.FIFO0_numberOfIDs = 3;
	rxCfg.FIFO1_numberOfIDs = 0;
	u32 ids[3] = {0x008, 0x009, 0x00F};
	rxCfg.FIFO0_IDs = ids;
	rxCfg.FIFO1_IDs = NULL;
	rxCfg.nonMatchingFrames = CAN_RX_REJECT;

	GPIO_voidInitPin(&canTxPin);
	GPIO_voidInitPin(&canRxPin);
	CAN_voidInit(CAN1, &rxCfg, &txCfg);
}

void delay(u32 ms)
{
	for(u32 i = 0; i < ms; i++)
		for(u32 j = 0; j < 1080; j++);
}
