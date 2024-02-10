/*
 * RCC_Registers.h
 *
 *  Created on: Dec 5, 2023
 *      Author: Marwan Ahmed
 *      Layer: MCAL
 *      Version: 1.0
 */

#ifndef RCC_REGISTERS_H_
#define RCC_REGISTERS_H_

/****************************************************************************/
/*							RCC Register Definitions						*/
/****************************************************************************/
#define RCC_BASE_ADDRESS			0X40021000

typedef struct
{
	u32 CR;
	u32 ICSCR;
	u32	CFGR;
	u32	PLLCFGR;
	u32 Reserved1[2];
	u32 CIER;
	u32	CIFR;
	u32 CICR;
	u32 Reserved2;
	u32 AHB1RSTR;
	u32 AHB2RSTR;
	u32 AHB3RSTR;
	u32 Reserved3;
	u32 APB1RSTR1;
	u32 APB1RSTR2;
	u32 APB2RSTR;
	u32 Reserved4;
	u32 AHB1ENR;
	u32 AHB2ENR;
	u32 AHB3ENR;
	u32 Reserved5;
	u32 APB1ENR1;
	u32 APB1ENR2;
	u32 APB2ENR;
	u32 Reserved6;
	u32 AHB1SMENR;
	u32 AHB2SMENR;
	u32 AHB3SMENR;
	u32 Reserved7;
	u32 APB1SMENR1;
	u32 APB1SMENR2;
	u32 APB2SMENR;
	u32 Reserved8;
	u32 CCIPR;
	u32 Reserved9;
	u32 BDCR;
	u32 CSR;
	u32 CRRCR;
	u32 CCIPR2;
}RCC_Register_t;

#define	RCC							((volatile RCC_Register_t*)RCC_BASE_ADDRESS)

#endif /* RCC_REGISTERS_H_ */
