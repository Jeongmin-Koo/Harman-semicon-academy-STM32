/*
 * Button.h
 *
 *  Created on: Jun 19, 2025
 *      Author: kccistc
 */
#ifndef BUTTON_BUTTON_H_
#define BUTTON_BUTTON_H_

#include <stdint.h>
#include "stm32f4xx_hal.h"

typedef struct {
	GPIO_TypeDef *GPIOx;
	uint16_t pinNum;
	uint32_t prevState;
}Button_TypeDef;

extern Button_TypeDef hBtnMode;
extern Button_TypeDef hBtnRunStop;
extern Button_TypeDef hBtnClear;

typedef enum { NO_ACT, ACT_PUSHED, ACT_RELEASED } button_state_t;
void Button_Init(Button_TypeDef *hbtn, GPIO_TypeDef *GPIOx, uint16_t pinNum);
button_state_t Button_GetState(Button_TypeDef *hbtn);

#endif /* BUTTON_BUTTON_H_ */
