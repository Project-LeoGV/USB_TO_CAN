/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include "../MCAL/RCC/RCC_Interface.h"
#include "../MCAL/GPIO/GPIO_Interface.h"
#include "../MCAL/FDCAN/CAN_Interface.h"

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

	APP_voidCanInit();

	// Initialize Variables
	CAN_Frame_t Frame[3];
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
	Frame[2].rtr = CAN_FRAME_DATA;
	Frame[2].dlc = 5;
	Frame[2].data[0] = 'M';
	Frame[2].data[1] = 'a';
	Frame[2].data[2] = 'h';
	Frame[2].data[3] = 'm';
	Frame[2].data[4] = 'o';
	Frame[2].data[5] = 'u';
	Frame[2].data[6] = 'd';
	Frame[2].data[7] = '0';




	while(1)
	{

		CAN_voidSendDataFrame(CAN1, &Frame[0]);
		delay(2000);
		CAN_voidSendDataFrame(CAN1, &Frame[1]);
		delay(2000);
		CAN_voidSendDataFrame(CAN1, &Frame[2]);
		delay(2000);
	}
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
	rxCfg.FIFO0_numberOfIDs = 2;
	rxCfg.FIFO1_numberOfIDs = 2;
	u32 ids[2] = {0x30, 0x31};
	rxCfg.FIFO0_IDs = ids;
	rxCfg.FIFO1_IDs = ids;
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
