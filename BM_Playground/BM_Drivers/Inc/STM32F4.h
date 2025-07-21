/*
 * STM32F401RE.h
 *
 *  Created on: Jan 26, 2025
 *      Author: voine
 */

#ifndef INC_STM32F4_H_
#define INC_STM32F4_H_

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
#define BASEADDR_AHB1	((uint32_t)0x40020000U)
//GPIOS
#define BASEADDR_GPIO_A	(BASEADDR_AHB1 + 0x0000)
#define BASEADDR_GPIO_B (BASEADDR_AHB1 + 0x0400)
#define BASEADDR_GPIO_C (BASEADDR_AHB1 + 0x0800)
#define BASEADDR_GPIO_D (BASEADDR_AHB1 + 0x0C00)
#define BASEADDR_GPIO_E (BASEADDR_AHB1 + 0x1000)
#define BASEADDR_GPIO_H (BASEADDR_AHB1 + 0x1400)

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

#define GPIO_BASEADDR_TO_CODE(x)      ((x == GPIOA)?0:\
										(x == GPIOB)?1:\
										(x == GPIOC)?2:0)




#define GPIOA   ((GPIO_RegDef_t *) BASEADDR_GPIO_A)
#define GPIOB   ((GPIO_RegDef_t *) BASEADDR_GPIO_B)
#define GPIOC   ((GPIO_RegDef_t *) BASEADDR_GPIO_C)
#define GPIOD   ((GPIO_RegDef_t *) BASEADDR_GPIO_D)
#define GPIOE   ((GPIO_RegDef_t *) BASEADDR_GPIO_E)
#define GPIOH   ((GPIO_RegDef_t *) BASEADDR_GPIO_H)
//RCC
#define BASEADDR_RCC 	(BASEADDR_AHB1 + 0x3800)

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

#define RCC    ((RCC_RegDef_t*)BASEADDR_RCC)

//AHB1^^^

//AHB2vvv
#define BASEADDR_AHB2  (uint32_t)0x5000_0000U
//AHB2^^^

//APB1vvv
#define BASEADDR_APB1  (uint32_t) 0x40000000U
#define APB1_CLOCK_FREQ_MHZ	(uint8_t)		8
#define APB1_CLOCK_FREQ						8000000
//TIMERS
#define BASEADDR_TIM_2 (BASEADDR_APB1 + 0x0000)
#define BASEADDR_TIM_3 (BASEADDR_APB1 + 0x0400)
#define BASEADDR_TIM_4 (BASEADDR_APB1 + 0x0800)
#define BASEADDR_TIM_5 (BASEADDR_APB1 + 0x0C00)

typedef struct{
	__vl uint32_t CR1;
	__vl uint32_t CR2;
	__vl uint32_t SMCR; //why?
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
}GP_TIM_RegDef_t;//general purpose timer

#define TIM2	((GP_TIM_RegDef_t *)BASEADDR_TIM_2)
#define TIM3	((GP_TIM_RegDef_t *)BASEADDR_TIM_3)

//SPIs
#define BASEADDR_SPI_2 (uint32_t)0x4000_3800U
#define BASEADDR_SPI_3 (uint32_t)0x4000_3C00U
//I2Cs
#define BASEADDR_I2C_1 (uint32_t)0x40005400U
#define BASEADDR_I2C_2 (uint32_t)0x4000_5800U
#define BASEADDR_I2C_3 (uint32_t)0x4000_5C00U
//APB1^^^
typedef struct{
	__vl uint32_t CR1;
	__vl uint32_t CR2;
	__vl uint32_t OAR1;
	__vl uint32_t OAR2;
	__vl uint32_t DR;
	__vl uint32_t SR1;
	__vl uint32_t SR2;
	__vl uint32_t CCR;
	__vl uint32_t TRISE;
	__vl uint32_t FLTR;
}I2C_RegDef_t;

#define I2C1 	((I2C_RegDef_t*)BASEADDR_I2C_1)

//APB2vvv
#define BASEADDR_APB2	 (uint32_t)0x40010000U
//TIMERS
#define BASEADDR_TIM_1 	 (BASEADDR_APB2 + 0x0000)
typedef struct{
	__vl uint32_t CR1;
	__vl uint32_t CR2;
	__vl uint32_t SMCR;
	__vl uint32_t DIER;
	__vl uint32_t SR;
	__vl uint32_t EGR;
	__vl uint32_t CCMR1;
	__vl uint32_t CCMR2;
	__vl uint32_t CCER;
	__vl uint32_t CNT;
	__vl uint32_t PSC;
	__vl uint32_t ARR;
	__vl uint32_t RCR;
	__vl uint32_t CCR1;
	__vl uint32_t CCR2;
	__vl uint32_t CCR3;
	__vl uint32_t CCR4;
	__vl uint32_t BDTR;
	__vl uint32_t DCR;
	__vl uint32_t DMAR;
}AD_TIM_RegDef_t;//ADVANCED CONTROL timer


#define TIM1	((AD_TIM_RegDef_t *)BASEADDR_TIM_1)

//USARTs
#define BASEADDR_USART_1 (uint32_t)0x4001_1000U
#define BASEADDR_USART_6 (uint32_t)0x4001_1400U
//SPIs
#define BASEADDR_SPI_1   (uint32_t)0x4001_3000U
#define BASEADDR_SPI_4 	 (uint32_t)0x4001_3400U
//EXTI & SYSCFG
#define BASEADDR_SYSCFG  (uint32_t)0x40013800U

typedef struct{
	__vl uint32_t MEMRMP;
	__vl uint32_t PMC;
	__vl uint32_t EXTICR[4];
	uint32_t      RESERVED1[2];
	__vl uint32_t CMPCR;
	uint32_t      RESERVED2[2];
	__vl uint32_t CFGR;
}SYSCFG_RegDef_t;

#define SYSCFG	((SYSCFG_RegDef_t *)BASEADDR_SYSCFG)
#define SYSCFG_PCLK_EN() (RCC->APB2ENR |= (1 << 14))

#define BASEADDR_EXTI    (uint32_t)0x40013C00U


typedef struct{
	__vl uint32_t IMR;
	__vl uint32_t EMR;
	__vl uint32_t RTSR;
	__vl uint32_t FTSR;
	__vl uint32_t SWIER;
	__vl uint32_t PR;
}EXTI_RegDef_t;

#define EXTI ((EXTI_RegDef_t *)BASEADDR_EXTI)

//APB2^^^

/* ^ ADDRESSES DEFINED HERE ^ */


/* v STRUCTS DEFINED HERE v */


//NVIC
#define NVIC_ISER0	 ((__vl uint32_t*)0xE000E100)
#define NVIC_ISER1	 ((__vl uint32_t*)0xE000E104)
#define NVIC_ISER2   ((__vl uint32_t*)0xE000E108)
#define NVIC_ISER3   ((__vl uint32_t*)0xE000E10c)

#define NVIC_ICER0	 ((__vl uint32_t*)0xE000E180)
#define NVIC_ICER1	 ((__vl uint32_t*)0xE000E184)
#define NVIC_ICER2   ((__vl uint32_t*)0XE000E188)
#define NVIC_ICER3	 ((__vl uint32_t*)0XE000E18C)

#define IRQ_NO_EXTI0 		6
#define IRQ_NO_EXTI1 		7
#define IRQ_NO_EXTI2 		8
#define IRQ_NO_EXTI3 		9
#define IRQ_NO_EXTI4 		10
#define IRQ_NO_EXTI9_5 		23
#define IRQ_NO_EXTI15_10 	40



#endif /* INC_STM32F4_H_ */
