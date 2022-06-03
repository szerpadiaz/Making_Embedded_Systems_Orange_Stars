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
#include <Application/handwriting_recognizer.h>

static uint32_t time_to_update = 0;
static bool is_time_to_check_button() {

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

	char selected_char = '0';

	Gui::init();
	Gui::draw_selected_char_display_area(selected_char);
	auto painting_image_ptr = Gui::get_painting_image();

	Handwriting_recognizer::init();
	Handwriting_recognizer::enable_debug(true);

	Gui::print_info(" << Welcome to magic Writer!");

	while (1) {

		if (Button::is_pressed() && is_time_to_check_button()) {
			Gui::clear_painting_area();
			selected_char = (selected_char == '9') ? '0' : (selected_char + 1);
			Gui::draw_selected_char_display_area(selected_char);

			if (User_control_is_blinking_led_enable())
				Led::toggle();
		}

		ConsoleProcess();

		switch (Gui::get_touch_event()) {
		case Gui_event_t::ON_PAINTING_AREA:
			//Gui::print_info("<< Painting");
			break;
		case Gui_event_t::ON_CLEAR_BUTTON:
			Gui::print_info("<< Clearing");
			break;
		case Gui_event_t::ON_CHECK_BUTTON:
		{
			Gui::print_info("<< Verifying");
			char detected_char = Handwriting_recognizer::get_char_from_image(painting_image_ptr);

			if(selected_char == detected_char)
				Gui::draw_right_answer_animation();
			else
				Gui::draw_wrong_answer_animation();

			Gui::print_info("<< Character detected = %c", detected_char);
		}
			break;
		default:
			break;
		}
	}
}
