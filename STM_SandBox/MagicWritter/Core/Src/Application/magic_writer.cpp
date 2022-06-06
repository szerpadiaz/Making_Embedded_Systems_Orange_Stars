/*
 * magic_writer.cpp
 *
 *  Created on: Jun 6, 2022
 *      Author: szerpadiaz
 */

#include "Application/magic_writer.h"
#include <Application/gui.h>
#include <Application/button.h>
#include <Application/handwriting_recognizer.h>

namespace Magic_writer {

Magic_writer::Magic_writer(void){
	this->selected_char = '0';
	Gui::draw_selected_char_display_area(this->selected_char);
	this->state = &Magic_writer::ready;
	(this->*state)(Event::ENTRY);
	this->time_to_check_button = 0;
}

Status Magic_writer::ready(Event event) {
    Status status;
    switch (event) {
    	case Event::ENTRY: {
    		Gui::print_info(">> STATE: READY");
    		Gui::clear_painting_area();
    		status = Status::HANDLED;
    		break;
    	}
        case Event::PAINT: {
            this->state = &Magic_writer::painting;
            status = Status::TRANSITION;
            break;
        }
        default: {
            status = Status::IGNORED;
            break;
        }
    }
    return status;

}

Status Magic_writer::painting(Event event) {
    Status status;
    switch (event) {
    	case Event::ENTRY: {
    		Gui::print_info(">> STATE: PAINTING");
    		status = Status::HANDLED;
    		break;
    	}
        case Event::SELECT: {
            this->state = &Magic_writer::ready;
            status = Status::TRANSITION;
            break;
        }
        case Event::CLEAR: {
            this->state = &Magic_writer::ready;
            status = Status::TRANSITION;
            break;
        }
        case Event::CHECK: {
    		Gui::print_info(">> VERIFYING PAINTING");
    		auto painting_image_ptr = Gui::get_painting_image();
    		char detected_char = Handwriting_recognizer::get_char_from_image(painting_image_ptr);
    		Gui::print_info(">> Char detected = %c ", detected_char);

    		if(selected_char == detected_char)
    			Gui::draw_right_answer_animation();
    		else
    			Gui::draw_wrong_answer_animation();

            this->state = &Magic_writer::ready;
            status = Status::TRANSITION;
            break;
        }
        default: {
            status = Status::IGNORED;
            break;
        }
    }
    return status;

}

bool Magic_writer::is_time_to_check_button() {

	auto const now = Time::ticks_ms();
	if (Time::ticks_diff(this->time_to_check_button, now) > 0) {
		return false;
	} else {
		this->time_to_check_button = Time::ticks_add(now, 300);
		return true;
	}
}

void Magic_writer::run(){

	if (Button::is_pressed() && this->is_time_to_check_button()) {
		this->selected_char = (selected_char == '9') ? '0' : (selected_char + 1);
		Gui::draw_selected_char_display_area(this->selected_char);
		this->handle_event(Event::SELECT);
	}

	switch (Gui::get_touch_event()) {
	case Gui_event_t::ON_PAINTING_AREA:
		this->handle_event(Event::PAINT);
		break;
	case Gui_event_t::ON_CLEAR_BUTTON:
		this->handle_event(Event::CLEAR);
		break;
	case Gui_event_t::ON_CHECK_BUTTON:
		this->handle_event(Event::CHECK);
		break;
	default:
		break;
	}
}

void Magic_writer::handle_event(Event event){

    Status status;
    State_Handler_t prev_state = this->state;
    //Q_ASSERT((me->state != (StateHandler)0) && (e->sig < MAX_SIG));
    status = (this->*state)(event);

    if(status == Status::TRANSITION) {
        //Q_ASSERT((me->state != (StateHandler)0));
        (this->*prev_state)(Event::EXIT);
        (this->*state)(Event::ENTRY);
    }
}

}


/*
#include <Application/magic_writer.h>
using namespace Magic_writer;

Magic_writer::Magic_writer magic_writer {};

magic_writer.run();

*/