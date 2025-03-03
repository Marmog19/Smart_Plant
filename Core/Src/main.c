/// Smart Plant
// This Microcontroller will receive data from:
//
// - The soil moisture sensor in the plant in the form of
//   Resistance: 0-300 = Dry; 300-700 = Humid; 700-1000= Water
//   Using UART or ADC readings
//
// - The Light sensor (Digital or Analog??)
//
// - The Air Temperature & Humidity Digital Sensor with I2C
//
//   The I2C pins are connected with 2 external pull-up resistors (4.7k)
// And then send the data to the Display via I2C
// All of these external modules will be powered by the Microcontroller

#include "main.h"

int main(void){
	GPIO_init();
	I2C1_MasterInit();

	I2C1_start();
	I2C1_address(DISPLAY_ADRESS);
	I2C1_send(0); // write request


    /* Loop forever */
	while(1){
	}
}

void GPIO_init(void) {
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN; // enable GPIOB

	// Power
	GPIOB->MODER |= (1 << (POWER_PIN*2)); // output mode
	GPIOB->OTYPER &= ~(1 << POWER_PIN); // push-pull
	GPIOB->OSPEEDR |= (3 << (POWER_PIN*2)); // Fast Speed

	// I2C1
	GPIOB->MODER |= (2 << (I2C1_SCL*2)) | (2 << (I2C1_SDA*2)); // Alt function mode
	GPIOB->AFR[1] |= (0b0100 << 0) | (0b0100 << 4); // I2C Alt function
	GPIOB->OTYPER |= (1 << I2C1_SCL) | (1 << I2C1_SDA); // Open Drain
	GPIOB->OSPEEDR |= (3 << (I2C1_SCL*2)) | (3 << (I2C1_SDA*2)); // Fast Speed
}
