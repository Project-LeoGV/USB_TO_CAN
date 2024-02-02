/*
 * GPIO_Interface.h
 *
 *  Created on: Nov 28, 2023
 *      Author: Nada Mamdouh
 *      Version: 02
 */

#ifndef MCAL_GPIO_GPIO_INT_H_
#define MCAL_GPIO_GPIO_INT_H_

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "GPIO_Registers.h"
#include "GPIO_Config.h"
/**
 * Debug pins:
 * - PA13
 * - PA14
 * - PA15
 * - PB3
 * - PB4
 * Boot pin:
 * - PB8
 */

typedef struct{
	u8 Port;
	u8 Pin;
	u8 Mode;
	u8 OutputType;
	u8 OutputSpeed;
	u8 InputPull;
	u8 AltFunc;
}MGPIO_Config_t;

/************************************************************/
/* Function name: GPIO_voidInitPin                          */
/* Description:Configuring pin mode,output type/speed,      */
/* pull up ,pull down and alternate function                */
/************************************************************/
void GPIO_voidInitPin(MGPIO_Config_t *A_xPin_Port_Config);
/************************************************************/
/* Function name: GPIO_voidInitPort                         */
/* Description:Configuring port mode,output type/speed,     */
/* pull up ,pull down and alternate function                */
/************************************************************/
void GPIO_voidInitPort(MGPIO_Config_t *A_xPin_Port_Config);
void GPIO_voidSetPinValue(u8 A_u8PortID, u8 A_u8PinNo, u8 A_u8PinValue);
u8   GPIO_u8GetPinData(u8 A_u8PortID, u8 A_u8PinNo);
void GPIO_voidTogglePin(u8 A_u8PortID, u8 A_u8PinNo);
void GPIO_voidSetPortValue(u8 A_u8PortID, u8 A_u8PortValue);
u16  GPIO_u16GetPortData(u8 A_u8PortID);
void GPIO_voidTogglePort(u8 A_u8PortID);

/* ------ PORTS ------ */
#define GPIO_PORTA        0
#define GPIO_PORTB        1
#define GPIO_PORTC        2
#define GPIO_PORTD        3
#define GPIO_PORTE        4
#define GPIO_PORTF        5
#define GPIO_PORTG        6

/* ------ PINS ------ */
#define GPIO_PIN0        0
#define GPIO_PIN1        1
#define GPIO_PIN2        2
#define GPIO_PIN3        3
#define GPIO_PIN4        4
#define GPIO_PIN5        5
#define GPIO_PIN6        6
#define GPIO_PIN7        7
#define GPIO_PIN8        8
#define GPIO_PIN9        9
#define GPIO_PIN10       10
#define GPIO_PIN11       11
#define GPIO_PIN12       12
#define GPIO_PIN13       13
#define GPIO_PIN14       14
#define GPIO_PIN15       15

/* ------ PIN VALUE ------ */
#define GPIO_VALUE_LOW      0
#define GPIO_VALUE_HIGH     1

/* ------ PIN MODE ------ */
#define GPIO_MODE_INPUT      0b00
#define GPIO_MODE_OUTPUT     0b01
#define GPIO_MODE_ALTF       0b10
#define GPIO_MODE_ANALOG     0b11

/* -------- PIN OUTPUT OR ALTERNATE TYPE -------- */
#define GPIO_OT_PUSHPULL        0
#define GPIO_OT_OPEN_DRAIN      1

/* ---------- PIN SPEED ---------- */
#define GPIO_SPEED_LOW    0b00
#define GPIO_SPEED_MED    0b01
#define GPIO_SPEED_HIGH   0b10
#define GPIO_SPEED_VHIGH  0b11

/* -------- PULL UP/DOWN -------- */
#define GPIO_NO_PULL      0b00
#define GPIO_PULL_UP      0b01
#define GPIO_PULL_DOWN    0b10

/* ----- ALTERNATE FUNCTION -----*/
#define GPIO_AF0		0
#define GPIO_AF1		1
#define GPIO_AF2		2
#define GPIO_AF3		3
#define GPIO_AF4		4
#define GPIO_AF5		5
#define GPIO_AF6		6
#define GPIO_AF7		7
#define GPIO_AF8		8
#define GPIO_AF9		9
#define GPIO_AF10		10
#define GPIO_AF11		11
#define GPIO_AF12		12
#define GPIO_AF13		13
#define GPIO_AF14		14
#define GPIO_AF15		15

#endif /* MCAL_GPIO_GPIO_INT_H_ */
