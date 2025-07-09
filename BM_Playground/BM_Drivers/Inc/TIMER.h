/*
 * F401RE_TIMER.h
 *
 *  Created on: Jan 27, 2025
 *      Author: voine
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

#include "GPIO.h"
#include "STM32F4.h"

#define TIM_CR1_CEN     (1 << 0)
#define TIM_SR_UIF		(1 << 0)
#define TIM_CR1_ARPE    (1 << 7)
#define TIM_EGR_UG      (1 << 0)
#define TIM_CR1_URS	    (1 << 2)
#define TIM_CR1_DIR		(1 << 3)
#define TIM_DIER_UIE	(1 << 0)

#define TIM1_UP_IRQ		(1 << 25)

#define TIM1_PCLK_EN()		(RCC->APB2ENR |= (1 << 0))
#define TIM2_PCLK_EN()		(RCC->APB1ENR |= (1 << 0))
#define TIM3_PCLK_EN()		(RCC->APB1ENR |= (1 << 1))


#define CH1	0
#define CH2	1
#define CH3	2
#define CH4	3

#define PRESCALER_16K 15999
#define DutyCycle_80 80
#define DutyCycle_60 60

#define PWM_OUTPUT  1
#define PWM_OFF     0
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

void AD_TIM_Start_Countdown(AD_TIM_RegDef_t *pTIMx, uint32_t time_ms);
void GP_TIM_PWM_INIT(GP_TIM_Handle_t *pGP_TIM_Handle);
void AD_TIM_CDN_INIT(AD_TIM_Handle_t *pAD_TIM_Handle);
void GP_TIM_SetChannel(GP_TIM_RegDef_t *pTIMx, uint8_t ch, uint16_t duty, uint8_t mode, uint8_t enable_output);
void GP_TIM_Control(GP_TIM_RegDef_t *pTIMx, uint8_t EN_or_DS);
void GP_TIM_PWM_Control(GP_TIM_Handle_t *pGP_TIM_Handle, uint8_t Channel, uint8_t Enable);
#endif /* INC_TIMER_H_ */
