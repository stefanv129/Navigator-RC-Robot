/*
 * I2C.c
 *
 *  Created on: Jun 24, 2025
 *      Author: voine
 */


#include "I2C.h"

static void  I2C_GenerateStartCondition(I2C_RegDef_t *pI2Cx);
static void I2C_ExecuteAddressPhaseWrite(I2C_RegDef_t *pI2Cx, uint8_t SlaveAddr);
static void I2C_ExecuteAddressPhaseRead(I2C_RegDef_t *pI2Cx, uint8_t SlaveAddr);
static void I2C_ClearADDRFlag(I2C_Handle_t *pI2CHandle);


static void I2C_GenerateStartCondition(I2C_RegDef_t *pI2Cx)
{
	pI2Cx->CR1 |= ( 1 << I2C_CR1_START);
}


static void I2C_ExecuteAddressPhaseWrite(I2C_RegDef_t *pI2Cx, uint8_t SlaveAddr)
{
	SlaveAddr = SlaveAddr << 1;
	SlaveAddr &= ~(1); //SlaveAddr is Slave address + r/nw bit=0
	pI2Cx->DR = SlaveAddr;
}


static void I2C_ExecuteAddressPhaseRead(I2C_RegDef_t *pI2Cx, uint8_t SlaveAddr)
{
	SlaveAddr = SlaveAddr << 1;
	SlaveAddr |= 1; //SlaveAddr is Slave address + r/nw bit=1
	pI2Cx->DR = SlaveAddr;
}


static void I2C_ClearADDRFlag(I2C_Handle_t *pI2CHandle )
{
	uint32_t dummy_read;
	//check for device mode
	if(pI2CHandle->pI2Cx->SR2 & ( 1 << I2C_SR2_MSL))
	{
		//device is in master mode
		if(pI2CHandle->TxRxState == I2C_BUSY_IN_RX)
		{
			if(pI2CHandle->RxSize  == 1)
			{
				//first disable the ack
				I2C_ManageAcking(pI2CHandle->pI2Cx,DISABLE);

				//clear the ADDR flag ( read SR1 , read SR2)
				dummy_read = pI2CHandle->pI2Cx->SR1;
				dummy_read = pI2CHandle->pI2Cx->SR2;
				(void)dummy_read;
			}

		}
		else
		{
			//clear the ADDR flag ( read SR1 , read SR2)
			dummy_read = pI2CHandle->pI2Cx->SR1;
			dummy_read = pI2CHandle->pI2Cx->SR2;
			(void)dummy_read;

		}

	}
	else
	{
		//device is in slave mode
		//clear the ADDR flag ( read SR1 , read SR2)
		dummy_read = pI2CHandle->pI2Cx->SR1;
		dummy_read = pI2CHandle->pI2Cx->SR2;
		(void)dummy_read;
	}


}


void I2C_GenerateStopCondition(I2C_RegDef_t *pI2Cx)
{
	pI2Cx->CR1 |= ( 1 << I2C_CR1_STOP);
}



void I2C_PeripheralControl(I2C_RegDef_t *pI2Cx, uint8_t EnOrDi)
{
	if(EnOrDi == ENABLE)
	{
		pI2Cx->CR1 |= (1 << I2C_CR1_PE);
		//pI2cBaseAddress->CR1 |= I2C_CR1_PE_Bit_Mask;
	}else
	{
		pI2Cx->CR1 &= ~(1 << 0);
	}

}

void I2C_PeriClockControl(I2C_RegDef_t *pI2Cx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		I2C1_PCLK_EN();

	}
	else
	{
		//TODO
	}

}


void I2C_SM_INIT(I2C_Handle_t *pI2CHandle)
{
	// 1. Enable peripheral clock
	I2C1_PCLK_EN();  // You can make this generic with pI2CHandle->pI2Cx

	// 2. Configure ACK
	pI2CHandle->pI2Cx->CR1 |= (pI2CHandle->I2C_Config.I2C_AckControl << 10); // Bit 10 = ACK

	// 3. Set peripheral clock frequency in MHz (FREQ in CR2[5:0])
	pI2CHandle->pI2Cx->CR2 = (APB1_CLOCK_FREQ_MHZ & 0x3F); // e.g., 16 MHz → write 0x10

	// 4. Configure CCR for Standard Mode
	uint16_t ccr_val = APB1_CLOCK_FREQ / (2 * pI2CHandle->I2C_Config.I2C_SCLSpeed);
	pI2CHandle->pI2Cx->CCR = (ccr_val & 0xFFF); // Standard mode, 12-bit CCR

	// 5. Set TRISE
	// TRISE = FREQ_MHz + 1 for Standard Mode (max rise time = 1000ns)
	pI2CHandle->pI2Cx->TRISE = APB1_CLOCK_FREQ_MHZ + 1;

	// 6. Enable the peripheral
	pI2CHandle->pI2Cx->CR1 |= I2C_CR1_PE;
}

uint8_t I2C_Master_Read_Reg(I2C_RegDef_t *pI2Cx, uint8_t slaveAddr, uint8_t regAddr)
{
	uint8_t data;

	// 1. Start
	pI2Cx->CR1 |= I2C_CR1_START;
	while (!(pI2Cx->SR1 & I2C_SR1_SB));
	(void)pI2Cx->SR1;

	// 2. Send address with write bit
	pI2Cx->DR = (slaveAddr << 1);
	while (!(pI2Cx->SR1 & I2C_SR1_ADDR));
	(void)pI2Cx->SR1;
	(void)pI2Cx->SR2;

	// 3. Send register address
	while (!(pI2Cx->SR1 & I2C_SR1_TXE));
	pI2Cx->DR = regAddr;
	while (!(pI2Cx->SR1 & I2C_SR1_BTF)); // Wait for reg addr sent

	// 4. Repeated start
	pI2Cx->CR1 |= I2C_CR1_START;
	while (!(pI2Cx->SR1 & I2C_SR1_SB));
	(void)pI2Cx->SR1;

	// 5. Send address with read bit
	pI2Cx->DR = (slaveAddr << 1) | 1;
	while (!(pI2Cx->SR1 & I2C_SR1_ADDR));

	// 6. Disable ACK, clear ADDR
	pI2Cx->CR1 &= ~I2C_CR1_ACK;
	(void)pI2Cx->SR1;
	(void)pI2Cx->SR2;

	// 7. Read data
	while (!(pI2Cx->SR1 & I2C_SR1_RXNE));
	data = pI2Cx->DR;

	// 8. Stop
	pI2Cx->CR1 |= I2C_CR1_STOP;

	return data;
}


//I2C_Master_Write_Reg(I2C1, 0x68, 0x6B, 0x00);  // Write 0x00 to PWR_MGMT_1
//uint8_t id = I2C_Master_Read_Reg(I2C1, 0x68, 0x75);  // Should return 0x68
//
//uint8_t accel_raw[6];
//for (int i = 0; i < 6; i++) {
//    accel_raw[i] = I2C_Master_Read_Reg(I2C1, 0x68, 0x3B + i);
//}
//int16_t accel_x = (accel_raw[0] << 8) | accel_raw[1];
//int16_t accel_y = (accel_raw[2] << 8) | accel_raw[3];
//int16_t accel_z = (accel_raw[4] << 8) | accel_raw[5];

//float gyro_x_dps = gyro_x / 131.0f;  // if default ±250°/s range

//0x43 → GYRO_XOUT_H
//0x44 → GYRO_XOUT_L
//0x45 → GYRO_YOUT_H
//0x46 → GYRO_YOUT_L
//0x47 → GYRO_ZOUT_H
//0x48 → GYRO_ZOUT_L


uint8_t I2C_GetFlagStatus(I2C_RegDef_t *pI2Cx , uint32_t FlagName)
{
	if(pI2Cx->SR1 & FlagName)
	{
		return FLAG_SET;
	}
	return FLAG_RESET;
}

void I2C_MasterSendData(I2C_Handle_t *pI2CHandle,uint8_t *pTxbuffer, uint32_t Len, uint8_t SlaveAddr,uint8_t Sr)
{
	// 1. Generate the START condition
	I2C_GenerateStartCondition(pI2CHandle->pI2Cx);

	//2. confirm that start generation is completed by checking the SB flag in the SR1
	//   Note: Until SB is cleared SCL will be stretched (pulled to LOW)
	while( !  I2C_GetFlagStatus(pI2CHandle->pI2Cx,I2C_FLAG_SB)   );

	//3. Send the address of the slave with r/nw bit set to w(0) (total 8 bits )
	I2C_ExecuteAddressPhaseWrite(pI2CHandle->pI2Cx,SlaveAddr);

	//4. Confirm that address phase is completed by checking the ADDR flag in teh SR1
	while( !  I2C_GetFlagStatus(pI2CHandle->pI2Cx,I2C_FLAG_ADDR)   );

	//5. clear the ADDR flag according to its software sequence
	//   Note: Until ADDR is cleared SCL will be stretched (pulled to LOW)
	I2C_ClearADDRFlag(pI2CHandle);

	//6. send the data until len becomes 0

	while(Len > 0)
	{
		while(! I2C_GetFlagStatus(pI2CHandle->pI2Cx,I2C_FLAG_TXE) ); //Wait till TXE is set
		pI2CHandle->pI2Cx->DR = *pTxbuffer;
		pTxbuffer++;
		Len--;
	}

	//7. when Len becomes zero wait for TXE=1 and BTF=1 before generating the STOP condition
	//   Note: TXE=1 , BTF=1 , means that both SR and DR are empty and next transmission should begin
	//   when BTF=1 SCL will be stretched (pulled to LOW)

	while(! I2C_GetFlagStatus(pI2CHandle->pI2Cx,I2C_FLAG_TXE) );

	while(! I2C_GetFlagStatus(pI2CHandle->pI2Cx,I2C_FLAG_BTF) );


	//8. Generate STOP condition and master need not to wait for the completion of stop condition.
	//   Note: generating STOP, automatically clears the BTF
	if(Sr == I2C_DISABLE_SR )
		I2C_GenerateStopCondition(pI2CHandle->pI2Cx);

}


void I2C_MasterReceiveData(I2C_Handle_t *pI2CHandle,uint8_t *pRxBuffer, uint8_t Len, uint8_t SlaveAddr,uint8_t Sr)
{

	//1. Generate the START condition
	I2C_GenerateStartCondition(pI2CHandle->pI2Cx);

	//2. confirm that start generation is completed by checking the SB flag in the SR1
	//   Note: Until SB is cleared SCL will be stretched (pulled to LOW)
	while( !  I2C_GetFlagStatus(pI2CHandle->pI2Cx,I2C_FLAG_SB)   );

	//3. Send the address of the slave with r/nw bit set to R(1) (total 8 bits )
	I2C_ExecuteAddressPhaseRead(pI2CHandle->pI2Cx,SlaveAddr);

	//4. wait until address phase is completed by checking the ADDR flag in teh SR1
	while( !  I2C_GetFlagStatus(pI2CHandle->pI2Cx,I2C_FLAG_ADDR)   );


	//procedure to read only 1 byte from slave
	if(Len == 1)
	{
		//Disable Acking
		I2C_ManageAcking(pI2CHandle->pI2Cx,I2C_ACK_DISABLE);


		//clear the ADDR flag
		I2C_ClearADDRFlag(pI2CHandle);

		//wait until  RXNE becomes 1
		while(! I2C_GetFlagStatus(pI2CHandle->pI2Cx,I2C_FLAG_RXNE) );

		//generate STOP condition
		if(Sr == I2C_DISABLE_SR )
			I2C_GenerateStopCondition(pI2CHandle->pI2Cx);

		//read data in to buffer
		*pRxBuffer = pI2CHandle->pI2Cx->DR;

	}


	//procedure to read data from slave when Len > 1
	if(Len > 1)
	{
		//clear the ADDR flag
		I2C_ClearADDRFlag(pI2CHandle);

		//read the data until Len becomes zero
		for ( uint32_t i = Len ; i > 0 ; i--)
		{
			//wait until RXNE becomes 1
			while(! I2C_GetFlagStatus(pI2CHandle->pI2Cx,I2C_FLAG_RXNE) );

			if(i == 2) //if last 2 bytes are remaining
			{
				//Disable Acking
				I2C_ManageAcking(pI2CHandle->pI2Cx,I2C_ACK_DISABLE);

				//generate STOP condition
				if(Sr == I2C_DISABLE_SR )
					I2C_GenerateStopCondition(pI2CHandle->pI2Cx);

			}

			//read the data from data register in to buffer
			*pRxBuffer = pI2CHandle->pI2Cx->DR;

			//increment the buffer address
			pRxBuffer++;

		}

	}

	//re-enable ACKing
	if(pI2CHandle->I2C_Config.I2C_AckControl == I2C_ACK_ENABLE)
	{
		I2C_ManageAcking(pI2CHandle->pI2Cx,I2C_ACK_ENABLE);
	}

}


void I2C_ManageAcking(I2C_RegDef_t *pI2Cx, uint8_t EnorDi)
{
	if(EnorDi == I2C_ACK_ENABLE)
	{
		//enable the ack
		pI2Cx->CR1 |= ( 1 << I2C_CR1_ACK);
	}else
	{
		//disable the ack
		pI2Cx->CR1 &= ~( 1 << I2C_CR1_ACK);
	}
}
