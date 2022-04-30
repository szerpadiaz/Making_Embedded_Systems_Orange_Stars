/*
 * machine.h
 *
 *  Created on: Apr 8, 2022
 *      Author: szerpadiaz
 */

#ifndef MACHINE_MACHINE_H_
#define MACHINE_MACHINE_H_

class Machine final {
public:
	static void init();
	static void error_handler();
private:
	static void configure_clock();
};

#endif /* MACHINE_MACHINE_H_ */

