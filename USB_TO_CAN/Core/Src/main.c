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
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usb_device.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "../../MCAL/GPIO/GPIO_Interface.h"
#include "../../MCAL/FDCAN/CAN_Interface.h"
/* USER CODE END Includes */

int main(void)
{
	// Clock System Initialize

	// Enable Peripherals

	// Initialize Variables

	// Initialize Peripherals
	MX_USB_Device_Init();

	while(1)
	{
		// Receive from USB

		// Send CAN Message

		// Check CAN Receive Buffer

		// Send USB Acknowledge (Containing whether we will send or receive)

		// Send to USB if CAN buffer has messages

	}
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
