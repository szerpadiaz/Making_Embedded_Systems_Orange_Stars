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

constexpr auto MIN_SELECTED_SYMBOL = 48;                      // digit 0
constexpr auto MAX_SELECTED_SYMBOL = MIN_SELECTED_SYMBOL + 9; // digit 9
static uint32_t selected_symbol = MIN_SELECTED_SYMBOL;
static void increment_selected_symbol(){
	selected_symbol = (selected_symbol == MAX_SELECTED_SYMBOL) ? MIN_SELECTED_SYMBOL : (selected_symbol + 1);
}

static uint32_t time_to_update = 0;
static bool is_time_to_update_selection() {

	auto const now = Time::ticks_ms();
	if (Time::ticks_diff(time_to_update, now) > 0) {
		return false;
	} else {
		time_to_update = Time::ticks_add(now, 300);
		return true;
	}
}

int main(void) {

	Machine::init();

	Led::init();

	Button::init();

	User_control_init();

	ConsoleInit();

	Gui::init();
	Gui::draw_selected_symbol_display_area(selected_symbol);

	while (1) {

		if (Button::is_pressed() && is_time_to_update_selection()) {
			Gui::clear_painting();
			increment_selected_symbol();
			Gui::draw_selected_symbol_display_area(selected_symbol);

			if (User_control_is_blinking_led_enable())
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
