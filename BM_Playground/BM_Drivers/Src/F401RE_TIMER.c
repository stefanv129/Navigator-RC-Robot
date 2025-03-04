/*
 * F401RE_TIMER.c
 *
 *  Created on: Jan 27, 2025
 *      Author: voine
 */



#include "F401RE_TIMER.h"
#include "F401RE_GPIO.h"

void AD_TIM_PWM_INIT(AD_TIM_Handle_t *pAD_TIM_Handle){
    if(pAD_TIM_Handle->pTIMx == TIM1){
        TIM1_PCLK_EN();
    }

    pAD_TIM_Handle->pTIMx->PSC = pAD_TIM_Handle->AD_TIM_Config.Prescaler;

    pAD_TIM_Handle->pTIMx->ARR = pAD_TIM_Handle->AD_TIM_Config.Period;  // FREQUENCY

    // Enable Auto-Reload Preload (ARPE)
    //To prevent changes in ARR from taking immediate effect (which could cause glitches)
    pAD_TIM_Handle->pTIMx->CR1 |= (1 << 7);


    // Channel 1 Setup
    if(pAD_TIM_Handle->AD_TIM_Config.CH_Setup[CH1].CH_Enabled) {
        // Check if PWM1 or PWM2 Mode

    	pAD_TIM_Handle->pTIMx->CCR1 = pAD_TIM_Handle->AD_TIM_Config.CH_Setup[CH1].DutyCycle;
        if(pAD_TIM_Handle->AD_TIM_Config.CH_Setup[CH1].CH_Mode == PWM1) {
            pAD_TIM_Handle->pTIMx->CCMR1 |= (6 << 4);  // Set PWM Mode 1 for Channel 1
        } else if(pAD_TIM_Handle->AD_TIM_Config.CH_Setup[CH1].CH_Mode == PWM2) {
        	pAD_TIM_Handle->pTIMx->CCMR1 &= ~(7 << 4);  // Clear bits
            pAD_TIM_Handle->pTIMx->CCMR1 |= (7 << 4);  // Set PWM Mode 2 for Channel 1
        }
        pAD_TIM_Handle->pTIMx->CCMR1 |= (1 << 3);  // Enable OCPE
        pAD_TIM_Handle->pTIMx->CCER |= (1 << 0);  // Enable Channel 1
    }

    // Channel 2 Setup
    if(pAD_TIM_Handle->AD_TIM_Config.CH_Setup[CH2].CH_Enabled) {
        // Check if PWM1 or PWM2 Mode
    	pAD_TIM_Handle->pTIMx->CCR2 = pAD_TIM_Handle->AD_TIM_Config.CH_Setup[CH2].DutyCycle;
        if(pAD_TIM_Handle->AD_TIM_Config.CH_Setup[CH2].CH_Mode == PWM1) {
        	pAD_TIM_Handle->pTIMx->CCMR1 &= ~(7 << 12);  // clear first
            pAD_TIM_Handle->pTIMx->CCMR1 |= (6 << 12);  // Set PWM Mode 1 for Channel 2
        } else if(pAD_TIM_Handle->AD_TIM_Config.CH_Setup[CH2].CH_Mode == PWM2) {
            pAD_TIM_Handle->pTIMx->CCMR1 |= (7 << 12);  // Set PWM Mode 2 for Channel 2
        }
        pAD_TIM_Handle->pTIMx->CCMR2 |= (1 << 11);  // Enable OCPE
        pAD_TIM_Handle->pTIMx->CCER |= (1 << 4);  // Enable Channel 2
    }

    // Channel 3 Setup
    if(pAD_TIM_Handle->AD_TIM_Config.CH_Setup[CH3].CH_Enabled) {
        // Check if PWM1 or PWM2 Mode
    	pAD_TIM_Handle->pTIMx->CCR3 = pAD_TIM_Handle->AD_TIM_Config.CH_Setup[CH3].DutyCycle;
        if(pAD_TIM_Handle->AD_TIM_Config.CH_Setup[CH3].CH_Mode == PWM1) {
        	pAD_TIM_Handle->pTIMx->CCMR2 &= ~(7 << 4);
        	pAD_TIM_Handle->pTIMx->CCMR2 |= (6 << 4);
        } else if(pAD_TIM_Handle->AD_TIM_Config.CH_Setup[CH3].CH_Mode == PWM2) {
        	pAD_TIM_Handle->pTIMx->CCMR2 |= (7 << 4);
        }
        pAD_TIM_Handle->pTIMx->CCMR2 |= (1 << 3);  // Enable OCPE
        pAD_TIM_Handle->pTIMx->CCER |= (1 << 8);  // Enable Channel 3
    }

    // Channel 4 Setup
    if(pAD_TIM_Handle->AD_TIM_Config.CH_Setup[CH4].CH_Enabled) {
        // Check if PWM1 or PWM2 Mode
    	pAD_TIM_Handle->pTIMx->CCR4 = pAD_TIM_Handle->AD_TIM_Config.CH_Setup[CH4].DutyCycle;
        if(pAD_TIM_Handle->AD_TIM_Config.CH_Setup[CH4].CH_Mode == PWM1) {
        	pAD_TIM_Handle->pTIMx->CCMR2 &= ~(7 << 12);
        	pAD_TIM_Handle->pTIMx->CCMR2 |= (6 << 12);
        } else if(pAD_TIM_Handle->AD_TIM_Config.CH_Setup[CH4].CH_Mode == PWM2) {
        	pAD_TIM_Handle->pTIMx->CCMR2 |= (7 << 12);
        }
        pAD_TIM_Handle->pTIMx->CCMR2 |= (1 << 11);  // Enable OCPE
        pAD_TIM_Handle->pTIMx->CCER |= (1 << 12);  // Enable Channel 4
    }

    pAD_TIM_Handle->pTIMx->CR1 |= (1 << 0);  // Start the timer (CEN bit)
}





void GPIO_ToggleOutputPin_PWM(GPIO_RegDef_t *pGPIOx,uint8_t PinNumber, uint8_t PWM){
	//pwm 0-100
		//AIN1 = 1
		//DELAY FOR PWM*T
		//AIN1 = 0
		//DELAY FOR PWM*T
		//is he function call delay significant?
}


