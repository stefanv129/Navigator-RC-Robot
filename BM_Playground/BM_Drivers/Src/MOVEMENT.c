/*
 * DRV8833.c
 *
 *  Created on: Jan 26, 2025
 *      Author: voine
 */


#include "TIMER.h"
#include "MOVEMENT.h"


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



//TREAT FUNCTIONS LIKE A STATE
void drive_FWD(GP_TIM_Handle_t *pGP_TIM_Handle){
	//GP_TIM_Control(pGP_TIM_Handle, DISABLE);
	GP_TIM_PWM_Control(pGP_TIM_Handle,CH1,PWM_OUTPUT);
	GP_TIM_PWM_Control(pGP_TIM_Handle,CH3,PWM_OUTPUT);
	GP_TIM_PWM_Control(pGP_TIM_Handle,CH2,PWM_OFF);//this doesnt stop pwm output...
	GP_TIM_PWM_Control(pGP_TIM_Handle,CH4,PWM_OFF);
	//GP_TIM_Control(pGP_TIM_Handle, ENABLE);
}

void turn_RGT(GP_TIM_Handle_t *pGP_TIM_Handle){
	GP_TIM_PWM_Control(pGP_TIM_Handle,CH1,PWM_OUTPUT);
	GP_TIM_PWM_Control(pGP_TIM_Handle,CH3,GND);
	GP_TIM_PWM_Control(pGP_TIM_Handle,CH2,GND);
	GP_TIM_PWM_Control(pGP_TIM_Handle,CH4,PWM_OUTPUT);
	//WAIT FOR CHANNEL
}

void turn_LFT(GP_TIM_Handle_t *pGP_TIM_Handle){
	GP_TIM_PWM_Control(pGP_TIM_Handle,CH1,GND);
	GP_TIM_PWM_Control(pGP_TIM_Handle,CH3,PWM_OUTPUT);
	GP_TIM_PWM_Control(pGP_TIM_Handle,CH2,PWM_OUTPUT);
	GP_TIM_PWM_Control(pGP_TIM_Handle,CH4,GND);
}

void go_IDLE(GP_TIM_Handle_t *pGP_TIM_Handle){
	GP_TIM_PWM_Control(pGP_TIM_Handle,CH1,GND);
	GP_TIM_PWM_Control(pGP_TIM_Handle,CH1,GND);
	GP_TIM_PWM_Control(pGP_TIM_Handle,CH1,GND);
	GP_TIM_PWM_Control(pGP_TIM_Handle,CH4,GND);
}


//CONTROL WILL WORK LIKE THIS, CAR ENTERS X STATE FOR Y TIME => Z TURN ANGLE
