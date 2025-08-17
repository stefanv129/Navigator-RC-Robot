/*
 * SPI.h
 *
 *  Created on: Aug 13, 2025
 *      Author: voine
 */

/*
 * stm32f407xx_spi_driver.h
 *
 *  Created on: Feb 9, 2019
 *      Author: admin
 */

#ifndef INC_STM32F407XX_SPI_DRIVER_H_
#define INC_STM32F407XX_SPI_DRIVER_H_

#include "STM32F4.h"
#include "GPIO.h"

#define MPU6500_PWR_MGMT_1      0x6B
#define MPU6500_SMPLRT_DIV      0x19
#define MPU6500_GYRO_CONFIG     0x1B
#define MPU6500_ACCEL_CONFIG    0x1C
#define MPU6500_GYRO_XOUT_H     0x43
#define MPU6500_GYRO_XOUT_L     0x44
#define MPU6500_GYRO_YOUT_H     0x45
#define MPU6500_GYRO_YOUT_L     0x46
#define MPU6500_GYRO_ZOUT_H     0x47
#define MPU6500_GYRO_ZOUT_L     0x48
#define MPU6500_CONFIG       	0x1A
#define MPU6500_PWR_MGMT_2 		0x6C

#define MPU6500_CS_LOW()     GPIO_Write_Pin(GPIOA, GPIO_PIN_NO_15, DISABLE)
#define MPU6500_CS_HIGH()    GPIO_Write_Pin(GPIOA, GPIO_PIN_NO_15, ENABLE)

#define GYRO_SENS_500DPS 65.5f
#define GYRO_SENS_1000DPS 32.8f
#define ACCEL_SENS_2G 16384.0f
#define GYRO_SENS_250DPS 131.0f
/*
 *  Configuration structure for SPIx peripheral
 */
typedef struct
{
	uint8_t SPI_DeviceMode;
	uint8_t SPI_BusConfig;
	uint8_t SPI_SclkSpeed;
	uint8_t SPI_DFF;
	uint8_t SPI_CPOL;
	uint8_t SPI_CPHA;
	uint8_t SPI_SSM;
}SPI_Config_t;


/*
 *Handle structure for SPIx peripheral
 */
typedef struct
{
	SPI_RegDef_t 	*pSPIx;
	SPI_Config_t 	SPIConfig;
	uint8_t 		*pTxBuffer;
	uint8_t 		*pRxBuffer;
	uint32_t 		TxLen;
	uint32_t 		RxLen;
	uint8_t 		TxState;
	uint8_t 		RxState;
}SPI_Handle_t;


/*
 * SPI application states
 */
#define SPI_READY 					0
#define SPI_BUSY_IN_RX 				1
#define SPI_BUSY_IN_TX 				2

/*
 * Possible SPI Application events
 */
#define SPI_EVENT_TX_CMPLT   1
#define SPI_EVENT_RX_CMPLT   2
#define SPI_EVENT_OVR_ERR    3
#define SPI_EVENT_CRC_ERR    4



/*
 * @SPI_DeviceMode
 */
#define SPI_DEVICE_MODE_MASTER    1
#define SPI_DEVICE_MODE_SLAVE     0


/*
 * @SPI_BusConfig
 */
#define SPI_BUS_CONFIG_FD                1
#define SPI_BUS_CONFIG_HD                2
#define SPI_BUS_CONFIG_SIMPLEX_RXONLY    3

/*
 * @SPI_SclkSpeed
 */
#define SPI_SCLK_SPEED_DIV2             	0
#define SPI_SCLK_SPEED_DIV4             	1
#define SPI_SCLK_SPEED_DIV8             	2
#define SPI_SCLK_SPEED_DIV16             	3
#define SPI_SCLK_SPEED_DIV32             	4
#define SPI_SCLK_SPEED_DIV64             	5
#define SPI_SCLK_SPEED_DIV128             	6
#define SPI_SCLK_SPEED_DIV256             	7

/*
 * @SPI_DFF
 */
#define SPI_DFF_8BITS 	0
#define SPI_DFF_16BITS  1

/*
 * @CPOL
 */
#define SPI_CPOL_HIGH 1
#define SPI_CPOL_LOW 0

/*
 * @CPHA
 */
#define SPI_CPHA_HIGH 1
#define SPI_CPHA_LOW 0

/*
 * @SPI_SSM
 */
#define SPI_SSM_EN     1
#define SPI_SSM_DI     0


/*
 * SPI related status flags definitions
 */
#define SPI_TXE_FLAG    ( 1 << SPI_SR_TXE)
#define SPI_RXNE_FLAG   ( 1 << SPI_SR_RXNE)
#define SPI_BUSY_FLAG   ( 1 << SPI_SR_BSY)



void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi);

/*
 * Init and De-init
 */
void SPI_Init(SPI_Handle_t *pSPIHandle);
void SPI_DeInit(SPI_RegDef_t *pSPIx);


/*
 * Data Send and Receive
 */
void SPI_SendData(SPI_RegDef_t *pSPIx,uint8_t *pTxBuffer, uint32_t Len);
void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t Len);

void MPU6500_Init(void);
void MPU6500_ReadRegs(uint8_t reg, uint8_t *buffer, uint8_t len);
uint8_t MPU6500_ReadReg(uint8_t reg);
void MPU6500_WriteReg(uint8_t reg, uint8_t data);
void SPI_TransferData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint8_t *pRxBuffer, uint32_t len);
void SPI_ApplicationEventCallback(SPI_Handle_t *pSPIHandle,uint8_t AppEv);
float MPU6500_Read_GyroZ_DPS(void);
void  SPI_SSIConfig(SPI_RegDef_t *pSPIx, uint8_t EnOrDi);
void  SPI_SSOEConfig(SPI_RegDef_t *pSPIx, uint8_t EnOrDi);
float MPU6500_Read_AccelX_G(void);

#endif /* INC_STM32F407XX_SPI_DRIVER_H_ */
