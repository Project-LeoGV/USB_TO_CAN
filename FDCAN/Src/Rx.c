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
	ledCfg.Pin = 5;
	ledCfg.Port = GPIO_PORTA;

	MGPIO_Config_t canRxCfg;
	canRxCfg.Mode = GPIO_MODE_ALTF;
	canRxCfg.Port = GPIO_PORTB;
	canRxCfg.Pin = 8;
	canRxCfg.OutputType = GPIO_OT_OPEN_DRAIN;
	canRxCfg.AltFunc = GPIO_AF9;

	MGPIO_Config_t canTxCfg;
	canTxCfg.Mode = GPIO_MODE_ALTF;
	canTxCfg.Port = GPIO_PORTB;
	canTxCfg.Pin = 9;
	canTxCfg.OutputType = GPIO_OT_OPEN_DRAIN;
	canTxCfg.AltFunc = GPIO_AF9;

	CAN_TxConfig_t txCfg;
	txCfg.transmitPause = CAN_TX_PAUSE_DISABLE;
	txCfg.bufferType = CAN_TX_BUFFER_FIFO;
	txCfg.automaticTransmission = CAN_AUTOMATIC_TRANSMISSION_ENABLE;

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
	u8 d[6] = "Hello\n";
	frame.data = d;
	frame.dlc = 6;
	frame.id = 0x30;
	frame.ide = CAN_FRAME_STANDARD_ID;
	frame.rtr = CAN_FRAME_DATA;

	RCC_Init();

	GPIO_voidInitPin(&canTxCfg);
	GPIO_voidInitPin(&canRxCfg);

	GPIO_voidInitPin(&ledCfg);
	ledCfg.Pin = 0;
	GPIO_voidInitPin(&ledCfg);
	ledCfg.Pin = 1;
	GPIO_voidInitPin(&ledCfg);

	CAN_voidInit(CAN1, &rxCfg, &txCfg);

	u8 count = 0;
	while(1)
	{
		count = CAN_u8GetReceivedMessagesCount(CAN1, CAN_RX_FIFO0);

		if(count == 0){
			GPIO_voidSetPinValue(GPIO_PORTA, 5, 1);
			GPIO_voidSetPinValue(GPIO_PORTA, 0, 0);
			GPIO_voidSetPinValue(GPIO_PORTA, 1, 0);
		}
		else{
			GPIO_voidSetPinValue(GPIO_PORTA, 5, 0);
			if(count == 1)
				GPIO_voidSetPinValue(GPIO_PORTA, 0, 1);
			else
				GPIO_voidSetPinValue(GPIO_PORTA, 1, 1);
		}
		delay(500);
	}
}

void RCC_Init(void)
{
	RCC->RCC_AHB2ENR |= (1 << 0);
	RCC->RCC_AHB2ENR |= (1 << 1);

	RCC->RCC_APB1ENR1 |= (1 << 25);
}

void delay(u32 ms)
{
	for(u32 i = 0; i < ms; i++)
		for(u32 j = 0; j < 1080; j++);
}
