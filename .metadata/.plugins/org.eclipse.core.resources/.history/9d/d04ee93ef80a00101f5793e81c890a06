/*
 * F401RE_TIMER.c
 *
 *  Created on: Jan 27, 2025
 *      Author: voine
 */



#include "F401RE_TIMER.h"


void AD_TIM_PWM_INIT(AD_TIM_Handle_t *pAD_TIM_Handle) {
	// Enable the clock for TIM1
	if (pAD_TIM_Handle->pTIMx == TIM1) {
		TIM1_PCLK_EN();
	}

	// Enable Auto-Reload Preload (ARPE)
	pAD_TIM_Handle->pTIMx->CR1 |= (1 << 7);  // ARPE: Auto-Reload Preload Enable
	// Set Prescaler & Auto-Reload Value
	pAD_TIM_Handle->pTIMx->PSC = pAD_TIM_Handle->AD_TIM_Config.Prescaler;
	pAD_TIM_Handle->pTIMx->ARR = pAD_TIM_Handle->AD_TIM_Config.Period;  // Frequency

	// Configure PWM Channels
	for (int ch = 0; ch < 4; ch++) {
		if (pAD_TIM_Handle->AD_TIM_Config.CH_Setup[ch].CH_Enabled) {
			uint16_t dutyCycle = pAD_TIM_Handle->AD_TIM_Config.CH_Setup[ch].DutyCycle;
			dutyCycle = ((float)dutyCycle / 100) * pAD_TIM_Handle->AD_TIM_Config.Period; // ex.(50/100)
			//duty Cycle is 0 for some reason
			switch (ch) {
			case CH1:
				pAD_TIM_Handle->pTIMx->CCR1 = dutyCycle;
				pAD_TIM_Handle->pTIMx->CCMR1 &= ~(7 << 4);
				pAD_TIM_Handle->pTIMx->CCMR1 |= (pAD_TIM_Handle->AD_TIM_Config.CH_Setup[ch].CH_Mode == PWM1) ? (6 << 4) : (7 << 4);
				pAD_TIM_Handle->pTIMx->CCMR1 |= (1 << 3); // Enable Output Compare Preload
				break;

			case CH2:
				pAD_TIM_Handle->pTIMx->CCR2 = dutyCycle;
				pAD_TIM_Handle->pTIMx->CCMR1 &= ~(7 << 12);
				pAD_TIM_Handle->pTIMx->CCMR1 |= (pAD_TIM_Handle->AD_TIM_Config.CH_Setup[ch].CH_Mode == PWM1) ? (6 << 12) : (7 << 12);
				pAD_TIM_Handle->pTIMx->CCMR1 |= (1 << 11); // Enable Output Compare Preload
				break;

			case CH3:
				pAD_TIM_Handle->pTIMx->CCR3 = dutyCycle;
				pAD_TIM_Handle->pTIMx->CCMR2 &= ~(7 << 4);
				pAD_TIM_Handle->pTIMx->CCMR2 |= (pAD_TIM_Handle->AD_TIM_Config.CH_Setup[ch].CH_Mode == PWM1) ? (6 << 4) : (7 << 4);
				pAD_TIM_Handle->pTIMx->CCMR2 |= (1 << 3); // Enable Output Compare Preload
				break;

			case CH4:
				pAD_TIM_Handle->pTIMx->CCR4 = dutyCycle;
				pAD_TIM_Handle->pTIMx->CCMR2 &= ~(7 << 12);
				pAD_TIM_Handle->pTIMx->CCMR2 |= (pAD_TIM_Handle->AD_TIM_Config.CH_Setup[ch].CH_Mode == PWM1) ? (6 << 12) : (7 << 12);
				pAD_TIM_Handle->pTIMx->CCMR2 |= (1 << 11); // Enable Output Compare Preload
				break;
			}
		}
	}

	// Enable the Timer (CEN Bit)
	pAD_TIM_Handle->pTIMx->CR1 |= (1 << 0);  // Start the Timer
}


void AD_TIM_PWM_Start(AD_TIM_Handle_t *pTIM_Handle, uint8_t channel) {
	// Enable the main output (MOE) for Advanced Timers (TIM1)
	pTIM_Handle->pTIMx->BDTR |= (1 << 15);  // MOE Bit in BDTR

	// Enable the selected PWM channel
	switch (channel) {
	case CH1:
		pTIM_Handle->pTIMx->CCER |= (1 << 0);  // Enable CH1 (CC1E)
		break;
	case CH2:
		pTIM_Handle->pTIMx->CCER |= (1 << 4);  // Enable CH2 (CC2E)
		break;
	case CH3:
		pTIM_Handle->pTIMx->CCER |= (1 << 8);  // Enable CH3 (CC3E)
		break;
	case CH4:
		pTIM_Handle->pTIMx->CCER |= (1 << 12); // Enable CH4 (CC4E)
		break;
	}

	// Enable the Timer Counter
	pTIM_Handle->pTIMx->CR1 |= (1 << 0);  // Start the Timer (CEN Bit)
}



