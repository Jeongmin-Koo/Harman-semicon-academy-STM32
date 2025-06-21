/*
 * FND.h
 *
 *  Created on: Jun 19, 2025
 *      Author: kccistc
 */

#ifndef DRIVER_FND_FND_H_
#define DRIVER_FND_FND_H_

#include <stdint.h>
#include "stm32f4xx.h"
#include "GPIO.h"
#include "Systick.h"

typedef enum {dot_off =0, dot_on =1} dot_t;
enum {DIGIT_1=0, DIGIT_10, DIGIT_100, DIGIT_1000};

void FND_Init();
void FND_WriteData(uint16_t data);
uint16_t FND_ReadData();
void FND_DispData();
void FND_SetDot(dot_t dot);


#endif /* DRIVER_FND_FND_H_ */
