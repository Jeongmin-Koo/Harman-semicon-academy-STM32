/*
 * Button.c
 *
 *  Created on: Jun 19, 2025
 *      Author: kccistc
 */

//#include "Button.h"
//
//enum {PUSHED=0, RELEASED};
//typedef enum {NO_ACT, ACT_PUSHED, ACT_RELEASED} button_state_t;
//
//void Button_Init()
//{
//	GPIO_Init(GPIOC, 13, INPUT);
//}
//
//button_state_t Button_GetState()
//{
//	static uint32_t prevState = RELEASED;
//	uint32_t curState;
//	curState = GPIO_ReadPin(GPIOC, 13); // normal state is high
//
//	if ((prevState == RELEASED) && (curState == PUSHED)) { // button released -> pushed
//		prevState = PUSHED;
//		return ACT_PUSHED;
//	}
//	else if ((prevState == PUSHED) && (curState == RELEASED)) { // button released -> pushed
//		prevState = RELEASED;
//		return ACT_RELEASED;
//	}
//	return NO_ACT;
//}
#include "Button.h"

#define BUTTON_PIN 13
#define BUTTON_PORT GPIOC

// 입력값이 0이면 눌린 상태 (풀업 기준)
#define BUTTON_PRESSED   0
#define BUTTON_RELEASED  1

Button_TypeDef hBtnLed1;
Button_TypeDef hBtnLed2;
Button_TypeDef hBtnLed3;

void Button_Init(Button_TypeDef *hbtn, GPIO_TypeDef *GPIOx, uint16_t pinNum)
{
	hbtn->GPIOx = GPIOx;
	hbtn->pinNum = pinNum;
	hbtn->prevState = BUTTON_RELEASED;
}

button_state_t Button_GetState(Button_TypeDef *hbtn)
{
    uint32_t curState = HAL_GPIO_ReadPin(hbtn->GPIOx, hbtn->pinNum);

    button_state_t result = NO_ACT;

    if (hbtn->prevState == BUTTON_RELEASED && curState == BUTTON_PRESSED) {
		HAL_Delay(2); // debounce
		if (HAL_GPIO_ReadPin(hbtn->GPIOx, hbtn->pinNum) == BUTTON_PRESSED) {
			result = ACT_PUSHED;
    	}
    }
    else if (hbtn->prevState == BUTTON_PRESSED && curState == BUTTON_RELEASED) {
    	HAL_Delay(2); // debounce
		if (HAL_GPIO_ReadPin(hbtn->GPIOx, hbtn->pinNum) == BUTTON_RELEASED) {
			result = ACT_RELEASED;
    	}
    }
    hbtn->prevState = curState;
    return result;
}
