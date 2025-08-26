/*
 * UltraSonic.c
 *
 *  Created on: Jun 26, 2025
 *      Author: kccistc
 */
#include "UltraSonic.h"
#define FILTER_SIZE 5

void delay_us(uint16_t us)
{
	__HAL_TIM_SET_COUNTER(&htim4, 0);
	HAL_TIM_Base_Start(&htim4);

	while(__HAL_TIM_GET_COUNTER(&htim4) < us);
	HAL_TIM_Base_Stop(&htim4);
}

void UltraSonic_Init(UltraSonic_TypeDef *hultra, GPIO_TypeDef *Trig_GPIOx, uint16_t Trig_pinNum,  GPIO_TypeDef *Echo_GPIOx, uint16_t Echo_pinNum) {
	hultra->Trig_GPIOx = Trig_GPIOx;
	hultra->Trig_pinNum = Trig_pinNum;
	hultra->Echo_GPIOx = Echo_GPIOx;
	hultra->Echo_pinNum = Echo_pinNum;
}

int UltraSonic_GetDistance (UltraSonic_TypeDef *hultra)
{
	uint32_t count = 0;
	int distance = 0;

	// trig
	HAL_GPIO_WritePin(hultra->Trig_GPIOx, hultra->Trig_pinNum, GPIO_PIN_SET);
	delay_us(10);
	HAL_GPIO_WritePin(hultra->Trig_GPIOx, hultra->Trig_pinNum, GPIO_PIN_RESET);

	// wait echo -> high
	uint32_t timeout = 60000;
	while(!(HAL_GPIO_ReadPin(hultra->Echo_GPIOx, hultra->Echo_pinNum)))
	{
		if (--timeout == 0)
			return -1;
	}

	// timer start
	__HAL_TIM_SET_COUNTER(&htim4, 0);
	HAL_TIM_Base_Start(&htim4);

	// wait echo -> low
	timeout = 60000;
	while(HAL_GPIO_ReadPin(hultra->Echo_GPIOx, hultra->Echo_pinNum))
	{
		if (--timeout == 0)
			return -1;
	}

	// timer stop
	HAL_TIM_Base_Stop(&htim4);
	count = __HAL_TIM_GET_COUNTER(&htim4);

	distance = count / 58;

	return distance;
}
