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

#include <machine/Machine.h>
#include "main.h"
#include <stdbool.h>

static void MX_GPIO_Init(void);


volatile uint32_t last_changed_time = 0;
volatile bool button_pressed = false;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if(GPIO_Pin == GPIO_PIN_0)
    {
    	uint32_t current_time = HAL_GetTick();
    	if ((last_changed_time - current_time) > 15)
    	{
    		// When the button is held-down, the signal is high (GPIO_PIN_SET, connected to power). Otherwise, the signal is low (connected to ground).
    		button_pressed = (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_SET);
    	}
    	last_changed_time = current_time;
    }
}

int main(void) {

	Machine::init();

	MX_GPIO_Init();

	uint32_t time_to_toggle_led = HAL_GetTick();

	while (1) {
		if (button_pressed && (HAL_GetTick() > time_to_toggle_led)) {
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

  // Configure user-button
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING; //GPIO_MODE_IT_RISING, GPIO_MODE_IT_RISING_FALLING
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  // Configure irq for user-button
  HAL_NVIC_SetPriority(EXTI0_IRQn, 2, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

}
