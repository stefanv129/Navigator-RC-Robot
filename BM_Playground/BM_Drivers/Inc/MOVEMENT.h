/*
 * DRV8833.h
 *
 *  Created on: Jan 26, 2025
 *      Author: voine
 */

#ifndef INC_DRV8833_H_
#define INC_DRV8833_H_

#include "GPIO.h"
#include <stdlib.h> //for rand()
#include "STM32F4.h"
#include "TIMER.h"

typedef struct {
    GPIO_RegDef_t *Port;
    uint8_t Pin;   // Pin number
}MotorPin_t;

typedef struct {
    MotorPin_t AIN1;  // Input pin for motor A direction
    MotorPin_t AIN2;  // Input pin for motor A reverse
    MotorPin_t BIN1;  // Input pin for motor B direction
    MotorPin_t BIN2;  // Input pin for motor B reverse
}DRV8833_Inputs_t;

void MotorInputs_INIT(DRV8833_Inputs_t *motor_inputs);

void seed_random(uint32_t seed_value);
uint8_t calc_turn_time();
uint8_t choose_direction();


void drive_FWD(GP_TIM_Handle_t *pGP_TIM_Handle);
void turn_RGT(GP_TIM_Handle_t *pGP_TIM_Handle);
void turn_LFT(GP_TIM_Handle_t *pGP_TIM_Handle);
void go_IDLE(GP_TIM_Handle_t *pGP_TIM_Handle);

//typedef enum {
//    SEARCH_STATE,
//    TURN_STATE,
//    IDLE_STATE
//} RobotState_t;
//
//volatile RobotState_t current_state = IDLE_STATE;
//
//typedef struct {
//    float x;
//    float y;
//    float heading_deg;
//} Position_t;
//
//volatile Position_t current_pos;

#endif /* INC_DRV8833_H_ */
