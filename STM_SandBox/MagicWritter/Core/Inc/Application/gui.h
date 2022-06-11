/*
 * gui.h
 *
 *  Created on: 7 May 2022
 *      Author: szerpadiaz
 */

#ifndef INC_APPLICATION_GUI_H_
#define INC_APPLICATION_GUI_H_

#include <tuple>
#include <stdint.h>
#include <application_settings.h>

enum class Gui_event_t {
	NONE, ON_PAINTING_AREA, ON_CLEAR_BUTTON, ON_CHECK_BUTTON
};

class Gui final {
public:
	static void init();
	static std::tuple<Gui_event_t, uint32_t, uint32_t> get_touch_event();
	static raw_painting_image_t const * get_painting_image();
	static void draw_selected_char_display_area(char selected_char);
	static void draw_right_answer_animation();
	static void draw_wrong_answer_animation();
	static void clear_painting_area(char selected_char);
	static void update_painting_areas(uint32_t x, uint32_t y);
	static std::pair<uint32_t, uint32_t> from_rescaled_to_painting_point(uint32_t rescaled_x, uint32_t rescaled_y);

	static void print_info(const char *format, ...);

	static void turn_on();
	static void turn_off();

private:
	static void draw_menu();
	static void vprint(const char* string);

	static bool is_position_in_painting_area(uint32_t x, uint32_t y);
	static bool is_position_in_clear_button(uint32_t x, uint32_t y);
	static bool is_position_in_ok_button(uint32_t x, uint32_t y);
};

#endif /* INC_APPLICATION_GUI_H_ */
