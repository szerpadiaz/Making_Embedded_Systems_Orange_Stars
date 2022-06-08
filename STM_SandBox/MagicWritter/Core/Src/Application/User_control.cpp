/*
 * User_control.cpp
 *
 *  Created on: Apr 30, 2022
 *      Author: szerpadiaz
 */

#include <Application/User_control.h>
#include <Application/consoleCommands.h>
#include <Application/consoleIo.h>

using namespace Magic_writer;
static 	Magic_writer_t * magic_writer_ptr = nullptr;

void Magic_writer_remote_control::init(Magic_writer_t * magic_writer) {
	magic_writer_ptr = magic_writer;
}

eCommandResult_T Magic_writer_remote_control::enable(const char buffer[]) {

	int16_t parameterInt;
	eCommandResult_T result;
	result = ConsoleReceiveParamInt16(buffer, 1, &parameterInt);
	if ( COMMAND_SUCCESS == result )
	{
		magic_writer_ptr->enable_remote_control(static_cast<bool>(parameterInt));

		ConsoleIoSendString(STR_ENDLINE);
	}
	return result;
}


eCommandResult_T Magic_writer_remote_control::select(const char buffer[]) {
	IGNORE_UNUSED_VARIABLE(buffer);
	magic_writer_ptr->set_remote_event(Event_t::SELECT);

	ConsoleIoSendString(STR_ENDLINE);
	return COMMAND_SUCCESS;
}

eCommandResult_T Magic_writer_remote_control::paint(const char buffer[]) {
	int16_t x = 0;
	int16_t y = 0;
	eCommandResult_T result;
	result = ConsoleReceiveParamInt16(buffer, 1, &x);
	if ( COMMAND_SUCCESS == result )
		result = ConsoleReceiveParamInt16(buffer, 2, &y);

	if ( COMMAND_SUCCESS == result )
	{
		magic_writer_ptr->set_remote_event(Event_t::PAINT, x, y);

		ConsoleIoSendString(STR_ENDLINE);
		return COMMAND_SUCCESS;
	}
	else
	{
		return COMMAND_PARAMETER_ERROR;
	}
}

eCommandResult_T Magic_writer_remote_control::clear(const char buffer[]) {
	IGNORE_UNUSED_VARIABLE(buffer);
	magic_writer_ptr->set_remote_event(Event_t::CLEAR);

	ConsoleIoSendString(STR_ENDLINE);
	return COMMAND_SUCCESS;
}

eCommandResult_T Magic_writer_remote_control::check(const char buffer[]) {
	IGNORE_UNUSED_VARIABLE(buffer);
	magic_writer_ptr->set_remote_event(Event_t::CHECK);

	ConsoleIoSendString(STR_ENDLINE);
	return COMMAND_SUCCESS;
}


