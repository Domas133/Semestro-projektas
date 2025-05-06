#ifndef INC_DHT11_H_
#define INC_DHT11_H_

#include "main.h"

typedef struct {
	uint8_t Temperature;
	uint8_t Humidity;
} DHT11_Data_t;

void DHT11_Init(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
uint8_t DHT11_Read(DHT11_Data_t *data, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

#endif /* INC_DHT11_H_ */
