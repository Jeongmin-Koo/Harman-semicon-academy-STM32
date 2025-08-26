/*
 * Listener.c
 *
 *  Created on: Jul 3, 2025
 *      Author: kccistc
 */
#include "Listener.h"

Button_TypeDef hbtnMode;

void Listener_Init()
{
	Button_Init(&hbtnMode, GPIOB, GPIO_PIN_5);
	Listener_TimeWatchInit();
	Listener_StopWatchInit();
	Listener_DistanceInit();
}

void Listener_Execute()
{
	eModeState_t state = Model_GetModeState();

	switch(state)
	{
	case S_TIME_WATCH_MODE : Listener_TimeWatchExecute();
		break;
	case S_STOP_WATCH_MODE : Listener_StopWatchExecute();
		break;
	case S_DISTANCE_MODE : Listener_DistanceExecute();
		break;
	}
	Listener_CheckButton();
}

void Listener_CheckButton()
{
	if (Button_GetState(&hbtnMode) == ACT_RELEASED) {
		osMessagePut(modeEventMsgBox, EVENT_MODE, 0);
	}
}
