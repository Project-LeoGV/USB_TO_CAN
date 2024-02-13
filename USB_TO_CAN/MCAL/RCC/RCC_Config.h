/*
 * RCC_Config.h
 *
 *  Created on: Dec 5, 2023
 *      Author: Marwan Ahmed
 *      Layer: MCAL
 *      Version: 1.0
 */

#ifndef RCC_CONFIG_H_
#define RCC_CONFIG_H_

/****************************************************************************/
/*						Peripheral Clock Configurations						*/
/****************************************************************************/
/* USART Peripheral Clock Configurations
 * PCLK 	-> 00
 * SYSCLK 	-> 01
 * HSI16 	-> 10
 * LSE 		-> 11 */
#define	RCC_USART1_CLK			0b01
#define	RCC_USART2_CLK			0b01
#define	RCC_USART3_CLK			0b01
#define	RCC_USART4_CLK			0b01
#define	RCC_USART5_CLK			0b01
#define	RCC_LPUSART_CLK			0b01

/****************************************************************************/
/* I2C Peripheral Clock Configurations
 * PCLK 				-> 00
 * SYSCLK 				-> 01
 * HSI16 				-> 10
 * Reserved 			-> 11 */
#define	RCC_I2C1_CLK			0b01
#define	RCC_I2C2_CLK			0b01
#define	RCC_I2C3_CLK			0b01
#define	RCC_I2C4_CLK			0b01

/****************************************************************************/
/* QSPI Peripheral Clock Configurations
 * SYSCLK 				-> 00
 * HSI16 				-> 01
 * PLL"Q" 				-> 10
 * Reserved 			-> 11 */
#define	RCC_QSPI_CLK			0b00

/****************************************************************************/
/* FDCAN Peripheral Clock Configurations
 * HSE 					-> 00
 * PLL"Q" 				-> 01
 * PCLK 				-> 10
 * Reserved 			-> 11 */
#define	RCC_FDCAN_CLK			0b00

/****************************************************************************/
/* ADC Peripheral Clock Configurations
 * No Clock Selected	-> 00
 * PLL"P" 				-> 01
 * SYSCLK 				-> 10
 * Reserved 			-> 11 */
#define	RCC_ADC12_CLK			0b10
#define	RCC_ADC345_CLK			0b10

/****************************************************************************/
/* Low Power Timer Peripheral Clock Configurations
 * PCLK 				-> 00
 * LSI	 				-> 01
 * HSI16 				-> 10
 * LSE					-> 11 */
#define	RCC_LPTIM1_CLK			0b00

/****************************************************************************/
/* SAI1 Peripheral Clock Configurations
 * SYSCLK 				-> 00
 * PLL"Q" 				-> 01
 * I2S_CKIN pin CLK 	-> 10
 * HSI16				-> 11 */
#define	RCC_SAI1_CLK			0b00

/****************************************************************************/
/* I2S23 Peripheral Clock Configurations
 * SYSCLK 				-> 00
 * PLL"Q" 				-> 01
 * I2S_CKIN pin CLK 	-> 10
 * HSI16				-> 11 */
#define	RCC_I2S23_CLK			0b00

/****************************************************************************/
/* CLK48 Peripheral Clock Configurations
 * HSI48 				-> 00
 * Reserved 			-> 01
 * PLL"Q" (PLL48M1CLK) 	-> 10
 * Reserved				-> 11 */
#define	RCC_CLK48_CLK			0b00

/****************************************************************************/
/*						RCC_CR Register Bits/States							*/
/****************************************************************************/
#define RCC_HSI_OFF				0					//Read-Write bit
#define	RCC_HSI_ON				1					//Read-Write bit

#define	RCC_HSIKER_OFF			0					//Read-Write bit
#define RCC_HSIKER_ON			1					//Read-Write bit

#define RCC_HSE_OFF				0					//Read-Write bit
#define RCC_HSE_ON				1					//Read-Write bit

#define	RCC_HSEBYP_OFF			0					//Read-Write bit
#define	RCC_HSEBYP_ON			1					//Read-Write bit

#define RCC_CSS_ON				1					//Read-Set bit

#define RCC_PLL_OFF				0					//Read-Write bit
#define RCC_PLL_ON				1					//Read-Write bit
/****************************************************************************/
/*						RCC_ICSCR Register Bits/States						*/
/****************************************************************************/
/* HSI Clock Trim Value
 * This value is 64 -> 0b1000000 by default */
#define RCC_HSITRIM_VAL			0b1000000

/****************************************************************************/
/*						RCC_CFGR Register Bits/States						*/
/****************************************************************************/
/* System clock source select
 00: Reserved, must be kept at reset value
 01: HSI16 selected as system clock
 10: HSE selected as system clock
 11: PLL selected as system clock */
#define RCC_SYSCLK_SEL			0b01
/****************************************************************************/

/* AHB Prescaler
 0xxx: SYSCLK not divided
 1000: SYSCLK divided by 2
 1001: SYSCLK divided by 4
 1010: SYSCLK divided by 8
 1011: SYSCLK divided by 16
 1100: SYSCLK divided by 64
 1101: SYSCLK divided by 128
 1110: SYSCLK divided by 256
 1111: SYSCLK divided by 512 */
#define RCC_AHB_PRE				0b0000
/****************************************************************************/

/*	APB1 Prescaler
 0xx: HCLK not divided
 100: HCLK divided by 2
 101: HCLK divided by 4
 110: HCLK divided by 8
 111: HCLK divided by 16 */
#define RCC_APB1_PRE			0b000
/****************************************************************************/

/*	APB2 Prescaler
 0xx: HCLK not divided
 100: HCLK divided by 2
 101: HCLK divided by 4
 110: HCLK divided by 8
 111: HCLK divided by 16 */
#define RCC_APB2_PRE			0b000
/****************************************************************************/

/* Micro-controller clock output select
 0000: MCO output disabled, no clock on MCO
 0001: SYSCLK system clock selected
 0010: Reserved, must be kept at reset value
 0011: HSI16 clock selected
 0100: HSE clock selected
 0101: Main PLL clock selected
 0110: LSI clock selected
 0111: LSE clock selected
 1000: Internal HSI48 clock selected */
#define RCC_MCO_SEL				0b1000
/****************************************************************************/

/* Micro-controller clock output prescaler
 000: MCO is divided by 1
 001: MCO is divided by 2
 010: MCO is divided by 4
 011: MCO is divided by 8
 100: MCO is divided by 16 */
#define RCC_MCO_PRE				0b000

/****************************************************************************/
/*						RCC_PLLCFGR Register Bits/States					*/
/****************************************************************************/
/* PLL clock source select
 00: No clock sent to PLL (Power Saver)
 01: No clock sent to PLL
 10: HSI16 clock selected as PLL clock entry
 11: HSE clock selected as PLL clock entry */
#define RCC_PLL_SEL				0b00
/****************************************************************************/

/* Division factor for the main PLL input clock
 * VCO input frequency = PLL input clock frequency / PLLM
 0000: PLLM = 1
 0001: PLLM = 2
 0010: PLLM = 3
 0011: PLLM = 4
 0100: PLLM = 5
 0101: PLLM = 6
 0110: PLLM = 7
 0111: PLLM = 8
 1000: PLLSYSM = 9
 ...
 1111: PLLSYSM= 16 */
#define RCC_PLLM				0b0000
/****************************************************************************/

/* Main PLL multiplication factor for VCO
 * VCO output frequency = VCO input frequency x PLLN with 8 =< PLLN =< 127
0000000: PLLN = 0 wrong configuration
0000001: PLLN = 1 wrong configuration
...
0000111: PLLN = 7 wrong configuration
0001000: PLLN = 8
0001001: PLLN = 9
...
1111111: PLLN = 127 */
#define RCC_PLLN				0b0000
/****************************************************************************/

/* Main PLL"P" clock output enable*/
#define RCC_PLLP_DIS				0
#define RCC_PLLP_EN					1
/****************************************************************************/

/*Main PLLP division factor
 *PLL “P” output clock frequency = VCO frequency / PLLPDIV
 00000: PLL “P” clock is controlled by the bit PLLP
 00001: Reserved.
 00010: PLL “P” clock = VCO / 2
 ....
 11111: PLL “P” clock = VCO / 31 */
#define RCC_PLLP_DIV				0b00000
/****************************************************************************/

/*Main PLL division factor for PLL “P” clock.
 0: PLLP = 7
 1: PLLP = 17 */
#define RCC_PLLP					0
/****************************************************************************/

/* Main PLL"P" clock output enable*/
#define RCC_PLLQ_DIS				0
#define RCC_PLLQ_EN					1
/****************************************************************************/

/*Main PLL division factor for PLL “Q” clock.
 * PLL “Q” output clock frequency = VCO frequency / PLLQ with PLLQ = 2, 4, 6, or 8
 00: PLLQ = 2
 01: PLLQ = 4
 10: PLLQ = 6
 11: PLLQ = 8 */
#define RCC_PLLQ					0b00
/****************************************************************************/

/* Main PLL"P" clock output enable*/
#define RCC_PLLR_DIS				0
#define RCC_PLLR_EN					1
/****************************************************************************/

/*Main PLL division factor for PLL “R” clock.
 * PLL “R” output clock frequency = VCO frequency / PLLR with PLLR = 2, 4, 6, or 8
 00: PLLQ = 2
 01: PLLQ = 4
 10: PLLQ = 6
 11: PLLQ = 8 */
#define RCC_PLLR					0b00
/****************************************************************************/
/*HSI48  RC oscillator  */
/*0: HSI48OFF
 *1: HSI48ON
 */
#define RCC_HSI48                     1

#endif /* RCC_CONFIG_H_ */
