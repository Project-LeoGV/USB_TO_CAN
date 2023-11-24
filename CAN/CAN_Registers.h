/*
 * CAN_Registers.h
 *
 *  Created on: Nov 24, 2023
 *      Author: Mahmoud Ahmed Ibrahim
 */

#ifndef CAN_CAN_REGISTERS_H_
#define CAN_CAN_REGISTERS_H_

#define CAN1_BASE_ADDR	0x40006400U
#define CAN2_BASE_ADDR	0x40006800U

typedef struct{
	u32 MCR;
	u32 MSR;
	u32 TSR;
	u32 RF0R;
	u32 RF1R;
	u32 IER;
	u32 ESR;
	u32 BTR;
	u32 reserved0[88]; // 0x020 - 0x17F

	u32 TI0R;
	u32 TDT0R;
	u32 TDL0R;
	u32 TDH0R;

	u32 TI1R;
	u32 TDT1R;
	u32 TDL1R;
	u32 TDH1R;

	u32 TI2R;
	u32 TDT2R;
	u32 TDL2R;
	u32 TDH2R;

	u32 RI0R;
	u32 RDT0R;
	u32 RDL0R;
	u32 RDH0R;

	u32 RI1R;
	u32 RDT1R;
	u32 RDL1R;
	u32 RDH1R;

	u32 reserved1[12]; // 0x1D0 - 0x1FF

	u32 FMR;
	u32 FM1R;
	u32 reserved2;
	u32 FS1R;
	u32 reserved3;
	u32 FFA1R;
	u32 reserved4;
	u32 FA1R;
	u32 reserved5;
	u32 reserved6[8]; // 0x224 - 0x23F

	u64 FR[28];

}st_CAN_RegDef_t;


#define CAN1	(st_CAN_RegDef_t *)(CAN1_BASE_ADDR)
#define CAN2	(st_CAN_RegDef_t *)(CAN2_BASE_ADDR)

#endif /* CAN_CAN_REGISTERS_H_ */
