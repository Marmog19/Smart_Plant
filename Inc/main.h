#ifndef __MAIN_H
#define __MAIN_H


#include <stdint.h>
#include <stm32f4xx.h>
#include "I2C_lib.h"
#include "SysTickDelay.h"


#define DISPLAY_ADRESS 0x78
// GPIOB
#define I2C1_SCL 8
#define I2C1_SDA 9
#define POWER_PIN 0


void GPIO_init(void);
void Display_Show(unsigned char *);

#endif /* __MAIN_H */
