/*
 * SystemClock.h
 *
 *  Created on: Jun 19, 2025
 *      Author: kccistc
 */

#ifndef DRIVER_SYSTEMCLOCK_SYSTEMCLOCK_H_
#define DRIVER_SYSTEMCLOCK_SYSTEMCLOCK_H_
#include <stdint.h>
#include "stm32f411xe.h"

void SystemClock_Init();
void delay(int loop);

#endif /* DRIVER_SYSTEMCLOCK_SYSTEMCLOCK_H_ */
