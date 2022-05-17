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

constexpr size_t RAW_IMAGE_LENGTH = 28*28;
using raw_image_t = float;

class Handwriting_recognizer final {
public:
	static void init();
	static char predict_ascii_char_from_raw_image(raw_image_t * raw_image_ptr);
};


#endif /* INC_APPLICATION_HANDWRITING_RECOGNIZER_H_ */
