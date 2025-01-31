/*
 * F401RE_GPIO.h
 *
 *  Created on: Jan 27, 2025
 *      Author: voine
 */

#ifndef INC_F401RE_GPIO_H_
#define INC_F401RE_GPIO_H_

#include "STM32F401RE.h"


typedef struct{
	uint8_t GPIO_PinNumber;
	uint8_t GPIO_PinMode;
	uint8_t GPIO_PinSpeed;
	uint8_t GPIO_PinPuPdControl;
	uint8_t GPIO_PinOPType;
	uint8_t GPIO_PinAltFunMode;
}GPIO_PinConfig_t;

typedef struct{
	GPIO_RegDef_t *pGPIOx;
	GPIO_PinConfig_t GPIO_PinConfig;//THIS ISNT A REGISTER, JUST A WAY TO STORE DATA
}GPIO_Handle_t;


void GPIO_Init(GPIO_Handle_t *pGPIOHandle);
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx);


void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx,uint8_t PinNumber, uint8_t STATE);
void GPIO_ToggleOutputPin_PWM(GPIO_RegDef_t *pGPIOx,uint8_t PinNumber, uint8_t PWM);
#endif /* INC_F401RE_GPIO_H_ */
