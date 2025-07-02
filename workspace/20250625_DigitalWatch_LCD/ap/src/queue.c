/*
 * queue.c
 *
 *  Created on: Jun 25, 2025
 *      Author: kccistc
 */
#include "queue.h"

void Que_Init(Que_TypeDef *q)
{
	q->front = 0;
	q->rear = 0;
}

int isQueFull(Que_TypeDef *q)
{
	return q->front == (q->rear+1) % QUE_SIZE; // full 조건
}

int isQueEmpty(Que_TypeDef *q)
{
	return q->front == q->rear; // empty 조건
}

void enQue(Que_TypeDef *q, int data)
{
	if (isQueFull(q)) {
		return;
	}
	q->queData[q->rear] = data;
	q->rear = (q->rear+1) % QUE_SIZE;
}

int deQue(Que_TypeDef *q)
{
	if (isQueEmpty(q)) {
		return;
	}
	int data = q->queData[q->front];
	q->front = (q->front+1) % QUE_SIZE;

	return data;
}

// 맨 위 값 확인
int peekQue(Que_TypeDef *q)
{
	if (isQueEmpty(q)) {
		return;
	}
	else {
		return q->queData[q->front];
	}
}
