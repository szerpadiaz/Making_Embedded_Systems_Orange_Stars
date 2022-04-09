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
#include <Machine/time.h>

int main(void) {

	Machine::init();

	Led::init();

	Button::init();

	auto time_to_toggle_led = Time::ticks_ms();

	while (1) {
		if (Button::is_pressed())
		{
			auto const now = Time::ticks_ms();
			if (Time::ticks_diff(time_to_toggle_led, now) <= 0)
			{
				Led::toggle();
				time_to_toggle_led = Time::ticks_add(now, 200);
			}
		}
	}
}


