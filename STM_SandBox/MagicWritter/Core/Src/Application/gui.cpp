/*
 * gui.cpp
 *
 *  Created on: 7 May 2022
 *      Author: szerpadiaz
 */

#include <Application/gui.h>

#include "stm32f429i_discovery.h"
#include "stm32f429i_discovery_lcd.h"
#include "stm32f429i_discovery_ts.h"

#include "../../../Utilities/right_answer_img.h"
#include "../../../Utilities/wrong_answer_img.h"

#define LCD_FRAME_BUFFER_LAYER0                  (LCD_FRAME_BUFFER+0x130000)
#define LCD_FRAME_BUFFER_LAYER1                  LCD_FRAME_BUFFER

constexpr uint32_t GUI_LAYOUT_LINE_COLOR = LCD_COLOR_BLACK;
constexpr uint32_t PAINTING_AREA_WIDTH = 224;
constexpr uint32_t PAINTING_AREA_HIGHT = 224;
constexpr uint32_t PAINTING_AREA_X = 8;
constexpr uint32_t PAINTING_AREA_Y = 55;
constexpr uint32_t PEN_COLOR = LCD_COLOR_DARKGREEN;
constexpr uint32_t PEN_RADIUS = 8;

constexpr uint32_t CLEAR_BUTTON_RADIUS = 20;
constexpr uint32_t CLEAR_BUTTON_X = 40;
constexpr uint32_t CLEAR_BUTTON_Y = 25;
constexpr uint32_t CLEAR_BUTTON_COLOR = LCD_COLOR_RED;

constexpr uint32_t SELECTED_SYMBOL_DISPLAY_AREA_WIDTH = 28;
constexpr uint32_t SELECTED_SYMBOL_DISPLAY_AREA_HIGHT = 28;
constexpr uint32_t SELECTED_SYMBOL_DISPLAY_AREA_X = 120 - SELECTED_SYMBOL_DISPLAY_AREA_WIDTH - 4;
constexpr uint32_t SELECTED_SYMBOL_DISPLAY_AREA_Y = 12;

constexpr uint32_t PAINTING_SYMBOL_DISPLAY_AREA_WIDTH = 28;
constexpr uint32_t PAINTING_SYMBOL_DISPLAY_AREA_HIGHT = 28;
constexpr uint32_t PAINTING_SYMBOL_DISPLAY_AREA_X = 120 + 4;
constexpr uint32_t PAINTING_SYMBOL_DISPLAY_AREA_Y = 12;

constexpr uint32_t OK_BUTTON_RADIUS = 20;
constexpr uint32_t OK_BUTTON_X = 240 - 40;
constexpr uint32_t OK_BUTTON_Y = 25;
constexpr uint32_t OK_BUTTON_COLOR = LCD_COLOR_GREEN;

constexpr uint32_t RESCLAE_RATIO = 8;

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

	draw_menu();
}

Gui::event_info_t Gui::get_touch_event() {
	TS_StateTypeDef TS_State;
	BSP_TS_GetState(&TS_State);
	uint32_t x = TS_State.X;
	uint32_t y = (TS_State.Y - 320) * -1;

	if (TS_State.TouchDetected) {
		print_xy_in_info_area(x, y);

		if (is_position_in_painting_area(x, y)) {
			update_painting(x, y);
			uint32_t rescaled_x = (x - PAINTING_AREA_X) / RESCLAE_RATIO;
			uint32_t rescaled_y = (y - PAINTING_AREA_Y) / RESCLAE_RATIO;
			return {Gui_event_t::ON_PAINTING_AREA, rescaled_x, rescaled_y};
		} else if (is_position_in_clear_button(x, y)) {
			//clear_painting();
			return {Gui_event_t::ON_CLEAR_BUTTON, 0, 0};
		} else if (is_position_in_ok_button(x, y)) {
			//draw_celebration_animation();
			return {Gui_event_t::ON_CHECK_BUTTON, 0, 0};
		}
	}
	return {Gui_event_t::NONE, 0 , 0};
}

void Gui::draw_menu(void) {
	/* Draw background Layer */
	BSP_LCD_SelectLayer(0);
	BSP_LCD_Clear(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_FillRect(0, 0, BSP_LCD_GetXSize(), BSP_LCD_GetYSize());

	draw_clear_button();
	draw_selected_symbol_display_area(0);
	draw_painting_symbol_display_area();
	draw_ok_button();
	draw_painting_area();
	draw_info_area();

	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(PEN_COLOR);
}

void Gui::draw_painting_area() {

	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_FillRect(PAINTING_AREA_X, PAINTING_AREA_Y, PAINTING_AREA_WIDTH, PAINTING_AREA_HIGHT);

	BSP_LCD_SetTextColor(GUI_LAYOUT_LINE_COLOR);
	BSP_LCD_DrawRect(PAINTING_AREA_X, PAINTING_AREA_Y, PAINTING_AREA_WIDTH, PAINTING_AREA_HIGHT);
}

bool Gui::is_position_in_painting_area(uint32_t x, uint32_t y) {
	const bool x_in_rect = (x > PAINTING_AREA_X + PEN_RADIUS
			&& x < (PAINTING_AREA_X + PAINTING_AREA_WIDTH - PEN_RADIUS));
	const bool y_in_rect = (y > PAINTING_AREA_Y + PEN_RADIUS
			&& y < (PAINTING_AREA_Y + PAINTING_AREA_HIGHT - PEN_RADIUS));

	return (x_in_rect && y_in_rect);
}

void Gui::clear_painting() {
	// draw painting area and display are for painting
	draw_painting_symbol_display_area();
	draw_painting_area();

	// make sure to set painting setting again
	// BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	// BSP_LCD_SetTextColor(PEN_COLOR);
}

void Gui::draw_clear_button() {
	BSP_LCD_SetTextColor(CLEAR_BUTTON_COLOR);
	BSP_LCD_DrawCircle(CLEAR_BUTTON_X, CLEAR_BUTTON_Y, CLEAR_BUTTON_RADIUS + 2);
	BSP_LCD_FillCircle(CLEAR_BUTTON_X, CLEAR_BUTTON_Y, CLEAR_BUTTON_RADIUS);
}

bool Gui::is_position_in_clear_button(uint32_t x, uint32_t y) {
	const bool x_in_rect = x > (CLEAR_BUTTON_X - CLEAR_BUTTON_RADIUS) && x < (CLEAR_BUTTON_X + CLEAR_BUTTON_RADIUS);
	const bool y_in_rect = y > (CLEAR_BUTTON_Y - CLEAR_BUTTON_RADIUS) && y < (CLEAR_BUTTON_Y + CLEAR_BUTTON_RADIUS);
	return (x_in_rect && y_in_rect);
}

void Gui::draw_selected_symbol_display_area(uint32_t ascii_char) {

	// Clear
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_FillRect(SELECTED_SYMBOL_DISPLAY_AREA_X,
			SELECTED_SYMBOL_DISPLAY_AREA_Y,
			SELECTED_SYMBOL_DISPLAY_AREA_WIDTH,
			SELECTED_SYMBOL_DISPLAY_AREA_HIGHT);
	// Draw line
	BSP_LCD_SetTextColor(GUI_LAYOUT_LINE_COLOR);
	BSP_LCD_DrawRect(SELECTED_SYMBOL_DISPLAY_AREA_X,
			SELECTED_SYMBOL_DISPLAY_AREA_Y,
			SELECTED_SYMBOL_DISPLAY_AREA_WIDTH,
			SELECTED_SYMBOL_DISPLAY_AREA_HIGHT);

	// Print ascii symbol
	sFONT *pFont = &Font20;
	BSP_LCD_SetFont(pFont);
	BSP_LCD_SetTextColor(PEN_COLOR);
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_DisplayChar(SELECTED_SYMBOL_DISPLAY_AREA_X + 8,
			SELECTED_SYMBOL_DISPLAY_AREA_Y + 6, ascii_char);
}

void Gui::draw_painting_symbol_display_area() {

	// Clear
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_FillRect(PAINTING_SYMBOL_DISPLAY_AREA_X,
			PAINTING_SYMBOL_DISPLAY_AREA_Y,
			PAINTING_SYMBOL_DISPLAY_AREA_WIDTH,
			PAINTING_SYMBOL_DISPLAY_AREA_HIGHT);

	// Draw line
	BSP_LCD_SetTextColor(GUI_LAYOUT_LINE_COLOR);
	BSP_LCD_DrawRect(PAINTING_SYMBOL_DISPLAY_AREA_X,
			PAINTING_SYMBOL_DISPLAY_AREA_Y,
			PAINTING_SYMBOL_DISPLAY_AREA_WIDTH,
			PAINTING_SYMBOL_DISPLAY_AREA_HIGHT);
}

void Gui::update_painting(uint32_t x, uint32_t y)
{
	// draw point in painting area
	BSP_LCD_FillCircle(x, y, PEN_RADIUS);

	// convert point in painting area to an offset (the source offset)
	auto src_offset_x = x - PAINTING_AREA_X;
	auto src_offset_y = y - PAINTING_AREA_Y;

	// calculate offset in display area (the destination offset)
	auto dst_offset_x = src_offset_x / RESCLAE_RATIO;
	auto dst_offset_y = src_offset_y / RESCLAE_RATIO;

	// calculate point in display area
	auto dst_x = dst_offset_x + PAINTING_SYMBOL_DISPLAY_AREA_X;
	auto dst_y = dst_offset_y + PAINTING_SYMBOL_DISPLAY_AREA_Y;

	// draw point in display area
	BSP_LCD_DrawPixel(dst_x, dst_y, PEN_COLOR);
}

void Gui::draw_ok_button() {
	BSP_LCD_SetTextColor(OK_BUTTON_COLOR);
	BSP_LCD_DrawCircle(OK_BUTTON_X, OK_BUTTON_Y, OK_BUTTON_RADIUS + 2);
	BSP_LCD_FillCircle(OK_BUTTON_X, OK_BUTTON_Y, OK_BUTTON_RADIUS);
}

bool Gui::is_position_in_ok_button(uint32_t x, uint32_t y) {
	const bool x_in_rect = x > (OK_BUTTON_X - OK_BUTTON_RADIUS) && x < (OK_BUTTON_X + OK_BUTTON_RADIUS);
	const bool y_in_rect = y > (OK_BUTTON_Y - OK_BUTTON_RADIUS) && y < (OK_BUTTON_Y + OK_BUTTON_RADIUS);
	return (x_in_rect && y_in_rect);
}

void Gui::draw_right_answer_animation() {
	BSP_LCD_SelectLayer(1);
	//BSP_LCD_Clear(LCD_COLOR_WHITE);

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
	//BSP_LCD_Clear(LCD_COLOR_WHITE);

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

void Gui::draw_info_area() {
	sFONT *pFont = &Font8;
	BSP_LCD_SetFont(pFont);
	BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_DisplayStringAt(10, (BSP_LCD_GetYSize() - 15),
			(uint8_t*) "Dimension: WWW x HHH | Position: (000 , 000)",
			LEFT_MODE);
	print_number_at_position(10 + 11 * pFont->Width, (BSP_LCD_GetYSize() - 15),
			BSP_LCD_GetXSize());
	print_number_at_position(10 + 17 * pFont->Width, (BSP_LCD_GetYSize() - 15),
			BSP_LCD_GetYSize());
}

void Gui::print_xy_in_info_area(uint32_t pos_x, uint32_t pos_y) {
	sFONT *pFont = &Font8;
	BSP_LCD_SetFont(pFont);
	BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	print_number_at_position(10 + 34 * pFont->Width, (BSP_LCD_GetYSize() - 15),
			pos_x);
	print_number_at_position(10 + 40 * pFont->Width, (BSP_LCD_GetYSize() - 15),
			pos_y);

	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(PEN_COLOR);
}

void Gui::print_number_at_position(uint32_t pos_x, uint32_t pos_y,
		uint16_t number) {
	sFONT *pFont = BSP_LCD_GetFont();
	uint16_t w = pFont->Width;

	uint32_t x_d1 = number / 100;
	uint32_t x_d2 = (number - x_d1 * 100) / 10;
	uint32_t x_d3 = number - x_d1 * 100 - x_d2 * 10;

	BSP_LCD_DisplayChar(pos_x, pos_y, x_d1 + 48);
	BSP_LCD_DisplayChar(pos_x + w, pos_y, x_d2 + 48);
	BSP_LCD_DisplayChar(pos_x + 2 * w, pos_y, x_d3 + 48);
}

