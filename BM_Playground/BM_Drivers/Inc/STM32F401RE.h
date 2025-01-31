/*
 * STM32F401RE.h
 *
 *  Created on: Jan 26, 2025
 *      Author: voine
 */

#ifndef INC_STM32F401RE_H_
#define INC_STM32F401RE_H_

#include <stdint.h>

/* v MACROS DEFINED HERE v */

#define ENABLE 	1
#define DISABLE 0

#define SET		ENABLE
#define RESET	DISABLE

#define __vl 	volatile
/* ^ MACROS DEFINED HERE ^ */

/* v ADDRESSES DEFINED HERE v */

//AHB1vvv
#define BASEADDR_AHB1	(uint32_t)0x4002_0000U
//GPIOS
#define BASEADDR_GPIO_A (uint32_t)0x4002_0000U
#define BASEADDR_GPIO_B (uint32_t)0x4002_0400U
#define BASEADDR_GPIO_C (uint32_t)0x4002_0800U
#define BASEADDR_GPIO_D (uint32_t)0x4002_0C00U
#define BASEADDR_GPIO_E (uint32_t)0x4002_1000U
#define BASEADDR_GPIO_H (uint32_t)0x4002_C000U

typedef struct{
	__vl uint32_t MODER;
	__vl uint32_t OTYPER;
	__vl uint32_t OSPEEDR;
	__vl uint32_t PUPDR;
	__vl uint32_t IDR;
	__vl uint32_t ODR;
	__vl uint32_t BSRR;
	__vl uint32_t LCKR;
	__vl uint32_t AFR[2];

}GPIO_RegDef_t;
#define GPIO_A   ((GPIO_RegDef_t *) BASEADDR_GPIO_A)
#define GPIO_B   ((GPIO_RegDef_t *) BASEADDR_GPIO_B)
#define GPIO_C   ((GPIO_RegDef_t *) BASEADDR_GPIO_C)
#define GPIO_D   ((GPIO_RegDef_t *) BASEADDR_GPIO_D)
#define GPIO_E   ((GPIO_RegDef_t *) BASEADDR_GPIO_E)
#define GPIO_H   ((GPIO_RegDef_t *) BASEADDR_GPIO_H)
//RCC
#define BASEADDR_RCC 	(uint32_t)0x4002_3800U

typedef struct{
	__vl uint32_t CR;
	__vl uint32_t PLLCFGR;
	__vl uint32_t CFGR;
	__vl uint32_t CIR;
	__vl uint32_t AHB1RSTR;
	__vl uint32_t AHB2RSTR;
	uint32_t reserved1[2];
	__vl uint32_t APB1RSTR;
	__vl uint32_t APB2RSTR;
	uint32_t reserved2[2];
	__vl uint32_t AHB1ENR;
	__vl uint32_t AHB2ENR;
	uint32_t reserved3[2];
	__vl uint32_t APB1ENR;
	__vl uint32_t APB2ENR;
	uint32_t reserved4[2];
	__vl uint32_t AHB1LPENR;
	__vl uint32_t AHB2LPENR;
	uint32_t reserved5[2];
	__vl uint32_t APB1LPENR;
	__vl uint32_t APB2LPENR;
	uint32_t reserved6[2];
	__vl uint32_t BDCR;
	__vl uint32_t CSR;
	uint32_t reserved7[2];
	__vl uint32_t SSCGR;
	__vl uint32_t PLLI2SCFGR;
	__vl uint32_t DCKCFGR;
}RCC_RegDef_t;

//AHB1^^^

//AHB2vvv
#define BASEADDR_AHB2  (uint32_t)0x5000_0000U
//AHB2^^^

//APB1vvv
#define BASEADDR_APB1  (uint32_t) 0x4000_0000U
//TIMERS
#define BASEADDR_TIM_2 (uint32_t)0x4000_0000U
#define BASEADDR_TIM_3 (uint32_t)0x4002_0400U
#define BASEADDR_TIM_4 (uint32_t)0x4002_0800U
#define BASEADDR_TIM_5 (uint32_t)0x4002_0C00U

typedef struct{
	__vl uint32_t CR1;
	__vl uint32_t CR2;
	__vl uint32_t DIER;
	__vl uint32_t SR;
	__vl uint32_t EGR;
	__vl uint32_t CCMR1;
	__vl uint32_t CCMR2;
	__vl uint32_t CCER;
	__vl uint32_t CNT;
	__vl uint32_t PSC;
	__vl uint32_t ARR;
	uint32_t reserved1;
	__vl uint32_t CCR1;
	__vl uint32_t CCR2;
	__vl uint32_t CCR3;
	__vl uint32_t CCR4;
	uint32_t reserved2;
	__vl uint32_t DCR;
	__vl uint32_t DMAR;
	__vl uint32_t TIM2_OR;
	__vl uint32_t TIM5_OR;
}TIM2_5_RegDef_t;//general purpose timer

//SPIs
#define BASEADDR_SPI_2 (uint32_t)0x4000_3800U
#define BASEADDR_SPI_3 (uint32_t)0x4000_3C00U
//I2Cs
#define BASEADDR_I2C_1 (uint32_t)0x4000_5400U
#define BASEADDR_I2C_2 (uint32_t)0x4000_5800U
#define BASEADDR_I2C_3 (uint32_t)0x4000_5C00U
//APB1^^^

//APB2vvv
#define BASEADDR_APB2	 (uint32_t)0x4001_0000U
//TIMERS
#define BASEADDR_TIM_1 	 (uint32_t)0x4001_0000U
#define BASEADDR_TIM_9   (uint32_t)0x4001_4000U
#define BASEADDR_TIM_10  (uint32_t)0x4002_4400U
#define BASEADDR_TIM_11  (uint32_t)0x4002_4800U
//USARTs
#define BASEADDR_USART_1 (uint32_t)0x4001_1000U
#define BASEADDR_USART_6 (uint32_t)0x4001_1400U
//SPIs
#define BASEADDR_SPI_1   (uint32_t)0x4001_3000U
#define BASEADDR_SPI_4 	 (uint32_t)0x4001_3400U
//EXTI & SYSCFG
#define BASEADDR_SYSCFG  (uint32_t)0x4001_3800U
#define BASEADDR_EXTI    (uint32_t)0x4001_3C00U
//APB2^^^

/* ^ ADDRESSES DEFINED HERE ^ */


/* v STRUCTS DEFINED HERE v */
















#endif /* INC_STM32F401RE_H_ */
