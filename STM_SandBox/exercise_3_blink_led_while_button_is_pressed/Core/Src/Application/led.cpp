/*
 * led.cpp
 *
 *  Created on: Apr 9, 2022
 *      Author: szerpadiaz
 */
#include "Application/led.h"
#include <Machine/gpio.h>
#include <Machine/io_mapping.h>

void Led::init() {
	HAL_GPIO_WritePin(USER_LED_PORT, USER_LED_PIN, GPIO_PIN_RESET);
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Pin =  USER_LED_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(USER_LED_PORT, &GPIO_InitStruct);
}

void Led::on()
{
	HAL_GPIO_WritePin(USER_LED_PORT, USER_LED_PIN, GPIO_PIN_SET);
}

void Led::off()
{
	HAL_GPIO_WritePin(USER_LED_PORT, USER_LED_PIN, GPIO_PIN_RESET);
}

void Led::toggle()
{
	HAL_GPIO_TogglePin(USER_LED_PORT, USER_LED_PIN);
}
