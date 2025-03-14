#ifndef __INC_I2C_LIB_H
#define __INC_I2C_LIB_H

#include "main.h"

#define CLOCK_FREQ 0x10		// Frequency (MHz) = SystemCoreClock (16MHz)
#define T_RISE 300			// Max Rise time (ns)

//In Master mode, the I2C interface initiates a data transfer and generates the clock signal. A
//serial data transfer always begins with a Start condition and ends with a Stop condition.
//Master mode is selected as soon as the Start condition is generated on the bus with a
//START bit.
void I2C1_MasterInit(void);


// sends address
void I2C1_address(uint8_t);


// sends start bit
void I2C1_start(void);


// Sends one character at the time to the Display
void I2C1_send(uint8_t);


// Ends the I2C transmission
void I2C1_stop(void);

#endif /* __INC_I2C_LIB_H */
