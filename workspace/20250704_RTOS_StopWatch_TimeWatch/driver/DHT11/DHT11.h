/*
 * dht.h
 *
 *  Created on: Jun 27, 2025
 *      Author: kccistc
 */

#ifndef DRIVER_DHT11_DHT_H_
#define DRIVER_DHT11_DHT_H_

#include "stm32f4xx_hal.h"
#include "gpio.h"
#include "tim.h"

typedef struct {
    GPIO_TypeDef *data_GPIOx;
    uint16_t data_pinNum;
} DHT11_TypeDef;

void     DHT11_Init(DHT11_TypeDef *dht, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
uint8_t  DHT11_Read(DHT11_TypeDef *dht, uint8_t *temp, uint8_t *humi);
void     delay_us_dht(uint16_t us);  // 타이머 기반 딜레이


#endif /* DRIVER_DHT11_DHT_H_ */
