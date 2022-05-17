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

#include <Application/console.h>
#include <Application/User_control.h>
#include <Application/gui.h>

static bool is_time_to_toggle_led();
static uint32_t selected_symbol = 48; // digits from 0 to 9 coded in ascii

int main(void) {

	Machine::init();

	Led::init();

	Button::init();

	User_control_init();

	ConsoleInit();

	Gui::init();
	Gui::draw_selected_symbol_display_area(selected_symbol);

	while (1) {
		const bool toggle_led_enabled = Button::is_pressed()
				|| User_control_is_blinking_led_enable();
		if (toggle_led_enabled && is_time_to_toggle_led()) {
			Led::toggle();
		}

		ConsoleProcess();

		auto gui_event = Gui::get_touch_event();

		switch (std::get<0>(gui_event)) {
		case Gui_event_t::ON_PAINTING_AREA:
			// store point to BMP image
			// auto x = std::get<1>(gui_event);
			// auto y = std::get<2>(gui_event);
			break;
		case Gui_event_t::ON_CLEAR_BUTTON:
			Gui::clear_painting();
			break;
		case Gui_event_t::ON_CHECK_BUTTON:
			// check BMP image using ML model
			Gui::draw_celebration_animation();
			break;
		default:
			break;
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
