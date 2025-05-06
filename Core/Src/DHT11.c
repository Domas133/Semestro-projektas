#include "dht11.h"

extern TIM_HandleTypeDef htim6; // Timer6 delay_us

void delay_us(uint16_t us) {
	__HAL_TIM_SET_COUNTER(&htim6, 0);
	while (__HAL_TIM_GET_COUNTER(&htim6) < us);
}

void DHT11_Init(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin) {
	HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_SET);
}

uint8_t DHT11_Read(DHT11_Data_t *data, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin) {
	uint8_t bits[5] = {0};
	uint8_t temp_h, temp_l, hum_h, hum_l, check_sum;

	GPIO_InitTypeDef GPIO_InitStruct = {0};

	// Start signal
	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);

	HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_RESET);
	HAL_Delay(18);
	HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_SET);
	delay_us(20);

	// Input mode
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);

	delay_us(40);
	if(HAL_GPIO_ReadPin(GPIOx, GPIO_Pin)) return 1;
	delay_us(80);
	if(!HAL_GPIO_ReadPin(GPIOx, GPIO_Pin)) return 1;
	delay_us(80);

	for(int j=0;j<5;j++) {
		for(int i=0;i<8;i++) {
			while(!HAL_GPIO_ReadPin(GPIOx, GPIO_Pin));
			delay_us(40);
			if(HAL_GPIO_ReadPin(GPIOx, GPIO_Pin))
				bits[j] |= (1 << (7-i));
			while(HAL_GPIO_ReadPin(GPIOx, GPIO_Pin));
		}
	}

	hum_h = bits[0];
	hum_l = bits[1];
	temp_h = bits[2];
	temp_l = bits[3];
	check_sum = bits[4];

	if (check_sum != (hum_h + hum_l + temp_h + temp_l)) return 2;

	data->Humidity = hum_h;
	data->Temperature = temp_h;

	return 0;
}
