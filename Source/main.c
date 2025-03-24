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

	// display ON
	I2C1_Write(DISPLAY_ADRESS, 0, 0b00001111);
	Display_Show("test");

    /* Loop forever */
	while(1){
	}
}

void GPIO_init(void) {
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN; // Enable GPIOB
	RCC->APB1ENR |= RCC_APB1ENR_I2C1EN; // Enable I2C1

	// Power
	GPIOB->MODER |= (1 << (POWER_PIN*2)); // output mode
	GPIOB->OTYPER &= ~(1 << POWER_PIN); // push-pull
	GPIOB->ODR |= (1 << POWER_PIN); // Initializes as HIGH

	// I2C1
	GPIOB->MODER |= (2 << (I2C1_SCL*2)) | (2 << (I2C1_SDA*2)); // Alt function mode
	GPIOB->OTYPER |= (1 << I2C1_SCL) | (1 << I2C1_SDA); // Open Drain
	GPIOB->OSPEEDR |= (3 << (I2C1_SCL*2)) | (3 << (I2C1_SDA*2)); // Fast Speed
	GPIOB->AFR[1] |= (4 << 0) | (4 << 4); // I2C Alt function
	//GPIOB->PUPDR |= (1 << (I2C1_SCL*2)) | (1 << (I2C1_SDA*2)); // Pull-Up
}

// Send string to Display
void Display_Show(unsigned char *text) {
	int n;

	I2C1_start();
	I2C1_address(DISPLAY_ADRESS); //0x78
	I2C1_send(0x40); // Address to show on screen

	for(n=0;n<20;n++){
		I2C1_send(*text);
		++text;
	}

	I2C1_stop();
}