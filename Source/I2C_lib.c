#include "I2C_lib.h"


void I2C1_MasterInit(void) {
	//uint32_t clock_period = 0;

	// reset I2C1
	I2C1->CR1 |= I2C_CR1_SWRST;
	I2C1->CR1 &= ~I2C_CR1_SWRST;

	I2C1->CR1 &= ~I2C_CR1_PE; // Disable Peripheral

	//	Program the peripheral input clock in I2C_CR2 Register
	//	in order to generate correct timings
	I2C1->CR2 |= CLOCK_FREQ; // 16MHz
	//clock_period = 62; // (1 / FREQ) ns

	//  Configure the clock control registers
	//  Calculations:
	//  100KHz = 10us = T_high + T_low = 5us + 5us
	//  T_high / clock_period = 5us / 62.5ns = 80 = 0x50
	//  88KHz = 11.3us = T_high + T_low = 5.6 + 5.6
	//  T_high / clock_period = 5.6us / 62.5ns = 90 = 0x5A
	I2C1->CCR = 0x50; // Standard mode (100KHz)

	//  Configure the rise time register
	I2C1->TRISE = T_RISE; // (300 / 62.5)+1 = 5.8

	// Own Address
	I2C1->OAR1 |= (0x32<<1);

	//  Program the I2C_CR1 register to enable the peripheral
	//I2C1->CR1 |= I2C_CR1_ACK; // Enable ACK bit
	I2C1->CR1 |= I2C_CR1_PE; // Enable Peripheral
}


void I2C1_start(void) {
	//  Set the START bit in the I2C_CR1 register
	//  to generate a Start condition
	I2C1->CR1 |= I2C_CR1_ACK;
	I2C1->CR1 |= I2C_CR1_START;

	while (!(I2C1->SR1 & I2C_SR1_SB)); // wait until generation is complete
}


void I2C1_address(uint8_t address) {
	uint16_t reg;

	I2C1->DR = address; // writes in the data register;

	while (!(I2C1->SR1 & I2C_SR1_ADDR)); // wait until address is sent
	reg = I2C1->SR1 | I2C1->SR2;         // reads status registers
	while (!(I2C1->SR1 & I2C_SR1_TXE));  // wait until transmission is complete
}


void I2C1_send(uint8_t out) {
	I2C1->DR = out; // writes in the data register

	while (!(I2C1->SR1 & I2C_SR1_BTF)); // wait until byte is received
	while (!(I2C1->SR1 & I2C_SR1_TXE));  // wait until transmission is complete
}


void I2C1_stop(void) {
	I2C1->CR1 |= I2C_CR1_STOP; // generates STOP bit
}

void I2C1_Write (uint8_t Address, uint8_t Reg, uint8_t Data) {
	I2C1_start();
	I2C1_address(Address);
	I2C1_send(Reg);
	I2C1_send(Data);
	I2C1_stop();
}