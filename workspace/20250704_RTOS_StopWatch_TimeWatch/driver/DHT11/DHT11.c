/*
 * dht.c
 *
 *  Created on: Jun 27, 2025
 *      Author: kccistc
 */


#include "DHT11.h"

extern TIM_HandleTypeDef htim5;

static void Set_Pin_Output(DHT11_TypeDef *dht) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = dht->data_pinNum;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(dht->data_GPIOx, &GPIO_InitStruct);
}

static void Set_Pin_Input(DHT11_TypeDef *dht) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = dht->data_pinNum;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(dht->data_GPIOx, &GPIO_InitStruct);
}

void delay_us_dht(uint16_t us)
{
    __HAL_TIM_SET_COUNTER(&htim5, 0);
    HAL_TIM_Base_Start(&htim5);
    while (__HAL_TIM_GET_COUNTER(&htim5) < us);
    HAL_TIM_Base_Stop(&htim5);
}

void DHT11_Init(DHT11_TypeDef *dht, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin) {
    dht->data_GPIOx = GPIOx;
    dht->data_pinNum = GPIO_Pin;
}

uint8_t DHT11_Read(DHT11_TypeDef *dht, uint8_t *temp, uint8_t *humi) {
    uint8_t data[5] = {0};

    // Start signal
    Set_Pin_Output(dht);
    HAL_GPIO_WritePin(dht->data_GPIOx, dht->data_pinNum, GPIO_PIN_RESET);
    delay_us_dht(18000);
    HAL_GPIO_WritePin(dht->data_GPIOx, dht->data_pinNum, GPIO_PIN_SET);
    delay_us_dht(30);

    Set_Pin_Input(dht);

    // 응답 신호 대기
    uint32_t timeout = 0;
    while (HAL_GPIO_ReadPin(dht->data_GPIOx, dht->data_pinNum) == GPIO_PIN_SET)
        if (++timeout > 10000) return 1;

    while (HAL_GPIO_ReadPin(dht->data_GPIOx, dht->data_pinNum) == GPIO_PIN_RESET);
    while (HAL_GPIO_ReadPin(dht->data_GPIOx, dht->data_pinNum) == GPIO_PIN_SET);

    // 40bit 데이터 수신
    for (int i = 0; i < 40; i++) {
        while (HAL_GPIO_ReadPin(dht->data_GPIOx, dht->data_pinNum) == GPIO_PIN_RESET);
        delay_us_dht(40);

        if (HAL_GPIO_ReadPin(dht->data_GPIOx, dht->data_pinNum) == GPIO_PIN_SET)
            data[i/8] = (data[i/8] << 1) | 1;
        else
            data[i/8] = (data[i/8] << 1);

        while (HAL_GPIO_ReadPin(dht->data_GPIOx, dht->data_pinNum) == GPIO_PIN_SET);
    }

    // 체크섬 검증
    if (data[4] == (data[0] + data[1] + data[2] + data[3])) {
        *humi = data[0];
        *temp = data[2];
        return 0;
    }

    return 2;
}
