/*
 * i2cbitbang_driver.cpp
 *
 *  Created on: 25 lis 2019
 *      Author: Tata
 *  Modified for LPC1768: Uses direct register access without HAL
 */

#include "i2cbitbang.h"

I2CBB_DECLARE_STRUCTURE();

void i2cbitbang::conf_hardware(void)
{
	/* Enable GPIO power (if not already enabled) */
	LPC_GPIO_PowerEnable();
	
	/* Configure SCL pin for I2C bit-banging (open-drain with pull-up) */
	LPC_GPIO_ConfigI2CPin(i2cbbConfigTable[instance].GPIOclk_port,
	                      i2cbbConfigTable[instance].pinClk);
	
	/* Configure SDA pin for I2C bit-banging (open-drain with pull-up) */
	LPC_GPIO_ConfigI2CPin(i2cbbConfigTable[instance].GPIOdta_port,
	                      i2cbbConfigTable[instance].pinDta);
}

void i2cbitbang::i2c_bus_init(void)
{
	error = I2CBB_ERROR_NONE;
	set_SDA();
	set_SCL();

	/* TODO: confirm that SDA and SCL are set, otherwise bus error */
}

bool i2cbitbang::read_SCL(void)  /* Return current level of SCL line, 0 or 1 */
{
	return GPIO_READ_PIN(i2cbbConfigTable[instance].GPIOclk_port,
	                     i2cbbConfigTable[instance].pinClk);
}

bool i2cbitbang::read_SDA(void)  /* Return current level of SDA line, 0 or 1 */
{
	return GPIO_READ_PIN(i2cbbConfigTable[instance].GPIOdta_port,
	                     i2cbbConfigTable[instance].pinDta);
}

void i2cbitbang::set_SCL(void)   /* Do not drive SCL (set pin high-impedance via open-drain) */
{
	GPIO_SET_PIN(i2cbbConfigTable[instance].GPIOclk_port,
	             i2cbbConfigTable[instance].pinClk);
}

void i2cbitbang::clear_SCL(void) /* Actively drive SCL signal low */
{
	GPIO_CLEAR_PIN(i2cbbConfigTable[instance].GPIOclk_port,
	               i2cbbConfigTable[instance].pinClk);
}

void i2cbitbang::set_SDA(void)   /* Do not drive SDA (set pin high-impedance via open-drain) */
{
	GPIO_SET_PIN(i2cbbConfigTable[instance].GPIOdta_port,
	             i2cbbConfigTable[instance].pinDta);
}

void i2cbitbang::clear_SDA(void) /* Actively drive SDA signal low */
{
	GPIO_CLEAR_PIN(i2cbbConfigTable[instance].GPIOdta_port,
	               i2cbbConfigTable[instance].pinDta);
}
