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

	Gui::init();

	Handwriting_recognizer::init();
	Handwriting_recognizer::enable_debug(true);

	ConsoleInit();

	Magic_writer_t magic_writer {};
	Magic_writer_remote_control::init();

	while (1) {

		ConsoleProcess();

		magic_writer.run();
	}
}
