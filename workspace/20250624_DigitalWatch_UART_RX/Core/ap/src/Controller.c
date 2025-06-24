/*
 * Controller.c
 *
 *  Created on: Jun 24, 2025
 *      Author: kccistc
 */
#include "Controller.h"

typedef enum {TIME_WATCH=0, STOP_WATCH} watchMode_state_t;

inputData_TypeDef controlData = {0};
static watchMode_state_t modeState = TIME_WATCH;

void Controller_Excute()
{
	Controller_Mode();
}

void Controller_SetInputData(inputData_TypeDef inputData)
{
	if (inputData.id == MODE) {
		controlData.id = MODE;
		controlData.data = MODE_ACT;
	}
	else if (inputData.id == STOPWATCH_RUN_STOP) {
		controlData.id = STOPWATCH_RUN_STOP;
		controlData.data = MODE_ACT;
	}
	else if (inputData.id == STOPWATCH_CLEAR) {
		controlData.id = STOPWATCH_CLEAR;
		controlData.data = MODE_ACT;
	}
}

void Controller_Mode()
{
	switch(modeState)
	{
		case TIME_WATCH:
			if (controlData.id == MODE) {
				controlData.id = NO_CONTROL;
				modeState = STOP_WATCH;
			}
			TimeWatch_Excute();
			break;
		case STOP_WATCH:
			if (controlData.id == MODE) {
				controlData.id = NO_CONTROL;
				modeState = TIME_WATCH;
			}
			StopWatch_Excute();
		break;
	}
}
