/*
 * main.h
 *
 *  Created on: Jan 27, 2024
 *      Author: Mahmoud Ahmed
 */

#ifndef MAIN_H_
#define MAIN_H_

#include "../LIB/STD_TYPES.h"
#define RCC_BASE_ADDRESS			0X40021000

typedef struct
{
	u32 RCC_CR;
	u32 RCC_ICSCR;
	u32	RCC_CFGR;
	u32	RCC_PLLCFGR;
	u32 r0[2];
	u32 RCC_CIER;
	u32	RCC_CIFR;
	u32 RCC_CICR;
	u32 r1;
	u32 RCC_AHB1RSTR;
	u32 RCC_AHB2RSTR;
	u32 RCC_AHB3RSTR;
	u32 r2;
	u32 RCC_APB1RSTR1;
	u32 RCC_APB1RSTR2;
	u32 RCC_APB2RSTR;
	u32 r3;
	u32 RCC_AHB1ENR;
	u32 RCC_AHB2ENR;
	u32 RCC_AHB3ENR;
	u32 r4;
	u32 RCC_APB1ENR1;
	u32 RCC_APB1ENR2;
	u32 RCC_APB2ENR;
	u32 r5;
	u32 RCC_AHB1SMENR;
	u32 RCC_AHB2SMENR;
	u32 RCC_AHB3SMENR;
	u32 r6;
	u32 RCC_APB1SMENR1;
	u32 RCC_APB1SMENR2;
	u32 RCC_APB2SMENR;
	u32 r7;
	u32 RCC_CCIPR;
	u32 RCC_BDCR;
	u32 RCC_CSR;
	u32 RCC_CRRCR;
	u32 RCC_CCIPR2;
}RCC_Register_t;

#define	RCC							((volatile RCC_Register_t*)RCC_BASE_ADDRESS)

#endif /* MAIN_H_ */
