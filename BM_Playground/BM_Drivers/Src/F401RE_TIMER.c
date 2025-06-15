/*
 * F401RE_TIMER.c
 *
 *  Created on: Jan 27, 2025
 *      Author: voine
 */



#include "F401RE_TIMER.h"

void AD_TIM_Start_Countdown(AD_TIM_Handle_t *pAD_TIM_Handle, uint32_t time){
	//for general use
	//trigger interrupt when countdown ends
	//to use at beginning of turn states
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
	while (!(RCC->APB1ENR & (1 << 0))) {}

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

		GP_TIM_SetChannel(pGP_TIM_Handle, ch, duty, mode, enabled);
	}

	// Force update to load all values
	pGP_TIM_Handle->pTIMx->EGR |= (1 << 0);

}

void GP_TIM_SetChannel(GP_TIM_Handle_t *pGP_TIM_Handle, uint8_t ch, uint16_t duty, uint8_t mode, uint8_t enable_output) {
	volatile uint32_t *ccmr = (ch < 2) ? &pGP_TIM_Handle->pTIMx->CCMR1 : &pGP_TIM_Handle->pTIMx->CCMR2;
	volatile uint32_t *ccr;
	uint8_t shift;
	uint32_t enable_bit;

	switch (ch) {
	case CH1: ccr = &pGP_TIM_Handle->pTIMx->CCR1; shift = 4; enable_bit = 1 << 0; break;
	case CH2: ccr = &pGP_TIM_Handle->pTIMx->CCR2; shift = 12; enable_bit = 1 << 4; break;
	case CH3: ccr = &pGP_TIM_Handle->pTIMx->CCR3; shift = 4; enable_bit = 1 << 8; break;
	case CH4: ccr = &pGP_TIM_Handle->pTIMx->CCR4; shift = 12; enable_bit = 1 << 12; break;
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
		pGP_TIM_Handle->pTIMx->CCER |= enable_bit;
	} else {
		pGP_TIM_Handle->pTIMx->CCER &= ~enable_bit;
	}
}

void GP_TIM_Control(GP_TIM_Handle_t *pGP_TIM_Handle, uint8_t EN_or_DS) {
	if (EN_or_DS == ENABLE) {
		pGP_TIM_Handle->pTIMx->CR1 |= TIM_CR1_CEN;
	} else {
		pGP_TIM_Handle->pTIMx->CR1 &= ~TIM_CR1_CEN;
	}
}

void GP_TIM_PWM_Control(GP_TIM_Handle_t *pGP_TIM_Handle, uint8_t channel, uint8_t PWM_ON) {
	if (channel > 3) return;

	uint32_t ccer_mask = (1 << (channel * 4)); // CCxE bit

	if (PWM_ON) {
		// Make sure duty is set first
		uint16_t duty = (uint16_t)((pGP_TIM_Handle->GP_TIM_Config.CH_Setup[channel].DutyCycle / 100.0f) *
				pGP_TIM_Handle->GP_TIM_Config.Period);
		switch(channel) {
		case CH1: pGP_TIM_Handle->pTIMx->CCR1 = duty; break;
		case CH2: pGP_TIM_Handle->pTIMx->CCR2 = duty; break;
		case CH3: pGP_TIM_Handle->pTIMx->CCR3 = duty; break;
		case CH4: pGP_TIM_Handle->pTIMx->CCR4 = duty; break;
		}

		pGP_TIM_Handle->pTIMx->CCER |= ccer_mask; // Enable output
	} else {
		//uint16_t duty = 0;
		//switch(channel) {
		//case CH1: pGP_TIM_Handle->pTIMx->CCR1 = duty; break;
		//case CH2: pGP_TIM_Handle->pTIMx->CCR2 = duty; break;
		//case CH3: pGP_TIM_Handle->pTIMx->CCR3 = duty; break;
		//case CH4: pGP_TIM_Handle->pTIMx->CCR4 = duty; break;
		//}
		pGP_TIM_Handle->pTIMx->CCER &= ~ccer_mask; // Disable output
	}


}

