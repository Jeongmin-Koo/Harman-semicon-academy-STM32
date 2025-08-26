/*
 * TimeWatch.h
 *
 *  Created on: Jul 4, 2025
 *      Author: kccistc
 */

#ifndef AP_CONTROLLER_TIMEWATCH_H_
#define AP_CONTROLLER_TIMEWATCH_H_
#include <stdint.h>
#include "cmsis_os.h"
#include "Model_TimeWatch.h"

extern timeWatch_t timeWatchData;

void TimeWatch_Init();
void TimeWatch_Execute();
void TimeWatch_IncTimeCallBack();
void TimeWatch_Normal();
void TimeWatch_ModifyHour();
void TimeWatch_ModifyMin();
void TimeWatch_ModifySec();

#endif /* AP_CONTROLLER_TIMEWATCH_H_ */
