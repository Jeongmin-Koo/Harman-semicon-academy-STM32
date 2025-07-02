/*
 * Listener.h
 *
 *  Created on: Jun 24, 2025
 *      Author: kccistc
 */
#ifndef AP_LISTENER_H_
#define AP_LISTENER_H_

#include "stm32f4xx_hal.h"
#include "Controller.h"
#include "Button.h"
#include "usart.h"
#include "queue.h"

void Listener_Init();
void Listener_Excute();
void Listener_UartCallBack();


#endif /* AP_LISTENER_H_ */
