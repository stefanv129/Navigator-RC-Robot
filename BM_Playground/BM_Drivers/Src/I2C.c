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

void I2C_Master_RX_Read(I2C_Handle_t *pI2C_Handle){

}

//void I2C_MasterReceive(I2C_TypeDef *I2Cx, uint8_t slaveAddr, uint8_t *rxBuffer, uint32_t len)
//{
//    // 1. Generate START
//    I2Cx->CR1 |= I2C_CR1_START;
//    while (!(I2Cx->SR1 & I2C_SR1_SB)); // Wait for start condition
//
//    // 2. Send slave address with read bit
//    I2Cx->DR = (slaveAddr << 1) | 1;
//    while (!(I2Cx->SR1 & I2C_SR1_ADDR)); // Wait for address to be sent
//
//    // 3. Handle address flag
//    if (len == 1)
//    {
//        // Disable ACK, clear ADDR, send STOP
//        I2Cx->CR1 &= ~I2C_CR1_ACK;
//        (void)I2Cx->SR1;
//        (void)I2Cx->SR2;
//        I2Cx->CR1 |= I2C_CR1_STOP;
//
//        while (!(I2Cx->SR1 & I2C_SR1_RXNE));
//        rxBuffer[0] = I2Cx->DR;
//    }
//    else if (len == 2)
//    {
//        // Clear ACK, set POS, clear ADDR
//        I2Cx->CR1 &= ~I2C_CR1_ACK;
//        I2Cx->CR1 |= I2C_CR1_POS;
//        (void)I2Cx->SR1;
//        (void)I2Cx->SR2;
//
//        while (!(I2Cx->SR1 & I2C_SR1_BTF));
//        I2Cx->CR1 |= I2C_CR1_STOP;
//        rxBuffer[0] = I2Cx->DR;
//        rxBuffer[1] = I2Cx->DR;
//    }
//    else
//    {
//        (void)I2Cx->SR1;
//        (void)I2Cx->SR2;
//
//        while (len > 3)
//        {
//            while (!(I2Cx->SR1 & I2C_SR1_RXNE));
//            *rxBuffer++ = I2Cx->DR;
//            len--;
//        }
//
//        // Prepare to NACK next-to-last
//        while (!(I2Cx->SR1 & I2C_SR1_BTF));
//        I2Cx->CR1 &= ~I2C_CR1_ACK;
//        *rxBuffer++ = I2Cx->DR;
//
//        while (!(I2Cx->SR1 & I2C_SR1_BTF));
//        I2Cx->CR1 |= I2C_CR1_STOP;
//        *rxBuffer++ = I2Cx->DR;
//        *rxBuffer++ = I2Cx->DR;
//    }
//
//    // Re-enable ACK for next reception
//    I2Cx->CR1 |= I2C_CR1_ACK;
//}

//we need to read from slaves
//master == receiver
