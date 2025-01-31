/*
 * F401RE_GPIO.c
 *
 *  Created on: Jan 27, 2025
 *      Author: voine
 */

#include "F401RE_GPIO.h"

//ENABLE PERIPHERAL CLOCK

void GPIO_Init(GPIO_Handle_t *pGPIOHandle){

}
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx){

}

void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx,uint8_t PinNumber, uint8_t STATE){

}

void GPIO_ToggleOutputPin_PWM(GPIO_RegDef_t *pGPIOx,uint8_t PinNumber, uint8_t PWM){
	//pwm 0-100
		//AIN1 = 1
		//DELAY FOR PWM*T
		//AIN1 = 0
		//DELAY FOR PWM*T
		//is he function call delay significant?
}
