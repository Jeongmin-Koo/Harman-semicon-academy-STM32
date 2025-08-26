/*
 * Model_Mode.h
 *
 *  Created on: Jul 4, 2025
 *      Author: kccistc
 */

#ifndef AP_MODEL_MODEL_MODE_H_
#define AP_MODEL_MODEL_MODE_H_
#include <stdio.h>
#include "cmsis_os.h"

typedef enum {S_TIME_WATCH_MODE, S_STOP_WATCH_MODE, S_DISTANCE_MODE}eModeState_t;
typedef enum {EVENT_MODE}eModeEvent_t;


extern osMessageQId modeEventMsgBox;

void Model_ModeInit();
void Model_SetModeState(eModeState_t state);
eModeState_t Model_GetModeState();

#endif /* AP_MODEL_MODEL_MODE_H_ */
