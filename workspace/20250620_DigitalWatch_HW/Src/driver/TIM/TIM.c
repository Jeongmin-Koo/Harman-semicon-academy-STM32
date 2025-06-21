/*
 * TIM.c
 *
 *  Created on: Jun 20, 2025
 *      Author: kccistc
 */
#include "TIM.h"

void TIM_Init(TIM_TypeDef *TIMx, uint32_t psc, uint32_t arr)
{
	TIM_WritePSC(TIMx, psc);
	TIM_WriteARR(TIMx, arr);
	TIM_WriteCNT(TIMx, 0);
}

void TIM_CntStart(TIM_TypeDef *TIMx)
{
	TIMx->CR1 |= 1<<0;
}

void TIM_CntStop(TIM_TypeDef *TIMx)
{
	TIMx->CR1 &= ~(1<<0);
}

// Interrupt ON
void TIM_UIEnable(TIM_TypeDef *TIMx)
{
	TIMx->DIER |= 1<<0;
}

// Interrupt OFF
void TIM_UIDisable(TIM_TypeDef *TIMx)
{
	TIMx->DIER &= ~(1<<0);
}

uint32_t TIM_ReadCNT(TIM_TypeDef *TIMx)
{
	return TIMx->CNT;
}

uint32_t TIM_WriteCNT(TIM_TypeDef *TIMx, uint32_t cnt)
{
	TIMx->CNT = cnt;
}

uint32_t TIM_ReadPSC(TIM_TypeDef *TIMx)
{
	return TIMx->PSC;
}

uint32_t TIM_WritePSC(TIM_TypeDef *TIMx, uint32_t psc)
{
	TIMx->PSC = psc;
}

uint32_t TIM_ReadARR(TIM_TypeDef *TIMx)
{
	return TIMx->ARR;
}

uint32_t TIM_WriteARR(TIM_TypeDef *TIMx, uint32_t arr)
{
	TIMx->ARR = arr;
}

void TIM_ClearUIFlag(TIM_TypeDef *TIMx)
{
	TIMx->SR &= ~(1<<0);
}
