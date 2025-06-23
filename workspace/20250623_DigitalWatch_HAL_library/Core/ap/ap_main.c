/*
 * ap_main.c
 *
 *  Created on: Jun 19, 2025
 *      Author: kccistc
 */

#include "ap_main.h"

typedef enum {TIME_WATCH=0, STOP_WATCH} watch_state_t;

Button_TypeDef hBtnMode;
Button_TypeDef hBtnRunStop;
Button_TypeDef hBtnClear;

dot_t dot[4] = {dot_off, dot_off, dot_off, dot_off};

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM2) {
		FND_DispData();
		TimeWatch_IncTimeCallBack();
		StopWatch_IncTimeCallBack();
	}

}

int ap_main()
{
	watch_state_t modeState = TIME_WATCH;

	FND_WriteData(1234);
	HAL_TIM_Base_Start_IT(&htim2);
	while (1)
	{
		switch(modeState)
		{
		case TIME_WATCH:
			TimeWatch_Excute();
			dot[DIGIT_1] = dot_on;
			dot[DIGIT_10] = dot_on;
			dot[DIGIT_100] = dot_on;
			dot[DIGIT_1000] = dot_on;
			if (Button_GetState(&hBtnMode) == ACT_RELEASED) {
				modeState = STOP_WATCH;
			}
			break;
		case STOP_WATCH:
			StopWatch_Excute();
			if (Button_GetState(&hBtnMode) == ACT_RELEASED) {
				modeState = TIME_WATCH;
			}
			break;
		}
	}
	return 0;
}

void ap_init()
{
	Button_Init(&hBtnMode, GPIOB, GPIO_PIN_5);
	Button_Init(&hBtnRunStop, GPIOB, GPIO_PIN_3);
	Button_Init(&hBtnClear, GPIOA, GPIO_PIN_10);
}
