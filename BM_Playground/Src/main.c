/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>
#include "F401RE_GPIO.h"
#include "F401RE_TIMER.h"
#include "F401RE_RCC.h"





int main(void) {

	RCC_Handle_t RCC_Handle;
	RCC_Handle.pRCC = RCC;
	RCC_Handle.RCC_Config.CLK_Source = HSI;
	//RCC_Handle.RCC_Config.PLL_Facs.PLL_M = 16;
	//RCC_Handle.RCC_Config.PLL_Facs.PLL_N = 400;
	//RCC_Handle.RCC_Config.PLL_Facs.PLL_P = 3;
	RCC_Handle.RCC_Config.Prescalers.AHB_Presc = AHB_DIV1;
	RCC_Handle.RCC_Config.Prescalers.APB1_Presc = APB1_DIV2;
	RCC_Handle.RCC_Config.Prescalers.APB2_Presc = APB2_DIV2;
	//=> 8Mhz for peripherals, 16 for timers
	RCC_Clock_Config(&RCC_Handle);

	// Timer Configuration
	GP_TIM_Handle_t TIM2_PWM;
	TIM2_PWM.pTIMx = TIM2;
	TIM2_PWM.GP_TIM_Config.Prescaler = 4;
	TIM2_PWM.GP_TIM_Config.Period = 99;
	TIM2_PWM.GP_TIM_Config.CH_Setup[CH1].CH_Enabled = 1;
	TIM2_PWM.GP_TIM_Config.CH_Setup[CH2].CH_Enabled = 0;
	TIM2_PWM.GP_TIM_Config.CH_Setup[CH3].CH_Enabled = 0;
	TIM2_PWM.GP_TIM_Config.CH_Setup[CH4].CH_Enabled = 0;
	TIM2_PWM.GP_TIM_Config.CH_Setup[CH1].CH_Mode = PWM1;
	TIM2_PWM.GP_TIM_Config.CH_Setup[CH1].DutyCycle = DutyCycle_80;  // 80% Duty

	GP_TIM_PWM_INIT(&TIM2_PWM);
	GP_TIM_PWM_Start(&TIM2_PWM, TIM2_PWM.GP_TIM_Config.CH_Setup);

	// GPIO Configuration for TIM1 CH1 (PA8)
	GPIO_Handle_t GpioCH1;
	GpioCH1.pGPIOx = GPIOA;
	GpioCH1.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
	GpioCH1.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	GpioCH1.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH;  // Set higher speed for PWM
	GpioCH1.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GpioCH1.GPIO_PinConfig.GPIO_PinAltFunMode = 1;  // AF1 for TIM2_PWM
	GpioCH1.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;



	// Initialize GPIO
	GPIO_Init(&GpioCH1);

	/* Loop forever */
	while (1) {
		// PWM is automatically generated by hardware
	}

	return 0;
}
