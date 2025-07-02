/*
 * Presenter.h
 *
 *  Created on: Jun 24, 2025
 *      Author: kccistc
 */

#ifndef AP_PRESENTER_H_
#define AP_PRESENTER_H_

#include "Model_Watch.h"
#include "FND.h"
#include "i2c.h"
#include "lcd.h"

void Presenter_Init();
void Presenter_OutData(watch_t watchData);
void Presenter_Excute();

#endif /* AP_PRESENTER_H_ */
