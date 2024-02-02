/*
 * GPIO_Registers.h
 *
 *  Created on: Nov 28, 2023
 *      Author: Nada Mamdouh
 *      Version: 02
 */

#ifndef MCAL_GPIO_GPIO_REG_H_
#define MCAL_GPIO_GPIO_REG_H_

#define GPIOA_BASE_ADDR           0x48000000U
#define GPIOB_BASE_ADDR           0x48000400U
#define GPIOC_BASE_ADDR           0x48000800U
#define GPIOD_BASE_ADDR           0x48000C00U
#define GPIOE_BASE_ADDR           0x48001000U
#define GPIOF_BASE_ADDR           0x48001400U
#define GPIOG_BASE_ADDR           0x48001800U

typedef volatile struct{
	u32 MODER;
	u32 OTYPER;
	u32 OSPEEDR;
	u32 PUPDR;
	u32 IDR;
	u32 ODR;
	u32 BSRR;
	u32 LCKR;
	u32 AFRL;
	u32 AFRH;
	u32 BRR;
}GPIO_RegMap_t;

#define GPIOA       (( GPIO_RegMap_t*)(GPIOA_BASE_ADDR))
#define GPIOB       (( GPIO_RegMap_t*)(GPIOB_BASE_ADDR))
#define GPIOC       (( GPIO_RegMap_t*)(GPIOC_BASE_ADDR))
#define GPIOD       (( GPIO_RegMap_t*)(GPIOD_BASE_ADDR))
#define GPIOE       (( GPIO_RegMap_t*)(GPIOE_BASE_ADDR))
#define GPIOF       (( GPIO_RegMap_t*)(GPIOF_BASE_ADDR))
#define GPIOG       (( GPIO_RegMap_t*)(GPIOG_BASE_ADDR))

#endif /* MCAL_GPIO_GPIO_REG_H_ */
