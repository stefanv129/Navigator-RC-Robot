/*
 * F401RE_TIMER.c
 *
 *  Created on: Jan 27, 2025
 *      Author: voine
 */



#include "F401RE_TIMER.h"

//TIM2 exclusivelyy used for PWM outputs now
void GP_TIM_PWM_INIT(GP_TIM_Handle_t *pGP_TIM_Handle) {

	if (pGP_TIM_Handle->pTIMx == TIM2) {
		TIM2_PCLK_EN();
	}else if(pGP_TIM_Handle->pTIMx == TIM3){
		TIM3_PCLK_EN();
	}
	while (!(RCC->APB1ENR & (1 << 0))) {}
	//WAIT A BIT

	// Enable Auto-Reload Preload (ARPE)
	pGP_TIM_Handle->pTIMx->CR1 |= (1 << 7);  // ARPE: Auto-Reload Preload Enable

	// Set Prescaler & Auto-Reload Value
	pGP_TIM_Handle->pTIMx->PSC = pGP_TIM_Handle->GP_TIM_Config.Prescaler;
	pGP_TIM_Handle->pTIMx->ARR = (pGP_TIM_Handle->GP_TIM_Config.Period - 1);  // Frequency

	// Configure PWM Channels
	for (int ch = 0; ch < 4; ch++) {
		if (pGP_TIM_Handle->GP_TIM_Config.CH_Setup[ch].CH_Enabled) {
			uint16_t dutyCycle = pGP_TIM_Handle->GP_TIM_Config.CH_Setup[ch].DutyCycle;
			dutyCycle = (uint16_t)(((float)dutyCycle / 100) * pGP_TIM_Handle->GP_TIM_Config.Period); // ex.(50/100)
			//79 result here
			switch (ch) {
			case CH1:
				pGP_TIM_Handle->pTIMx->CCR1 = dutyCycle;
				pGP_TIM_Handle->pTIMx->CCMR1 &= ~(7 << 4);
				pGP_TIM_Handle->pTIMx->CCMR1 |= (pGP_TIM_Handle->GP_TIM_Config.CH_Setup[ch].CH_Mode == PWM1) ? (6 << 4) : (7 << 4);
				pGP_TIM_Handle->pTIMx->CCMR1 |= (1 << 3); // Enable Output Compare Preload
				break;

			case CH2:
				pGP_TIM_Handle->pTIMx->CCR2 = dutyCycle;
				pGP_TIM_Handle->pTIMx->CCMR1 &= ~(7 << 12);
				pGP_TIM_Handle->pTIMx->CCMR1 |= (pGP_TIM_Handle->GP_TIM_Config.CH_Setup[ch].CH_Mode == PWM1) ? (6 << 12) : (7 << 12);
				pGP_TIM_Handle->pTIMx->CCMR1 |= (1 << 11); // Enable Output Compare Preload
				break;

			case CH3:
				pGP_TIM_Handle->pTIMx->CCR3 = dutyCycle;
				pGP_TIM_Handle->pTIMx->CCMR2 &= ~(7 << 4);
				pGP_TIM_Handle->pTIMx->CCMR2 |= (pGP_TIM_Handle->GP_TIM_Config.CH_Setup[ch].CH_Mode == PWM1) ? (6 << 4) : (7 << 4);
				pGP_TIM_Handle->pTIMx->CCMR2 |= (1 << 3); // Enable Output Compare Preload
				break;

			case CH4:
				pGP_TIM_Handle->pTIMx->CCR4 = dutyCycle;
				pGP_TIM_Handle->pTIMx->CCMR2 &= ~(7 << 12);
				pGP_TIM_Handle->pTIMx->CCMR2 |= (pGP_TIM_Handle->GP_TIM_Config.CH_Setup[ch].CH_Mode == PWM1) ? (6 << 12) : (7 << 12);
				pGP_TIM_Handle->pTIMx->CCMR2 |= (1 << 11); // Enable Output Compare Preload
				break;
			}
		}
	}
	//pGP_TIM_Handle->pTIMx->CR1 |= (1 << 0); NOT NECESSARY BEACUSE PWM START DOES IT
}

void GP_TIM_PWM_Start(GP_TIM_Handle_t *pGP_TIM_Handle, uint8_t channel) {
	// Enable the main output (MOE) for Advanced Timers (TIM1)
	//pGP_TIM_Handle->pTIMx->BDTR |= (1 << 15);  // MOE Bit in BDTR

	// Enable the selected PWM channel
	switch (channel) {
	case CH1:
		pGP_TIM_Handle->pTIMx->CCER |= (1 << 0);  // Enable CH1 (CC1E)
		break;
	case CH2:
		pGP_TIM_Handle->pTIMx->CCER |= (1 << 4);  // Enable CH2 (CC2E)
		break;
	case CH3:
		pGP_TIM_Handle->pTIMx->CCER |= (1 << 8);  // Enable CH3 (CC3E)
		break;
	case CH4:
		pGP_TIM_Handle->pTIMx->CCER |= (1 << 12); // Enable CH4 (CC4E)
		break;

		// Enable the Timer Counter (CEN Bit)
		pGP_TIM_Handle->pTIMx->CR1 |= (1 << 0);  // Start the Timer (CEN Bit)
	}
}

void GP_TIM_PWM_Change_State(GP_TIM_Handle_t *pTIM_Handle, uint8_t Channel, uint8_t State){
	//briefly disable timer
	//0 1 2 3
	if(State == PWM_OUTPUT){
		pTIM_Handle->pTIMx->CCER |= (1 << (Channel * 4));  // Enable CH (CC1E)
		//ADD WAIT
	}
	else{
		pTIM_Handle->pTIMx->CCER &= ~(1 << (Channel * 4));  // Ground CH (CC1E)
		//ADD WAIT
	}


}
