/*
 * gui.h
 *
 *  Created on: 7 May 2022
 *      Author: szerpadiaz
 */

#ifndef INC_APPLICATION_GUI_H_
#define INC_APPLICATION_GUI_H_

#include <stdint.h>
#include <tuple>

enum class Gui_event_t {
	NONE, ON_PAINTING_AREA, ON_CLEAR_BUTTON, ON_CHECK_BUTTON
};



class Gui final {
	using event_info_t = std::tuple<Gui_event_t, uint32_t, uint32_t>;
public:
	static void init();
	static event_info_t get_touch_event(void);
	static void clear_painting();
	static void draw_selected_symbol_display_area(uint32_t ascii_char);
	static void draw_right_answer_animation();
	static void draw_wrong_answer_animation();

private:
	static void draw_menu(void);
	static void draw_clear_button();
	static void draw_ok_button();
	static void draw_painting_symbol_display_area();
	static void update_painting(uint32_t x, uint32_t y);
	static void draw_painting_area();

	static void draw_info_area();
	static void print_xy_in_info_area(uint32_t pos_x, uint32_t pos_y);
	static void print_number_at_position(uint32_t pos_x, uint32_t pos_y,
			uint16_t number);

	static bool is_position_in_painting_area(uint32_t x, uint32_t y);
	static bool is_position_in_clear_button(uint32_t x, uint32_t y);
	static bool is_position_in_ok_button(uint32_t x, uint32_t y);
};

#endif /* INC_APPLICATION_GUI_H_ */
