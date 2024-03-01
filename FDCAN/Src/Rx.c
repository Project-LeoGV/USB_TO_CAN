/*
 * Rx.c
 *
 *  Created on: Jan 30, 2024
 *      Author: Mahmoud Ahmed
 */

#include "main.h"
#include "../MCAL/FDCAN/CAN_Interface.h"
#include "../MCAL/GPIO/GPIO_Interface.h"

void RCC_Init(void);
void delay(u32 ms);

int main()
{
	MGPIO_Config_t ledCfg;
	ledCfg.Mode = GPIO_MODE_OUTPUT;
	ledCfg.Pin = 13;
	ledCfg.Port = GPIO_PORTC;

	MGPIO_Config_t btnCfg;
	btnCfg.Mode = GPIO_MODE_INPUT;
	btnCfg.Pin = 5;
	btnCfg.Port = GPIO_PORTA;
	btnCfg.InputPull = GPIO_PULL_UP;
	btnCfg.OutputType = GPIO_OT_PUSHPULL;

	MGPIO_Config_t canRxCfg;
	canRxCfg.Mode = GPIO_MODE_ALTF;
	canRxCfg.Port = GPIO_PORTB;
	canRxCfg.Pin = 8;
	canRxCfg.OutputType = GPIO_OT_PUSHPULL;
	canRxCfg.AltFunc = GPIO_AF9;
	canRxCfg.OutputSpeed = GPIO_SPEED_LOW;

	MGPIO_Config_t canTxCfg;
	canTxCfg.Mode = GPIO_MODE_ALTF;
	canTxCfg.Port = GPIO_PORTB;
	canTxCfg.Pin = 9;
	canTxCfg.OutputType = GPIO_OT_PUSHPULL;
	canTxCfg.AltFunc = GPIO_AF9;
	canTxCfg.OutputSpeed = GPIO_SPEED_LOW;

	CAN_TxConfig_t txCfg;
	txCfg.transmitPause = CAN_TX_PAUSE_DISABLE;
	txCfg.bufferType = CAN_TX_BUFFER_FIFO;
	txCfg.automaticTransmission = CAN_AUTOMATIC_TRANSMISSION_DISABLE;

	CAN_RxConfig_t rxCfg;
	rxCfg.FIFO0_Mode = CAN_RX_FIFO_OVERWRITE;
	rxCfg.FIFO1_Mode = CAN_RX_FIFO_OVERWRITE;
	rxCfg.FIFO0_numberOfIDs = 5;
	rxCfg.FIFO1_numberOfIDs = 5;
	u32 ids[5] = {0x08, 0x09, 0x0A, 0x0F, 0x10};
	rxCfg.FIFO0_IDs = ids;
	rxCfg.FIFO1_IDs = ids;
	rxCfg.nonMatchingFrames = CAN_RX_REJECT;


	CAN_Frame_t frame;
	frame.id = 0;
	frame.dlc = 0;
	frame.rtr = 0;
	frame.ide = CAN_FRAME_STANDARD_ID;
	frame.data[0] = '0';
	frame.data[1] = '1';
	frame.data[2] = '2';
	frame.data[3] = '3';
	frame.data[4] = '4';
	frame.data[5] = '5';
	frame.data[6] = '6';
	frame.data[7] = '\n';

	RCC_Init();

	GPIO_voidInitPin(&canTxCfg);
	GPIO_voidInitPin(&canRxCfg);

	GPIO_voidInitPin(&ledCfg);
	GPIO_voidInitPin(&btnCfg);

	CAN_voidInit(CAN1, &rxCfg, &txCfg);

	u8 count = 0;
	while(1)
	{
		count = CAN_u8GetReceivedMessagesCount(CAN1, CAN_RX_FIFO0);
		if(count != 0)
		{
			CAN_voidReceiveDataFrame(CAN1, &frame, CAN_RX_FIFO0);
			//delay(100);
			//CAN_voidSendDataFrame(CAN1, &frame);
		}
		//delay(500);
	}
}

void RCC_Init(void)
{
	RCC->RCC_CCIPR |= (1 << 25);

	RCC->RCC_AHB2ENR |= (1 << 0);
	RCC->RCC_AHB2ENR |= (1 << 1);
	RCC->RCC_AHB2ENR |= (1 << 2);

	RCC->RCC_APB1ENR1 |= (1 << 25);
}

void delay(u32 ms)
{
	for(u32 i = 0; i < ms; i++)
		for(u32 j = 0; j < 1080; j++);
}
