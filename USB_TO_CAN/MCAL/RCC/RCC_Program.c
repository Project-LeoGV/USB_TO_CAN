/*
 * RCC_Program.c
 *
 *  Created on: Dec 5, 2023
 *      Author: Marwan Ahmed
 *      Layer: MCAL
 *      Version: 1.0
 */

/****************************************************************************/
/*							Included Files									*/
/****************************************************************************/
#include "RCC_Interface.h"

/****************************************************************************/
/*							Function Implementation							*/
/****************************************************************************/
void RCC_voidInit(void)
{
	/*Clear All Registers To Avoid Errors*/

	RCC->CR = 0x00000000;
	RCC->ICSCR = 0x00000000;
	RCC->CFGR = 0x00000000;
	RCC->PLLCFGR = 0x00000000;
	RCC->BDCR = 0x00000000;
	RCC->CSR = 0x00000000;
	RCC->CRRCR = 0x00000000;

	/*Turn HSI48 RC oscillator */
	RCC->CRRCR |=(RCC_HSI48<<0);

	/*Turn on the different clocks*/
	RCC->CR |= (RCC_HSI_ON<<8);			//HSI Clock ON
	RCC->CR |= (RCC_HSIKER_ON<<9);		//HSIKER Clock ON
	RCC->CR |= (RCC_HSE_ON<<16);		//HSE Clock ON
	RCC->CR |= (RCC_HSEBYP_ON<<18);		//HSE BYP ON
	//RCC->CR |= (RCC_PLL_ON<<24);		//PLL Clock ON


	/*HSI Trimming Value Adjust*/
	RCC->ICSCR |= (RCC_HSITRIM_VAL<<24);

	/*Select System Clock*/
	RCC->CFGR |= (RCC_SYSCLK_SEL<<0);
	/*Select Micro-controller Output Clock*/
	RCC->CFGR |= (RCC_MCO_SEL<<24);

	/*Select Micro-controller Output Prescaler*/
	RCC->CFGR |= (RCC_MCO_PRE<<28);
	/*Select AHB Prescaler*/
	RCC->CFGR |= (RCC_AHB_PRE<<4);
	/*Select APB1 Prescaler*/
	RCC->CFGR |= (RCC_APB1_PRE<<8);
	/*Select APB2 Prescaler*/
	RCC->CFGR |= (RCC_APB2_PRE<<11);



}
void RCC_voidPeripheralClockEnable(u8 A_u8BusName, RCC_Peripheral_t A_tPeripheral)
{
	switch(A_u8BusName)
	{
		case RCC_AHB1:
			SET_BIT(RCC->AHB1ENR, A_tPeripheral);
			break;

		case RCC_AHB2:
			SET_BIT(RCC->AHB2ENR, A_tPeripheral);
			break;

		case RCC_AHB3:
			SET_BIT(RCC->AHB3ENR, A_tPeripheral);
			break;

		case RCC_APB1_1:
			SET_BIT(RCC->APB1ENR1, A_tPeripheral);
			break;

		case RCC_APB1_2:
			SET_BIT(RCC->APB1ENR2, A_tPeripheral);
			break;

		case RCC_APB2:
			SET_BIT(RCC->APB2ENR, A_tPeripheral);
			break;
	}
}
void RCC_voidPeripheralClockDisable(u8 A_u8BusName, RCC_Peripheral_t A_tPeripheral)
{
	switch(A_u8BusName)
		{
			case RCC_AHB1:
				CLR_BIT(RCC->AHB1ENR, A_tPeripheral);
				break;

			case RCC_AHB2:
				CLR_BIT(RCC->AHB2ENR, A_tPeripheral);
				break;

			case RCC_AHB3:
				CLR_BIT(RCC->AHB3ENR, A_tPeripheral);
				break;

			case RCC_APB1_1:
				CLR_BIT(RCC->APB1ENR1, A_tPeripheral);
				break;

			case RCC_APB1_2:
				CLR_BIT(RCC->APB1ENR2, A_tPeripheral);
				break;

			case RCC_APB2:
				CLR_BIT(RCC->APB2ENR, A_tPeripheral);
				break;
		}
}
void RCC_voidSSMPeripheralClockEnable(u8 A_u8BusName, RCC_Peripheral_t A_tPeripheral)		//SSMP -> Sleep/Stop Mode Peripheral
{
	switch(A_u8BusName)
	{
		case RCC_AHB1:
			SET_BIT(RCC->AHB1SMENR, A_tPeripheral);
			break;

		case RCC_AHB2:
			SET_BIT(RCC->AHB2SMENR, A_tPeripheral);
			break;

		case RCC_AHB3:
			SET_BIT(RCC->AHB3SMENR, A_tPeripheral);
			break;

		case RCC_APB1_1:
			SET_BIT(RCC->APB1SMENR1, A_tPeripheral);
			break;

		case RCC_APB1_2:
			SET_BIT(RCC->APB1SMENR2, A_tPeripheral);
			break;

		case RCC_APB2:
			SET_BIT(RCC->APB2SMENR, A_tPeripheral);
			break;
	}
}
void RCC_voidSSMPeripheralClockDisable(u8 A_u8BusName, RCC_Peripheral_t A_tPeripheral)		//SSMP -> Sleep/Stop Mode Peripheral
{
	switch(A_u8BusName)
	{
		case RCC_AHB1:
			CLR_BIT(RCC->AHB1SMENR, A_tPeripheral);
			break;

		case RCC_AHB2:
			CLR_BIT(RCC->AHB2SMENR, A_tPeripheral);
			break;

		case RCC_AHB3:
			CLR_BIT(RCC->AHB3SMENR, A_tPeripheral);
			break;

		case RCC_APB1_1:
			CLR_BIT(RCC->APB1SMENR1, A_tPeripheral);
			break;

		case RCC_APB1_2:
			CLR_BIT(RCC->APB1SMENR2, A_tPeripheral);
			break;

		case RCC_APB2:
			CLR_BIT(RCC->APB2SMENR, A_tPeripheral);
			break;
	}
}
void RCC_voidPeripheralReset(u8 A_u8BusName, RCC_Peripheral_t A_tPeripheral)
{
	switch(A_u8BusName)
	{
		case RCC_AHB1:
			SET_BIT(RCC->AHB1RSTR, A_tPeripheral);
			break;

		case RCC_AHB2:
			SET_BIT(RCC->AHB2RSTR, A_tPeripheral);
			break;

		case RCC_AHB3:
			SET_BIT(RCC->AHB3RSTR, A_tPeripheral);
			break;

		case RCC_APB1_1:
			SET_BIT(RCC->APB1RSTR1, A_tPeripheral);
			break;

		case RCC_APB1_2:
			SET_BIT(RCC->APB1RSTR2, A_tPeripheral);
			break;

		case RCC_APB2:
			SET_BIT(RCC->APB2RSTR, A_tPeripheral);
			break;
	}
}
void RCC_voidPeripheralClockCfg(u8 A_u8RegName, RCC_Peripheral_Cfg_t A_tCfgPeripheral)
{
	switch(A_u8RegName)
	{
		case RCC_CCIPR_REG1:
			switch(A_tCfgPeripheral)
			{
				case USART1_Cfg:
					RCC->CCIPR |= (RCC_USART1_CLK<<USART1_Cfg);
					break;
				case USART2_Cfg:
					RCC->CCIPR |= (RCC_USART2_CLK<<USART2_Cfg);
					break;
				case USART3_Cfg:
					RCC->CCIPR |= (RCC_USART3_CLK<<USART3_Cfg);
					break;
				case USART4_Cfg:
					RCC->CCIPR |= (RCC_USART4_CLK<<USART4_Cfg);
					break;
				case USART5_Cfg:
					RCC->CCIPR |= (RCC_USART5_CLK<<USART5_Cfg);
					break;
				case LPUART1_Cfg:
					RCC->CCIPR |= (RCC_LPUSART_CLK<<LPUART1_Cfg);
					break;
				case I2C1_Cfg:
					RCC->CCIPR |= (RCC_I2C1_CLK<<I2C1_Cfg);
					break;
				case I2C2_Cfg:
					RCC->CCIPR |= (RCC_I2C2_CLK<<I2C2_Cfg);
					break;
				case I2C3_Cfg:
					RCC->CCIPR |= (RCC_I2C3_CLK<<I2C3_Cfg);
					break;
				case LPTIM1_Cfg:
					RCC->CCIPR |= (RCC_LPTIM1_CLK<<LPTIM1_Cfg);
					break;
				case SAI1_Cfg:
					RCC->CCIPR |= (RCC_SAI1_CLK<<SAI1_Cfg);
					break;
				case I2S23_Cfg:
					RCC->CCIPR |= (RCC_I2S23_CLK<<I2S23_Cfg);
					break;
				case FDCAN_Cfg:
					RCC->CCIPR |= (RCC_FDCAN_CLK<<FDCAN_Cfg);
					break;
				case CLK48_Cfg:
					RCC->CCIPR |= (RCC_CLK48_CLK<<CLK48_Cfg);
					break;
				case ADC12_Cfg:
					RCC->CCIPR |= (RCC_ADC12_CLK<<ADC12_Cfg);
					break;
				case ADC345_Cfg:
					RCC->CCIPR |= (RCC_ADC345_CLK<<ADC345_Cfg);
					break;
			}
			break;

		case RCC_CCIPR_REG2:
			switch(A_tCfgPeripheral)
			{
				case I2C4_Cfg:
					RCC->CCIPR2 |= (RCC_I2C4_CLK<<I2C4_Cfg);
					break;

				case QSPI_Cfg:
					RCC->CCIPR2 |= (RCC_QSPI_CLK<<QSPI_Cfg);
					break;
			}
			break;
	}
}
