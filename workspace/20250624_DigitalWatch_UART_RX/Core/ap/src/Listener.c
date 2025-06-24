/*
 * Listener.c
 *
 *  Created on: Jun 24, 2025
 *      Author: kccistc
 */
#include "Listener.h"

static void Listener_CheckButton();

void Listener_Init()
{
	Button_Init(&hBtnMode, GPIOB, GPIO_PIN_5);
	Button_Init(&hBtnRunStop, GPIOB, GPIO_PIN_3);
	Button_Init(&hBtnClear, GPIOA, GPIO_PIN_10);
}

void Listener_Excute()
{
	Listener_CheckButton();
	Listener_CheckUart();
}

void Listener_CheckButton()
{
	inputData_TypeDef inputData;

	if (Button_GetState(&hBtnMode) == ACT_RELEASED) {
		inputData.id = MODE;
		inputData.data = MODE_ACT;
		Controller_SetInputData(inputData);
	}
	else if (Button_GetState(&hBtnRunStop) == ACT_RELEASED) {
		inputData.id = STOPWATCH_RUN_STOP;
		inputData.data = MODE_ACT;
		Controller_SetInputData(inputData);
	}
	else if (Button_GetState(&hBtnClear) == ACT_RELEASED) {
		inputData.id = STOPWATCH_CLEAR;
		inputData.data = MODE_ACT;
		Controller_SetInputData(inputData);
	}
}

void Listener_CheckUart()
{
    uint8_t rxData;
    inputData_TypeDef inputData;

    if (HAL_UART_Receive(&huart2, &rxData, 1, 100) == HAL_OK)
    {
        if (rxData == 'm')
        {
            inputData.id = MODE;
            inputData.data = MODE_ACT;
            Controller_SetInputData(inputData);
        }
        else if (rxData == 'r')
        {
    		inputData.id = STOPWATCH_RUN_STOP;
    		inputData.data = MODE_ACT;
    		Controller_SetInputData(inputData);
        }
        else if (rxData == 'c')
        {
    		inputData.id = STOPWATCH_CLEAR;
    		inputData.data = MODE_ACT;
    		Controller_SetInputData(inputData);
        }
    }
}
