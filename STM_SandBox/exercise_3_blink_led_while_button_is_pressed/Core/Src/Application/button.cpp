/*
 * button.cpp
 *
 *  Created on: Apr 8, 2022
 *      Author: szerpadiaz
 */

#include "Application/button.h"
#include <Machine/gpio.h>
#include <Machine/io_mapping.h>

volatile uint32_t last_irq_time = 0;
volatile bool button_pressed = false;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if(GPIO_Pin == USER_BUTTON_PIN)
    {
    	uint32_t current_time = HAL_GetTick();
    	if ((last_irq_time - current_time) > 15)
    	{
    		// When the button is held-down, the signal is high (GPIO_PIN_SET, connected to power). Otherwise, the signal is low (connected to ground).
    		button_pressed = (HAL_GPIO_ReadPin(USER_BUTTON_PORT, USER_BUTTON_PIN) == GPIO_PIN_SET);
    	}
    	last_irq_time = current_time;
    }
}

void Button::init() {
	// Configure user-button
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = USER_BUTTON_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING; //GPIO_MODE_IT_RISING, GPIO_MODE_IT_RISING_FALLING
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(USER_BUTTON_PORT, &GPIO_InitStruct);

	// Configure irq for user-button
	HAL_NVIC_SetPriority(static_cast<IRQn_Type>(USER_BUTTON_IRQn), 2, 0);
	HAL_NVIC_EnableIRQ (static_cast<IRQn_Type>(USER_BUTTON_IRQn));
}

bool Button::is_pressed()
{
	return button_pressed;
}
