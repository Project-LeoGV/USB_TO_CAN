/*
 * USB_Registers.h
 *
 *  Created on: Dec 8, 2023
 *      Author: Mahmoud Ahmed
 */

#ifndef USB_USB_REGISTERS_H_
#define USB_USB_REGISTERS_H_

#define USB_BASE_ADDR		0x40005C00U
#define USB_SRAM_BASE_ADDR	0x40006000U

typedef volatile struct{
	u32 EPR[8];
	u32 reserved0[8];

	u32 CNTR;
	u32 ISTR;
	u32 FNR;
	u32 DADDR;

	u32 BTABLE;
	u32 LPMCSR;
	u32 BCDR;
}USB_RegDef_t;

typedef struct{

}USB_SRAM_RegDef_t;

#define USB					(USB_RegDef_t *)(USB_BASE_ADDR)
#define USB_SRAM			(USB_SRAM_RegDef_t *)(USB_SRAM_BASE_ADDR)

#endif /* USB_USB_REGISTERS_H_ */
