/*
 * User_control.cpp
 *
 *  Created on: Apr 30, 2022
 *      Author: szerpadiaz
 */

#ifndef INC_APPLICATION_USER_CONTROL_H_
#define INC_APPLICATION_USER_CONTROL_H_

class User_control final {
public:
	static void init();
	static bool is_blinking_led_enable();
	static void enable_blinking_led();
	static void disable_blinking_led();
};

#endif /* INC_APPLICATION_USER_CONTROL_H_ */
