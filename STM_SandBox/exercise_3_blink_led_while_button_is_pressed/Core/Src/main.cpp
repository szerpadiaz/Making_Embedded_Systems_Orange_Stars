/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */


#include "main.h"

#include <Button.h>
#include <Led.h>
#include <Machine/Machine.h>

int main(void) {

	Machine::init();

	Led::init();

	Button::init();

	uint32_t time_to_toggle_led = HAL_GetTick();

	while (1) {
		if (Button::is_pressed() && (HAL_GetTick() > time_to_toggle_led)) {
			Led::toggle();
			time_to_toggle_led += 200;
		}
	}
}


