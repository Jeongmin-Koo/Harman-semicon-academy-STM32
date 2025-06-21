/*
 * SysTick.h
 *
 *  Created on: Jun 20, 2025
 *      Author: kccistc
 */

#ifndef DRIVER_SYSTICK_SYSTICK_H_
#define DRIVER_SYSTICK_SYSTICK_H_

#include <stdint.h>
#include "stm32f4xx.h"
#include "TIM.h"

uint32_t getTick();
void incTick();

#endif /* DRIVER_SYSTICK_SYSTICK_H_ */
