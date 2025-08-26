/*
 * Listener_StopWatch.h
 *
 *  Created on: Jul 3, 2025
 *      Author: kccistc
 */

#ifndef AP_LISTENER_LISTENER_STOPWATCH_H_
#define AP_LISTENER_LISTENER_STOPWATCH_H_

#include <stdint.h>
#include "cmsis_os.h"
#include "Model_StopWatch.h"
#include "Button.h"

void Listener_StopWatchInit();
void Listener_StopWatchExecute();
void Listener_StopWatch_CheckButton();

#endif /* AP_LISTENER_LISTENER_STOPWATCH_H_ */
