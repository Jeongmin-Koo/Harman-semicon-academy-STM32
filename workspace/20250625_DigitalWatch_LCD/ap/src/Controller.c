/*
 * Controller.c
 *
 *  Created on: Jun 24, 2025
 *      Author: kccistc
 */
#include "Controller.h"

typedef enum {S_TIME_WATCH=0, S_STOP_WATCH} watchMode_state_t;

inputData_TypeDef controlData = {0};
static watchMode_state_t modeState = TIME_WATCH;
static void Controller_Mode();

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
		case S_TIME_WATCH:
			if (controlData.id == MODE) {
				controlData.id = NO_CONTROL;
				modeState = S_STOP_WATCH;
			}
			TimeWatch_Excute();
			break;
		case S_STOP_WATCH:
			if (controlData.id == MODE) {
				controlData.id = NO_CONTROL;
				modeState = S_TIME_WATCH;
			}
			StopWatch_Excute();
		break;
	}
}
