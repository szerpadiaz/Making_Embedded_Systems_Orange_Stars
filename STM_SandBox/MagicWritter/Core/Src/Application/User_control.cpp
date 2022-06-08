/*
 * User_control.cpp
 *
 *  Created on: Apr 30, 2022
 *      Author: szerpadiaz
 */

#include <Application/User_control.h>

static 	bool blinking_led_enabled;

void User_control::init() {
	blinking_led_enabled = true;
}

bool User_control::is_blinking_led_enable() {
	return blinking_led_enabled;
}

void User_control::enable_blinking_led(){
	blinking_led_enabled = true;
}

void User_control::disable_blinking_led()
{
	blinking_led_enabled = false;
}



