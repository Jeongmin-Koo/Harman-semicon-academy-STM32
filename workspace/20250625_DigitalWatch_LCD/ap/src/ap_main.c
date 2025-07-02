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

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart->Instance == USART2) {
		Listener_UartCallBack();
	}
}

int ap_main()
{

	HAL_TIM_Base_Start_IT(&htim2);
//	LCD_writeCharData('H');
//	LCD_writeCharData('E');
//	LCD_writeCharData('L');
//	LCD_writeCharData('L');
//	LCD_writeCharData('O');
	LCD_writeString("Hello");

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
	Presenter_Init();
}
