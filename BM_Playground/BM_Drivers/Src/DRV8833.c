/*
 * DRV8833.c
 *
 *  Created on: Jan 26, 2025
 *      Author: voine
 */


#include "DRV8833.h"


#define DRV8833_FREQ	20000
#define TURN_TIME_MIN 50
#define TURN_TIME_MAX 200
#define TIMER_DELAY 100

//can use functions from gpio drivers!!

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
}

void MotorInputs_INIT(DRV8833_Inputs_t *motor_inputs){
	//need PERICLOCKCTRL AND GPIO INIT FOR THIS
}

void turn_RANDOM(DRV8833_Inputs_t *motor_inputs){
	//we consider AIN2 and BIN2 0
	//choose right or left direction based on random number
	//for example random_number(0, 10)
	//5 > => right so drive left wheel FWD (and maybe right wheel BWD)
	//do this with a timer for a random amount of time(very short so it doesnt 180)
	//we will need to see how much time it takes for a 180 turn to avoid it
	//random_number(0, x)
	//need to use interrupts with timer yet again
	 uint8_t turn_time_ms = calc_turn_time(); // Get random turn time
	 uint8_t direction = choose_direction(); // Get random direction
	 turn_x_degrees(pGPIOx1,PinNumber1, pGPIOx2, PinNumber2, direction, turn_time_ms);
	 //WE ALSO NEED THE REAL ANGLE TO CALC COORDINATES
}

void turn_x_degrees(DRV8833_Inputs_t *motor_inputs, uint8_t direction, uint8_t turn_time_ms){
	//angle is angular velocity * time taken
	//angle should be between 0-145 degrees
	//TIMER IS SET BASED ON turn_time_ms
	uint8_t timer = 100;
	if(direction){//RIGHT
		//START TIMER HERE

		GPIO_WriteToOutputPin(&pGPIOx2,PinNumber2, RESET);// to set BIN1 off
		while(timer){
			//AIN1 = 1;BIN1 = 0;
			GPIO_ToggleOutputPin_PWM(&pGPIOx1,PinNumber1, 70);//pwm constant?
		}
	}
	else{//LEFT
		//START TIMER HERE
		GPIO_WriteToOutputPin(&pGPIOx1,PinNumber1, RESET);// to set AIN1 off
		while(timer){
			GPIO_ToggleOutputPin_PWM(pGPIOx2,PinNumber2, 70);
		}
	}

	//ANGLE GLOBAL VARIABLE IS RECALCULAED HERE!!!!!!!

	GPIO_WriteToOutputPin(pGPIOx1,PinNumber1, RESET);//STOP BOTH MOTORS
	GPIO_WriteToOutputPin(pGPIOx2,PinNumber2, RESET);//GO BACK TO DRIVE FWD
	//is it a problem that thes functions are not called simultanously?
	//AIN1 = 0;BIN1 = 0;	 */
}

void drive_FWD(DRV8833_Inputs_t *motor_inputs, uint8_t PWM){
	//4 gpio ports and pins so maybe use a structure as input that holds everything

	//drive FWD forever, loop breaks if sensor does interrupt
	//maybe use while(drive_condition)
	//interrupt will have many tasks, one of them to run turn_random function
	//*pGPIOx1 AIN1,*pGPIOx3 BIN1
	//HOW DO WE MAKE BOTH INPUTS RISE SIMULTANOUSLY?
	//we can use same GND pin for AIN2 BIN2
	//AIN2 = 0 BIN2 = 0
	//EXAMPLE:
	//LOOP
	//AIN1 = 1; BIN1 = 1;
	//DELAY FOR PWM*T
	//AIN1 = 0; BIN1 = 0;
	//DELAY FOR (1-PWM)*T
	//use Toggle_Pin

	//INCREMENT THE X Y COORDINATES BASE DON PHYSICAL ANGLE
	//whenever angle is changed modify the global variable
	//implement in giro driver file


	//when sensor gives Interrupt via I2C turn_Random is ran
}








