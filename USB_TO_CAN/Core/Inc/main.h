/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H


#include "stm32g4xx_hal.h"
#include "usb_device.h"
#include "usbd_cdc_if.h"
#include "../../MCAL/RCC/RCC_Interface.h"
#include "../../MCAL/GPIO/GPIO_Interface.h"
#include "../../MCAL/FDCAN/CAN_Interface.h"

/* MACROS */
#define CAN_IDS_COUNT		13 // To be edited later

typedef struct
{
	u32 msg_id;
	u8 rtr;
	u8 dlc;
	u8 data[8];
}USB_RX_t;

/* Functions Prototypes */
void APP_voidSystemClockInit(void);
void APP_voidCanInit(void);

u8 APP_u8SameMessage(USB_RX_t* A_previous, USB_RX_t* A_current);
void APP_voidSendAckUSB(u8 A_ack);
void APP_voidSendDataUSB(CAN_Frame_t* A_frame);
void APP_voidReceiveDataUSB(uint8_t* buffer, USB_RX_t *A_xDecoded_data);

void APP_voidDecimalToHex(u32 decimal, u8* hex);
u32 APP_u32StringToHex(u8 *A_u8str);

void Error_Handler(void);

#endif /* __MAIN_H */
