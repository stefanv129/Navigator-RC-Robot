/*
 * F401RE_TIMER.h
 *
 *  Created on: Jan 27, 2025
 *      Author: voine
 */

#ifndef INC_F401RE_TIMER_H_
#define INC_F401RE_TIMER_H_

#include "F401RE_GPIO.h"


#define TIM1_PCLK_EN()		(RCC->APB2ENR |= (1 << 0))
#define TIM2_PCLK_EN()		(RCC->APB1ENR |= (1 << 0))

#define CH1	0
#define CH2	1
#define CH3	2
#define CH4	3

#define DutyCycle_80 80

#define PWM_OUTPUT  1
#define GND 		0


#define ACTIVE_HIGH	1
#define UP_COUNTER  0


//ADVANCED TIMERS SHOULD BE SEPARATED FROM GP
//Currently only configured for PWM output

typedef enum{
	PWM1 = 0,
	PWM2 = 1
}CH_Mode_t;


typedef struct{
	uint8_t CH_Enabled;
	CH_Mode_t CH_Mode;
	uint16_t DutyCycle;
}TIM_Channel_t;

typedef struct{
	uint16_t Prescaler;
	uint16_t Period;//ARR value
	uint8_t CounterMode;
	uint8_t ClockDivision;
	uint8_t RepetitionCounter;
	uint8_t OC_Polarity;
	uint8_t OC_Enable;
	TIM_Channel_t CH_Setup[4];

}AD_TIM_Config_t;


typedef struct{
	AD_TIM_RegDef_t *pTIMx;
	AD_TIM_Config_t AD_TIM_Config;
}AD_TIM_Handle_t;




typedef struct{
	uint16_t Prescaler;
	uint16_t Period;//ARR value
	uint8_t CounterMode;
	uint8_t ClockDivision;
	uint8_t OC_Polarity;
	uint8_t OC_Enable;
	TIM_Channel_t CH_Setup[4];

}GP_TIM_Config_t;


typedef struct{
	GP_TIM_RegDef_t *pTIMx;
	GP_TIM_Config_t GP_TIM_Config;
}GP_TIM_Handle_t;

void GP_TIM_PWM_INIT(GP_TIM_Handle_t *pGP_TIM_Handle);
void GP_TIM_PWM_Start(AD_TIM_Handle_t *pGPTIM_Handle, uint8_t channel);
void GP_TIM_PWM_Change_State(GP_TIM_Handle_t *pTIM_Handle, uint8_t Channel, uint8_t State);
#endif /* INC_F401RE_TIMER_H_ */
