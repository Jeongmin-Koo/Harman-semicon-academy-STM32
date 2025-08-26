/*
 * Model_TimeWatch.c
 *
 *  Created on: Jul 4, 2025
 *      Author: kccistc
 */

#include "Model_TimeWatch.h"

static eTimeWatchState_t timeWatchState = S_TIMEWATCH_NORMAL;

osMailQId timeWatchDataMailBox;
osMailQDef(timeWatchDataQueue, 4, timeWatch_t);

osMessageQId timeWatchEventMsgBox;
osMessageQDef(timeWatchEventQueue, 4, uint16_t);

void Model_TimeWatchInit()
{
	timeWatchEventMsgBox = osMessageCreate(osMessageQ(timeWatchEventQueue), NULL);
	timeWatchDataMailBox = osMailCreate(osMailQ(timeWatchDataQueue), NULL);
}

void Model_SetTimeWatchState(eTimeWatchState_t state)
{
	timeWatchState = state;
}

eTimeWatchState_t Model_GetTimeWatchState()
{
	return timeWatchState;
}
