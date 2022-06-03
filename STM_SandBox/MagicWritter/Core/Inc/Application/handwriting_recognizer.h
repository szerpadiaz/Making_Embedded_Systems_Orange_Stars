/*
 * handwriting_recognizer.h
 *
 *  Created on: May 17, 2022
 *      Author: szerpadiaz
 */

#ifndef INC_APPLICATION_HANDWRITING_RECOGNIZER_H_
#define INC_APPLICATION_HANDWRITING_RECOGNIZER_H_

#include <stddef.h>
#include <array>

#include <application_settings.h>


class Handwriting_recognizer final {
public:
	static void init();
	static char get_char_from_image(raw_painting_image_t const * raw_image_ptr);
	static void enable_debug(bool enable);
};


#endif /* INC_APPLICATION_HANDWRITING_RECOGNIZER_H_ */
