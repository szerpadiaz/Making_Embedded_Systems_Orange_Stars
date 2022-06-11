/*
 * gui.cpp
 *
 *  Created on: 7 May 2022
 *      Author: szerpadiaz
 */

#include <Application/gui.h>
#include <algorithm>
#include <stdarg.h>
#include <stdio.h>

#include "stm32f429i_discovery.h"
#include "stm32f429i_discovery_lcd.h"
#include "stm32f429i_discovery_ts.h"

#include "../../../Utilities/main_menu_img.h"
#include "../../../Utilities/right_answer_img.h"
#include "../../../Utilities/wrong_answer_img.h"

static raw_painting_image_t raw_painting_image[PAINTING_IMAGE_LENGTH];

#define LCD_FRAME_BUFFER_LAYER0                  (LCD_FRAME_BUFFER+0x130000)
#define LCD_FRAME_BUFFER_LAYER1                  LCD_FRAME_BUFFER

constexpr uint32_t CLEAR_BUTTON_RADIUS = 20;
constexpr uint32_t CLEAR_BUTTON_X = 30;
constexpr uint32_t CLEAR_BUTTON_Y = 25;

constexpr uint32_t SELECTED_CHAR_DISPLAY_AREA_X = 120 - 29;
constexpr uint32_t SELECTED_CHAR_DISPLAY_AREA_Y = 12;

constexpr uint32_t RESCALED_PAINTING_DISPLAY_AREA_WIDTH = PAINTING_IMAGE_WIDTH;
constexpr uint32_t RESCALED_PAINTING_DISPLAY_AREA_HIGHT = PAINTING_IMAGE_HIGH;
constexpr uint32_t RESCALED_PAINTING_DISPLAY_AREA_X = 120 + 8;
constexpr uint32_t RESCALED_PAINTING_DISPLAY_AREA_Y = 12;

constexpr uint32_t OK_BUTTON_RADIUS = 20;
constexpr uint32_t OK_BUTTON_X = 240 - 30;
constexpr uint32_t OK_BUTTON_Y = 25;

constexpr uint32_t GUI_LAYOUT_LINE_COLOR = LCD_COLOR_BLACK;
constexpr uint32_t PAINTING_AREA_WIDTH = PAINTING_IMAGE_WIDTH * GUI_PAINTING_AREA_RESCALED_RATIO;
constexpr uint32_t PAINTING_AREA_HIGHT = PAINTING_IMAGE_HIGH * GUI_PAINTING_AREA_RESCALED_RATIO;
constexpr uint32_t PAINTING_AREA_X = 8;
constexpr uint32_t PAINTING_AREA_Y = 55;

constexpr uint32_t INFO_DISPLAY_AREA_WIDTH = PAINTING_AREA_WIDTH - 20;
constexpr uint32_t INFO_DISPLAY_AREA_HIGHT = 16;
constexpr uint32_t INFO_DISPLAY_AREA_X = PAINTING_AREA_X + 10;
constexpr uint32_t INFO_DISPLAY_AREA_Y = PAINTING_AREA_Y + PAINTING_AREA_HIGHT + 18;


void Gui::init() {

	BSP_LCD_Init();

	/* Configure foreground layer (only visible to show animation when winning/losing)*/
	BSP_LCD_LayerDefaultInit(1, LCD_FRAME_BUFFER_LAYER1);
	BSP_LCD_SelectLayer(1);
	BSP_LCD_Clear(LCD_COLOR_WHITE);
	BSP_LCD_SetColorKeying(1, LCD_COLOR_WHITE);
	BSP_LCD_SetTransparency(1, 255);
	BSP_LCD_SetLayerVisible(1, DISABLE);

	/* Configure background layer (it's always used and visible)*/
	BSP_LCD_LayerDefaultInit(0, LCD_FRAME_BUFFER_LAYER0);
	BSP_LCD_SelectLayer(0);

	BSP_LCD_DisplayOn();
	BSP_LCD_Clear(LCD_COLOR_WHITE);

	BSP_TS_Init(BSP_LCD_GetXSize(), BSP_LCD_GetYSize());

	BSP_LCD_SelectLayer(0);
	draw_menu();

	Gui::print_info(" >> ");
}

void Gui::turn_on() {
	// Turn on backlight?
	BSP_LCD_SetTransparency(0, 255);
	BSP_LCD_DisplayOn();
}

void Gui::turn_off() {
	// Turn off backlight?
	BSP_LCD_SetTransparency(0, 0);
	BSP_LCD_DisplayOff();
}

std::tuple<Gui_event_t, uint32_t, uint32_t> Gui::get_touch_event() {
	TS_StateTypeDef TS_State;
	BSP_TS_GetState(&TS_State);
	uint32_t x = TS_State.X;
	uint32_t y = (TS_State.Y - 320) * -1;

	if (TS_State.TouchDetected) {
		if (is_position_in_painting_area(x, y)) {
			return {Gui_event_t::ON_PAINTING_AREA, x, y};
		} else if (is_position_in_clear_button(x, y)) {
			return {Gui_event_t::ON_CLEAR_BUTTON, 0, 0};
		} else if (is_position_in_ok_button(x, y)) {
			return {Gui_event_t::ON_CHECK_BUTTON, 0, 0};
		}
	}
	return {Gui_event_t::NONE, 0, 0};
}

raw_painting_image_t const * Gui::get_painting_image() {
	return raw_painting_image;
}

void Gui::draw_menu(void) {

	clear_painting_area(' ');

	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(GUI_PAINTING_PEN_COLOR);
}

void Gui::draw_selected_char_display_area(char selected_char) {
	sFONT *pFont = &Font20;
	BSP_LCD_SetFont(pFont);
	BSP_LCD_SetTextColor(GUI_PAINTING_PEN_COLOR);
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_DisplayChar(SELECTED_CHAR_DISPLAY_AREA_X + 8,
			SELECTED_CHAR_DISPLAY_AREA_Y + 6, selected_char);
}

bool Gui::is_position_in_painting_area(uint32_t x, uint32_t y) {
	const bool x_in_rect = (x > PAINTING_AREA_X + GUI_PAINTING_PEN_RADIUS
			&& x < (PAINTING_AREA_X + PAINTING_AREA_WIDTH - GUI_PAINTING_PEN_RADIUS));
	const bool y_in_rect = (y > PAINTING_AREA_Y + GUI_PAINTING_PEN_RADIUS
			&& y < (PAINTING_AREA_Y + PAINTING_AREA_HIGHT - GUI_PAINTING_PEN_RADIUS));

	return (x_in_rect && y_in_rect);
}

void Gui::clear_painting_area(char selected_char) {
	BSP_LCD_DrawBitmap(0, 0, (uint8_t *)main_menu_img);
	draw_selected_char_display_area(selected_char);
	std::fill_n(raw_painting_image, PAINTING_IMAGE_LENGTH, PAINTING_IMAGE_PIXEL_CLEAR_COLOR);
}

bool Gui::is_position_in_clear_button(uint32_t x, uint32_t y) {
	const bool x_in_rect = x > (CLEAR_BUTTON_X - CLEAR_BUTTON_RADIUS) && x < (CLEAR_BUTTON_X + CLEAR_BUTTON_RADIUS);
	const bool y_in_rect = y > (CLEAR_BUTTON_Y - CLEAR_BUTTON_RADIUS) && y < (CLEAR_BUTTON_Y + CLEAR_BUTTON_RADIUS);
	return (x_in_rect && y_in_rect);
}

std::pair<uint32_t, uint32_t> Gui::from_rescaled_to_painting_point(uint32_t rescaled_x, uint32_t rescaled_y)
{
	auto const x = (rescaled_x * GUI_PAINTING_AREA_RESCALED_RATIO) + PAINTING_AREA_X;
	auto const y = (rescaled_y * GUI_PAINTING_AREA_RESCALED_RATIO) + PAINTING_AREA_Y;
	return {x,y};
}

void Gui::update_painting_areas(uint32_t x, uint32_t y)
{
	// draw point in painting area
	BSP_LCD_FillCircle(x, y, GUI_PAINTING_PEN_RADIUS);

	// Re-scale point
	auto rescaled_x = (x - PAINTING_AREA_X) / GUI_PAINTING_AREA_RESCALED_RATIO;
	auto rescaled_y = (y - PAINTING_AREA_Y) / GUI_PAINTING_AREA_RESCALED_RATIO;

	// Update scaled image of painting area
	raw_painting_image[rescaled_y*PAINTING_IMAGE_WIDTH + rescaled_x] = PAINTING_IMAGE_PIXEL_SET_COLOR;

	// draw point in display area
	auto dst_x = rescaled_x + RESCALED_PAINTING_DISPLAY_AREA_X;
	auto dst_y = rescaled_y + RESCALED_PAINTING_DISPLAY_AREA_Y;
	BSP_LCD_DrawPixel(dst_x, dst_y, GUI_PAINTING_PEN_COLOR);
}

bool Gui::is_position_in_ok_button(uint32_t x, uint32_t y) {
	const bool x_in_rect = x > (OK_BUTTON_X - OK_BUTTON_RADIUS) && x < (OK_BUTTON_X + OK_BUTTON_RADIUS);
	const bool y_in_rect = y > (OK_BUTTON_Y - OK_BUTTON_RADIUS) && y < (OK_BUTTON_Y + OK_BUTTON_RADIUS);
	return (x_in_rect && y_in_rect);
}

void Gui::draw_right_answer_animation() {
	BSP_LCD_SelectLayer(1);

	BSP_LCD_DrawBitmap(0, 0, (uint8_t *)right_answer_img);
	BSP_LCD_SetLayerVisible(1, ENABLE);
	HAL_Delay(250);
	BSP_LCD_SetLayerVisible(1, DISABLE);
	HAL_Delay(250);
	BSP_LCD_SetLayerVisible(1, ENABLE);
	HAL_Delay(1500);
	BSP_LCD_SetLayerVisible(1, DISABLE);

	BSP_LCD_SelectLayer(0);
}

void Gui::draw_wrong_answer_animation() {
	BSP_LCD_SelectLayer(1);

	BSP_LCD_DrawBitmap(0, 0, (uint8_t *)wrong_answer_img);
	BSP_LCD_SetLayerVisible(1, ENABLE);
	HAL_Delay(250);
	BSP_LCD_SetLayerVisible(1, DISABLE);
	HAL_Delay(250);
	BSP_LCD_SetLayerVisible(1, ENABLE);
	HAL_Delay(1500);
	BSP_LCD_SetLayerVisible(1, DISABLE);

	BSP_LCD_SelectLayer(0);
}

void Gui::vprint(const char* string) {

	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_FillRect(INFO_DISPLAY_AREA_X, INFO_DISPLAY_AREA_Y, INFO_DISPLAY_AREA_WIDTH, INFO_DISPLAY_AREA_HIGHT);

	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(GUI_PAINTING_PEN_COLOR);

	sFONT *pFont = &Font12;
	BSP_LCD_SetFont(pFont);
	BSP_LCD_DisplayStringAt(
			INFO_DISPLAY_AREA_X,
			INFO_DISPLAY_AREA_Y,
			(uint8_t*) string,
			LEFT_MODE);
}

void Gui::print_info(const char *format, ...) {
    va_list myargs;
    va_start(myargs, format);

    char string[200];
	if(0 < vsprintf(string, format, myargs)) //	Build string
	{
		vprint(string);
	}

    va_end(myargs);
}

