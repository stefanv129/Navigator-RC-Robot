/*
 * F401RE.c
 *
 *  Created on: Jan 27, 2025
 *      Author: voine
 */

#include "F401RE_RCC.h"

//either make a example funcion or use a config struct

void RCC_Clock_Config(RCC_Handle_t *pRCC_Handle_t) {

	// 4. Configure AHB, APB1, APB2 prescalers
	RCC->CFGR |= (RCC_CFGR_HPRE_DIV1 |  // AHB = SYSCLK / 1 (no division)
			RCC_CFGR_PPRE1_DIV2 | // APB1 = HCLK / 2
			RCC_CFGR_PPRE2_DIV2); // APB2 = HCLK / 2

	if(pRCC_Handle_t->RCC_Config.CLK_Source == HSI)
	{
		RCC->CR |= RCC_CR_HSION;
		while (!(RCC->CR & RCC_CR_HSIRDY));// 1. Enable HSI


	}
	else if(pRCC_Handle_t->RCC_Config.CLK_Source == PLLCLK)
	{
		// 2. Configure the PLL
		RCC->PLLCFGR = (16 << RCC_PLLCFGR_PLLM_Pos) |  // M = 16
				(400 << RCC_PLLCFGR_PLLN_Pos) |  // N = 400
				(0x2 << RCC_PLLCFGR_PLLP_Pos) |  // P = 8 (00: /2, 01: /4, 10: /8, 11: /16)
				(RCC_PLLCFGR_PLLSRC_HSI);        // HSI as PLL source
		// 3. Enable the PLL
		RCC->CR |= RCC_CR_PLLON;
		while (!(RCC->CR & RCC_CR_PLLRDY)); // Wait until PLL is ready
		// 5. Select the PLL as the system clock source
		RCC->CFGR &= ~RCC_CFGR_SW; // Clear system clock switch bits
		RCC->CFGR |= RCC_CFGR_SW_PLL; // Select PLL as system clock source

		while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL); // Wait until PLL is used as system clock
	}


	RCC->CR |= RCC_CR_HSION;
	while (!(RCC->CR & RCC_CR_HSIRDY)); // Wait until HSI is ready







	// 6. Update SystemCoreClock global variable (optional)
	SystemCoreClockUpdate();
}

typedef struct{
	SYSCLK_Src_t CLK_Source;
	PLL_Factors_t PLL_Facs;
	Bus_Prescalers_t Prescalers;
}RCC_Config_t;

typedef struct{
	RCC_RegDef_t *pRCC;
	RCC_Config_t RCC_Config;
}RCC_Handle_t;
