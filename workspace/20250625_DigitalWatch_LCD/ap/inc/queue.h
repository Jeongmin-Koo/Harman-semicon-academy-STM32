/*
 * queue.h
 *
 *  Created on: Jun 25, 2025
 *      Author: kccistc
 */

#ifndef AP_INC_QUEUE_H_
#define AP_INC_QUEUE_H_

#include "stm32f4xx_hal.h"
#define QUE_SIZE	4

typedef struct {
	int front;
	int rear;
	int queData[QUE_SIZE];
}Que_TypeDef;



void Que_Init(Que_TypeDef *q);
int isQueFull(Que_TypeDef *q);
int isQueEmpty(Que_TypeDef *q);
void enQue(Que_TypeDef *q, int data);
int deQue(Que_TypeDef *q);
int peekQue(Que_TypeDef *q);

#endif /* AP_INC_QUEUE_H_ */
