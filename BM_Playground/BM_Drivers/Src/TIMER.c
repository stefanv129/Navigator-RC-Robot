/*
 * F401RE_TIMER.c
 *
 *  Created on: Jan 27, 2025
 *      Author: voine
 */



#include "TIMER.h"

void AD_TIM_Start_FreeRun(AD_TIM_RegDef_t *pTIMx, uint32_t time_ms) {
	pTIMx->CR1 &= ~TIM_CR1_CEN;
	while((pTIMx->CR1 & TIM_CR1_CEN) != 0);
	// Clear any pending update flag
	pTIMx->SR &= ~TIM_SR_UIF;

	// Configure for single countdown
	pTIMx->CNT = 0;

	pTIMx->EGR |= TIM_EGR_UG;

	pTIMx->CR1 |= TIM_CR1_CEN;
	while((pTIMx->CR1 & TIM_CR1_CEN) == 0);
	// Clear update flag
}




void AD_TIM_FreeRun_INIT(AD_TIM_Handle_t *pAD_TIM_Handle) {
    if (pAD_TIM_Handle->pTIMx == TIM1) {
        TIM1_PCLK_EN();
    }

    // Count up
    pAD_TIM_Handle->pTIMx->CR1 &= ~TIM_CR1_DIR;

    // Auto-Reload Preload
    pAD_TIM_Handle->pTIMx->CR1 |= TIM_CR1_ARPE;

    // Max ARR
    pAD_TIM_Handle->pTIMx->ARR = 0xFFFF;

    // Prescaler (set before calling or assign here)
    pAD_TIM_Handle->pTIMx->PSC = pAD_TIM_Handle->AD_TIM_Config.Prescaler;

    // Load PSC and ARR immediately
    pAD_TIM_Handle->pTIMx->EGR |= TIM_EGR_UG;

    // Start free-running timer
    pAD_TIM_Handle->pTIMx->CR1 |= TIM_CR1_CEN;
}

//TIM2 exclusivelyy used for PWM outputs now
void GP_TIM_PWM_INIT(GP_TIM_Handle_t *pGP_TIM_Handle) {
	// Enable peripheral clock
	if (pGP_TIM_Handle->pTIMx == TIM2) {
		TIM2_PCLK_EN();
	} else if (pGP_TIM_Handle->pTIMx == TIM3) {
		TIM3_PCLK_EN();
	}

	// Wait until peripheral clock is stable
	while (!(RCC->APB1ENR & (1 << 0)));

	// Timer base configuration
	pGP_TIM_Handle->pTIMx->CR1 |= TIM_CR1_ARPE;  // Enable Auto-Reload Preload
	pGP_TIM_Handle->pTIMx->PSC = pGP_TIM_Handle->GP_TIM_Config.Prescaler;
	pGP_TIM_Handle->pTIMx->ARR = pGP_TIM_Handle->GP_TIM_Config.Period - 1;

	// Configure all channels using the unified function
	for (int ch = 0; ch < 4; ch++) {
		float duty_percent = pGP_TIM_Handle->GP_TIM_Config.CH_Setup[ch].DutyCycle;
		uint16_t duty = (uint16_t)((duty_percent / 100.0f) * pGP_TIM_Handle->GP_TIM_Config.Period);
		uint8_t mode = pGP_TIM_Handle->GP_TIM_Config.CH_Setup[ch].CH_Mode;
		uint8_t enabled = pGP_TIM_Handle->GP_TIM_Config.CH_Setup[ch].CH_Enabled;

		GP_TIM_SetChannel(pGP_TIM_Handle->pTIMx, ch, duty, mode, enabled);
	}

	// Force update to load all values
	pGP_TIM_Handle->pTIMx->EGR |= (1 << 0);

}



void GP_TIM_SetChannel(GP_TIM_RegDef_t *pTIMx, uint8_t ch, uint16_t duty, uint8_t mode, uint8_t enable_output) {
	volatile uint32_t *ccmr = (ch < 2) ? &pTIMx->CCMR1 : &pTIMx->CCMR2;
	volatile uint32_t *ccr;
	uint8_t shift;
	uint32_t enable_bit;

	switch (ch) {
	case CH1: ccr = &pTIMx->CCR1; shift = 4; enable_bit = 1 << 0; break;
	case CH2: ccr = &pTIMx->CCR2; shift = 12; enable_bit = 1 << 4; break;
	case CH3: ccr = &pTIMx->CCR3; shift = 4; enable_bit = 1 << 8; break;
	case CH4: ccr = &pTIMx->CCR4; shift = 12; enable_bit = 1 << 12; break;
	default: return;
	}

	*ccr = duty;

	// Clear and set output compare mode (PWM1 or PWM2)
	*ccmr &= ~(7 << shift);
	*ccmr |= (mode == PWM1 ? 6 : 7) << shift;

	// Enable preload
	*ccmr |= (1 << (shift - 1));

	// Only enable output if requested
	if (enable_output) {
		pTIMx->CCER |= enable_bit;
	} else {
		pTIMx->CCER &= ~enable_bit;
	}
}

void GP_TIM_Control(GP_TIM_RegDef_t *pTIMx, uint8_t EN_or_DS) {
	if (EN_or_DS == ENABLE) {
		pTIMx->CR1 |= TIM_CR1_CEN;
		while((pTIMx->CR1 & TIM_CR1_CEN) == 0);
	} else {
		pTIMx->CR1 &= ~TIM_CR1_CEN;
		while((pTIMx->CR1 & TIM_CR1_CEN) == 1);
	}
}

void GP_TIM_PWM_Control(GP_TIM_Handle_t *pGP_TIM_Handle, uint8_t channel, uint8_t PWM_STATE) {
	if (channel > 3) return;

	//		uint32_t ccer_mask = (1 << (channel * 4)); // CCxE bit

	if (PWM_STATE == PWM_OUTPUT) {
		// Make sure duty is set first
		uint16_t duty = (uint16_t)((pGP_TIM_Handle->GP_TIM_Config.CH_Setup[channel].DutyCycle / 100.0f) *
				pGP_TIM_Handle->GP_TIM_Config.Period);
		switch(channel) {
		case CH1: pGP_TIM_Handle->pTIMx->CCR1 = duty; break;
		case CH2: pGP_TIM_Handle->pTIMx->CCR2 = duty; break;
		case CH3: pGP_TIM_Handle->pTIMx->CCR3 = duty; break;
		case CH4: pGP_TIM_Handle->pTIMx->CCR4 = duty; break;
		}

		//		pGP_TIM_Handle->pTIMx->CCER |= ccer_mask; // Enable output
	} else if(PWM_STATE == PWM_STOP)
	{
		uint16_t duty = 0;
		switch(channel) {
		case CH1: pGP_TIM_Handle->pTIMx->CCR1 = duty; break;
		case CH2: pGP_TIM_Handle->pTIMx->CCR2 = duty; break;
		case CH3: pGP_TIM_Handle->pTIMx->CCR3 = duty; break;
		case CH4: pGP_TIM_Handle->pTIMx->CCR4 = duty; break;
		}
	}
	else
	{
		//pGP_TIM_Handle->pTIMx->CCER &= ~ccer_mask; // Disable output
	}


}



