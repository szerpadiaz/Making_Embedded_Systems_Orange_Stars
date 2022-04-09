/*
 * led.cpp
 *
 *  Created on: Apr 9, 2022
 *      Author: szerpadiaz
 */

#include <Machine/Machine.h>
#include "led.h"

#include "main.h"

void Led::init() {
	HAL_GPIO_WritePin(GPIOD, LD4_Pin, GPIO_PIN_RESET);
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Pin =  LD4_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
}

void Led::on()
{
	HAL_GPIO_WritePin(GPIOD, LD4_Pin, GPIO_PIN_SET);
}

void Led::off()
{
	HAL_GPIO_TogglePin(GPIOD, LD4_Pin);
}

void Led::toggle()
{
	HAL_GPIO_WritePin(GPIOD, LD4_Pin, GPIO_PIN_RESET);
}
