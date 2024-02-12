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
	RCC_DMA1,
	RCC_DMA2,
	RCC_DMAMUX1,
	RCC_CORDIC,
	RCC_FMAC,
	RCC_FLASH=8,
	RCC_CRC=12,
	/*AHB2 Bus Peripherals Bits*/
	RCC_GPIO_A=0,
	RCC_GPIO_B,
	RCC_GPIO_C,
	RCC_GPIO_D,
	RCC_GPIO_E,
	RCC_GPIO_F,
	RCC_GPIO_G,
	RCC_ADC12=13,
	RCC_ADC345,
	RCC_DAC1=16,
	RCC_DAC2,
	RCC_DAC3,
	RCC_DAC4,
	RCC_AES=24,
	RCC_RNG=26,
	/*AHB3 Bus Peripherals Bits*/
	RCC_FMC=0,
	RCC_QSPIEN=8,
	/*APB1_1 Bus Peripherals Bits*/
	RCC_TIM2=0,
	RCC_TIM3,
	RCC_TIM4,
	RCC_TIM5,
	RCC_TIM6,
	RCC_TIM7,
	RCC_CRS=8,
	RCC_RTCAPB=10,
	RCC_WWDG,
	RCC_SPI2=14,
	RCC_SPI3,
	RCC_USART2=17,
	RCC_USART3,
	RCC_USART4,
	RCC_USART5,
	RCC_I2C1,
	RCC_I2C2,
	RCC_USB,
	RCC_FDCAN=25,
	RCC_PWR=28,
	RCC_I2C3=30,
	RCC_LPTIM1,
	/*APB1_2 Bus Peripherals Bits*/
	RCC_LPUART1=0,
	RCC_I2C4,
	RCC_UCPD1=8,
	/*APB2 Bus Peripherals Bits*/
	RCC_SYSCFG=0,
	RCC_TIM1=11,
	RCC_SPI1,
	RCC_TIM8,
	RCC_USART1,
	RCC_SPI4,
	RCC_TIM15,
	RCC_TIM16,
	RCC_TIM17,
	RCC_TIM20=20,
	RCC_SAI1,
	RCC_HRTIM1=26,
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
