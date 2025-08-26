/*
 * TimeWatch.c
 *
 *  Created on: Jul 4, 2025
 *      Author: kccistc
 */
#include "TimeWatch.h"
#include <string.h>

timeWatch_t timeWatchData;

void TimeWatch_Init()
{
	timeWatchData.hour = 12;
	timeWatchData.min  = 0;
	timeWatchData.sec  = 0;
	timeWatchData.msec = 0;

	timeWatch_t *pTimeWatchData = osMailAlloc(timeWatchDataMailBox, 0);
	memcpy(pTimeWatchData, &timeWatchData, sizeof(timeWatch_t));
	osMailPut(timeWatchDataMailBox, pTimeWatchData);
}

void TimeWatch_Execute()
{
	eTimeWatchState_t state = Model_GetTimeWatchState();

	switch(state)
	{
	case S_TIMEWATCH_NORMAL:
		TimeWatch_Normal();
		break;
	case S_TIMEWATCH_MODIFY_HOUR:
		TimeWatch_ModifyHour();
		break;
	case S_TIMEWATCH_MODIFY_MIN:
		TimeWatch_ModifyMin();
		break;
	case S_TIMEWATCH_MODIFY_SEC:
		TimeWatch_ModifySec();
		break;
	default:
		break;
	}
}

void TimeWatch_Normal()
{
	static uint8_t prevMilSec = 0;
	if (prevMilSec == timeWatchData.msec) {
		return;
	}
	prevMilSec = timeWatchData.msec;

	timeWatch_t *pTimeWatchData = osMailAlloc(timeWatchDataMailBox, 0);
	memcpy(pTimeWatchData, &timeWatchData, sizeof(timeWatch_t));
	osMailPut(timeWatchDataMailBox, pTimeWatchData);

	osEvent evt = osMessageGet(timeWatchEventMsgBox, 0);
	uint16_t evtState;

	if (evt.status == osEventMessage) {
		evtState = evt.value.v;

		if (evtState == EVENT_TIME_MODIFY) {
			Model_SetTimeWatchState(S_TIMEWATCH_MODIFY_HOUR);
		}
	}
}

void TimeWatch_ModifyHour()
{
	osEvent evt = osMessageGet(timeWatchEventMsgBox, 0);
	uint16_t evtState;

	if (evt.status == osEventMessage) {
		evtState = evt.value.v;

		if (evtState == EVENT_TIME_MODIFY) {
			Model_SetTimeWatchState(S_TIMEWATCH_MODIFY_MIN);
		}
		else if (evtState == EVENT_TIME_SET) {
			if (timeWatchData.hour == 23) {
				timeWatchData.hour = 0;
			}
			else {
				timeWatchData.hour++;
			}
			// Presenter에서 반영되도록
			timeWatch_t *pTimeWatchData = osMailAlloc(timeWatchDataMailBox, 0);
			memcpy(pTimeWatchData, &timeWatchData, sizeof(timeWatch_t));
			osMailPut(timeWatchDataMailBox, pTimeWatchData);
		}
	}

}

void TimeWatch_ModifyMin()
{
	osEvent evt = osMessageGet(timeWatchEventMsgBox, 0);
	uint16_t evtState;

	if (evt.status == osEventMessage) {
		evtState = evt.value.v;

		if (evtState == EVENT_TIME_MODIFY) {
			Model_SetTimeWatchState(S_TIMEWATCH_MODIFY_SEC);
		}
		else if (evtState == EVENT_TIME_SET) {
			if (timeWatchData.min == 59) {
				timeWatchData.min = 0;
			}
			else {
				timeWatchData.min++;
			}
			// Presenter에서 반영되도록
			timeWatch_t *pTimeWatchData = osMailAlloc(timeWatchDataMailBox, 0);
			memcpy(pTimeWatchData, &timeWatchData, sizeof(timeWatch_t));
			osMailPut(timeWatchDataMailBox, pTimeWatchData);
		}
	}
}

void TimeWatch_ModifySec()
{
	osEvent evt = osMessageGet(timeWatchEventMsgBox, 0);
	uint16_t evtState;

	if (evt.status == osEventMessage) {
		evtState = evt.value.v;

		if (evtState == EVENT_TIME_MODIFY) {
			Model_SetTimeWatchState(S_TIMEWATCH_NORMAL);
		}
		else if (evtState == EVENT_TIME_SET) {
			timeWatchData.sec = 0;
			timeWatchData.msec = 0;
			// Presenter에서 반영되도록
			timeWatch_t *pTimeWatchData = osMailAlloc(timeWatchDataMailBox, 0);
			memcpy(pTimeWatchData, &timeWatchData, sizeof(timeWatch_t));
			osMailPut(timeWatchDataMailBox, pTimeWatchData);
		}
	}
}

void TimeWatch_IncTimeCallBack()
{
	if (timeWatchData.msec <= 1000-1) {
		timeWatchData.msec++;
		return;
	}
	else {
		timeWatchData.msec = 0;
	}

	if (timeWatchData.sec <= 60-1) {
		timeWatchData.sec++;
		return;
	}
	else {
		timeWatchData.sec = 0;
	}

	if (timeWatchData.min <= 60-1) {
		timeWatchData.min++;
		return;
	}
	else {
		timeWatchData.min = 0;
	}

	if (timeWatchData.hour <= 24-1) {
		timeWatchData.hour++;
		return;
	}
	else {
		timeWatchData.hour = 0;
	}
}
