/*
 * application_settings.h
 *
 *  Created on: Jun 3, 2022
 *      Author: szerpadiaz
 */

#ifndef INC_APPLICATION_SETTINGS_H_
#define INC_APPLICATION_SETTINGS_H_

#include <stdint.h>
#include "stm32f429i_discovery_lcd.h"


/** Input image for hand recognizer (EdgeImpulse model): */
constexpr uint32_t PAINTING_IMAGE_HIGH = 28;
constexpr uint32_t PAINTING_IMAGE_WIDTH = 28;
constexpr uint32_t PAINTING_IMAGE_LENGTH = PAINTING_IMAGE_HIGH * PAINTING_IMAGE_WIDTH;

using raw_painting_image_t = float;
//using raw_painting_image_t = std::array<float, PAINTING_IMAGE_LENGTH>;
//std::array would be better but does not work with  EdgeImpulse model

constexpr raw_painting_image_t PAINTING_IMAGE_PIXEL_SET_COLOR = 0xffffff;
constexpr raw_painting_image_t PAINTING_IMAGE_PIXEL_CLEAR_COLOR = 0;


constexpr uint32_t GUI_PAINTING_AREA_RESCALED_RATIO = 8;
constexpr uint32_t GUI_PAINTING_PEN_COLOR = LCD_COLOR_DARKGREEN;
constexpr uint32_t GUI_PAINTING_PEN_RADIUS = GUI_PAINTING_AREA_RESCALED_RATIO;

#endif /* INC_APPLICATION_SETTINGS_H_ */
