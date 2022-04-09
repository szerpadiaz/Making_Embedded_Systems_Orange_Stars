/**
  ******************************************************************************
  * @file           : main.cpp
  * @brief          : Main program body
  ******************************************************************************
  ******************************************************************************
  */

#include <Application/button.h>
#include <Application/led.h>
#include <Machine/machine.h>
#include "main.h"

int main(void) {

	Machine::init();

	Led::init();

	Button::init();

	uint32_t time_to_toggle_led = HAL_GetTick();

	while (1) {
		if (Button::is_pressed() && (HAL_GetTick() > time_to_toggle_led)) {
			Led::toggle();
			time_to_toggle_led += 200;
		}
	}
}


