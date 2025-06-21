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
		{GPIOA, 12},
		{GPIOC, 5},
		{GPIOC, 6},
		{GPIOC, 8}
};

FND_TypeDef fndPin[8] = {
		{GPIOA, 11}, // A
		{GPIOB, 12}, // B
		{GPIOB,  2}, // C
		{GPIOB,  1}, // D
		{GPIOB, 15}, // E
		{GPIOB, 14}, // F
		{GPIOB, 13}, // G
		{GPIOC,  4}  // dp
};

//typedef enum {CLOCK=0, STOPWATCH} mode_t;

static void FND_DispOff(int fndPos);
static void FND_DispOn(int fndPos);
static void FND_DispOffAll();
static void FND_DispDigit(uint16_t digit);

static uint16_t fndDispNum = 0; // fnd main data

void FND_Init()
{
	for (int i=0; i<4; i++) {
		GPIO_Init(fndDigitCom[i].GPIOx, fndDigitCom[i].pinNum, OUTPUT);
	}

	for (int i=0; i<8; i++) {
		GPIO_Init(fndPin[i].GPIOx, fndPin[i].pinNum, OUTPUT);
	}
}

// write fndDispNum
void FND_WriteData(uint16_t data)
{
	fndDispNum = data;
}

// read fndDispNum
uint16_t FND_ReadData()
{
	return fndDispNum;
}

void FND_SetDot(dot_t dot)
{
	if (dot == dot_on) {
		GPIO_WritePin(fndPin[7].GPIOx, fndPin[7].pinNum, PIN_RESET);
	} else {
		GPIO_WritePin(fndPin[7].GPIOx, fndPin[7].pinNum, PIN_SET);
	}
}

// display fndDispNum
void FND_DispData(dot_t dot[4])
{
	static int digitPos = 0;
	// 인터럽트가 발생하면 한 자리씩 출력한다.
	digitPos = (digitPos+1) % 4;
	switch(digitPos)
	{
	case DIGIT_1:
		FND_DispOffAll();
		FND_DispDigit(fndDispNum % 10);
		FND_SetDot(dot[DIGIT_1]);
		FND_DispOn(digitPos);
		return;
	case DIGIT_10:
		FND_DispOffAll();
		FND_DispDigit(fndDispNum /10 % 10);
		FND_SetDot(dot[DIGIT_10]);
		FND_DispOn(digitPos);
		return;
	case DIGIT_100:
		FND_DispOffAll();
		FND_DispDigit(fndDispNum /100 % 10);
		FND_SetDot(dot[DIGIT_100]);
		FND_DispOn(digitPos);
		return;
	case DIGIT_1000:
		FND_DispOffAll();
		FND_DispDigit(fndDispNum /1000 % 10);
		FND_SetDot(dot[DIGIT_1000]);
		FND_DispOn(digitPos);
		return;
	}
}

void FND_DispOff(int fndPos)
{
	// GPIO_Write(GPIOx, Pin, RESET);
	GPIO_WritePin(fndDigitCom[fndPos].GPIOx, fndDigitCom[fndPos].pinNum, PIN_RESET);
}

void FND_DispOffAll()
{
	// GPIO_Write(GPIOx, Pin, RESET);
	for (int i=0; i<4; i++) {
		GPIO_WritePin(fndDigitCom[i].GPIOx, fndDigitCom[i].pinNum, PIN_RESET);
	}
}

void FND_DispOn(int fndPos)
{
	// GPIO_Write(GPIOx, Pin, SET);
	GPIO_WritePin(fndDigitCom[fndPos].GPIOx, fndDigitCom[fndPos].pinNum, PIN_SET);
}

void FND_DispDigit(uint16_t digit)
{
	const uint8_t segFont[10] = {
		    0xC0,  // 0
		    0xF9,  // 1
		    0xA4,  // 2
		    0xB0,  // 3
		    0x99,  // 4
		    0x92,  // 5
		    0x82,  // 6
		    0xF8,  // 7
		    0x80,  // 8
		    0x90   // 9
	};

	for (int i=0; i<8; i++) {
		if (!(segFont[digit] & (1<<i))) {
			GPIO_WritePin(fndPin[i].GPIOx, fndPin[i].pinNum, PIN_RESET); // 0 -> on
		}
		else {
			GPIO_WritePin(fndPin[i].GPIOx, fndPin[i].pinNum, PIN_SET); // 1 -> off
		}
	}
}
