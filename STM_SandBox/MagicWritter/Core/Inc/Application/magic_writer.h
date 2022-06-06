/*
 * magic_writer.h
 *
 *  Created on: Jun 6, 2022
 *      Author: szerpadiaz
 */

#ifndef INC_APPLICATION_MAGIC_WRITER_H_
#define INC_APPLICATION_MAGIC_WRITER_H_

#include <Machine/m_time.h>

namespace Magic_writer {

enum class Event {
	ENTRY, EXIT,
	//TIMEOUT,
	SELECT,
	PAINT,
	CHECK,
	CLEAR,
	MAX_SIG
};
enum class Status {
	TRANSITION, HANDLED, IGNORED, INIT
};


class Magic_writer {
	typedef Status(Magic_writer::*State_Handler_t)(Event event);
public:

	Magic_writer();
	void run();

private:
	void handle_event(Event event);
	Status ready(Event event);
	Status painting(Event event);

	bool is_time_to_check_button();

	State_Handler_t state;
	char selected_char;
	uint32_t time_to_check_button;
};

}

#endif /* INC_APPLICATION_MAGIC_WRITER_H_ */
