/*
 * GPIO_Program.c
 *
 *  Created on: Nov 28, 2023
 *      Author: Nada Mamdouh
 *      Version: 02
 */

#include "GPIO_Interface.h"

static void GPIO_voidSetPinMode(u8 A_u8PortID, u8 A_u8PinNo, u8 A_u8Mode);
/************************************************************/
/*Function name: GPIO_voidSetPinOutput_typ_spd              */
/*Description:Configuring pin output type and speed         */
/************************************************************/
static void GPIO_voidSetPinOutput_typ_spd(u8 A_u8PortID, u8 A_u8PinNo, u8 A_u8Output_t,u8 A_u8OutputSpeed);
/************************************************************/
/*Function name: GPIO_voidSetPinPUPD                        */
/*Description:Configuring pin input as pull up or pull down */
/************************************************************/
static void GPIO_voidSetPinPUPD(u8 A_u8PortID, u8 A_u8PinNo, u8 A_u8PullU_D);
static void GPIO_voidAltFunc(u8 A_u8PortID, u8 A_u8PinNo, u8 A_u8AltFunc);

static void GPIO_voidSetPinMode(u8 A_u8PortID, u8 A_u8PinNo, u8 A_u8Mode)
{
	GPIO_RegMap_t *GPIOx = NULL;
	switch(A_u8PortID)
	{
	case GPIO_PORTA:
		GPIOx = GPIOA;
		break;
	case GPIO_PORTB:
		GPIOx = GPIOB;
		break;
	case GPIO_PORTC:
		GPIOx = GPIOC;
		break;
	case GPIO_PORTD:
		GPIOx = GPIOD;
		break;
	case GPIO_PORTE:
		GPIOx = GPIOE;
		break;
	case GPIO_PORTF:
		GPIOx = GPIOF;
		break;
	case GPIO_PORTG:
		GPIOx = GPIOG;
		break;
	default:
		/* Port ID out of range */
		break;
	}
	GPIOx->MODER &= ~(0b11<<(2*A_u8PinNo));
	GPIOx->MODER |= (A_u8Mode<<(2*A_u8PinNo));
}
static void GPIO_voidSetPinOutput_typ_spd(u8 A_u8PortID, u8 A_u8PinNo, u8 A_u8Output_t, u8 A_u8OutputSpeed)
{
	GPIO_RegMap_t *GPIOx = NULL;
	switch(A_u8PortID)
	{
	case GPIO_PORTA:
		GPIOx = GPIOA;
		break;
	case GPIO_PORTB:
		GPIOx = GPIOB;
		break;
	case GPIO_PORTC:
		GPIOx = GPIOC;
		break;
	case GPIO_PORTD:
		GPIOx = GPIOD;
		break;
	case GPIO_PORTE:
		GPIOx = GPIOE;
		break;
	case GPIO_PORTF:
		GPIOx = GPIOF;
		break;
	case GPIO_PORTG:
		GPIOx = GPIOG;
		break;
	default:
		/* Port ID out of range */
		break;
	}
	if(A_u8Output_t == GPIO_OT_PUSHPULL)
	{
		/* Set pin type */
		CLR_BIT(GPIOx->OTYPER,A_u8PinNo);

	}else if(A_u8Output_t == GPIO_OT_OPEN_DRAIN)
	{
		SET_BIT(GPIOx->OTYPER,A_u8PinNo);
	}
	/* Set pin speed */
	GPIOx->OSPEEDR &= ~(0b11<<(2*A_u8PinNo));
	GPIOx->OSPEEDR |= (A_u8OutputSpeed<<(2*A_u8PinNo));
}
void GPIO_voidSetPinValue(u8 A_u8PortID, u8 A_u8PinNo, u8 A_u8PinValue)
{
	GPIO_RegMap_t *GPIOx = NULL;
	switch(A_u8PortID)
	{
	case GPIO_PORTA:
		GPIOx = GPIOA;
		break;
	case GPIO_PORTB:
		GPIOx = GPIOB;
		break;
	case GPIO_PORTC:
		GPIOx = GPIOC;
		break;
	case GPIO_PORTD:
		GPIOx = GPIOD;
		break;
	case GPIO_PORTE:
		GPIOx = GPIOE;
		break;
	case GPIO_PORTF:
		GPIOx = GPIOF;
		break;
	case GPIO_PORTG:
		GPIOx = GPIOG;
		break;
	default:
		/* Port ID out of range */
		break;
	}
	if(A_u8PinValue == GPIO_VALUE_HIGH)
	{
		SET_BIT(GPIOx->ODR,A_u8PinNo);
	}
	else if(A_u8PinValue == GPIO_VALUE_LOW)
	{
		CLR_BIT(GPIOx->ODR,A_u8PinNo);
	}
}
static void GPIO_voidSetPinPUPD(u8 A_u8PortID, u8 A_u8PinNo, u8 A_u8PullU_D)
{
	GPIO_RegMap_t *GPIOx = NULL;
	switch(A_u8PortID)
	{
	case GPIO_PORTA:
		GPIOx = GPIOA;
		break;
	case GPIO_PORTB:
		GPIOx = GPIOB;
		break;
	case GPIO_PORTC:
		GPIOx = GPIOC;
		break;
	case GPIO_PORTD:
		GPIOx = GPIOD;
		break;
	case GPIO_PORTE:
		GPIOx = GPIOE;
		break;
	case GPIO_PORTF:
		GPIOx = GPIOF;
		break;
	case GPIO_PORTG:
		GPIOx = GPIOG;
		break;
	default:
		/* Port ID out of range */
		break;
	}
	GPIOx->PUPDR &= ~(0b11<<(2*A_u8PinNo));
	GPIOx->PUPDR |= (A_u8PullU_D<<(2*A_u8PinNo));
}
u8  GPIO_u8GetPinData(u8 A_u8PortID, u8 A_u8PinNo)
{
	u8 L_u8PinData;
	GPIO_RegMap_t *GPIOx = NULL;
	switch(A_u8PortID)
	{
	case GPIO_PORTA:
		GPIOx = GPIOA;
		break;
	case GPIO_PORTB:
		GPIOx = GPIOB;
		break;
	case GPIO_PORTC:
		GPIOx = GPIOC;
		break;
	case GPIO_PORTD:
		GPIOx = GPIOD;
		break;
	case GPIO_PORTE:
		GPIOx = GPIOE;
		break;
	case GPIO_PORTF:
		GPIOx = GPIOF;
		break;
	case GPIO_PORTG:
		GPIOx = GPIOG;
		break;
	default:
		/* Port ID out of range */
		break;
	}
	L_u8PinData = GET_BIT(GPIOx->IDR,A_u8PinNo);
	return L_u8PinData;
}
void GPIO_voidTogglePin(u8 A_u8PortID, u8 A_u8PinNo)
{
	GPIO_RegMap_t *GPIOx = NULL;
	switch(A_u8PortID)
	{
	case GPIO_PORTA:
		GPIOx = GPIOA;
		break;
	case GPIO_PORTB:
		GPIOx = GPIOB;
		break;
	case GPIO_PORTC:
		GPIOx = GPIOC;
		break;
	case GPIO_PORTD:
		GPIOx = GPIOD;
		break;
	case GPIO_PORTE:
		GPIOx = GPIOE;
		break;
	case GPIO_PORTF:
		GPIOx = GPIOF;
		break;
	case GPIO_PORTG:
		GPIOx = GPIOG;
		break;
	default:
		/* Port ID out of range */
		break;
	}
	TOG_BIT(GPIOx->ODR,A_u8PinNo);
}
static void GPIO_voidAltFunc(u8 A_u8PortID, u8 A_u8PinNo, u8 A_u8AltFunc)
{
	GPIO_RegMap_t *GPIOx = NULL;
	switch(A_u8PortID)
	{
	case GPIO_PORTA:
		GPIOx = GPIOA;
		break;
	case GPIO_PORTB:
		GPIOx = GPIOB;
		break;
	case GPIO_PORTC:
		GPIOx = GPIOC;
		break;
	case GPIO_PORTD:
		GPIOx = GPIOD;
		break;
	case GPIO_PORTE:
		GPIOx = GPIOE;
		break;
	case GPIO_PORTF:
		GPIOx = GPIOF;
		break;
	case GPIO_PORTG:
		GPIOx = GPIOG;
		break;
	default:
		/* Port ID out of range */
		break;
	}
	if(A_u8PinNo < 8)
	{
		GPIOx->AFRL &= ~(0b1111<<(4*A_u8PinNo));
		GPIOx->AFRL |= (A_u8AltFunc<<(4*A_u8PinNo));

	}else
	{
		GPIOx->AFRH &= ~(0b1111<<(4*(A_u8PinNo-8)));
		GPIOx->AFRH |= (A_u8AltFunc<<(4*(A_u8PinNo-8)));
	}

}
void GPIO_voidSetPortValue(u8 A_u8PortID, u8 A_u8PortValue)
{
	GPIO_RegMap_t *GPIOx = NULL;
	switch(A_u8PortID)
	{
	case GPIO_PORTA:
		GPIOx = GPIOA;
		break;
	case GPIO_PORTB:
		GPIOx = GPIOB;
		break;
	case GPIO_PORTC:
		GPIOx = GPIOC;
		break;
	case GPIO_PORTD:
		GPIOx = GPIOD;
		break;
	case GPIO_PORTE:
		GPIOx = GPIOE;
		break;
	case GPIO_PORTF:
		GPIOx = GPIOF;
		break;
	case GPIO_PORTG:
		GPIOx = GPIOG;
		break;
	default:
		/* Port ID out of range */
		break;
	}

	GPIOx->ODR = A_u8PortValue;
}
u16 GPIO_u16GetPortData(u8 A_u8PortID)
{
	u16 L_u8PortData;
	GPIO_RegMap_t *GPIOx = NULL;
	switch(A_u8PortID)
	{
	case GPIO_PORTA:
		GPIOx = GPIOA;
		break;
	case GPIO_PORTB:
		GPIOx = GPIOB;
		break;
	case GPIO_PORTC:
		GPIOx = GPIOC;
		break;
	case GPIO_PORTD:
		GPIOx = GPIOD;
		break;
	case GPIO_PORTE:
		GPIOx = GPIOE;
		break;
	case GPIO_PORTF:
		GPIOx = GPIOF;
		break;
	case GPIO_PORTG:
		GPIOx = GPIOG;
		break;
	default:
		/* Port ID out of range */
		break;
	}
	L_u8PortData = GPIOx->IDR ;
	return L_u8PortData;
}
void GPIO_voidTogglePort(u8 A_u8PortID)
{
	GPIO_RegMap_t *GPIOx = NULL;
	switch(A_u8PortID)
	{
	case GPIO_PORTA:
		GPIOx = GPIOA;
		break;
	case GPIO_PORTB:
		GPIOx = GPIOB;
		break;
	case GPIO_PORTC:
		GPIOx = GPIOC;
		break;
	case GPIO_PORTD:
		GPIOx = GPIOD;
		break;
	case GPIO_PORTE:
		GPIOx = GPIOE;
		break;
	case GPIO_PORTF:
		GPIOx = GPIOF;
		break;
	case GPIO_PORTG:
		GPIOx = GPIOG;
		break;
	default:
		/* Port ID out of range */
		break;
	}
	GPIOx->ODR ^= 0xFFFF;
}
void GPIO_voidInitPin(MGPIO_Config_t *A_xPin_Port_Config)
{
	GPIO_voidSetPinMode(A_xPin_Port_Config->Port, A_xPin_Port_Config->Pin, A_xPin_Port_Config->Mode);
	GPIO_voidSetPinOutput_typ_spd(A_xPin_Port_Config->Port, A_xPin_Port_Config->Pin, A_xPin_Port_Config->OutputType,A_xPin_Port_Config->OutputSpeed);
	GPIO_voidSetPinPUPD(A_xPin_Port_Config->Port, A_xPin_Port_Config->Pin, A_xPin_Port_Config->InputPull);
	GPIO_voidAltFunc(A_xPin_Port_Config->Port, A_xPin_Port_Config->Pin, A_xPin_Port_Config->AltFunc);
}
void GPIO_voidInitPort(MGPIO_Config_t *A_xPin_Port_Config)
{
	for(u8 L_u8PinIndex = 0;L_u8PinIndex < 16; L_u8PinIndex++)
	{
		GPIO_voidSetPinMode(A_xPin_Port_Config->Port, L_u8PinIndex, A_xPin_Port_Config->Mode);
		GPIO_voidSetPinOutput_typ_spd(A_xPin_Port_Config->Port,L_u8PinIndex, A_xPin_Port_Config->OutputType,A_xPin_Port_Config->OutputSpeed);
		GPIO_voidSetPinPUPD(A_xPin_Port_Config->Port, L_u8PinIndex, A_xPin_Port_Config->InputPull);
		GPIO_voidAltFunc(A_xPin_Port_Config->Port, L_u8PinIndex, A_xPin_Port_Config->AltFunc);
	}
}
