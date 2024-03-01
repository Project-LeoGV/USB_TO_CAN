/*
 * RCC_Interface.h
 *
 *  Created on: Dec 5, 2023
 *      Author: Marwan Ahmed
 *      Layer: MCAL
 *      Version: 1.0
 */

#ifndef RCC_INTERFACE_H_
#define RCC_INTERFACE_H_

/****************************************************************************/
/*							Included Files									*/
/****************************************************************************/
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

#include "RCC_Config.h"
#include "RCC_Registers.h"

/****************************************************************************/
/*							Bus Register Names								*/
/****************************************************************************/
#define RCC_AHB1				0
#define RCC_AHB2				1
#define RCC_AHB3				2
#define RCC_APB1_1				3
#define RCC_APB1_2				4
#define RCC_APB2				5
/****************************************************************************/
/*				Peripheeral Configuration Register Names					*/
/****************************************************************************/
#define RCC_CCIPR_REG1			1
#define RCC_CCIPR_REG2			2
/****************************************************************************/
/*					Peripheral In the Bus Registers							*/
/****************************************************************************/
typedef enum
{
	/*AHB1 Bus Peripherals Bits*/
	DMA1,
	DMA2,
	DMAMUX1,
	CORDIC,
	FMAC,
	FLASH=8,
	CRC=12,
	/*AHB2 Bus Peripherals Bits*/
	GPIO_A=0,
	GPIO_B,
	GPIO_C,
	GPIO_D,
	GPIO_E,
	GPIO_F,
	GPIO_G,
	ADC12=13,
	ADC345,
	DAC1=16,
	DAC2,
	DAC3,
	DAC4,
	AES=24,
	RNG=26,
	/*AHB3 Bus Peripherals Bits*/
	FMC=0,
	QSPIEN=8,
	/*APB1_1 Bus Peripherals Bits*/
	TIM2=0,
	TIM3,
	TIM4,
	TIM5,
	TIM6,
	TIM7,
	CRS=8,
	RTCAPB=10,
	WWDG,
	SPI2=14,
	SPI3,
	USART2=17,
	USART3,
	USART4,
	USART5,
	I2C1,
	I2C2,
	USB,
	FDCAN=25,
	PWR=28,
	I2C3=30,
	LPTIM1,
	/*APB1_2 Bus Peripherals Bits*/
	LPUART1=0,
	I2C4,
	UCPD1=8,
	/*APB2 Bus Peripherals Bits*/
	SYSCFG=0,
	TIM1=11,
	SPI1,
	TIM8,
	USART1,
	SPI4,
	TIM15,
	TIM16,
	TIM17,
	TIM20=20,
	SAI1,
	HRTIM1=26,
}RCC_Peripheral_t;
/****************************************************************************/
/*			Peripheral In the Peripheral Configuration Registers			*/
/****************************************************************************/
typedef enum
{
	/*RCC_CCIPR Register Peripherals Bits*/
	USART1_Cfg,
	USART2_Cfg=2,
	USART3_Cfg=4,
	USART4_Cfg=6,
	USART5_Cfg=8,
	LPUART1_Cfg=10,
	I2C1_Cfg=12,
	I2C2_Cfg=14,
	I2C3_Cfg=16,
	LPTIM1_Cfg=18,
	SAI1_Cfg=20,
	I2S23_Cfg=22,
	FDCAN_Cfg=24,
	CLK48_Cfg=26,
	ADC12_Cfg=28,
	ADC345_Cfg=30,
	/*RCC_CCIPR2 Register Peripherals Bits*/
	I2C4_Cfg=0,
	QSPI_Cfg=20
}RCC_Peripheral_Cfg_t;
/****************************************************************************/
/*							Function Prototypes								*/
/****************************************************************************/
void RCC_voidInit(void);
void RCC_voidPeripheralClockEnable(u8 A_u8BusName, RCC_Peripheral_t A_tPeripheral);
void RCC_voidPeripheralClockDisable(u8 A_u8BusName, RCC_Peripheral_t A_tPeripheral);
void RCC_voidSSMPeripheralClockEnable(u8 A_u8BusName, RCC_Peripheral_t A_tPeripheral);		//SSMP -> Sleep/Stop Mode Peripheral
void RCC_voidSSMPeripheralClockDisable(u8 A_u8BusName, RCC_Peripheral_t A_tPeripheral);		//SSMP -> Sleep/Stop Mode Peripheral
void RCC_voidPeripheralReset(u8 A_u8BusName, RCC_Peripheral_t A_tPeripheral);
void RCC_voidPeripheralClockCfg(u8 A_u8RegName, RCC_Peripheral_Cfg_t A_tCfgPeripheral);

#endif /* RCC_INTERFACE_H_ */
