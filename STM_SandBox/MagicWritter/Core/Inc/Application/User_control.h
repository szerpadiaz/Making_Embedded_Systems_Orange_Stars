/*
 * User_control.cpp
 *
 *  Created on: Apr 30, 2022
 *      Author: szerpadiaz
 */

#ifndef INC_APPLICATION_USER_CONTROL_H_
#define INC_APPLICATION_USER_CONTROL_H_

#include "Application/magic_writer.h"
#include <Application/console.h>

class Magic_writer_remote_control final {
public:
	static void init(Magic_writer::Magic_writer_t * magic_writer);
	static eCommandResult_T enable(const char buffer[]);
	static eCommandResult_T select(const char buffer[]);
	static eCommandResult_T paint(const char buffer[]);
	static eCommandResult_T clear(const char buffer[]);
	static eCommandResult_T check(const char buffer[]);
};

#endif /* INC_APPLICATION_USER_CONTROL_H_ */
