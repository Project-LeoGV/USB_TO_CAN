/*
 * Tx.c
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
	rxCfg.FIFO0_numberOfIDs = 2;
	rxCfg.FIFO1_numberOfIDs = 2;
	u32 ids[2] = {0x30, 0x31};
	rxCfg.FIFO0_IDs = ids;
	rxCfg.FIFO1_IDs = ids;
	rxCfg.nonMatchingFrames = CAN_RX_ACCEPT_FIFO1;


	CAN_Frame_t frame;
	u8 d[8] = "Hello";
	frame.data = d;
	frame.dlc = 5;
	frame.id = 0x09;
	frame.ide = CAN_FRAME_STANDARD_ID;
	frame.rtr = CAN_FRAME_DATA;

	RCC_Init();

	GPIO_voidInitPin(&canTxCfg);
	GPIO_voidInitPin(&canRxCfg);

	GPIO_voidInitPin(&ledCfg);

	CAN_voidInit(CAN1, &rxCfg, &txCfg);

	CAN_voidSendDataFrame(CAN1, &frame);
	while(1)
	{
		CAN_voidSendDataFrame(CAN1, &frame);
		GPIO_voidTogglePin(GPIO_PORTC, 13);
		delay(500);
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
