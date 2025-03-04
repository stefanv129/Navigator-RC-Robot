/*
 * F401RE_RCC.h
 *
 *  Created on: Jan 27, 2025
 *      Author: voine
 */

#ifndef INC_F401RE_RCC_H_
#define INC_F401RE_RCC_H_

typedef enum{
	HSI = 0,
	PLLCLK = 1,
}SYSCLK_Src_t;


typedef struct{
	int PLL_M;
	int PLL_N;
	int PLL_P;
}PLL_Factors_t;

typedef struct{
	int AHB_Presc;
	int APB1_Presc;
	int APB2_Presc;
}Bus_Prescalers_t;


typedef struct{
	SYSCLK_Src_t CLK_Source;
	PLL_Factors_t PLL_Facs;
	Bus_Prescalers_t Prescalers;
}RCC_Config_t;

typedef struct{
	RCC_RegDef_t *pRCC;
	RCC_Config_t RCC_Config;
}RCC_Handle_t;

void RCC_Clock_Config(RCC_Handle_t *pRCC_Handle_t);





#endif /* INC_F401RE_RCC_H_ */
