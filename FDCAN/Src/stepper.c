/*
 * stepper.c
 *
 *  Created on: Apr 11, 2024
 *      Author: Mahmoud Ahmed
 */


#include "../MCAL/RCC/RCC_Interface.h"
#include "../MCAL/GPIO/GPIO_Interface.h"
#include "../MCAL/FDCAN/CAN_Interface.h"

void APP_voidSystemClockInit(void);
void APP_voidGpioInit(void);
void APP_voidCanInit(void);

void delay(u32 ms);

int main()
{
	APP_voidSystemClockInit();
	APP_voidGpioInit();
	APP_voidCanInit();

	CAN_Frame_t received;
	CAN_Frame_t feedback;
	while(1)
	{
		if(CAN_u8GetReceivedMessagesCount(CAN1, CAN_RX_FIFO0))
		{
			CAN_voidReceiveDataFrame(CAN1, &received, CAN_RX_FIFO0);
			switch(received.id)
			{
			case 0x021: /* Home */
				GPIO_voidTogglePin(GPIO_PORTA, 9);
				delay(2000);
				GPIO_voidTogglePin(GPIO_PORTA, 9);
				break;

			case 0x022:
				for(u8 i = 0; i < 10; i++){
					GPIO_voidTogglePin(GPIO_PORTA, 10);
					delay(100);
				}
				break;

			case 0x023:
				GPIO_voidTogglePin(GPIO_PORTA, 3);
				feedback.id = 0x023;
				feedback.dlc = 2;
				feedback.ide = CAN_FRAME_STANDARD_ID;
				feedback.rtr = CAN_FRAME_DATA;
				feedback.data[0] = 'H';
				feedback.data[1] = 'i';
				CAN_voidSendDataFrame(CAN1, &feedback);
				delay(500);
				GPIO_voidTogglePin(GPIO_PORTA, 3);
				break;

			case 0x029:
				GPIO_voidTogglePin(GPIO_PORTA, 3);
				feedback.id = 0x029;
				feedback.dlc = 8;
				feedback.ide = CAN_FRAME_STANDARD_ID;
				feedback.rtr = CAN_FRAME_DATA;
				feedback.data[0] = '0';
				feedback.data[1] = '0';
				feedback.data[2] = '1';
				feedback.data[3] = '0';
				feedback.data[4] = '1';
				feedback.data[5] = '1';
				feedback.data[6] = '0';
				feedback.data[7] = '1';
				CAN_voidSendDataFrame(CAN1, &feedback);
				delay(500);
				GPIO_voidTogglePin(GPIO_PORTA, 3);
				break;
			}
			GPIO_voidTogglePin(GPIO_PORTC, 13);
			//delay(50);
		}
	}
}

void APP_voidSystemClockInit(void)
{
	RCC_voidInit();
	RCC->CCIPR |= (1 << 25);

	RCC_voidPeripheralClockEnable(RCC_AHB2, GPIO_A);
	RCC_voidPeripheralClockEnable(RCC_AHB2, GPIO_B);
	RCC_voidPeripheralClockEnable(RCC_AHB2, GPIO_C);
	RCC_voidPeripheralClockEnable(RCC_APB1_1, FDCAN);
}

void APP_voidGpioInit(void)
{
	MGPIO_Config_t led = {.Port = GPIO_PORTC, .Pin = 13, .OutputType = GPIO_OT_PUSHPULL, .OutputSpeed = GPIO_SPEED_LOW, .Mode = GPIO_MODE_OUTPUT, .InputPull = GPIO_NO_PULL};
	GPIO_voidInitPin(&led);
	// TX1 --> PA9
	// RX1 --> PA10
	// TX2 --> PA2
	// RX2 --> PA3
	led.Port = GPIO_PORTA;
	led.Pin = 9;
	GPIO_voidInitPin(&led);
	led.Pin = 10;
	GPIO_voidInitPin(&led);
	led.Pin = 2;
	GPIO_voidInitPin(&led);
	led.Pin = 3;
	GPIO_voidInitPin(&led);

	GPIO_voidSetPinValue(GPIO_PORTA, 2, 1);
	GPIO_voidSetPinValue(GPIO_PORTA, 3, 1);
	GPIO_voidSetPinValue(GPIO_PORTA, 9, 1);
	GPIO_voidSetPinValue(GPIO_PORTA, 10, 1);
	GPIO_voidSetPinValue(GPIO_PORTC, 13, 1);
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
	rxCfg.FIFO0_numberOfIDs = 5;
	rxCfg.FIFO1_numberOfIDs = 0;
	u32 ids[5] = {0x021, 0x022, 0x023, 0x029, 0x00F};
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

