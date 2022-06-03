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

static raw_image_t raw_image[RAW_IMAGE_LENGTH] = { 0 };

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

constexpr auto SET_PIXEL = 0xffffff; //1, 0xffffff
constexpr auto CLEAR_PIXEL = 0;
int main(void) {

	Machine::init();

	Led::init();

	Button::init();

	User_control_init();

	ConsoleInit();

	Gui::init();
	Gui::draw_selected_char_display_area(selected_symbol);

	Handwriting_recognizer::init();
	std::fill_n (raw_image, RAW_IMAGE_LENGTH, CLEAR_PIXEL);

	while (1) {

		if (Button::is_pressed() && is_time_to_update_selection()) {
			Gui::clear_painting_area();
			increment_selected_symbol();
			Gui::draw_selected_char_display_area(selected_symbol);
			std::fill_n (raw_image, RAW_IMAGE_LENGTH, CLEAR_PIXEL);

			if (User_control_is_blinking_led_enable())
				Led::toggle();
		}

		ConsoleProcess();

		auto [gui_event, x, y] = Gui::get_touch_event();
		char detected_symbol = ' ';

		switch (gui_event) {
		case Gui_event_t::ON_PAINTING_AREA:
			raw_image[y*28 + x] = SET_PIXEL;
			break;
		case Gui_event_t::ON_CLEAR_BUTTON:
			Gui::clear_painting_area();
			std::fill_n (raw_image, RAW_IMAGE_LENGTH, CLEAR_PIXEL);
			break;
		case Gui_event_t::ON_CHECK_BUTTON:
			// check BMP image using ML model
			detected_symbol = Handwriting_recognizer::get_char_from_raw_image(raw_image);

			if(selected_symbol == detected_symbol)
				Gui::draw_right_answer_animation();
			else
				Gui::draw_wrong_answer_animation();
			break;
		default:
			break;
		}
	}
}
