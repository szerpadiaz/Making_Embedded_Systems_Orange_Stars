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
#include <Application/User_control.h>
#include <Application/led.h>

using namespace Magic_writer;

constexpr int32_t timeout_ms = 100000;
constexpr int32_t led_rate_ms = 300;
constexpr int32_t update_selection_rate_ms = 300;

Magic_writer_t::Magic_writer_t(void){

	this->selected_char = '0';
	Gui::draw_selected_char_display_area(this->selected_char);
	this->selection_last_update_time = Time::ticks_ms();

	this->state = &Magic_writer_t::ready;
	(this->*state)(Event_t::ENTRY);

	const auto now = Time::ticks_ms();
	this->last_event_time = now;
	this->last_led_toggle_time = now;
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
    		Gui::clear_painting_area(this->selected_char);
    		Gui::print_info(">> STATE: READY");
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
        case Event_t::CLEAR: {;
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
	auto const now = Time::ticks_ms();
	if (Time::ticks_diff(now, this->selection_last_update_time) > update_selection_rate_ms) {
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

bool Magic_writer_t::handle_local_event(){
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

	return (touch_event != Gui_event_t::NONE || button_pressed);
}

bool Magic_writer_t::handle_remote_event(){

	const auto [remote_event, rescaled_x, rescaled_y]= Magic_writer_remote_control::get_event();
	switch (remote_event) {
	case Magic_writer_remote_event_t::PAINT: {
		auto const [x, y] = Gui::from_rescaled_to_painting_point(rescaled_x, rescaled_y);
		this->x = x;
		this->y = y;
		this->handle_event(Event_t::PAINT);
		break;
	}
	case Magic_writer_remote_event_t::CLEAR:
		this->handle_event(Event_t::CLEAR);
		break;
	case Magic_writer_remote_event_t::CHECK:
		this->handle_event(Event_t::CHECK);
		break;
	case Magic_writer_remote_event_t::SELECT:
		this->handle_event(Event_t::SELECT);
	default:
		break;
	}

	return (remote_event != Magic_writer_remote_event_t::NONE);
}

void Magic_writer_t::run(){

	bool there_was_an_event;
	if(Magic_writer_remote_control::is_remote_control_enable())
	{
		there_was_an_event = this->handle_remote_event();
	}
	else {
		there_was_an_event = this->handle_local_event();
	}

	// Check timeout
	const auto now = Time::ticks_ms();
	if (there_was_an_event) {
		this->last_event_time = now;
	}
	else if (Time::ticks_diff(now, this->last_event_time) > timeout_ms) {
		this->handle_event(Event_t::TIMEOUT);
	}

	// Toggle status led
	if (Time::ticks_diff(now, this->last_led_toggle_time) > led_rate_ms) {
		Led::toggle();
		this->last_led_toggle_time = now;
	}
}

void Magic_writer_t::handle_event(Event_t event){
    //ASSERT((this->state != (State_Handler_t)0) && (event < Event_t::TOTAL_EVENTS));
    Status_t status;
    State_Handler_t prev_state = this->state;
    status = (this->*state)(event); // updates this->state

    if(status == Status_t::TRANSITION) {
        //ASSERT((this->state != (State_Handler_t)0));
        (this->*prev_state)(Event_t::EXIT);
        (this->*state)(Event_t::ENTRY);
    }
}


