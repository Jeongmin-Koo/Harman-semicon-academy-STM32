/*
 * Presenter.c
 *
 *  Created on: Jul 3, 2025
 *      Author: kccistc
 */
#include "Presenter.h"

void Presenter_Init()
{
	Presenter_TimeWatchInit();
	Presenter_StopWatchInit();
	Presenter_DistanceInit();
}

void Presenter_Execute()
{
	eModeState_t state = Model_GetModeState();
	switch(state)
	{
	case S_TIME_WATCH_MODE:
		Presenter_TimeWatchExecute();
		break;
	case S_STOP_WATCH_MODE:
		Presenter_StopWatchExecute();
		break;
	case S_DISTANCE_MODE:
		Presenter_DistanceExecute();
		break;
	}
}
