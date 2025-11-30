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
 * I2C Instance Configuration Table
 * Format: {SCL_Port, SCL_Pin, SDA_Port, SDA_Pin}
 * 
 * Pin assignment example:
 *   - Instance 0 (SCCB): SCL on P0.4, SDA on P0.5
 *   - Instance 1 (OLED): SCL on P2.13, SDA on P1.15
 *   - Instance 2 (LSM):  SCL on P1.8, SDA on P1.9
 */
#define I2CBB_DECLARE_STRUCTURE()                                          \
    const i2cbbConfig_t i2cbbConfigTable[NUMBER_OF_I2CBB_INSTANCES] = {    \
        { LPC_GPIO0, GPIO_PIN_4,  LPC_GPIO0, GPIO_PIN_5  },  /* SCCB */    \
        { LPC_GPIO2, GPIO_PIN_13, LPC_GPIO1, GPIO_PIN_15 },  /* OLED */    \
        { LPC_GPIO1, GPIO_PIN_8,  LPC_GPIO1, GPIO_PIN_9  }   /* LSM  */    \
    }

#endif /* INC_I2CBITBANG_BOARD_H_ */
