/*
 * Listener.c
 *
 *  Created on: Jun 24, 2025
 *      Author: kccistc
 */
#include "Listener.h"

static void Listener_CheckButton();
static void Listener_CheackUart();

static uint8_t rcvData = 0;
static Que_TypeDef uartRxQue;

void Listener_Init()
{
	Button_Init(&hBtnMode, GPIOB, GPIO_PIN_5);
	Button_Init(&hBtnRunStop, GPIOB, GPIO_PIN_3);
	Button_Init(&hBtnClear, GPIOA, GPIO_PIN_10);
	Que_Init(&uartRxQue);
	HAL_UART_Receive_IT(&huart2, &rcvData, 1);
}

void Listener_Excute()
{
	Listener_CheckButton();
	Listener_CheackUart();
}

void Listener_CheckButton()
{
	// 100ms마다 button check
	static uint32_t prevChkBtnTime = 0;
	uint32_t curTick = HAL_GetTick(); // 1ms마다 1씩 증가
	if ((curTick - prevChkBtnTime) < 100) {
		return;
	}
	prevChkBtnTime = curTick;

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

void Listener_CheackUart()
{
	if (isQueEmpty(&uartRxQue)) {
		return;
	}
	int uartRxData = deQue(&uartRxQue);

	inputData_TypeDef inputData;

	if (uartRxData == 'm') {
		inputData.id = MODE;
		inputData.data = MODE_ACT;
		Controller_SetInputData(inputData);
	}
	else if (uartRxData == 'r') {
		inputData.id = STOPWATCH_RUN_STOP;
		inputData.data = MODE_ACT;
		Controller_SetInputData(inputData);
	}
	else if (uartRxData == 'c') {
		inputData.id = STOPWATCH_CLEAR;
		inputData.data = MODE_ACT;
		Controller_SetInputData(inputData);
	}
}

void Listener_UartCallBack()
{
	enQue(&uartRxQue,rcvData);
	HAL_UART_Receive_IT(&huart2, &rcvData, 1); //interrupt enable
}
