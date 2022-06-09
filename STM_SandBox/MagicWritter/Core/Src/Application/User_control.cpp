/*
 * User_control.cpp
 *
 *  Created on: Apr 30, 2022
 *      Author: szerpadiaz
 */

#include <Application/User_control.h>
#include <Application/consoleCommands.h>
#include <Application/consoleIo.h>


static uint32_t rescaled_x;
static uint32_t rescaled_y;
static Magic_writer_remote_event_t remote_event;
static bool remote_control_enable;


void Magic_writer_remote_control::init() {
	rescaled_x = 0;
	rescaled_y = 0;
	remote_event = Magic_writer_remote_event_t::NONE;
	remote_control_enable = false;
}

std::tuple<Magic_writer_remote_event_t, uint32_t, uint32_t> Magic_writer_remote_control::get_event()
{
	auto const current_event = remote_event;
	remote_event = Magic_writer_remote_event_t::NONE;

	return {current_event, rescaled_x, rescaled_y};
}

bool Magic_writer_remote_control::is_remote_control_enable()
{
	return remote_control_enable;
}


eCommandResult_T Magic_writer_remote_control::enable(const char buffer[]) {

	int16_t parameterInt;
	eCommandResult_T result;
	result = ConsoleReceiveParamInt16(buffer, 1, &parameterInt);
	if ( COMMAND_SUCCESS == result )
	{
		remote_control_enable = static_cast<bool>(parameterInt);

		ConsoleIoSendString(STR_ENDLINE);
	}
	return result;
}

eCommandResult_T Magic_writer_remote_control::select(const char buffer[]) {
	IGNORE_UNUSED_VARIABLE(buffer);

	remote_event = Magic_writer_remote_event_t::SELECT;

	ConsoleIoSendString(STR_ENDLINE);
	return COMMAND_SUCCESS;
}

eCommandResult_T Magic_writer_remote_control::paint(const char buffer[]) {
	int16_t param_x = 0;
	int16_t param_y = 0;
	eCommandResult_T result;
	result = ConsoleReceiveParamInt16(buffer, 1, &param_x);
	if ( COMMAND_SUCCESS == result )
		result = ConsoleReceiveParamInt16(buffer, 2, &param_y);

	if ( COMMAND_SUCCESS == result )
	{
		remote_event = Magic_writer_remote_event_t::PAINT;
		rescaled_x = param_x;
		rescaled_y = param_y;

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

	remote_event = Magic_writer_remote_event_t::CLEAR;

	ConsoleIoSendString(STR_ENDLINE);
	return COMMAND_SUCCESS;
}

eCommandResult_T Magic_writer_remote_control::check(const char buffer[]) {
	IGNORE_UNUSED_VARIABLE(buffer);

	remote_event = Magic_writer_remote_event_t::CHECK;

	ConsoleIoSendString(STR_ENDLINE);
	return COMMAND_SUCCESS;
}


