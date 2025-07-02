/*
 * Controller.h
 *
 *  Created on: Jun 24, 2025
 *      Author: kccistc
 */
#ifndef AP_CONTROLLER_H_
#define AP_CONTROLLER_H_

#include "timeWatch.h"
#include "stopWatch.h"

enum {NO_CONTROL, MODE, STOPWATCH_RUN_STOP, STOPWATCH_CLEAR};
enum {MODE_NO_ACT, MODE_ACT, STOPWATCH_NO_ACT, STOPWATCH_ACT};

typedef struct {
	int id;
	int data;
}inputData_TypeDef;

void Controller_Excute();
void Controller_SetInputData(inputData_TypeDef inputData);

#endif /* AP_CONTROLLER_H_ */
