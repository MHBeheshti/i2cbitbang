/*
 * i2cbitbang_board.h
 *
 *  Created on: 25 lis 2019
 *      Author: Tata
 *  Modified for LPC1768: Uses LPC_GPIO0-4 port definitions
 */

#ifndef INC_I2CBITBANG_BOARD_H_
#define INC_I2CBITBANG_BOARD_H_

#include "lpc1768_gpio.h"

/* I2C Instance Definitions */
#define I2CBB_SCCB   0
#define I2CBB_OLED   1
#define I2CBB_LSM    2

#define NUMBER_OF_I2CBB_INSTANCES 3

/*
 * BE CAREFUL!
 * This configuration supports GPIO pins on LPC1768 GPIO ports 0-4.
 * Pins are configured as open-drain outputs with internal pull-up.
 *
 * Pin assignment example:
 *   - Instance 0 (SCCB): SCL on P0.4, SDA on P0.5
 *   - Instance 1 (OLED): SCL on P2.13, SDA on P1.15
 *   - Instance 2 (LSM):  SCL on P1.8, SDA on P1.9
 */

#define I2CBB_DECLARE_STRUCTURE() \
	const i2cbbConfig_t i2cbbConfigTable[NUMBER_OF_I2CBB_INSTANCES] = \
	{ \
		{LPC_GPIO0, GPIO_PIN_4,     /* SCL 0 */ \
		 LPC_GPIO0, GPIO_PIN_5},    /* SDA 0 */ \
\
		{LPC_GPIO2, GPIO_PIN_13,    /* SCL 1 */ \
		 LPC_GPIO1, GPIO_PIN_15},   /* SDA 1 */ \
\
		{LPC_GPIO1, GPIO_PIN_8,     /* SCL 2 */ \
		 LPC_GPIO1, GPIO_PIN_9},    /* SDA 2 */ \
	}

#endif /* INC_I2CBITBANG_BOARD_H_ */
