/*
 * ap_main.c
 *
 *  Created on: Jun 19, 2025
 *      Author: kccistc
 */


#include "ap_main.h"


Button_TypeDef hBtnLeft;
Button_TypeDef hBtnRight;
Button_TypeDef hBtnOnoff;

typedef enum {CLOCK=0, STOPWATCH}mode_t;
typedef enum {STOP=0, RUN, CLEAR}stopWatch_state_t;

dot_t dot[4] = {dot_off, dot_off, dot_off, dot_off};

void TIM2_IRQHandler(void)
{
	incTick(); // 1ms tick
	FND_DispData(dot);
	TIM_ClearUIFlag(TIM2);
}

int ap_main()
{
	uint16_t counter = 0;
	uint16_t time = 1200;
	mode_t mode = CLOCK;
	stopWatch_state_t state = STOP;

	uint32_t prevCounterTime = 0;

	while (1)
	{
		uint32_t tick = getTick();

		if (getTick() - prevCounterTime >= 1000) {
			prevCounterTime = getTick();
			time++;
		}

		switch (mode)
		{
		case CLOCK :
			dot[DIGIT_1000] = dot_off;
			dot[DIGIT_100] = ((tick/500)%2)? dot_on:dot_off;
			dot[DIGIT_10] = dot_off;
			dot[DIGIT_1] = dot_off;

			FND_WriteData(time);

			if (Button_GetState(&hBtnRight) == ACT_RELEASED) {
				mode = STOPWATCH;
			}

			break;
		case STOPWATCH :
			// 0.1초 주기
			if (Button_GetState(&hBtnRight) == ACT_RELEASED) {
				mode = CLOCK;
				state = STOP;
			}

			switch (state)
			{
			case STOP:
				dot[DIGIT_1000] = dot_off;
				dot[DIGIT_100] = dot_off;
				dot[DIGIT_10] = dot_off;
				dot[DIGIT_1] = dot_off;

				FND_WriteData(counter);
				if (Button_GetState(&hBtnLeft) == ACT_RELEASED) {
					state = RUN;
				} else if (Button_GetState(&hBtnOnoff) == ACT_RELEASED){
					state = CLEAR;
				}
				break;
			case RUN:
				dot[DIGIT_1000] = ((tick/500)%2)? dot_on:dot_off;
				dot[DIGIT_100] = dot_off;
				dot[DIGIT_10] = ((tick/50)%2)? dot_on:dot_off;
				dot[DIGIT_1] = dot_off;

				// 0.1s
				if (getTick() - prevCounterTime >= 100) {
					prevCounterTime = getTick();
					FND_WriteData(counter++);
				}
				if (Button_GetState(&hBtnLeft) == ACT_RELEASED) {
					state = STOP;
				}
				break;
			case CLEAR:
				dot[DIGIT_1000] = dot_off;
				dot[DIGIT_100] = dot_off;
				dot[DIGIT_10] = dot_off;
				dot[DIGIT_1] = dot_off;

				counter = 0;
				FND_WriteData(counter);
				if (Button_GetState(&hBtnOnoff) == ACT_RELEASED) {
					state = STOP;
				}
				break;
			}

			break;
		}
	}
	return 0;
}

void ap_init()
{
	SystemClock_Init();

	LedBar_Init();

	Button_Init(&hBtnLeft, GPIOB, 5);
	Button_Init(&hBtnRight, GPIOB, 3);
	Button_Init(&hBtnOnoff, GPIOA, 10);

	FND_Init();

	TIM_Init(TIM2, 16-1, 1000-1); // 1ms
	TIM_CntStart(TIM2);
	TIM_UIEnable(TIM2);
	NVIC_EnableIRQ(TIM2_IRQn); // core_cm4.h에 정의됨.
}
