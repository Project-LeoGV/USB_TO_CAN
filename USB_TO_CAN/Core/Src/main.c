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
#include "usb_device.h"
#include "usbd_cdc_if.h"
#include "../../MCAL/RCC/RCC_Interface.h"
#include "../../MCAL/GPIO/GPIO_Interface.h"
#include "../../MCAL/FDCAN/CAN_Interface.h"

/* MACROS */
#define CAN_IDS_COUNT		2 // To be edited later

/* Global Variables */
u32 IDs[CAN_IDS_COUNT] = {0x01, 0x02}; // Should Contain All UpStream IDs

/* Functions Prototypes */
void USB_voidSendAck(u8 A_ack);
void USB_voidSendCan(CAN_Frame_t* A_frame);
void decimalToHex(u32 decimal, u8* hex);

int main(void)
{
	// Clock System Initialize
	RCC_voidInit();

	// Enable Peripherals
	RCC_voidPeripheralClockEnable(RCC_AHB2, RCC_GPIO_A);
	RCC_voidPeripheralClockEnable(RCC_AHB2, RCC_GPIO_B);
	RCC_voidPeripheralClockEnable(RCC_AHB2, RCC_GPIO_C);
	RCC_voidPeripheralClockEnable(RCC_APB1_1, RCC_FDCAN);

	// Initialize Variables
	CAN_TxConfig_t txConfig;

	CAN_RxConfig_t rxConfig;
	rxConfig.FIFO0_IDs = IDs;
	rxConfig.FIFO0_numberOfIDs = CAN_IDS_COUNT;
	rxConfig.FIFO0_Mode = CAN_RX_FIFO_OVERWRITE;
	rxConfig.nonMatchingFrames = CAN_RX_ACCEPT_FIFO1;

	CAN_Frame_t receiveFrame;
	u8 receiveData[8];
	receiveFrame.data = receiveData;
	receiveFrame.id = 0x00;

	u8 receivedMsgCount = 0;
	// Initialize Peripherals
	CAN_voidInit(CAN1, &rxConfig, &txConfig);
	MX_USB_Device_Init();

	while(1)
	{
		// Receive from USB

		// Send CAN Message

		// Check CAN Receive Buffer
		receivedMsgCount = CAN_u8IsRxBufferFull(CAN1, CAN_RX_FIFO0);

		// Send USB Acknowledge (Containing whether we will send or receive)
		if(receivedMsgCount == 0){
			USB_voidSendAck(1);
		}
		else{
			USB_voidSendAck(2);
			CAN_voidReceiveDataFrame(CAN1, &receiveFrame, CAN_RX_FIFO0);
			USB_voidSendCan(&receiveFrame);
		}
	}
}

void USB_voidSendAck(u8 A_ack)
{
	u8 msg[5] = "0000\n";
	msg[3] = '0' + A_ack;
	CDC_Transmit_FS(msg, 4);
}

void USB_voidSendCan(CAN_Frame_t* A_frame)
{
	u8 msg[14];
	/* Message Format
	 *  ID  RTR DLC data       end
	 *  000  0   0   00000000	\n
	 */

	// ID
	decimalToHex(A_frame->id, msg);

	// RTR
	msg[3] = '0' + A_frame->rtr;

	// DLC
	msg[4] = '0' + A_frame->dlc;

	// Data
	u8 i = 0;
	for(i = 0; i < 8; i++){
		if(i < A_frame->dlc)
			msg[5 + i] = '0' + A_frame->data[i];
		else
			msg[5 + i] = '0';
	}

	// End
	msg[13] = '\n';

	// Send Message Via USB
	CDC_Transmit_FS(msg, 14);
}

void decimalToHex(u32 decimal, u8* hex)
{
	u8 h[16] = {'0', '1', '2', '3', '4',
				'5', '6', '7', '8', '9',
				'A', 'B', 'C', 'D', 'E',
				'F'};
	hex[2] = h[decimal % 16];
	hex[1] = h[(decimal % 256) / 16];
	hex[0] = h[decimal / 256];
}


void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
