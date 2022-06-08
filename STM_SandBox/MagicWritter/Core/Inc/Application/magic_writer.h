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

enum class Event_t {
	ENTRY,
	EXIT,
	TIMEOUT,
	SELECT,
	PAINT,
	CHECK,
	CLEAR,
	TOTAL_EVENTS
};

enum class Status_t {TRANSITION, HANDLED, IGNORED};


class Magic_writer_t {
	typedef Status_t(Magic_writer_t::*State_Handler_t)(Event_t event);
public:

	Magic_writer_t();
	void run();
	//void set_remote_event();

private:
	void handle_local_event();
	//Event_t handle_remote_event();


	void handle_event(Event_t event);
	Status_t idle(Event_t event);
	Status_t ready(Event_t event);
	Status_t painting(Event_t event);

	void update_selection();
	void verify_selection();

	State_Handler_t state;
	char selected_char;
	uint32_t selection_last_update_time;
	uint32_t last_event_time;
	uint32_t x;
	uint32_t y;

	//Event_t remote_event;

};

}

#endif /* INC_APPLICATION_MAGIC_WRITER_H_ */
