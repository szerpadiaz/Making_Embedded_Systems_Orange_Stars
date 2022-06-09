/*
 * User_control.cpp
 *
 *  Created on: Apr 30, 2022
 *      Author: szerpadiaz
 */

#ifndef INC_APPLICATION_USER_CONTROL_H_
#define INC_APPLICATION_USER_CONTROL_H_

#include <Application/console.h>
#include <tuple>

enum class Magic_writer_remote_event_t {
	NONE, SELECT, PAINT, CLEAR, CHECK
};

class Magic_writer_remote_control final {
public:
	static void init();
	static std::tuple<Magic_writer_remote_event_t, uint32_t, uint32_t> get_event();
	static bool is_remote_control_enable();

	static eCommandResult_T enable(const char buffer[]);
	static eCommandResult_T select(const char buffer[]);
	static eCommandResult_T paint(const char buffer[]);
	static eCommandResult_T clear(const char buffer[]);
	static eCommandResult_T check(const char buffer[]);
};

#endif /* INC_APPLICATION_USER_CONTROL_H_ */
