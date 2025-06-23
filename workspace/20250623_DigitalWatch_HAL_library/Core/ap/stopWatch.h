/*
 * stopWatch.h
 *
 *  Created on: Jun 23, 2025
 *      Author: kccistc
 */

#ifndef AP_STOPWATCH_H_
#define AP_STOPWATCH_H_

#include "stm32f4xx_hal.h"
#include "FND.h"
#include "Button.h"


void StopWatch_IncTimeCallBack();
void StopWatch_IncTime();
void StopWatch_Excute();
void StopWatch_Stop();
void StopWatch_Run();
void StopWatch_Clear();

extern Button_TypeDef hBtnMode;
extern Button_TypeDef hBtnRunStop;
extern Button_TypeDef hBtnClear;

#endif /* AP_STOPWATCH_H_ */
