/*
 * Delays.h
 *
 *  Created on: Oct 18, 2019
 *      Author: Tata
 *  Modified for LPC1768: Uses SysTick timer for accurate delays
 */

#ifndef DELAY_H_
#define DELAY_H_

#include "lpc1768_gpio.h"

class Delay {

private:
	void SysTick_Init(void);

public:
	Delay();
	virtual ~Delay();

	void hns(uint32_t hns);  /* hundreds of nanoseconds delay (0.1 us units) */
	void us(uint32_t);       /* microseconds delay */
	void ms(uint32_t);       /* milliseconds delay */

};

#endif /* DELAY_H_ */
