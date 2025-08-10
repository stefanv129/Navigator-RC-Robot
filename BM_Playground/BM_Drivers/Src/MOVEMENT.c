/*
 * DRV8833.c
 *
 *  Created on: Jan 26, 2025
 *      Author: voine
 */


#include "TIMER.h"
#include "MOVEMENT.h"
#include "GPIO.h"


#define DRV8833_FREQ	20000
#define TURN_TIME_MIN 50
#define TURN_TIME_MAX 200
#define TIMER_DELAY 100


//USE A TIMER TO SEED!!!
void seed_random(uint32_t seed_value) {
	srand(seed_value);
}

uint8_t calc_turn_time(){
	//notice min max values
	//rand needs to be seeded
	uint8_t turn_time_ms = (rand() % (200 - 50 + 1)) + 50;
	//50-200 ms angular_speed = ct degrees/ms
	return turn_time_ms;
}

uint8_t choose_direction(){
	//notice min max values
	//rand needs to be seeded
	uint8_t random_number = (rand() % (10 - 1 + 1)) + 1;
	if(random_number > 5) return 1;
	else return 0;
} //would rather turn right and left alternatively and usew random to calc he turn time => angle

void us_delay(uint32_t time_us) {
	for (volatile uint32_t i = 0; i < time_us * 3; ++i) {
		__asm__("nop");
	}
}

//TREAT FUNCTIONS LIKE A STATE
void drive_FWD(GP_TIM_Handle_t *pGP_TIM_Handle){

	pGP_TIM_Handle->pTIMx->CCER = 0;
	GPIO_Write_Pin(GPIOB, GPIO_PIN_NO_15, DISABLE);

	GP_TIM_PWM_Control(pGP_TIM_Handle,CH1,PWM_OUTPUT);
	GP_TIM_PWM_Control(pGP_TIM_Handle,CH3,PWM_OUTPUT);
	GP_TIM_PWM_Control(pGP_TIM_Handle,CH2,GND);
	GP_TIM_PWM_Control(pGP_TIM_Handle,CH4,GND);


	// Enable CH1, CH3
	pGP_TIM_Handle->pTIMx->CCER |= (1 << (4 * CH1)) | (1 << (4 * CH3));

	// Disable CH2, CH4
	pGP_TIM_Handle->pTIMx->CCER &= ~((1 << (4 * CH2)) | (1 << (4 * CH4)));


	pGP_TIM_Handle->pTIMx->EGR |= (1 << 0);

	GPIO_Write_Pin(GPIOB, GPIO_PIN_NO_15, ENABLE);//connected to sleep
}

void stop_FWD(GP_TIM_Handle_t *pGP_TIM_Handle){

	GPIO_Write_Pin(GPIOB, GPIO_PIN_NO_15, DISABLE);

	GP_TIM_PWM_Control(pGP_TIM_Handle,CH1,PWM_STOP);
	GP_TIM_PWM_Control(pGP_TIM_Handle,CH3,PWM_STOP);
	GP_TIM_PWM_Control(pGP_TIM_Handle,CH2,PWM_STOP);
	GP_TIM_PWM_Control(pGP_TIM_Handle,CH4,PWM_STOP);

	pGP_TIM_Handle->pTIMx->CCER &= ~((1 << (4 * CH2)) | (1 << (4 * CH4)) | (1 << (4 * CH1)) | (1 << (4 * CH3)));

	pGP_TIM_Handle->pTIMx->EGR |= (1 << 0);
	GPIO_Write_Pin(GPIOB, GPIO_PIN_NO_15, ENABLE);
}

void turn_RGT(GP_TIM_Handle_t *pGP_TIM_Handle){

	pGP_TIM_Handle->pTIMx->CCER = 0;
	GPIO_Write_Pin(GPIOB, GPIO_PIN_NO_15, DISABLE);

	GP_TIM_PWM_Control(pGP_TIM_Handle,CH1,PWM_OUTPUT);
	GP_TIM_PWM_Control(pGP_TIM_Handle,CH3,GND);
	GP_TIM_PWM_Control(pGP_TIM_Handle,CH2,GND);
	GP_TIM_PWM_Control(pGP_TIM_Handle,CH4,PWM_OUTPUT);

	uint32_t ccer_mask = ((1 << 4 * CH1) | (1 << 4 * CH4)) & ~((1 << 4 * CH3) | (1 << 4 * CH2));
	pGP_TIM_Handle->pTIMx->CCER |= ccer_mask;

	pGP_TIM_Handle->pTIMx->EGR |= (1 << 0);

	GPIO_Write_Pin(GPIOB, GPIO_PIN_NO_15, ENABLE);
}

void turn_LFT(GP_TIM_Handle_t *pGP_TIM_Handle){

	pGP_TIM_Handle->pTIMx->CCER = 0;
	GPIO_Write_Pin(GPIOB, GPIO_PIN_NO_15, DISABLE);

	GP_TIM_PWM_Control(pGP_TIM_Handle,CH1,GND);
	GP_TIM_PWM_Control(pGP_TIM_Handle,CH3,PWM_OUTPUT);
	GP_TIM_PWM_Control(pGP_TIM_Handle,CH2,PWM_OUTPUT);
	GP_TIM_PWM_Control(pGP_TIM_Handle,CH4,GND);

	uint32_t ccer_mask = ((1 << 4 * CH3) | (1 << 4 * CH2)) & ~((1 << 4 * CH4) | (1 << 4 * CH1));
	pGP_TIM_Handle->pTIMx->CCER |= ccer_mask;

	pGP_TIM_Handle->pTIMx->EGR |= (1 << 0);

	GPIO_Write_Pin(GPIOB, GPIO_PIN_NO_15, ENABLE);
}




//CONTROL WILL WORK LIKE THIS, CAR ENTERS X STATE FOR Y TIME => Z TURN ANGLE
