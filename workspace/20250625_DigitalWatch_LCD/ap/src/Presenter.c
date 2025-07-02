/*
 * Presenter.c
 *
 *  Created on: Jun 24, 2025
 *      Author: kccistc
 */
#include "Presenter.h"
#include <string.h>
#include <stdio.h>
#include "usart.h"

static void Presenter_DispTimeWatch(watch_t watchData);
static void Presenter_DispStopWatch(watch_t watchData);
static void Presenter_DispFndTimeWatch(watch_t watchData);
static void Presenter_DispFndStopWatch(watch_t watchData);
static void Presenter_DispMonitorTimeWatch(watch_t watchData);
static void Presenter_DispMonitorStopWatch(watch_t watchData);
static void Presenter_DispLCDTimeWatch(watch_t watchData);

static watch_t dispData = {TIME_WATCH,12,0,0,0};

void Presenter_OutData(watch_t watchData)
{
	memcpy(&dispData, &watchData, sizeof(watch_t)); // data copy (watchData -> dispData)
}

void Presenter_Init()
{
	LCD_Init(&hi2c1);
}

void Presenter_Excute()
{
	if (dispData.id == TIME_WATCH) {
		Presenter_DispTimeWatch(dispData);
	} else {
		Presenter_DispStopWatch(dispData);
	}
}

void Presenter_DispTimeWatch(watch_t watchData)
{
	Presenter_DispFndTimeWatch(watchData);
	Presenter_DispMonitorTimeWatch(watchData);
	Presenter_DispLCDTimeWatch(watchData);
}

void Presenter_DispStopWatch(watch_t watchData)
{
	Presenter_DispFndStopWatch(watchData);
	Presenter_DispMonitorStopWatch(watchData);
	Presenter_DispLCDTimeWatch(watchData);
}

void Presenter_DispFndTimeWatch(watch_t watchData)
{
	FND_WriteData(watchData.hour*100 + watchData.min);

	FND_WriteDp(FND_DP_1000|FND_DP_1|FND_DP_10, FND_DP_OFF);

	if(watchData.msec < 500){
		FND_WriteDp(FND_DP_100, FND_DP_ON);
	} else {
	    FND_WriteDp(FND_DP_100, FND_DP_OFF);
	}
}

void Presenter_DispFndStopWatch(watch_t watchData)
{
	FND_WriteData((watchData.min %10 * 1000) + (watchData.sec*10)+(watchData.msec/100));
//	LCD_writeString(watchData.min + watchData.sec);

	FND_WriteDp(FND_DP_100|FND_DP_1, FND_DP_OFF);

	if (watchData.msec%100 < 50){            //
	   FND_WriteDp(FND_DP_10, FND_DP_ON);
	} else {
	   FND_WriteDp(FND_DP_10, FND_DP_OFF);
	}

	if (watchData.msec < 500){
	   FND_WriteDp(FND_DP_1000, FND_DP_ON);
	} else {
	   FND_WriteDp(FND_DP_1000, FND_DP_OFF);
	}
}

void Presenter_DispMonitorTimeWatch(watch_t watchData)
{
	char str[50];
	sprintf(str, "Time Watch : %02d:%02d:%02d.%03d\n", watchData.hour, watchData.min, watchData.sec, watchData.msec);
	HAL_UART_Transmit(&huart2, (uint8_t *)str, strlen(str), 1000);
}

void Presenter_DispMonitorStopWatch(watch_t watchData)
{
	char str[50];
	sprintf(str, "Stop Watch : %02d:%02d:%02d.%03d\n", watchData.hour, watchData.min, watchData.sec, watchData.msec);
	HAL_UART_Transmit(&huart2, (uint8_t *)str, strlen(str), 1000);
}

void Presenter_DispLCDTimeWatch(watch_t watchData)
{
	char lcdStr[20];
	sprintf(lcdStr, "%02d:%02d:%02d", watchData.hour, watchData.min, watchData.sec);

	LCD_writeStringXY(0, 0, lcdStr);
}
