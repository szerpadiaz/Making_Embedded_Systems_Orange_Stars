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

void vprint(const char *fmt, va_list argp)
{
    char string[200];
    if(0 < vsprintf(string, fmt, argp)) // build string
    {
        //HAL_UART_Transmit(&huart1, (uint8_t*)string, strlen(string), 0xffffff);
    	// send message via UART
    	ConsoleIoSendString(string);
    }
}

void ei_printf(const char *format, ...) {
    va_list myargs;
    va_start(myargs, format);
    vprint(format, myargs);
    va_end(myargs);
}

static raw_image_t * raw_image_ptr;

int get_feature_data(size_t offset, size_t length, float *out_ptr) {
    memcpy(out_ptr, raw_image_ptr + offset, length * sizeof(float));
    return 0;
}

void Handwriting_recognizer::init() {

}

char Handwriting_recognizer::predict_ascii_char_from_raw_image(raw_image_t * raw_image)
{
	signal_t signal;
	raw_image_ptr = raw_image;
	signal.total_length = RAW_IMAGE_LENGTH;
	signal.get_data = &get_feature_data;

    ei_impulse_result_t result = { 0 };
    EI_IMPULSE_ERROR res = run_classifier(&signal, &result, false);
    ei_printf("run_classifier returned: %d\n", res);

    ei_printf("Predictions (DSP: %d ms., Classification: %d ms., Anomaly: %d ms.): \n",
        result.timing.dsp, result.timing.classification, result.timing.anomaly);

    // print the predictions
    ei_printf("[");
    for (size_t ix = 0; ix < EI_CLASSIFIER_LABEL_COUNT; ix++) {
  	  ei_printf_float(result.classification[ix].value);
        if (ix != EI_CLASSIFIER_LABEL_COUNT - 1) {
            ei_printf(", ");
        }
    }
    ei_printf("]\n\n\n");

	return 48;
}
