/*
 * TIM.h
 *
 *  Created on: Jun 20, 2025
 *      Author: kccistc
 */

#ifndef DRIVER_TIM_TIM_H_
#define DRIVER_TIM_TIM_H_

#include <stdint.h>
#include "stm32f4xx.h"

void TIM_Init(TIM_TypeDef *TIMx, uint32_t psc, uint32_t arr);

void TIM_ClearUIFlag(TIM_TypeDef *TIMx);

void TIM_CntStart(TIM_TypeDef *TIMx);
void TIM_CntStop(TIM_TypeDef *TIMx);

void TIM_UIEnable(TIM_TypeDef *TIMx);
void TIM_UIDisable(TIM_TypeDef *TIMx);

uint32_t TIM_ReadCNT(TIM_TypeDef *TIMx);
uint32_t TIM_ReadPSC(TIM_TypeDef *TIMx);
uint32_t TIM_ReadARR(TIM_TypeDef *TIMx);

uint32_t TIM_WriteCNT(TIM_TypeDef *TIMx, uint32_t cnt);
uint32_t TIM_WritePSC(TIM_TypeDef *TIMx, uint32_t psc);
uint32_t TIM_WriteARR(TIM_TypeDef *TIMx, uint32_t arr);

#endif /* DRIVER_TIM_TIM_H_ */
