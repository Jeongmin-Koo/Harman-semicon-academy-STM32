/*
 * UltraSonic.h
 *
 *  Created on: Jun 26, 2025
 *      Author: kccistc
 */

#ifndef DRIVER_ULTRASONIC_ULTRASONIC_H_
#define DRIVER_ULTRASONIC_ULTRASONIC_H_

#include "stm32f4xx_hal.h"
#include "gpio.h"
#include "tim.h"

typedef struct {
	GPIO_TypeDef *Trig_GPIOx;
	uint16_t Trig_pinNum;

	GPIO_TypeDef *Echo_GPIOx;
	uint16_t Echo_pinNum;
} UltraSonic_TypeDef;

void delay_us(uint16_t us);
void UltraSonic_Init(UltraSonic_TypeDef *hultra, GPIO_TypeDef *Trig_GPIOx, uint16_t Trig_pinNum,  GPIO_TypeDef *Echo_GPIOx, uint16_t Echo_pinNum);
int UltraSonic_GetDistance (UltraSonic_TypeDef *hultra);
int Filter_Distance(int new_dist);

#endif /* DRIVER_ULTRASONIC_ULTRASONIC_H_ */
