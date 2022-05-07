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

#define LCD_FRAME_BUFFER_LAYER0                  (LCD_FRAME_BUFFER+0x130000)
#define LCD_FRAME_BUFFER_LAYER1                  LCD_FRAME_BUFFER

static uint32_t selected_symbol = 0;
static uint32_t radius = 12;
static uint32_t pencil_color = LCD_COLOR_DARKGREEN;

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
			BSP_LCD_FillCircle(x, y, radius);
			return {Gui_event_t::ON_PAINTING_AREA, x, y};
		} else if (is_position_in_clear_button(x, y)) {
			//clear_painting_area();
			return {Gui_event_t::ON_CLEAR_BUTTON, 0, 0};
		} else if (is_position_in_check_button(x, y)) {
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
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_FillRect(0, 0, BSP_LCD_GetXSize(), BSP_LCD_GetYSize());

	draw_clear_button();
	draw_symbol_display_area();
	draw_check_button();
	draw_painting_area();
	draw_info_area();

	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(pencil_color);
}

void Gui::draw_painting_area() {
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_FillRect(10, 50, BSP_LCD_GetXSize() - 20, BSP_LCD_GetYSize() - 75);

	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_DrawRect(15, 55, BSP_LCD_GetXSize() - 30, BSP_LCD_GetYSize() - 85);
}

bool Gui::is_position_in_painting_area(uint32_t x, uint32_t y) {
	const bool x_in_rect = (x > 15 + radius
			&& x < (15 + BSP_LCD_GetXSize() - 30 - radius));
	const bool y_in_rect = (y > 55 + radius
			&& y < (55 + BSP_LCD_GetYSize() - 85 - radius));

	return (x_in_rect && y_in_rect);
}

void Gui::clear_painting_area() {
	draw_painting_area();
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(pencil_color);
}

void Gui::draw_clear_button() {
	BSP_LCD_SetTextColor(LCD_COLOR_RED);
	BSP_LCD_DrawRect(5, 5, 60, 30);
	BSP_LCD_FillRect(10, 10, 50, 20);

	sFONT *pFont = &Font12;
	BSP_LCD_SetFont(pFont);
	BSP_LCD_SetBackColor(LCD_COLOR_RED);
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);

	BSP_LCD_DisplayStringAt(10, 15, (uint8_t*) " CLEAR ", LEFT_MODE);
}

bool Gui::is_position_in_clear_button(uint32_t x, uint32_t y) {
	const bool x_in_rect = (x > 10 && x < (10 + 50));
	const bool y_in_rect = (y > 10 && y < (10 + 20));
	return (x_in_rect && y_in_rect);
}

void Gui::draw_symbol_display_area() {
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_DrawCircle(BSP_LCD_GetXSize() / 2, 25, 20);
	BSP_LCD_FillCircle(BSP_LCD_GetXSize() / 2, 25, 15);
	update_symbol_display_area();
}

void Gui::update_symbol_display_area() {
	sFONT *pFont = &Font20;
	BSP_LCD_SetFont(pFont);
	BSP_LCD_SetTextColor(pencil_color);
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_DisplayChar(BSP_LCD_GetXSize() / 2 - 6, 17, selected_symbol + 48);
}

void Gui::draw_check_button() {
	BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
	BSP_LCD_DrawRect(BSP_LCD_GetXSize() - 65, 5, 60, 30);
	BSP_LCD_FillRect(BSP_LCD_GetXSize() - 60, 10, 50, 20);

	sFONT *pFont = &Font12;
	BSP_LCD_SetFont(pFont);
	BSP_LCD_SetBackColor(LCD_COLOR_GREEN);
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);

	BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize() - 10, 15, (uint8_t*) " DONE ",
			RIGHT_MODE);
}

bool Gui::is_position_in_check_button(uint32_t x, uint32_t y) {
	const bool x_in_rect = (x > (BSP_LCD_GetXSize() - 60))
			&& (x < (BSP_LCD_GetXSize() - 60 + 50));
	const bool y_in_rect = (y > 10 && y < (10 + 20));
	return (x_in_rect && y_in_rect);
}

void Gui::draw_celebration_animation() {
	BSP_LCD_SelectLayer(1);
	BSP_LCD_Clear(LCD_COLOR_WHITE);

	sFONT *pFont = &Font20;
	BSP_LCD_SetFont(pFont);
	BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
	BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
	BSP_LCD_DisplayStringAt(0, 50, (uint8_t*) "    WELL DONE!   ", CENTER_MODE);
	BSP_LCD_DisplayStringAt(0, 50 + pFont->Height,
			(uint8_t*) "        :)        ", CENTER_MODE);

	BSP_LCD_SetLayerVisible(1, ENABLE);
	HAL_Delay(1000);
	BSP_LCD_SetLayerVisible(1, DISABLE);
	HAL_Delay(500);
	BSP_LCD_SetLayerVisible(1, ENABLE);
	HAL_Delay(1000);
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
	BSP_LCD_SetTextColor(pencil_color);
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

