/*
 * time.cpp
 *
 *  Created on: Apr 9, 2022
 *      Author: szerpadiaz
 */
#include <Machine/m_time.h>
#include <Machine/processor_header.h>

//Time depends on in HAL_InitTick().
// HAL_InitTick() is called in HAL_Init() which is called in Machine::init()

uint32_t Time::ticks_ms()
{
	return HAL_GetTick();
}

uint32_t Time::ticks_add(uint32_t ticks, uint32_t delta)
{
	// here we should handle time-wrap-around!
	return (ticks + delta);
}

int32_t Time::ticks_diff(uint32_t ticks1, uint32_t ticks2)
{
	// here we should handle time-wrap-around!
	return (ticks1- ticks2);
}



