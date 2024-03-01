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
	rxCfg.FIFO0_numberOfIDs = 2;
	rxCfg.FIFO1_numberOfIDs = 2;
	u32 ids[2] = {0x30, 0x31};
	rxCfg.FIFO0_IDs = ids;
	rxCfg.FIFO1_IDs = ids;
	rxCfg.nonMatchingFrames = CAN_RX_REJECT;


	CAN_Frame_t ON;
	ON.data[0] = 'O';
	ON.data[1] = 'N';
	ON.dlc = 2;
	ON.id = 0x09;
	ON.ide = CAN_FRAME_STANDARD_ID;
	ON.rtr = CAN_FRAME_DATA;

	CAN_Frame_t OFF;
	ON.data[0] = 'M';
	ON.data[1] = 'A';
	ON.data[2] = 'O';
	OFF.dlc = 3;
	OFF.id = 0x08;
	OFF.ide = CAN_FRAME_STANDARD_ID;
	OFF.rtr = CAN_FRAME_DATA;

	RCC_Init();

	GPIO_voidInitPin(&canTxCfg);
	GPIO_voidInitPin(&canRxCfg);

	GPIO_voidInitPin(&ledCfg);
	GPIO_voidInitPin(&btnCfg);

	CAN_voidInit(CAN1, &rxCfg, &txCfg);


	while(1)
	{
		/*if(GPIO_u8GetPinData(GPIO_PORTA, 5))
		{
			GPIO_voidSetPinValue(GPIO_PORTC, 13, 0);
			CAN_voidSendDataFrame(CAN1, &OFF);
		}
		else
		{
			GPIO_voidSetPinValue(GPIO_PORTC, 13, 1);
			CAN_voidSendDataFrame(CAN1, &ON);
		}*/
		CAN_voidSendDataFrame(CAN1, &ON);
		delay(500);
		CAN_voidSendDataFrame(CAN1, &OFF);
		delay(500);
		CAN_voidSendDataFrame(CAN1, &ON);
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
