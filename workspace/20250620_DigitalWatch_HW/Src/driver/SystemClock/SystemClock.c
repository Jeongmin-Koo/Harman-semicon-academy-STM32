/*
 * SystemClock.c
 *
 *  Created on: Jun 19, 2025
 *      Author: kccistc
 */


#include "SystemClock.h"

void SystemClock_Init()
{
	RCC->AHB1ENR |= (1U << 0);  // RCC_AHB1ENR -> GPIOA on
	RCC->AHB1ENR |= (1U << 1);  // RCC_AHB1ENR -> GPIOB on
	RCC->AHB1ENR |= (1U << 2);  // RCC_AHB1ENR -> GPIOC on
	RCC->APB1ENR |= (1U << 0);  // TIM2 en
	RCC->APB1ENR |= (1U << 3);  // TIM5 en
}

void delay(int loop)
{
	for (int j=0; j<loop; j++) {
		for (volatile int i = 0; i < 1000; i++);
	}
}
