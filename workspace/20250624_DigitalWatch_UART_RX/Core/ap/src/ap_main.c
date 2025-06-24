/*
 * ap_main.c
 *
 *  Created on: Jun 19, 2025
 *      Author: kccistc
 */
#include "ap_main.h"




void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM2) {
		FND_DispDataCallBack();

		TimeWatch_IncTimeCallBack();
		StopWatch_IncTimeCallBack();
	}
}

int ap_main()
{

	HAL_TIM_Base_Start_IT(&htim2);
	while (1)
	{
		Listener_Excute();
		Controller_Excute();
		Presenter_Excute();
	}
	return 0;
}

void ap_init()
{
	Listener_Init();
}
