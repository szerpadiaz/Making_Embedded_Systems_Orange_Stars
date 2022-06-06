/**
 ******************************************************************************
 * @file           : main.cpp
 * @brief          : Program to blink an LED while a push-button is pressed
 ******************************************************************************
 ******************************************************************************
 */

#include <Application/button.h>
#include <Application/led.h>
#include <Machine/m_time.h>
#include <Machine/machine.h>

#include <Application/console.h>
#include <Application/User_control.h>
#include <Application/gui.h>
#include <Application/handwriting_recognizer.h>

#include <Application/magic_writer.h>
using namespace Magic_writer;

int main(void) {

	Machine::init();

	Led::init();

	Button::init();

	User_control_init();

	ConsoleInit();

	Gui::init();

	Handwriting_recognizer::init();
	Handwriting_recognizer::enable_debug(true);


	Magic_writer::Magic_writer magic_writer {};

	while (1) {

		//if (User_control_is_blinking_led_enable())
		//	Led::toggle();

		ConsoleProcess();

		magic_writer.run();
	}
}
