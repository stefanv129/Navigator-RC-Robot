/*
 * SPI.c
 *
 *  Created on: Aug 13, 2025
 *      Author: voine
 */

#include "SPI.H"



static uint8_t MPU6500_Read_WhoAmI(void) {
	uint8_t who_am_i_reg = 0x75 | 0x80; // Adresa registrului WHO_AM_I + bitul de citire
	uint8_t who_am_i_value = 0;

	MPU6500_CS_LOW();

	SPI_TransferData(SPI1, &who_am_i_reg, NULL, 1);

	SPI_TransferData(SPI1, NULL, &who_am_i_value, 1);

	MPU6500_CS_HIGH();

	return who_am_i_value;
}




void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi)
{

	if(EnorDi == ENABLE)
	{
		if(pSPIx == SPI1)
		{
			SPI1_PCLK_EN();
		}
	}
	else
	{
		//TODO
	}
}
void SPI_PeripheralControl(SPI_RegDef_t *pSPIx, uint8_t EnOrDi)
{
	if(EnOrDi == ENABLE)
	{
		pSPIx->CR1 |=  (1 << SPI_CR1_SPE);
	}else
	{
		pSPIx->CR1 &=  ~(1 << SPI_CR1_SPE);
	}


}



void SPI_Init(SPI_Handle_t *pSPIHandle)
{

	//peripheral clock enable

	SPI_PeriClockControl(pSPIHandle->pSPIx, ENABLE);

	//first lets configure the SPI_CR1 register

	uint32_t tempreg = 0;

	//1. configure the device mode
	tempreg |= pSPIHandle->SPIConfig.SPI_DeviceMode << SPI_CR1_MSTR ;

	//2. Configure the bus config
	if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_FD)
	{
		//bidi mode should be cleared
		tempreg &= ~( 1 << SPI_CR1_BIDIMODE);

	}else if (pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_HD)
	{
		//bidi mode should be set
		tempreg |= ( 1 << SPI_CR1_BIDIMODE);
	}else if (pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_SIMPLEX_RXONLY)
	{
		//BIDI mode should be cleared
		tempreg &= ~( 1 << SPI_CR1_BIDIMODE);
		//RXONLY bit must be set
		tempreg |= ( 1 << SPI_CR1_RXONLY);
	}

	// 3. Configure the spi serial clock speed (baud rate)
	tempreg |= pSPIHandle->SPIConfig.SPI_SclkSpeed << SPI_CR1_BR;

	//4.  Configure the DFF
	tempreg |= pSPIHandle->SPIConfig.SPI_DFF << SPI_CR1_DFF;

	//5. configure the CPOL
	tempreg |= pSPIHandle->SPIConfig.SPI_CPOL << SPI_CR1_CPOL;

	//6 . configure the CPHA
	tempreg |= pSPIHandle->SPIConfig.SPI_CPHA << SPI_CR1_CPHA;

	tempreg |= pSPIHandle->SPIConfig.SPI_SSM << SPI_CR1_SSM;

	pSPIHandle->pSPIx->CR1 = tempreg;

	SPI_SSIConfig(SPI1, ENABLE);

	SPI_PeripheralControl(SPI1, ENABLE);

}


void SPI_DeInit(SPI_RegDef_t *pSPIx)
{

}

uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPIx , uint32_t FlagName)
{

	if(pSPIx->SR & FlagName)
	{
		return FLAG_SET; // 1
	}
	return FLAG_RESET; // 0
}


void SPI_SendData(SPI_RegDef_t *pSPIx,uint8_t *pTxBuffer, uint32_t Len)
{
	while(Len > 0)
	{

		while(!SPI_GetFlagStatus(pSPIx, SPI_TXE_FLAG));

		if( (pSPIx->CR1 & (1 << SPI_CR1_DFF)) )
		{
			pSPIx->DR = *((uint16_t*)pTxBuffer);
			Len -= 2;
			pTxBuffer += 2;
		}
		else
		{
			pSPIx->DR = *pTxBuffer;
			Len--;
			pTxBuffer++;
		}
	}
}


void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t Len)
{
	while(Len > 0)
	{

		while(!SPI_GetFlagStatus(pSPIx, SPI_RXNE_FLAG));

		if( (pSPIx->CR1 & (1 << SPI_CR1_DFF)) )
		{
			*((uint16_t*)pRxBuffer) = pSPIx->DR;
			Len -= 2;
			pRxBuffer += 2;
		}
		else
		{
			*pRxBuffer = pSPIx->DR;
			Len--;
			pRxBuffer++;
		}
	}
}






void  SPI_SSIConfig(SPI_RegDef_t *pSPIx, uint8_t EnOrDi)
{
	if(EnOrDi == ENABLE)
	{
		pSPIx->CR1 |=  (1 << SPI_CR1_SSI);
	}else
	{
		pSPIx->CR1 &=  ~(1 << SPI_CR1_SSI);
	}


}



void  SPI_SSOEConfig(SPI_RegDef_t *pSPIx, uint8_t EnOrDi)
{
	if(EnOrDi == ENABLE)
	{
		pSPIx->CR2 |=  (1 << SPI_CR2_SSOE);
	}else
	{
		pSPIx->CR2 &=  ~(1 << SPI_CR2_SSOE);
	}


}





void SPI_CloseTransmisson(SPI_Handle_t *pSPIHandle)
{
	pSPIHandle->pSPIx->CR2 &= ~( 1 << SPI_CR2_TXEIE);
	pSPIHandle->pTxBuffer = NULL;
	pSPIHandle->TxLen = 0;
	pSPIHandle->TxState = SPI_READY;

}

void SPI_CloseReception(SPI_Handle_t *pSPIHandle)
{
	pSPIHandle->pSPIx->CR2 &= ~( 1 << SPI_CR2_RXNEIE);
	pSPIHandle->pRxBuffer = NULL;
	pSPIHandle->RxLen = 0;
	pSPIHandle->RxState = SPI_READY;

}



void SPI_ClearOVRFlag(SPI_RegDef_t *pSPIx)
{
	uint8_t temp;
	temp = pSPIx->DR;
	temp = pSPIx->SR;
	(void)temp;

}

// ANGULAR MOVEMENT MEASURING
void MPU6500_WriteReg(uint8_t reg, uint8_t data) {
	uint8_t tx_data[2];
	tx_data[0] = reg;
	tx_data[1] = data;

	MPU6500_CS_LOW();
	ms_delay(1);
	SPI_TransferData(SPI1, tx_data, NULL, 2);
	MPU6500_CS_HIGH();
}

uint8_t MPU6500_ReadReg(uint8_t reg) {
    uint8_t data = 0;
    uint8_t dummy = 0x00;

    reg |= 0x80; // bit7 = read

    MPU6500_CS_LOW();
    ms_delay(1);


    SPI_TransferData(SPI1, &reg, NULL, 1);


    SPI_TransferData(SPI1, &dummy, &data, 1);

    MPU6500_CS_HIGH();
    return data;
}

void SPI_TransferData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint8_t *pRxBuffer, uint32_t len)
{
	while (len > 0)
	{

		while(!SPI_GetFlagStatus(pSPIx, SPI_TXE_FLAG));

		if(pTxBuffer)
		{
			pSPIx->DR = *pTxBuffer;
			pTxBuffer++;
		}
		else
		{
			pSPIx->DR = 0x00; // dummy byte
		}

		while(!SPI_GetFlagStatus(pSPIx, SPI_RXNE_FLAG));

		if(pRxBuffer)
		{
			*pRxBuffer = pSPIx->DR;
			pRxBuffer++;
		}
		else
		{
			(void)pSPIx->DR;
		}

		len--;
	}
}



static void MPU6500_ReadMultiReg_SPI(uint8_t reg_addr, uint8_t *data, uint8_t len) {
    uint8_t dummy = 0x00;

    // bit7 = read
    reg_addr |= 0x80;

    MPU6500_CS_LOW();
    ms_delay(1);

    SPI_TransferData(SPI1, &reg_addr, NULL, 1);

    for (uint8_t i = 0; i < len; i++) {
        SPI_TransferData(SPI1, &dummy, &data[i], 1);
    }

    MPU6500_CS_HIGH();
}

float MPU6500_Read_GyroZ_DPS(void) {
    uint8_t gyro_data[2];
    MPU6500_ReadMultiReg_SPI(0x47, gyro_data, 2); // GYRO_ZOUT_H/L

    int16_t gyro_z_raw = (int16_t)((gyro_data[0] << 8) | gyro_data[1]);
    return ((float)gyro_z_raw) / GYRO_SENS_500DPS;
}

float MPU6500_Read_AccelX_G(void) {
	uint8_t accel_data[2];

	MPU6500_ReadMultiReg_SPI(0x3B, accel_data, 2);

	int16_t accel_x_raw = (int16_t)((accel_data[0] << 8) | accel_data[1]);

	float accel_x_g = ((float)accel_x_raw) / ACCEL_SENS_2G;

	return accel_x_g;
}


void MPU6500_Init(void) {
	uint8_t who_am_i_value = 0;
	ms_delay(400);
	MPU6500_CS_HIGH();

	who_am_i_value = MPU6500_Read_WhoAmI();


	// THIS IS THE CRITICAL CHECK
	if (who_am_i_value != 0x70) {

		while(1) {
			GPIO_Toggle_Pin(GPIOC, GPIO_PIN_NO_13);
			ms_delay(100); // Fast blink for error
		}
	}

	// Wake up device
	MPU6500_WriteReg(MPU6500_PWR_MGMT_1, 0x00);
	ms_delay(100);

	MPU6500_WriteReg(MPU6500_PWR_MGMT_2, 0x00);

	// Configure sample rate divider
	MPU6500_WriteReg(MPU6500_SMPLRT_DIV, 0x07);

	MPU6500_WriteReg(MPU6500_GYRO_CONFIG, 0x08);//0X00

	MPU6500_WriteReg(MPU6500_ACCEL_CONFIG, 0x00);

	MPU6500_WriteReg(MPU6500_CONFIG, 0x01);
	ms_delay(100);
}
