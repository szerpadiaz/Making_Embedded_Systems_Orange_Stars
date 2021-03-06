/*
 * handwriting_recognizer.cpp
 *
 *  Created on: May 17, 2022
 *      Author: szerpadiaz
 */


#include "Application/handwriting_recognizer.h"

#include <Application/consoleIo.h>
#include <stdarg.h>
#include "edge-impulse-sdk/classifier/ei_run_classifier.h"


using namespace ei;

static bool debug = false;
constexpr bool debug_ei = false;

void vprint(const char *fmt, va_list argp)
{
    if(debug) {
        char string[200];
		if(0 < vsprintf(string, fmt, argp)) // build string
		{
			ConsoleIoSendString(string);
		}
    }
}

void ei_printf(const char *format, ...) {
    va_list myargs;
    va_start(myargs, format);
    vprint(format, myargs);
    va_end(myargs);
}

static raw_painting_image_t const * raw_image_ptr;

int get_feature_data(size_t offset, size_t length, raw_painting_image_t *out_ptr) {
    memcpy(out_ptr, raw_image_ptr + offset, length * sizeof(raw_painting_image_t));
    return 0;
}

void Handwriting_recognizer::init() {
	debug = false;
}

void Handwriting_recognizer::enable_debug(bool enable) {
	debug = enable;
}

char Handwriting_recognizer::get_char_from_image(raw_painting_image_t const * image_ptr)
{
	signal_t signal;
	raw_image_ptr = image_ptr;
	signal.total_length = PAINTING_IMAGE_LENGTH;
	signal.get_data = &get_feature_data;

    ei_impulse_result_t result = { 0 };
    EI_IMPULSE_ERROR res = run_classifier(&signal, &result, debug_ei);
    if (res != 0)
    	ei_printf("ERROR %d returned by run_classifier \r\n",res);

    // Convert prediction to char (so far only digits are supported)
    float max_value = 0;
    uint32_t label_detected = 0;
    for (size_t ix = 0; ix < EI_CLASSIFIER_LABEL_COUNT; ix++) {
    	auto const value = result.classification[ix].value;
    	if (value > max_value){
    		max_value = value;
    		label_detected = ix;
    	}
    }
    char char_detected = label_detected + 48;

    // Print detected character and prediction
    ei_printf("*********************************\r\n");
    ei_printf("*** CHARACTER DETECTED :  %c ***\r\n", char_detected);

    // Print all predictions
    ei_printf("Predictions (DSP: %d ms., Classification: %d ms.): \r\n",
        result.timing.dsp, result.timing.classification);
    for (size_t ix = 0; ix < EI_CLASSIFIER_LABEL_COUNT; ix++) {
    	const char * label = result.classification[ix].label;
    	ei_printf("(%s , ", label);
  	    ei_printf_float(result.classification[ix].value);
  	    ei_printf(")\r\n");
    }
    ei_printf("*********************************\r\n");

	return char_detected;
}
