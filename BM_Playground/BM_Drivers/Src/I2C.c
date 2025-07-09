/*
 * I2C.c
 *
 *  Created on: Jun 24, 2025
 *      Author: voine
 */


#include "I2C.h"


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


