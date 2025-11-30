/*
 * Delays.cpp
 *
 *  Created on: Oct 18, 2019
 *      Author: Tata
 *  Modified for LPC1768: Uses SysTick timer for accurate delays
 *  Uses direct register access without HAL dependencies
 */

#include <Delay.h>

static int32_t initDone = 0;

Delay::Delay() {
	if (!initDone)
	{
		SysTick_Init();
		initDone = 1;  /* Initialize only once regardless of number of objects */
	}
}

Delay::~Delay() {
}

/*
 * Initialize SysTick timer for delay functions
 * Configure SysTick to use CPU clock as source
 */
void Delay::SysTick_Init(void)
{
	/* Disable SysTick during configuration */
	SysTick->CTRL = 0;
	
	/* Set reload value to maximum (we'll use polling mode) */
	SysTick->LOAD = SysTick_LOAD_RELOAD_Msk;
	
	/* Reset counter value */
	SysTick->VAL = 0;
	
	/* Enable SysTick with CPU clock source, no interrupt */
	SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk;
}

/*
 * hns delay in 0.1 us (or 100ns) units
 * eg. Delay.hns(47) means 4.7 us delay
 */
void Delay::hns(uint32_t hns) /* hundreds of nanosec delay */
{
	if (hns > 0)
	{
		/* Calculate ticks needed: (hns * SystemCoreClock) / 10000000 */
		/* Simplified: (hns * (SystemCoreClock / 1000000)) / 10 */
		uint32_t ticksNeeded = (hns * (SystemCoreClock / 1000000UL) + 1) / 10;
		
		/* Get current SysTick value (counts down) */
		uint32_t startVal = SysTick->VAL;
		uint32_t elapsed = 0;
		
		while (elapsed < ticksNeeded)
		{
			uint32_t currentVal = SysTick->VAL;
			
			/* SysTick counts down, handle wraparound */
			if (currentVal <= startVal)
			{
				elapsed = startVal - currentVal;
			}
			else
			{
				/* Counter wrapped around */
				elapsed = startVal + (SysTick->LOAD - currentVal + 1);
			}
		}
	}
}

void Delay::us(uint32_t us) /* microseconds */
{
	if (us > 0)
	{
		uint32_t ticksNeeded = us * (SystemCoreClock / 1000000UL);
		
		/* Get current SysTick value (counts down) */
		uint32_t startVal = SysTick->VAL;
		uint32_t elapsed = 0;
		
		while (elapsed < ticksNeeded)
		{
			uint32_t currentVal = SysTick->VAL;
			
			/* SysTick counts down, handle wraparound */
			if (currentVal <= startVal)
			{
				elapsed = startVal - currentVal;
			}
			else
			{
				/* Counter wrapped around */
				elapsed = startVal + (SysTick->LOAD - currentVal + 1);
			}
		}
	}
}

void Delay::ms(uint32_t ms) /* milliseconds */
{
	uint32_t m = ms;
	while(m--) us(1000UL);
}
