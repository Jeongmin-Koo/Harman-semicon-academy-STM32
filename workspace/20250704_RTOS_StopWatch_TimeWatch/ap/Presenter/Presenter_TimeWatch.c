/*
 * Presenter_TimeWatch.c
 *
 *  Created on: Jul 4, 2025
 *      Author: kccistc
 */

#include "Presenter_TimeWatch.h"
#include <string.h>
#include <stdio.h>

void Presenter_TimeWatchInit()
{

}

void Presenter_TimeWatchExecute()
{
	timeWatch_t timeWatchData;
	timeWatch_t *pTimeWatchData;

	osEvent evt = osMailGet(timeWatchDataMailBox, 0);
	if (evt.status == osEventMail) {
		pTimeWatchData = evt.value.p;
		memcpy(&timeWatchData, pTimeWatchData, sizeof(timeWatch_t));
		osMailFree(timeWatchDataMailBox, pTimeWatchData);

		Presenter_TimeWatch_FND(timeWatchData);
		Presenter_TimeWatch_LCD(timeWatchData);
	}

}

void Presenter_TimeWatch_FND(timeWatch_t timeWatchData)
{
	FND_WriteData(timeWatchData.hour*100 + timeWatchData.min);
	FND_WriteDp(FND_DP_1, FND_DP_OFF);
	FND_WriteDp(FND_DP_10, FND_DP_OFF);
	FND_WriteDp(FND_DP_1000, FND_DP_OFF);

	if (timeWatchData.msec <500) {
		FND_WriteDp(FND_DP_100, FND_DP_ON);
	}
	else {
		FND_WriteDp(FND_DP_100, FND_DP_OFF);
	}
}


void Presenter_TimeWatch_LCD(timeWatch_t timeWatchData)
{
	char str[50];

	sprintf(str, "TimeWatch        ");
	LCD_writeStringXY(0, 0, str);
	if (timeWatchData.msec < 300 || timeWatchData.msec > 700) {
		sprintf(str, "%02d:%02d:%02d     ", timeWatchData.hour, timeWatchData.min, timeWatchData.sec);
	}
	else {
		sprintf(str, "%02d %02d %02d     ", timeWatchData.hour, timeWatchData.min, timeWatchData.sec);
	}
	LCD_writeStringXY(1, 0, str);
}
