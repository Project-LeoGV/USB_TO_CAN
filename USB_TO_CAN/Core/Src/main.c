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
uint8_t buffer[14] = "0010219024700\n";
typedef struct
{
	u32 msg_id;
	u8 rtr;
	u8 dlc;
	u8 data[8];
}USB_RX_t;

/* Functions Prototypes */
void USB_voidSendAck(u8 A_ack);
void USB_voidSendCan(CAN_Frame_t* A_frame);
void decimalToHex(u32 decimal, u8* hex);
void  Receive_USB_data(uint8_t* buffer,USB_RX_t *A_xDecoded_data);
u32 hexstr_to_Hex(u8 *A_u8str);

int main(void)
{
	// Clock System Initialize
	RCC_voidInit();
	RCC_voidPeripheralClockCfg(RCC_CCIPR_REG1,CLK48_Cfg);

	// Enable Peripherals
	RCC_voidPeripheralClockEnable(RCC_AHB2, RCC_GPIO_A);
	RCC_voidPeripheralClockEnable(RCC_AHB2, RCC_GPIO_B);
	RCC_voidPeripheralClockEnable(RCC_AHB2, RCC_GPIO_C);
	RCC_voidPeripheralClockEnable(RCC_APB1_1, RCC_FDCAN);
	RCC_voidPeripheralClockEnable(RCC_APB1_1, RCC_USB);

	// Initialize Variables
	MGPIO_Config_t canTxPin = {.Port = GPIO_PORTB, .Pin = GPIO_PIN9, .Mode = GPIO_MODE_ALTF,.AltFunc = GPIO_AF9,.OutputSpeed = GPIO_SPEED_LOW,.OutputType = GPIO_OT_PUSHPULL};
	CAN_TxConfig_t txConfig = {.automaticTransmission = CAN_AUTOMATIC_TRANSMISSION_DISABLE, .bufferType = CAN_TX_BUFFER_FIFO, .transmitPause = CAN_TX_PAUSE_DISABLE};
	MGPIO_Config_t usbCfg = {.Port = GPIO_PORTB,.Pin = GPIO_PIN3,.Mode = GPIO_MODE_ALTF,.AltFunc = GPIO_AF3, .OutputType = GPIO_OT_PUSHPULL, .OutputSpeed = GPIO_SPEED_LOW,.InputPull=GPIO_NO_PULL};

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


	CAN_Frame_t transmitFrame;
	transmitFrame.ide = CAN_FRAME_STANDARD_ID;



	// Initialize Peripherals
	GPIO_voidInitPin(&usbCfg);
	GPIO_voidInitPin(&canTxPin);
	CAN_voidInit(CAN1, &rxConfig, &txConfig);

	MX_USB_Device_Init();

	while(1)
	{
		USB_RX_t DecodedData;
		// Receive from USB
		Receive_USB_data(buffer,&DecodedData);

		// Send CAN Message
		//if msg_id contains address 0x000 and rtr contains 0 then there is no data
		if(DecodedData.msg_id == 0x000 && DecodedData.rtr == 0 )
		{

		}else{
			transmitFrame.id   = DecodedData.msg_id;
			transmitFrame.rtr  = DecodedData.rtr;
			transmitFrame.dlc  = DecodedData.dlc;
			transmitFrame.data = DecodedData.data;

			CAN_voidSendDataFrame(CAN1, &transmitFrame);
		}


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
void  Receive_USB_data(uint8_t* buffer,USB_RX_t *A_xDecoded_data)
{
	u8 hex_str[3];
	hex_str[0] = buffer[0] ;
	hex_str[1] = buffer[1] ;
	hex_str[2] = buffer[2] ;

	A_xDecoded_data->msg_id = hexstr_to_Hex(hex_str);

	A_xDecoded_data->rtr = buffer[3] - '0';

	A_xDecoded_data->dlc = buffer[4] - '0';

	for (u8 i = 0; i < A_xDecoded_data->dlc; i++) {
		A_xDecoded_data->data[i] = buffer[5 + i];
	}

}
u32 hexstr_to_Hex(u8 *A_u8str)
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
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1)
	{
	}
	/* USER CODE END Error_Handler_Debug */
}
