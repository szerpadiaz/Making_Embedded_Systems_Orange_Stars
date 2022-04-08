/*
 * button.h
 *
 *  Created on: Apr 8, 2022
 *      Author: szerpadiaz
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include <stdbool.h>

class Button final {
public:
	static void init();
	static bool is_pressed();
};



#endif /* INC_BUTTON_H_ */
