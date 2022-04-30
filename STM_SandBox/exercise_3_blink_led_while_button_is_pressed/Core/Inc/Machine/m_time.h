/*
 * Time.h
 *
 *  Created on: Apr 9, 2022
 *      Author: szerpadiaz
 */

#ifndef INC_MACHINE_M_TIME_H_
#define INC_MACHINE_M_TIME_H_

#include <stdint.h>

class Time final {
public:
	static uint32_t ticks_ms();
	static uint32_t ticks_add(uint32_t ticks, uint32_t delta);
	static int32_t ticks_diff(uint32_t ticks1, uint32_t ticks2);
};


#endif /* INC_MACHINE_M_TIME_H_ */
