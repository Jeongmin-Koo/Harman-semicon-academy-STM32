/*
 * Controller.h
 *
 *  Created on: Jul 3, 2025
 *      Author: kccistc
 */

#ifndef AP_CONTROLLER_CONTROLLER_H_
#define AP_CONTROLLER_CONTROLLER_H_
#include "Model_Mode.h"
#include "StopWatch.h"
#include "TimeWatch.h"
#include "Distance.h"
#include <string.h>
#include <stdio.h>

void Controller_Init();
void Controller_Execute();
void Controller_CheckEventMode();

#endif /* AP_CONTROLLER_CONTROLLER_H_ */
