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

#include <machine/Machine.h>
#include <Button.h>

static void MX_GPIO_Init(void);


int main(void) {

	Machine::init();

	MX_GPIO_Init();

	Button::init();

	uint32_t time_to_toggle_led = HAL_GetTick();

	while (1) {
		if (Button::is_pressed() && (HAL_GetTick() > time_to_toggle_led)) {
			HAL_GPIO_TogglePin(GPIOD, LD4_Pin);
			time_to_toggle_led += 200;
		}
	}
}


static void MX_GPIO_Init(void)
{
  // configure output LEDs
  HAL_GPIO_WritePin(GPIOD, LD3_Pin|LD4_Pin|LD5_Pin|LD6_Pin, GPIO_PIN_RESET);
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  GPIO_InitStruct.Pin = LD3_Pin|LD4_Pin|LD5_Pin|LD6_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
}
