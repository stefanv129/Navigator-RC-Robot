/*
 * F401RE.c
 *
 *  Created on: Jan 27, 2025
 *      Author: voine
 */

#include <RCC.h>

//either make a example funcion or use a config struct

void RCC_Clock_Config(RCC_Handle_t *pRCC_Handle_t) {
	// 4. Configure AHB, APB1, APB2 prescalers
	pRCC_Handle_t->pRCC->CFGR = ((pRCC_Handle_t->RCC_Config.Prescalers.AHB_Presc << 4) |  // AHB = SYSCLK / 1 (no division)
			(pRCC_Handle_t->RCC_Config.Prescalers.APB1_Presc << 13) | // APB1 = HCLK / 2
			(pRCC_Handle_t->RCC_Config.Prescalers.APB2_Presc << 10)); // APB2 = HCLK / 2

	if (pRCC_Handle_t->RCC_Config.CLK_Source == HSI) {
		// 1. Enable HSI
		pRCC_Handle_t->pRCC->CR |= RCC_CR_HSION;
		while (!(pRCC_Handle_t->pRCC->CR & RCC_CR_HSIRDY)); // Wait until HSI is ready

		// 2. Select HSI as the system clock source
		pRCC_Handle_t->pRCC->CFGR &= ~0x3; // Clear system clock switch bits
		pRCC_Handle_t->pRCC->CFGR |= RCC_CFGR_SW_HSI; // Select HSI as system clock source

		// 3. Wait until HSI is used as the system clock
		while ((pRCC_Handle_t->pRCC->CFGR & RCC_CFGR_SWS_HSI) != RCC_CFGR_SW_HSI); //TEST IF BITS 2 AND 3 ARE 0


	}
//	else if (pRCC_Handle_t->RCC_Config.CLK_Source == PLLCLK) {
//		// Enable HSI if it is selected as the PLL source
//		if (!(pRCC_Handle_t->pRCC->PLLCFGR & ~RCC_PLLCFGR_PLLSRC_HSI)) {
//			pRCC_Handle_t->pRCC->CR |= RCC_CR_HSION;
//			while (!(pRCC_Handle_t->pRCC->CR & RCC_CR_HSIRDY)); // Wait until HSI is ready
//		}
//
//		// 2. Configure the PLL
//		pRCC_Handle_t->pRCC->PLLCFGR &= RCC_PLLCFGR_PLLSRC_HSI;  // Ensure HSI is selected as PLL source
//		pRCC_Handle_t->pRCC->PLLCFGR |= (pRCC_Handle_t->RCC_Config.PLL_Factors.PLL_M |
//				(pRCC_Handle_t->RCC_Config.PLL_Factors.PLL_N << 6) |
//				(pRCC_Handle_t->RCC_Config.PLL_Factors.PLL_P << 16));
//
//		// 3. Enable the PLL
//		pRCC_Handle_t->pRCC->CR |= RCC_CR_PLLON;
//		while (!(pRCC_Handle_t->pRCC->CR & RCC_CR_PLLRDY)); // Wait until PLL is ready
//
//		// 4. Select the PLL as the system clock source
//		pRCC_Handle_t->pRCC->CFGR &= ~0x3; // Clear system clock switch bits
//		pRCC_Handle_t->pRCC->CFGR |= RCC_CFGR_SW_PLL; // Select PLL as system clock source
//
//		// 5. Wait until PLL is used as the system clock
//		//3 << 2
//		while ((pRCC_Handle_t->pRCC->CFGR & 0xF) != 0xA);
//	}
}


