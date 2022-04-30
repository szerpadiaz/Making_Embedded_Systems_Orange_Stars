/**
  ******************************************************************************
  * @file           : main.cpp
  * @brief          : Program to blink an LED while a push-button is pressed
  ******************************************************************************
  ******************************************************************************
  */

#include <Application/button.h>
#include <Application/led.h>
#include <Machine/m_time.h>
#include <Machine/machine.h>

static bool is_time_to_toggle_led();

int main(void) {

	Machine::init();

	Led::init();

	Button::init();

	while (1) {
		if (Button::is_pressed() && is_time_to_toggle_led()) {
			Led::toggle();
		}
	}
}


static bool is_time_to_toggle_led() {
	static uint32_t time_to_toggle_led = 0;

	auto const now = Time::ticks_ms();
	if (Time::ticks_diff(time_to_toggle_led, now) > 0) {
		return false;
	} else {
		time_to_toggle_led = Time::ticks_add(now, 200);
		return true;
	}
}
