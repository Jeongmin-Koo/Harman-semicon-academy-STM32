/*
 * Presenter_TimeWatch.h
 *
 *  Created on: Jul 4, 2025
 *      Author: kccistc
 */

#ifndef AP_PRESENTER_PRESENTER_TIMEWATCH_H_
#define AP_PRESENTER_PRESENTER_TIMEWATCH_H_

#include "cmsis_os.h"
#include "FND.h"
#include "lcd.h"
#include "Model_TimeWatch.h"
#include <stdio.h>
#include <string.h>
#include "stm32f4xx_hal.h"


void Presenter_TimeWatchInit();
void Presenter_TimeWatchExecute();
void Presenter_TimeWatch_FND(timeWatch_t timeWatchData);
void Presenter_TimeWatch_LCD(timeWatch_t timeWatchData);

#endif /* AP_PRESENTER_PRESENTER_TIMEWATCH_H_ */
