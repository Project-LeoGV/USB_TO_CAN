/* USER CODE BEGIN Header */
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

#include "main.h"

#define CAN_DEBUG_USING_LED 	1

/* Global Variables */
u32 IDs[CAN_IDS_COUNT] = {0x01, 0x02, 0x003, 0x008, 0x009, 0x00A, 0x00F}; // Should Contain All UpStream IDs
uint8_t buffer[14] = "0000000000000\n";

#if CAN_DEBUG_USING_LED
void delay(u32 ms)
{
	for(u32 i = 0; i < ms; i++)
		for(u32 j = 0; j < 1080; j++);
}
#endif

int main(void)
{
	// Clock System Initialize
	APP_voidSystemClockInit();

	// Initialize Peripherals
	MGPIO_Config_t PC13 = {.Port = GPIO_PORTC, .Pin = GPIO_PIN13, .Mode = GPIO_MODE_OUTPUT,.AltFunc = GPIO_AF9,.OutputSpeed = GPIO_SPEED_LOW,.OutputType = GPIO_OT_PUSHPULL};
	GPIO_voidInitPin(&PC13);
	APP_voidCanInit();
	MX_USB_Device_Init();

	// Initialize Variables
	CAN_Frame_t receiveFrame;
	receiveFrame.id = 0x00;

	CAN_Frame_t transmitFrame;
	transmitFrame.ide = CAN_FRAME_STANDARD_ID;
	transmitFrame.data[0] = 'W';
	transmitFrame.data[1] = 'a';
	transmitFrame.data[2] = 'k';
	transmitFrame.data[3] = 'e';
	transmitFrame.data[4] = 'U';
	transmitFrame.data[5] = 'p';

	USB_RX_t currentMessage, previousMessage;
	previousMessage.msg_id = 0x000;
	currentMessage.msg_id = 0x000;

	u8 receivedMsgCount = 0;
	u8 sameMsg;

	transmitFrame.id = 0x000;
	transmitFrame.rtr = CAN_FRAME_DATA;
	transmitFrame.dlc = 8;

#if CAN_DEBUG_USING_LED
	delay(1000);
	GPIO_voidSetPinValue(GPIO_PORTC, 13, 1);
	delay(1000);
#endif

	//CAN_voidSendDataFrame(CAN1, &transmitFrame);
	while(1)
	{
		// Receive from USB
		APP_voidReceiveDataUSB(buffer, &currentMessage);

		// Check if the message is new
		sameMsg = APP_u8SameMessage(&previousMessage, &currentMessage);

		// Send CAN Message
		if(sameMsg == 0 && currentMessage.msg_id != 0x000)
		{
			// Send CAN message
			transmitFrame.id   = currentMessage.msg_id;
			transmitFrame.rtr  = currentMessage.rtr;
			transmitFrame.dlc  = currentMessage.dlc;
			for(u8 i = 0; i < transmitFrame.dlc; i++)
				transmitFrame.data[i] = currentMessage.data[i];

/*
#if CAN_DEBUG_USING_LED
			for(u8 i = 0; i < currentMessage.dlc; i++)
			{
				if(currentMessage.data[i] == '5'){
					GPIO_voidTogglePin(GPIO_PORTC, 13);
					delay(100);
				}
			}
#endif
*/

			CAN_voidSendDataFrame(CAN1, &transmitFrame);

			// Update previous message
			previousMessage.msg_id = currentMessage.msg_id;
			previousMessage.rtr = currentMessage.rtr;
			previousMessage.dlc = currentMessage.dlc;
			for(u8 i = 0; i < currentMessage.dlc; i++)
				previousMessage.data[i] = currentMessage.data[i];

			delay(50);
			// Check CAN Receive Buffer
			receivedMsgCount = CAN_u8GetReceivedMessagesCount(CAN1, CAN_RX_FIFO0);

			// Send USB Acknowledge (Containing whether we will send or receive)
			if(receivedMsgCount == 0){
				APP_voidSendAckUSB(1);
				GPIO_voidSetPinValue(GPIO_PORTC, 13, 1);
			}
			else{
				APP_voidSendAckUSB(2);
				GPIO_voidSetPinValue(GPIO_PORTC, 13, 0);
				CAN_voidReceiveDataFrame(CAN1, &receiveFrame, CAN_RX_FIFO0);
				APP_voidSendDataUSB(&receiveFrame);
			}

		}

		delay(50);
		// Check CAN Receive Buffer
		receivedMsgCount = CAN_u8GetReceivedMessagesCount(CAN1, CAN_RX_FIFO0);

		// Send USB Acknowledge (Containing whether we will send or receive)
		if(receivedMsgCount != 0){
			APP_voidSendAckUSB(2);
			GPIO_voidSetPinValue(GPIO_PORTC, 13, 0);
			CAN_voidReceiveDataFrame(CAN1, &receiveFrame, CAN_RX_FIFO0);
			APP_voidSendDataUSB(&receiveFrame);
		}
	}
}

void APP_voidSystemClockInit(void)
{
	RCC_voidInit();
	//RCC_voidPeripheralClockCfg(RCC_CCIPR_REG1, FDCAN_Cfg);
	RCC->CCIPR |= (1 << 25);
	RCC_voidPeripheralClockCfg(RCC_CCIPR_REG1,CLK48_Cfg);


	// Enable Peripherals
	RCC_voidPeripheralClockEnable(RCC_AHB2, RCC_GPIO_A);
	RCC_voidPeripheralClockEnable(RCC_AHB2, RCC_GPIO_B);
	RCC_voidPeripheralClockEnable(RCC_AHB2, RCC_GPIO_C);
	RCC_voidPeripheralClockEnable(RCC_APB1_1, RCC_FDCAN);
	RCC_voidPeripheralClockEnable(RCC_APB1_1, RCC_USB);
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
	rxCfg.FIFO0_numberOfIDs = CAN_IDS_COUNT;
	rxCfg.FIFO1_numberOfIDs = 0;
	rxCfg.FIFO0_IDs = IDs;
	rxCfg.FIFO1_IDs = NULL;
	rxCfg.nonMatchingFrames = CAN_RX_REJECT;

	GPIO_voidInitPin(&canTxPin);
	GPIO_voidInitPin(&canRxPin);
	CAN_voidInit(CAN1, &rxCfg, &txCfg);
}

u8 APP_u8SameMessage(USB_RX_t* A_previous, USB_RX_t* A_current)
{
	u8 L_result = 0;

	if(A_previous->msg_id == A_current->msg_id
		&& A_previous->rtr == A_current->rtr
		&& A_previous->dlc == A_current->dlc
		)
	{
		L_result = 1;
		for(u8 i = 0; i < A_current->dlc; i++){
			if(A_previous->data[i] != A_current->data[i]){
				L_result = 0;
				break;
			}
		}
	}

	return L_result;
}

void APP_voidSendAckUSB(u8 A_ack)
{
	u8 msg[5] = "0000\n";
	msg[3] = '0' + A_ack;
	CDC_Transmit_FS(msg, 5);
}

void APP_voidSendDataUSB(CAN_Frame_t* A_frame)
{
	u8 msg[14];
	/* Message Format
	 *  ID  RTR DLC data       end
	 *  000  0   0   00000000	\n
	 */

	// ID
	APP_voidDecimalToHex(A_frame->id, msg);

	// RTR
	msg[3] = '0' + A_frame->rtr;

	// DLC
	msg[4] = '0' + A_frame->dlc;

	// Data
	u8 i = 0;
	for(i = 0; i < 8; i++){
		if(i < A_frame->dlc)
			msg[5 + i] = A_frame->data[i];
		else
			msg[5 + i] = '0';
	}

	// End
	msg[13] = '\n';

	// Send Message Via USB
	CDC_Transmit_FS(msg, 14);
}

void APP_voidReceiveDataUSB(uint8_t* buffer, USB_RX_t *A_xDecoded_data)
{
	u32 len = 14;
	CDC_Receive_FS(buffer, &len);
	u8 hex_str[3];
	hex_str[0] = buffer[0] ;
	hex_str[1] = buffer[1] ;
	hex_str[2] = buffer[2] ;

	A_xDecoded_data->msg_id = APP_u32StringToHex(hex_str);

	A_xDecoded_data->rtr = buffer[3] - '0';

	A_xDecoded_data->dlc = buffer[4] - '0';

	for (u8 i = 0; i < A_xDecoded_data->dlc; i++) {
		A_xDecoded_data->data[i] = buffer[5 + i];
	}
}

void APP_voidDecimalToHex(u32 decimal, u8* hex)
{
	u8 h[16] = {'0', '1', '2', '3', '4',
			'5', '6', '7', '8', '9',
			'A', 'B', 'C', 'D', 'E',
			'F'};
	hex[2] = h[decimal % 16];
	hex[1] = h[(decimal % 256) / 16];
	hex[0] = h[decimal / 256];
}


u32 APP_u32StringToHex(u8 *A_u8str)
{
	u32 hex = 0;
	for(u8 i = 0; i<3; i++)
	{
		if(A_u8str[i]>='0' && A_u8str[i]<= '9')
		{
			hex = hex *16 +  (A_u8str[i]-'0');
		}else if(A_u8str[i]>='A' && A_u8str[i]<= 'F')
		{
			hex = hex *16 +  (A_u8str[i]-'A' + 10);
		}
	}
	return hex;
}

void Error_Handler(void)
{
	/* USER CODE BEGIN Error_Handler_CAN_DEBUG_USING_LED */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1)
	{
	}
	/* USER CODE END Error_Handler_DEBUG */
}
