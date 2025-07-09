/*
 * I2C.h
 *
 *  Created on: Jun 24, 2025
 *      Author: voine
 */

#ifndef INC_I2C_H_
#define INC_I2C_H_

#include "STM32F4.h"

#define I2C1_PCLK_EN()		(RCC->APB1ENR |= (1 << 21))

#define I2C_CR1_ACK			(1 << 10)
#define I2C_CR1_PE			(1 << 0)
#define I2C_CR1_START		(1 << 8)
#define I2C_CR1_STOP		(1 << 9)
#define I2C_SR1_ADDR		(1 << 1)
#define I2C_SR1_RXNE		(1 << 6)
#define I2C_SR1_SB			(1 << 0)
#define I2C_SR1_TXE			(1 << 0)
#define I2C_SR1_BTF			(1 << 0)

#define I2C_SM_MODE				~(1<<15)
#define I2C_FM_MODE				(1<<15)
#define I2C_FM_SPEED_200K	200000
#define I2C_SM_SPEED_100K	100000
#define I2C_CCR_FOR_100KHZ  0x28

#define I2C_SM_SPEED_LIMIT	100000

typedef struct{
	uint32_t I2C_SCLSpeed;
	uint8_t  I2C_DeviceAddress;
	uint8_t  I2C_AckControl;
	uint8_t  I2C_FMDutyCycle;
}I2C_Config_t;

typedef struct
{
	I2C_RegDef_t 	*pI2Cx;
	I2C_Config_t 	I2C_Config;
	uint8_t 		*pTxBuffer; /* !< To store the app. Tx buffer address > */
	uint8_t 		*pRxBuffer;	/* !< To store the app. Rx buffer address > */
	uint32_t 		TxLen;		/* !< To store Tx len > */
	uint32_t 		RxLen;		/* !< To store Tx len > */
	uint8_t 		TxRxState;	/* !< To store Communication state > */
	uint8_t 		DevAddr;	/* !< To store slave/device address > */
    uint32_t        RxSize;		/* !< To store Rx size  > */
    uint8_t         Sr;			/* !< To store repeated start value  > */
}I2C_Handle_t;


void I2C_SM_INIT(I2C_Handle_t *pI2C_Handle);
uint8_t I2C_Master_Read_Reg(I2C_RegDef_t *pI2Cx, uint8_t slaveAddr, uint8_t regAddr);

#endif /* INC_I2C_H_ */
