/*
 * led.h
 *
 *  Created on: Apr 9, 2022
 *      Author: szerpadiaz
 */

#ifndef INC_LED_H_
#define INC_LED_H_

class Led final {
public:
	static void init();
	static void on();
	static void off();
	static void toggle();
};



#endif /* INC_LED_H_ */
