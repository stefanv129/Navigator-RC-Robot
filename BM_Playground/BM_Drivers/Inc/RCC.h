/*
 * F401RE_RCC.h
 *
 *  Created on: Jan 27, 2025
 *      Author: voine
 */

#ifndef INC_RCC_H_
#define INC_RCC_H_

#include "STM32F4.h"

#define AHB_DIV1 0x0 //1
#define APB1_DIV2 0x4 //100 => /2
#define APB2_DIV2 0x4 //100 => /2
#define RCC_CR_HSION 1
#define RCC_CR_PLLON (1 << 24)
#define RCC_CR_HSIRDY 2
#define RCC_CR_PLLRDY (1 << 25)
#define RCC_PLLCFGR_M 0x10 //M = 16/
#define RCC_CFGR_SW_HSI   0x0
#define RCC_CFGR_SWS_HSI (0x3 << 2)
#define RCC_CFGR_SW_PLL   0x2
#define RCC_CFGR_SWS_PLL (0x2 << 2)
#define RCC_PLLCFGR_PLLSRC_HSI  (~(1 << 22))  // Clears bit 22

typedef enum{
	HSI = 0,
	PLLCLK = 1,
}SYSCLK_Src_t;


typedef struct{
	int PLL_M;
	int PLL_N;
	int PLL_P;
}PLL_Factors_t;

typedef struct{
	int AHB_Presc;
	int APB1_Presc;
	int APB2_Presc;
}Bus_Prescalers_t;


typedef struct{
	SYSCLK_Src_t CLK_Source;
	PLL_Factors_t PLL_Factors;
	Bus_Prescalers_t Prescalers;
}RCC_Config_t;

typedef struct{
	RCC_RegDef_t *pRCC; //THERE IS ONLY ONE RCC?
	RCC_Config_t RCC_Config;
}RCC_Handle_t;

void RCC_Clock_Config(RCC_Handle_t *pRCC_Handle_t);



#endif /* INC_RCC_H_ */
