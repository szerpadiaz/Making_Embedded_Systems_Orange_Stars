/*
 * Magic_writer_t.cpp
 *
 *  Created on: Jun 6, 2022
 *      Author: szerpadiaz
 */

#include "Application/Magic_writer.h"
#include <Application/gui.h>
#include <Application/button.h>
#include <Application/handwriting_recognizer.h>

using namespace Magic_writer;

Magic_writer_t::Magic_writer_t(void){

	this->selected_char = '0';
	Gui::draw_selected_char_display_area(this->selected_char);
	this->selection_last_update_time = Time::ticks_ms();

	this->state = &Magic_writer_t::ready;
	(this->*state)(Event_t::ENTRY);

	this->last_event_time = Time::ticks_ms();

	this->remote_control_enable = false;
}

void Magic_writer_t::enable_remote_control(bool enable)
{
	this->remote_control_enable = enable;
}

Status_t Magic_writer_t::idle(Event_t event) {
    Status_t status;
    switch (event) {
    	case Event_t::ENTRY: {
    		Gui::print_info(">> STATE: IDLE");
    		Gui::turn_off();
    		status = Status_t::HANDLED;
    		break;
    	}
        case Event_t::SELECT: {
            this->state = &Magic_writer_t::ready;
            status = Status_t::TRANSITION;
            break;
        }
        case Event_t::EXIT: {
    		Gui::turn_on();
    		status = Status_t::HANDLED;
        	break;
        }
        default: {
            status = Status_t::IGNORED;
            break;
        }
    }
    return status;

}

Status_t Magic_writer_t::ready(Event_t event) {
    Status_t status;
    switch (event) {
    	case Event_t::ENTRY: {
    		Gui::print_info(">> STATE: READY");
    		Gui::clear_painting_area();
    		status = Status_t::HANDLED;
    		break;
    	}
        case Event_t::SELECT: {
        	this->update_selection();
            this->state = &Magic_writer_t::ready;
            status = Status_t::HANDLED;
            break;
        }
        case Event_t::PAINT: {
        	Gui::update_painting_areas(this->x, this->y);
            this->state = &Magic_writer_t::painting;
            status = Status_t::TRANSITION;
            break;
        }
        case Event_t::TIMEOUT: {
            this->state = &Magic_writer_t::idle;
            status = Status_t::TRANSITION;
            break;
        }
        default: {
            status = Status_t::IGNORED;
            break;
        }
    }
    return status;

}

Status_t Magic_writer_t::painting(Event_t event) {
    Status_t status;
    switch (event) {
    	case Event_t::ENTRY: {
    		Gui::print_info(">> STATE: PAINTING");
    		status = Status_t::HANDLED;
    		break;
    	}
        case Event_t::SELECT: {
        	this->update_selection();
            this->state = &Magic_writer_t::ready;
            status = Status_t::TRANSITION;
            break;
        }
        case Event_t::PAINT: {
        	Gui::update_painting_areas(this->x, this->y);
            this->state = &Magic_writer_t::painting;
            status = Status_t::HANDLED;
            break;
        }
        case Event_t::CLEAR: {
			Gui::clear_painting_area();
            this->state = &Magic_writer_t::ready;
            status = Status_t::TRANSITION;
            break;
        }
        case Event_t::CHECK: {
        	this->verify_selection();
            this->state = &Magic_writer_t::ready;
            status = Status_t::TRANSITION;
            break;
        }
        case Event_t::TIMEOUT: {
            this->state = &Magic_writer_t::idle;
            status = Status_t::TRANSITION;
            break;
        }
        default: {
            status = Status_t::IGNORED;
            break;
        }
    }
    return status;

}

void Magic_writer_t::update_selection() {

	constexpr uint32_t update_rate_ms = 300;
	auto const now = Time::ticks_ms();
	if (Time::ticks_diff(now, this->selection_last_update_time) > update_rate_ms) {
		this->selection_last_update_time = now;
		this->selected_char = (selected_char == '9') ? '0' : (selected_char + 1);
		Gui::draw_selected_char_display_area(this->selected_char);
	}
}

void Magic_writer_t::verify_selection() {

	Gui::print_info(">> VERIFYING PAINTING");

	auto painting_image_ptr = Gui::get_painting_image();
	char detected_char = Handwriting_recognizer::get_char_from_image(painting_image_ptr);
	Gui::print_info(">> Char detected = %c ", detected_char);

	if(selected_char == detected_char)
		Gui::draw_right_answer_animation();
	else
		Gui::draw_wrong_answer_animation();
}

void Magic_writer_t::handle_local_event(){
	const auto [touch_event, x, y]= Gui::get_touch_event();
	switch (touch_event) {
	case Gui_event_t::ON_PAINTING_AREA:
		this->x = x;
		this->y = y;
		this->handle_event(Event_t::PAINT);
		break;
	case Gui_event_t::ON_CLEAR_BUTTON:
		this->handle_event(Event_t::CLEAR);
		break;
	case Gui_event_t::ON_CHECK_BUTTON:
		this->handle_event(Event_t::CHECK);
		break;
	default:
		break;
	}

	const bool button_pressed = Button::is_pressed();
	if (button_pressed) {
		this->handle_event(Event_t::SELECT);
	}

	// Check timeout
	constexpr uint32_t timeout_ms = 10000;
	const auto now = Time::ticks_ms();
	if (touch_event != Gui_event_t::NONE || button_pressed) {
		this->last_event_time = now;
	}
	else if (Time::ticks_diff(now, this->last_event_time) > timeout_ms) {
		this->handle_event(Event_t::TIMEOUT);
	}
}

void Magic_writer_t::handle_remote_event(){

	switch (this->remote_event) {
	case Event_t::PAINT:
	case Event_t::CLEAR:
	case Event_t::SELECT:
	case Event_t::CHECK:
		this->handle_event(this->remote_event);
	default:
		break;
	}
}

void Magic_writer_t::set_remote_event(Event_t event, uint32_t rescaled_x, uint32_t rescaled_y)
{
	if(this->remote_control_enable)
	{
		this->remote_event = event;
		auto const [x, y] = Gui::from_rescaled_to_painting_point(rescaled_x, rescaled_y);
		this->x = x;
		this->y = y;
	}
}

void Magic_writer_t::run(){

	if(this->remote_control_enable)
	{
		this->handle_remote_event();
	}
	else {
		this->handle_local_event();
	}
}

void Magic_writer_t::handle_event(Event_t event){

    Status_t status;
    State_Handler_t prev_state = this->state;
    //Q_ASSERT((me->state != (StateHandler)0) && (e->sig < MAX_SIG));
    status = (this->*state)(event);

    if(status == Status_t::TRANSITION) {
        //Q_ASSERT((me->state != (StateHandler)0));
        (this->*prev_state)(Event_t::EXIT);
        (this->*state)(Event_t::ENTRY);
    }
}


