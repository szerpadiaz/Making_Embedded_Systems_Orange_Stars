/*
 * User_control.cpp
 *
 *  Created on: Apr 30, 2022
 *      Author: szerpadiaz
 */

#include <Application/User_control.h>

static 	bool blinking_led_enabled;

void User_control_init() {
	blinking_led_enabled = false;
}

bool User_control_is_blinking_led_enable() {
	return blinking_led_enabled;
}

void User_control_enable_blinking_led(){
	blinking_led_enabled = true;
}

void User_control_disable_blinking_led()
{
	blinking_led_enabled = false;
}



