#include "dht.h"

static void go_to_output(DHT *sensor)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

  HAL_GPIO_WritePin(sensor->port, sensor->pin, GPIO_PIN_SET);

  GPIO_InitStruct.Pin = sensor->pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;

  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(sensor->port, &GPIO_InitStruct);
}

static void go_to_input(DHT *sensor)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  GPIO_InitStruct.Pin = sensor->pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(sensor->port, &GPIO_InitStruct);
}

DHT_DATA get_dht_data(DHT *sensor) {
	DHT_DATA data = {-128.0f, -128.0f};

	uint16_t pollingInterval = DHT_POLLING_INTERVAL;

	// get last data if time interval less than polling interval
	if ((HAL_GetTick() - sensor->last_polling_time < pollingInterval) && sensor->last_polling_time != 0) {
		data.hum = sensor->last_hum;
		data.temp = sensor->last_temp;

		return data;
	}

	sensor->last_polling_time = HAL_GetTick() + 1;

	// set exit to out
	go_to_output(sensor);
	HAL_GPIO_WritePin(sensor->port, sensor->pin, GPIO_PIN_RESET);
	HAL_Delay(18);

	// set exit to in
	HAL_GPIO_WritePin(sensor->port, sensor->pin, GPIO_PIN_SET);
	go_to_input(sensor);

	__disable_irq();

	uint16_t timeout = 0;
	// low level
	while (HAL_GPIO_ReadPin(sensor->port, sensor->pin) == GPIO_PIN_SET) {
		timeout++;
	
		// if no DHT response
		if (timeout > DHT_TIMEOUT) {
			__enable_irq();

			sensor->last_hum = -128.0f;
			sensor->last_temp = -128.0f;

			return data;
		}
	}

	timeout = 0;
	// high level
	while (HAL_GPIO_ReadPin(sensor->port, sensor->pin) != GPIO_PIN_SET) {
		timeout++;

		// if no DHT response
		if (timeout > DHT_TIMEOUT) {
			__enable_irq();

			sensor->last_hum = -128.0f;
			sensor->last_temp = -128.0f;

			return data;
		}
	}

	timeout = 0;
	// low level
	while (HAL_GPIO_ReadPin(sensor->port, sensor->pin) == GPIO_PIN_SET) {
		timeout++;

		// if no DHT response
		if (timeout > DHT_TIMEOUT) {
			__enable_irq();

			return data;
		}
	}

	// get DHT data response
	uint8_t raw_data[5] = {0, 0, 0, 0, 0};
	for (uint8_t a = 0; a < 5; a++) {
		for (uint8_t b = 7; b != 255; b--) {
			uint16_t hT = 0, lT = 0;

			while ((HAL_GPIO_ReadPin(sensor->port, sensor->pin) != GPIO_PIN_SET) && lT != 65535) lT++;

			timeout = 0;

			while ((HAL_GPIO_ReadPin(sensor->port, sensor->pin) == GPIO_PIN_SET) && hT != 65535) hT++;

			if (hT > lT) raw_data[a] |= (1 << b);
		}
	}

	__enable_irq();

	// check data
	if((uint8_t) (raw_data[0] + raw_data[1] + raw_data[2] + raw_data[3]) == raw_data[4]) {
		data.hum = (float) raw_data[0];
		data.temp = (float) raw_data[2];
	}

	sensor->last_hum = data.hum;
	sensor->last_temp = data.temp;

	return data;	
}
