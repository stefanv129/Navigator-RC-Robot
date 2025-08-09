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


#define I2C_CR1_PE			0
#define I2C_CR1_START		8
#define I2C_CR1_STOP		9
#define I2C_CR1_ACK			10

#define I2C_SR1_SB			0
#define I2C_SR1_ADDR		1
#define I2C_SR1_BTF			2
#define I2C_SR1_RXNE		6
#define I2C_SR1_TXE			7


#define I2C_SM_MODE				~(1<<15)
#define I2C_FM_MODE				(1<<15)
#define I2C_FM_SPEED_200K	200000
#define I2C_SM_SPEED_100K	100000
#define I2C_CCR_FOR_100KHZ  0x28

#define I2C_SM_SPEED_LIMIT	100000

#define I2C_READY 					0
#define I2C_BUSY_IN_RX 				1
#define I2C_BUSY_IN_TX 				2

/*
 * @I2C_SCLSpeed
 */
#define I2C_SCL_SPEED_SM 	100000
#define I2C_SCL_SPEED_FM4K 	400000
#define I2C_SCL_SPEED_FM2K  200000


/*
 * @I2C_AckControl
 */
#define I2C_ACK_ENABLE        1
#define I2C_ACK_DISABLE       0


/*
 * @I2C_FMDutyCycle
 */
#define I2C_FM_DUTY_2        0
#define I2C_FM_DUTY_16_9     1


/*
 * I2C related status flags definitions
 */
#define I2C_FLAG_TXE   		( 1 << I2C_SR1_TXE)
#define I2C_FLAG_RXNE   	( 1 << I2C_SR1_RXNE)
#define I2C_FLAG_SB			( 1 << I2C_SR1_SB)
#define I2C_FLAG_OVR  		( 1 << I2C_SR1_OVR)
#define I2C_FLAG_AF   		( 1 << I2C_SR1_AF)
#define I2C_FLAG_ARLO 		( 1 << I2C_SR1_ARLO)
#define I2C_FLAG_BERR 		( 1 << I2C_SR1_BERR)
#define I2C_FLAG_STOPF 		( 1 << I2C_SR1_STOPF)
#define I2C_FLAG_ADD10 		( 1 << I2C_SR1_ADD10)
#define I2C_FLAG_BTF  		( 1 << I2C_SR1_BTF)
#define I2C_FLAG_ADDR 		( 1 << I2C_SR1_ADDR)
#define I2C_FLAG_TIMEOUT 	( 1 << I2C_SR1_TIMEOUT)

#define I2C_DISABLE_SR  	RESET
#define I2C_ENABLE_SR   	SET


/*
 * I2C application events macros
 */
#define I2C_EV_TX_CMPLT  	 	0
#define I2C_EV_RX_CMPLT  	 	1
#define I2C_EV_STOP       		2
#define I2C_ERROR_BERR 	 		3
#define I2C_ERROR_ARLO  		4
#define I2C_ERROR_AF    		5
#define I2C_ERROR_OVR   		6
#define I2C_ERROR_TIMEOUT 		7
#define I2C_EV_DATA_REQ         8
#define I2C_EV_DATA_RCV         9

#define I2C_SR2_MSL				0

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

void I2C_ManageAcking(I2C_RegDef_t *pI2Cx, uint8_t EnorDi);
void I2C_MasterReceiveData(I2C_Handle_t *pI2CHandle,uint8_t *pRxBuffer, uint8_t Len, uint8_t SlaveAddr,uint8_t Sr);
void I2C_MasterSendData(I2C_Handle_t *pI2CHandle,uint8_t *pTxbuffer, uint32_t Len, uint8_t SlaveAddr,uint8_t Sr);

void I2C_PeripheralControl(I2C_RegDef_t *pI2Cx, uint8_t EnOrDi);
uint8_t I2C_GetFlagStatus(I2C_RegDef_t *pI2Cx , uint32_t FlagName);
void I2C_ManageAcking(I2C_RegDef_t *pI2Cx, uint8_t EnorDi);
void I2C_GenerateStopCondition(I2C_RegDef_t *pI2Cx);

#endif /* INC_I2C_H_ */
