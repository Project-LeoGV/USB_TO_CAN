/*
 * CAN_Registers.h
 *
 *  Created on: Nov 29, 2023
 *      Author: Mahmoud Ahmed Ibrahim
 */

#ifndef FDCAN_CAN_REGISTERS_H_
#define FDCAN_CAN_REGISTERS_H_

/************************************************************************************************************************/
/********************************************* FDCANs Peripheral Registers **********************************************/
/************************************************************************************************************************/

#define FDCAN1_BASE_ADDR				0x40006400U
#define FDCAN2_BASE_ADDR				0x40006800U
#define FDCAN3_BASE_ADDR				0x40006C00U

typedef struct{
	u32 CREL;
	u32 ENDN;
	u32 reserved0;
	u32 DBTP;
	u32 TEST;
	u32 RWD;
	u32 CCCR;
	u32 NBTP;

	u32 TSCC;
	u32 TSCV;
	u32 TOCC;
	u32 TOCV;
	u32 reserved1[4];

	u32 ECR;
	u32 PSR;
	u32 TDCR;
	u32 reserved2;

	u32 IR;
	u32 IE;
	u32 ILS;
	u32 ILE;

	u32 reserved3[8];

	u32 RXGFC;
	u32 XIDAM;
	u32 HPMS;
	u32 reserved4[8];

	u32 RXF0S;
	u32 RXF0A;
	u32 RXF1S;
	u32 RXF1A;

	u32 reserved5[8];

	u32 TXBC;
	u32 TXFQS;
	u32 TXBRP;
	u32 TXBAR;

	u32 TXBCR;
	u32 TXBTO;
	u32 TXBCF;
	u32 TXBTIE;

	u32 TXBCIE;
	u32 TXEFS;
	u32 TXEFA;
	u32 reserved6;

	u32 CKDIV;
}st_CAN_RegDef_t;

#define CAN1	(st_CAN_RegDef_t *)(FDCAN1_BASE_ADDR)
#define CAN2	(st_CAN_RegDef_t *)(FDCAN2_BASE_ADDR)
#define CAN3	(st_CAN_RegDef_t *)(FDCAN3_BASE_ADDR)

/************************************************************************************************************************/
/************************************************* FDCANs Message RAM ***************************************************/
/************************************************************************************************************************/

#define FDCAN1_MESSAGES_SRAM_BASE_ADDR	0x4000A000U
#define FDCAN2_MESSAGES_SRAM_BASE_ADDR	0x40004000U
#define FDCAN3_MESSAGES_SRAM_BASE_ADDR	0x40008000U

typedef struct{
	u32 ID;
	u32 DLC;
	u32 data[16];
}CAN_RxFIFO_t;

typedef struct{
	u32 ID;
	u32 DLC;
	u32 data[16];
}CAN_TxBuffer_t;

typedef struct{
	u32 standardID[28];				// 28 elements / 28 word
	u32 extendedID[16];				// 8 elements  / 16 word
	CAN_RxFIFO_t RxFIFO0[3];		// 3 elements  / 54 word
	CAN_RxFIFO_t RxFIFO1[3];		// 3 elements  / 54 word
	u32 TxEvent[6];					// 3 elements  / 6 word
	CAN_TxBuffer_t TxBuffer[3];		// 3 elements  / 54 word
}st_CAN_MSG_SRAM_t;


#define CAN1_MESSAGES		(st_CAN_MSG_SRAM_t *)(FDCAN1_MESSAGES_SRAM_BASE_ADDR)
#define CAN2_MESSAGES		(st_CAN_MSG_SRAM_t *)(FDCAN2_MESSAGES_SRAM_BASE_ADDR)
#define CAN3_MESSAGES		(st_CAN_MSG_SRAM_t *)(FDCAN3_MESSAGES_SRAM_BASE_ADDR)

#endif /* FDCAN_CAN_REGISTERS_H_ */
