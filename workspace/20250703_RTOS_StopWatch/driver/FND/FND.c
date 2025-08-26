/*
 * FND.c
 *
 *  Created on: Jun 19, 2025
 *      Author: kccistc
 */

#include "FND.h"

typedef struct {
	GPIO_TypeDef *GPIOx;
	uint32_t pinNum;
}FND_TypeDef;

FND_TypeDef fndDigitCom[4] = {
		{GPIOA, GPIO_PIN_12},
		{GPIOC, GPIO_PIN_5},
		{GPIOC, GPIO_PIN_6},
		{GPIOC, GPIO_PIN_8}
};

FND_TypeDef fndPin[8] = {
		{GPIOA, GPIO_PIN_11}, // A
		{GPIOB, GPIO_PIN_12}, // B
		{GPIOB, GPIO_PIN_2}, // C
		{GPIOB, GPIO_PIN_1}, // D
		{GPIOB, GPIO_PIN_15}, // E
		{GPIOB, GPIO_PIN_14}, // F
		{GPIOB, GPIO_PIN_13}, // G
		{GPIOC, GPIO_PIN_4}  // dp
};

static void FND_DispOff(int fndPos);
static void FND_DispOn(int fndPos);
static void FND_DispOffAll();
static void FND_DispDigit(uint16_t digit);

static uint16_t fndDispNum = 0; // fnd main data
static uint8_t fndDispDp = 0; // fnd dp data, xxxx1111

void FND_WriteDp(uint8_t dpData, uint8_t dpState)
{
	if (dpState == FND_DP_ON)
		fndDispDp |= dpData;
	else
		fndDispDp &= ~dpData;
}

void FND_WriteData(uint16_t data)
{
	fndDispNum = data;
}

// read fndDispNum
uint16_t FND_ReadData()
{
	return fndDispNum;
}

// display fndDispNum
void FND_DispDataCallBack()
{
	static int digitPos = 0;
	// 인터럽트가 발생하면 한 자리씩 출력한다.
	digitPos = (digitPos+1) % 8;
	switch(digitPos)
	{
	case DIGIT_1:
		FND_DispOffAll();
		FND_DispDigit(fndDispNum % 10);
		FND_DispOn(digitPos);
		break;
	case DIGIT_10:
		FND_DispOffAll();
		FND_DispDigit(fndDispNum /10 % 10);
		FND_DispOn(digitPos);
		break;
	case DIGIT_100:
		FND_DispOffAll();
		FND_DispDigit(fndDispNum /100 % 10);
		FND_DispOn(digitPos);
		break;
	case DIGIT_1000:
		FND_DispOffAll();
		FND_DispDigit(fndDispNum /1000 % 10);
		FND_DispOn(digitPos);
		break;
	case DIGIT_DP_1:
		FND_DispOffAll();
		if (fndDispDp & (1<<0)) {
			FND_DispDigit(10); // DP ON
		} else {
			FND_DispDigit(11); // ALL OFF
		}
		FND_DispOn(digitPos%4);
		break;
	case DIGIT_DP_10:
		FND_DispOffAll();
		if (fndDispDp & (1<<1)) {
			FND_DispDigit(10); // DP ON
		} else {
			FND_DispDigit(11); // ALL OFF
		}
		FND_DispOn(digitPos%4);
		break;
	case DIGIT_DP_100:
		FND_DispOffAll();
		if (fndDispDp & (1<<2)) {
			FND_DispDigit(10); // DP ON
		} else {
			FND_DispDigit(11); // ALL OFF
		}
		FND_DispOn(digitPos%4);
		break;
	case DIGIT_DP_1000:
		FND_DispOffAll();
		if (fndDispDp & (1<<3)) {
			FND_DispDigit(10); // DP ON
		} else {
			FND_DispDigit(11); // ALL OFF
		}
		FND_DispOn(digitPos%4);
		break;
	}
}

void FND_DispOff(int fndPos)
{
	// GPIO_Write(GPIOx, Pin, RESET);
	HAL_GPIO_WritePin(fndDigitCom[fndPos].GPIOx, fndDigitCom[fndPos].pinNum, RESET);
}

void FND_DispOffAll()
{
	// GPIO_Write(GPIOx, Pin, RESET);
	for (int i=0; i<4; i++) {
		HAL_GPIO_WritePin(fndDigitCom[i].GPIOx, fndDigitCom[i].pinNum, RESET);
	}
}

void FND_DispOn(int fndPos)
{
	// GPIO_Write(GPIOx, Pin, SET);
	HAL_GPIO_WritePin(fndDigitCom[fndPos].GPIOx, fndDigitCom[fndPos].pinNum, SET);
}


void FND_DispDigit(uint16_t digit)
{
	const uint8_t segFont[12] = {
		    0xC0,  // 0
		    0xF9,  // 1
		    0xA4,  // 2
		    0xB0,  // 3
		    0x99,  // 4
		    0x92,  // 5
		    0x82,  // 6
		    0xF8,  // 7
		    0x80,  // 8
		    0x90,  // 9
			0x7F,  // dot
			0xFF   // all off
	};

	for (int i=0; i<8; i++) {
		if (!(segFont[digit] & (1<<i))) {
			HAL_GPIO_WritePin(fndPin[i].GPIOx, fndPin[i].pinNum, RESET); // 0 -> on
		}
		else {
			HAL_GPIO_WritePin(fndPin[i].GPIOx, fndPin[i].pinNum, SET); // 1 -> off
		}
	}
}
