/*
 * Presenter_StopWatch.c
 *
 *  Created on: Jul 3, 2025
 *      Author: kccistc
 */

#include "Presenter_StopWatch.h"

void Presenter_StopWatchInit()
{
	LCD_Init(&hi2c1);
}

void Presenter_StopWatchExecute()
{
	stopWatch_t stopWatchData;
	stopWatch_t *pStopWatchData;
	osEvent evt = osMailGet(stopWatchDataMailBox, 0);
	if (evt.status == osEventMail) {
		pStopWatchData = evt.value.p;
		memcpy(&stopWatchData, pStopWatchData, sizeof(stopWatch_t));
		osMailFree(stopWatchDataMailBox, pStopWatchData);
		Presenter_StopWatch_FND(stopWatchData);
		Presenter_StopWatch_LCD(stopWatchData);
	}
}

void Presenter_StopWatch_FND(stopWatch_t stopWatchData)
{
	FND_WriteData(stopWatchData.min%10*1000 + stopWatchData.sec%100*10 + stopWatchData.msec/100);
	FND_WriteDp(FND_DP_1, FND_DP_OFF);
	FND_WriteDp(FND_DP_100, FND_DP_OFF);
	if (stopWatchData.msec%100 <50) {
		FND_WriteDp(FND_DP_10, FND_DP_ON);
	}
	else {
		FND_WriteDp(FND_DP_10, FND_DP_OFF);
	}

	if (stopWatchData.msec <500) {
		FND_WriteDp(FND_DP_1000, FND_DP_ON);
	}
	else {
		FND_WriteDp(FND_DP_1000, FND_DP_OFF);
	}
}

void Presenter_StopWatch_LCD(stopWatch_t stopWatchData)
{
	char str[50];
	char str2[50];
	static uint32_t clearDispTime = 0;
	static uint8_t clearDispFlag = 0;

	eStopWatchState_t state;
	sprintf(str, "%02d:%02d:%02d.%03d          ", stopWatchData.hour, stopWatchData.min, stopWatchData.sec, stopWatchData.msec);
	LCD_writeStringXY(1, 0, str);
	state = Model_GetStopWatchState();

	if (state == S_STOPWATCH_RUN) {
		sprintf(str2, "StopWatch : RUN ");
	}
	else if (state == S_STOPWATCH_STOP) {
		sprintf(str2, "StopWatch : STOP");
	}
	else if (state == S_STOPWATCH_CLEAR) {
		sprintf(str2, "StopWatch : CLEAR");
	}
	LCD_writeStringXY(0, 0, str2);
}



